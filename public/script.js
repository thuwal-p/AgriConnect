const modal = document.querySelector('#accountModal');
const title = document.querySelector('#modalTitle');
const form = document.querySelector('#accountForm');
let selectedRole = '';
let selectedAction = '';
const API = '/api';

const CITIES = ["Agra", "Ahmedabad", "Ajmer", "Aligarh", "Almora", "Ambala", "Amritsar", "Aurangabad", "Bareilly", "Bengaluru", "Bhopal", "Bhubaneswar", "Bikaner", "Chandigarh", "Chennai", "Coimbatore", "Dehradun", "Delhi", "Faridabad", "Ghaziabad", "Gorakhpur", "Gurugram", "Guwahati", "Gwalior", "Haldwani", "Haridwar", "Hisar", "Hyderabad", "Indore", "Jabalpur", "Jaipur", "Jalandhar", "Jammu", "Jodhpur", "Kanpur", "Karnal", "Kashipur", "Kolkata", "Kota", "Kotdwar", "Lucknow", "Ludhiana", "Mathura", "Meerut", "Moradabad", "Mumbai", "Mussoorie", "Nagpur", "Nainital", "Nashik", "Noida", "Panipat", "Patiala", "Patna", "Pauri", "Pithoragarh", "Prayagraj", "Pune", "Raipur", "Rajkot", "Ranchi", "Rishikesh", "Rohtak", "Roorkee", "Rudrapur", "Saharanpur", "Shimla", "Solan", "Srinagar", "Srinagar Garhwal", "Surat", "Udaipur", "Ujjain", "Vadodara", "Varanasi"];
function field(label, id, type='text', placeholder='') {
  return `<label for="${id}">${label}</label><input id="${id}" name="${id}" type="${type}" required placeholder="${placeholder}">`;
}
function citySelect(){return '<label for="location">Nearest major city</label><select id="location" name="location" required><option value="">Select your nearest city</option>'+CITIES.map(c=>`<option>${c}</option>`).join('')+'</select>'+field('Village / town (optional)','village','text','Your village or town name');}
document.querySelectorAll('[data-role][data-action]').forEach(button => button.addEventListener('click', () => {
  selectedRole = button.dataset.role.toLowerCase(); selectedAction = button.dataset.action;
  title.textContent = `${button.dataset.role} ${selectedAction}`;
  if (selectedAction === 'Login') {
    form.innerHTML = field('Email / Username','id','text','Enter your registered email or username') + field('Password','password','password','Enter your password') + '<button class="button" type="submit">Login</button>';
  } else if (selectedRole === 'farmer') {
    form.innerHTML = field('Full name','name','text','Enter your full name') + field('Email address (used as Farmer ID)','id','email','Enter your email') + field('Phone number','phone','tel','Enter your phone number') + citySelect() + field('Create password','password','password','Create a password') + '<button class="button" type="submit">Create farmer account</button>';
  } else {
    form.innerHTML = field('Mandi name','name','text','Enter mandi name') + field('Contact person','contactName','text','Contact person name') + field('Email address (used as Mandi ID)','id','email','Enter email') + field('Phone number','phone','tel','Enter phone number') + citySelect() + field('Create password','password','password','Create a password') + field('Total capacity (quintals)','capacity','number','e.g. 500') + field('Crop name','crop','text','e.g. wheat') + field('Buying price per quintal (₹)','price','number','e.g. 2500') + '<button class="button" type="submit">Register mandi</button>';
  }
  modal.hidden = false; form.querySelector('input').focus();
}));
function closeModal(){ modal.hidden=true; form.reset(); }
document.querySelector('#closeModal').addEventListener('click', closeModal);
modal.addEventListener('click', e => { if(e.target===modal) closeModal(); });
document.addEventListener('keydown', e => { if(e.key==='Escape'&&!modal.hidden) closeModal(); });
form.addEventListener('submit', async e => {
  e.preventDefault(); const data = Object.fromEntries(new FormData(form).entries());
  const button=form.querySelector('[type="submit"]'); button.disabled=true;
  try {
    let response, result;
    if(selectedAction==='Login') {
      response=await fetch(`${API}/auth/login`,{method:'POST',headers:{'Content-Type':'application/json'},body:JSON.stringify({role:selectedRole,id:data.id,password:data.password})});
      result=await response.json();
    } else if(selectedRole==='farmer') {
      response=await fetch(`${API}/farmers/register`,{method:'POST',headers:{'Content-Type':'application/json'},body:JSON.stringify({id:data.id,password:data.password,name:data.name,location:data.location,village:data.village||'',phone:data.phone})});
      result=await response.json();
    } else {
      response=await fetch(`${API}/mandis/register`,{method:'POST',headers:{'Content-Type':'application/json'},body:JSON.stringify({id:data.id,password:data.password,name:data.name,contactPerson:data.contactName,phone:data.phone,location:data.location,village:data.village||'',capacity:Number(data.capacity),crops:[{crop:data.crop,price:Number(data.price)}]})});
      result=await response.json();
    }
    if(!response.ok||!result.success) throw new Error(result.message||'Request failed');
    sessionStorage.setItem('agriRole',selectedRole); sessionStorage.setItem('agriId',data.id.trim().toLowerCase());
    window.location.href=selectedRole==='farmer'?'farmer-dashboard.html':'mandi-dashboard.html';
  } catch(err) { alert(err.message || 'Could not connect to AgriConnect server.'); }
  finally { button.disabled=false; }
});
