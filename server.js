const express = require('express');
const { execFile } = require('child_process');
const path = require('path');

const lid = s => String(s == null ? '' : s).trim().toLowerCase(); // IDs are case-insensitive; passwords are not
const app = express();
const PORT = process.env.PORT || 3000;
const fs = require('fs');
const dataDir = path.join(__dirname, 'data');
const villageFile = path.join(dataDir, 'village_details.txt');
function saveVillage(id, village) {
  const v = String(village || '').trim().replace(/\s+/g, '_');
  if (v) fs.appendFileSync(villageFile, `${id} ${v}\n`);
}
function getVillage(id) {
  try {
    const line = fs.readFileSync(villageFile, 'utf8').split(/\r?\n/).reverse().find(l => l.split(' ')[0] === id);
    return line ? line.split(' ')[1].replace(/_/g, ' ') : '';
  } catch { return ''; }
}
const cppProgram = path.join(__dirname, 'build', process.platform === 'win32' ? 'AgriConnectAPI.exe' : 'AgriConnectAPI');
app.use(express.json());
// Never serve the .txt data files (they contain plain-text passwords) or source files.
app.use((req, res, next) => {
  if (/\.(txt|cpp|h|json)$/i.test(req.path) || /^\/(src|include|node_modules)\//i.test(req.path)) return res.status(404).end();
  next();
});
app.use(express.static(path.join(__dirname, 'public')));

function runCpp(args, res, after) {
  // These file formats are whitespace-delimited; reject values that would corrupt a record.
  if (args.some(value => String(value).includes('\n') || String(value).includes('\r'))) {
    return res.status(400).json({ success: false, message: 'Invalid input' });
  }
  execFile(cppProgram, args.map(String), { cwd: dataDir, windowsHide: true, maxBuffer: 1024 * 1024 }, (error, stdout, stderr) => {
    // A missing/unbuilt executable produces no stdout. Report the real startup
    // issue instead of masking it as a JSON parsing failure.
    if (error && (error.code === 'ENOENT' || !stdout.trim())) {
      console.error('Could not run C++ API:', error.message, stderr || '');
      return res.status(500).json({
        success: false,
        message: 'C++ API executable is missing or could not start. Stop the server and run: npm start'
      });
    }
    let data;
    try { data = JSON.parse(stdout.trim()); }
    catch {
      console.error('C++ output was not valid JSON:', stdout, stderr);
      return res.status(500).json({ success: false, message: 'C++ API returned malformed output. Check the Terminal for details.' });
    }
    if (error && data.success !== false) console.error(stderr || error.message);
    if (after) after(data);
    res.status(error && data.success !== false ? 500 : 200).json(data);
  });
}

app.get('/api/health', (req, res) => res.json({ success: true, message: 'AgriConnect server is running!' }));
app.post('/api/farmers/register', (req, res) => {
  const { id, password, name, location, phone } = req.body || {};
  if (/\s/.test(String(id || '')) || /\s/.test(String(password || ''))) return res.status(400).json({ success: false, message: 'ID and password cannot contain spaces' });
  if (![id, password, name, location, phone].every(v => typeof v === 'string' && v.trim())) return res.status(400).json({ success: false, message: 'ID, password, name and location are required' });
  runCpp(['registerFarmer', lid(id), password, name.trim().replace(/\s+/g, '_'), location.trim().replace(/\s+/g, '_'), phone.trim()], res, d => { if (d.success) saveVillage(lid(id), req.body.village); });
});
app.post('/api/mandis/register', (req, res) => {
  const { id, password, name, contactPerson, phone, location, capacity, crops } = req.body || {};
  if (/\s/.test(String(id || '')) || /\s/.test(String(password || ''))) return res.status(400).json({ success: false, message: 'ID and password cannot contain spaces' });
  if (![id, password, name, contactPerson, phone, location].every(v => typeof v === 'string' && v.trim()) || !Number.isFinite(Number(capacity)) || Number(capacity) <= 0 || !Array.isArray(crops) || !crops.length) return res.status(400).json({ success: false, message: 'Provide ID, password, mandi name, location, positive capacity and at least one crop-price pair' });
  const args = ['registerMandi', lid(id), password, name.trim().replace(/\s+/g, '_'), location.trim().replace(/\s+/g, '_'), Number(capacity), contactPerson.trim().replace(/\s+/g, '_'), phone.trim()];
  for (const item of crops) {
    if (!item.crop || !Number.isFinite(Number(item.price)) || Number(item.price) <= 0) return res.status(400).json({ success: false, message: 'Each crop needs a name and positive price' });
    args.push(String(item.crop).trim().replace(/\s+/g, '_'), Number(item.price));
  }
  runCpp(args, res, d => { if (d.success) saveVillage(lid(id), req.body.village); });
});
app.post('/api/auth/login', (req, res) => {
  const { role, id, password } = req.body || {};
  if (!['farmer', 'mandi'].includes(role) || !id || !password) return res.status(400).json({ success: false, message: 'Role, ID and password are required' });
  runCpp([role === 'farmer' ? 'loginFarmer' : 'loginMandi', lid(id), String(password)], res);
});
app.get('/api/farmers/:id', (req, res) => runCpp(['getFarmerProfile', lid(req.params.id)], res, d => { if (d.farmer) d.farmer.village = getVillage(lid(req.params.id)); }));
app.get('/api/farmers/:id/crops', (req, res) => runCpp(['getFarmerCrops', lid(req.params.id)], res));
app.post('/api/farmers/:id/crops', (req, res) => {
  const { crop, quantity } = req.body || {};
  if (!crop || !Number.isInteger(Number(quantity)) || Number(quantity) <= 0) return res.status(400).json({ success: false, message: 'Crop and positive whole-number quantity are required' });
  runCpp(['addCrop', lid(req.params.id), String(crop).trim().replace(/\s+/g, '_'), Number(quantity)], res);
});
app.put('/api/farmers/:id/crops/:crop', (req, res) => {
  const { quantity } = req.body || {};
  if (!Number.isInteger(Number(quantity)) || Number(quantity) <= 0) return res.status(400).json({ success: false, message: 'Positive whole-number quantity required' });
  runCpp(['updateCrop', lid(req.params.id), req.params.crop, Number(quantity)], res);
});
app.delete('/api/farmers/:id/crops/:crop', (req, res) => runCpp(['removeCrop', lid(req.params.id), req.params.crop], res));
app.get('/api/mandis', (req, res) => runCpp(['getAllMandis'], res));
app.get('/api/mandis/:id', (req, res) => runCpp(['getMandiProfile', lid(req.params.id)], res, d => { if (d.mandi) d.mandi.village = getVillage(lid(req.params.id)); }));
app.post('/api/mandis/:id/crops', (req, res) => {
  const { crop, price } = req.body || {};
  if (typeof crop !== 'string' || !crop.trim() || !Number.isFinite(Number(price)) || Number(price) <= 0) {
    return res.status(400).json({ success: false, message: 'Crop name and positive price are required' });
  }
  runCpp(['addMandiCrop', lid(req.params.id), crop.trim().replace(/\s+/g, '_'), Number(price)], res);
});
app.patch('/api/mandis/:id/crops/:crop/price', (req, res) => {
  const { price } = req.body || {};
  if (!Number.isFinite(Number(price)) || Number(price) <= 0) {
    return res.status(400).json({ success: false, message: 'Positive price is required' });
  }
  runCpp(['updateMandiCropPrice', lid(req.params.id), req.params.crop, Number(price)], res);
});
app.patch('/api/mandis/:id/capacity', (req, res) => {
  const { totalCapacity, occupiedCapacity } = req.body || {};
  if (!Number.isInteger(Number(totalCapacity)) || Number(totalCapacity) <= 0 ||
      !Number.isInteger(Number(occupiedCapacity)) || Number(occupiedCapacity) < 0 ||
      Number(occupiedCapacity) > Number(totalCapacity)) {
    return res.status(400).json({ success: false, message: 'Valid total and occupied capacity are required' });
  }
  runCpp(['updateMandiCapacity', lid(req.params.id), Number(totalCapacity), Number(occupiedCapacity)], res);
});
app.get('/api/farmers/:id/recommendations/:crop', (req, res) => runCpp(['recommendMandis', lid(req.params.id), req.params.crop], res));

app.listen(PORT, () => console.log(`Server running at http://localhost:${PORT}`));

// Instant order placement and persistent order history (orders.txt).
app.post('/api/orders', (req, res) => {
  const { farmerId, mandiId, crop, quantity } = req.body || {};
  if (![farmerId, mandiId, crop].every(v => typeof v === 'string' && v.trim()) ||
      !Number.isInteger(Number(quantity)) || Number(quantity) <= 0) {
    return res.status(400).json({ success: false, message: 'Farmer, mandi, crop and positive whole-number quantity are required' });
  }
  runCpp(['placeOrder', lid(farmerId), lid(mandiId), crop.trim().replace(/\s+/g, '_'), Number(quantity)], res);
});
app.get('/api/orders/farmer/:id', (req, res) => runCpp(['getOrders', 'farmer', lid(req.params.id)], res));
app.get('/api/orders/mandi/:id', (req, res) => runCpp(['getOrders', 'mandi', lid(req.params.id)], res));
