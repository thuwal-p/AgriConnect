
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <queue>
#include <map>
#include <limits>
#include <cmath>
#include <iomanip>

#include "include/cropinfo.h"
#include "include/farmer.h"
#include "include/mandi.h"
#include "include/user.h"
#include "include/recommendation.h"

using namespace std;

// Helper function to escape special characters in JSON strings
string escapeJson(string value)
{
    string result = "";

    for (int i = 0; i < value.length(); i++)
    {
        if (value[i] == '"' || value[i] == '\\')
            result += '\\';

        result += value[i];
    }

    return result;
}

// Lower-case + underscores->spaces + trim. Used for crop and city matching.
string normalizeText(string value)
{
    transform(value.begin(), value.end(), value.begin(), [](unsigned char c){ return (char)tolower(c); });
    replace(value.begin(), value.end(), '_', ' ');
    size_t a = value.find_first_not_of(" \t\r\n");
    if (a == string::npos) return "";
    size_t b = value.find_last_not_of(" \t\r\n");
    return value.substr(a, b - a + 1);
}
bool sameName(const string& a, const string& b) { return normalizeText(a) == normalizeText(b); }

struct GeoPoint { double lat, lon; };
// Approximate coordinates, used only when a city is not in the road graph.
const map<string, GeoPoint>& cityCoordinates()
{
    static const map<string, GeoPoint> m = {
        {"delhi",{28.6139,77.2090}},{"new delhi",{28.6139,77.2090}},{"noida",{28.5355,77.3910}},{"gurgaon",{28.4595,77.0266}},{"gurugram",{28.4595,77.0266}},
        {"ghaziabad",{28.6692,77.4538}},{"faridabad",{28.4089,77.3178}},{"meerut",{28.9845,77.7064}},{"agra",{27.1767,78.0081}},{"mathura",{27.4924,77.6737}},
        {"aligarh",{27.8974,78.0880}},{"lucknow",{26.8467,80.9462}},{"kanpur",{26.4499,80.3319}},{"varanasi",{25.3176,82.9739}},{"prayagraj",{25.4358,81.8463}},
        {"allahabad",{25.4358,81.8463}},{"bareilly",{28.3670,79.4304}},{"moradabad",{28.8386,78.7733}},{"saharanpur",{29.9680,77.5510}},{"gorakhpur",{26.7606,83.3732}},
        {"dehradun",{30.3165,78.0322}},{"haridwar",{29.9457,78.1642}},{"rishikesh",{30.0869,78.2676}},{"roorkee",{29.8543,77.8880}},{"haldwani",{29.2183,79.5130}},
        {"hld",{29.2183,79.5130}},{"nainital",{29.3919,79.4542}},{"rudrapur",{28.9845,79.4000}},{"kashipur",{29.2104,78.9619}},{"almora",{29.5971,79.6591}},
        {"mussoorie",{30.4598,78.0664}},{"pauri",{30.1529,78.7800}},{"srinagar garhwal",{30.2200,78.7800}},{"pithoragarh",{29.5829,80.2182}},{"kotdwar",{29.7460,78.5230}},
        {"jaipur",{26.9124,75.7873}},{"jodhpur",{26.2389,73.0243}},{"udaipur",{24.5854,73.7125}},{"kota",{25.2138,75.8648}},{"ajmer",{26.4499,74.6399}},{"bikaner",{28.0229,73.3119}},
        {"chandigarh",{30.7333,76.7794}},{"ludhiana",{30.9010,75.8573}},{"amritsar",{31.6340,74.8723}},{"jalandhar",{31.3260,75.5762}},{"patiala",{30.3398,76.3869}},
        {"ambala",{30.3782,76.7767}},{"karnal",{29.6857,76.9905}},{"panipat",{29.3909,76.9635}},{"rohtak",{28.8955,76.6066}},{"hisar",{29.1492,75.7217}},
        {"bhopal",{23.2599,77.4126}},{"indore",{22.7196,75.8577}},{"gwalior",{26.2183,78.1828}},{"jabalpur",{23.1815,79.9864}},{"ujjain",{23.1765,75.7885}},
        {"ahmedabad",{23.0225,72.5714}},{"surat",{21.1702,72.8311}},{"vadodara",{22.3072,73.1812}},{"rajkot",{22.3039,70.8022}},
        {"mumbai",{19.0760,72.8777}},{"pune",{18.5204,73.8567}},{"nagpur",{21.1458,79.0882}},{"nashik",{19.9975,73.7898}},{"aurangabad",{19.8762,75.3433}},
        {"hyderabad",{17.3850,78.4867}},{"bengaluru",{12.9716,77.5946}},{"bangalore",{12.9716,77.5946}},{"chennai",{13.0827,80.2707}},{"coimbatore",{11.0168,76.9558}},
        {"kolkata",{22.5726,88.3639}},{"patna",{25.5941,85.1376}},{"ranchi",{23.3441,85.3096}},{"bhubaneswar",{20.2961,85.8245}},{"raipur",{21.2514,81.6296}},
        {"guwahati",{26.1445,91.7362}},{"shimla",{31.1048,77.1734}},{"solan",{30.9045,77.0967}},{"jammu",{32.7266,74.8570}},{"srinagar",{34.0837,74.7973}}
    };
    return m;
}
double haversineKm(GeoPoint a, GeoPoint b)
{
    const double R = 6371.0, rad = 3.14159265358979 / 180.0;
    double dLat = (b.lat - a.lat) * rad, dLon = (b.lon - a.lon) * rad;
    double h = sin(dLat/2)*sin(dLat/2) + cos(a.lat*rad)*cos(b.lat*rad)*sin(dLon/2)*sin(dLon/2);
    return 2 * R * asin(sqrt(h));
}

string readContactField(const string& id, int field)
{
    ifstream in("contact_details.txt"); string savedId, person, phone;
    while(in >> savedId >> person >> phone) if(savedId==id) return field==0?person:phone;
    return "";
}
void saveContact(const string& id, const string& person, const string& phone)
{
    vector<string> rows; ifstream in("contact_details.txt"); string a,b,c;
    while(in>>a>>b>>c) if(a!=id) rows.push_back(a+" "+b+" "+c);
    in.close();
    rows.push_back(id+" "+(person.empty()?"-":person)+" "+(phone.empty()?"-":phone));
    ofstream out("contact_details.txt"); for(const auto& row:rows) out<<row<<"\n";
}


int readCapacityValue(const string& id, int field, int fallback)
{
    ifstream in("capacity_details.txt"); string saved; int total, occupied;
    while(in>>saved>>total>>occupied) if(saved==id) return field==0?total:occupied;
    return fallback;
}
void saveCapacityData(const string& id, int total, int occupied)
{
    vector<string> rows; ifstream in("capacity_details.txt"); string saved; int t,o;
    while(in>>saved>>t>>o) if(saved!=id) rows.push_back(saved+" "+to_string(t)+" "+to_string(o));
    in.close(); rows.push_back(id+" "+to_string(total)+" "+to_string(occupied));
    ofstream out("capacity_details.txt"); for(const auto& row:rows) out<<row<<"\n";
}
// Update crop-price pairs in a mandi record without changing other records.
bool modifyMandiCropListing(const string& mandiId, const string& cropName, double price, bool addCrop)
{
    if (cropName.empty() || price <= 0) return false;

    vector<string> rows;
    ifstream input("mandi_details.txt");
    if (!input) return false;
    string line;
    bool foundMandi = false, changed = false;

    while (getline(input, line))
    {
        istringstream row(line);
        string id, name, location, cropData;
        int capacity;
        if (!(row >> id >> name >> location >> capacity))
        {
            rows.push_back(line);
            continue;
        }
        row >> cropData;
        if (id != mandiId)
        {
            rows.push_back(line);
            continue;
        }
        foundMandi = true;
        vector<pair<string, string>> listings;
        string item;
        stringstream crops(cropData);
        while (getline(crops, item, ','))
        {
            size_t colon = item.find(':');
            if (colon == string::npos) continue;
            listings.push_back({item.substr(0, colon), item.substr(colon + 1)});
        }

        bool cropExists = false;
        for (auto& listing : listings)
        {
            if (sameName(listing.first, cropName))
            {
                cropExists = true;
                if (!addCrop) { listing.second = to_string(price); changed = true; }
            }
        }
        if (addCrop && !cropExists)
        {
            listings.push_back({cropName, to_string(price)});
            changed = true;
        }
        if (addCrop && cropExists) return false; // Do not duplicate crop listings.
        if (!addCrop && !cropExists) return false; // Only update an existing crop.

        string rebuilt = id + " " + name + " " + location + " " + to_string(capacity) + " ";
        for (size_t i = 0; i < listings.size(); ++i)
        {
            if (i) rebuilt += ",";
            rebuilt += listings[i].first + ":" + listings[i].second;
        }
        rows.push_back(rebuilt);
    }
    input.close();
    if (!foundMandi || !changed) return false;

    ofstream output("mandi_details.txt");
    if (!output) return false;
    for (const auto& record : rows) output << record << "\n";
    return output.good();
}


int main(int argc, char* argv[])
{
    // Check whether minimum arguments were provided
    if (argc < 2)
    {
        cout << "{\"success\":false,"
             << "\"message\":\"Missing arguments\"}";
        return 1;
    }

    // Save original cout buffer
    streambuf* originalCout = cout.rdbuf();

    // Read operation
    string operation = argv[1];

    // OPERATION 1: Fetch farmer's crops
    if (operation == "getFarmerCrops")
    {
        if (argc < 3) { cout << "{\"success\":false,\"message\":\"Farmer ID required\"}"; return 1; }
        string farmerId = argv[2];

        CropInfo cropInfo;

        vector<CropInfo> crops = cropInfo.getMyCrops(farmerId);

        cout << "{\"success\":true,\"crops\":[";

        for (int i = 0; i < crops.size(); i++)
        {
            if (i > 0)
                cout << ",";

            cout << "{";
            cout << "\"name\":\""
                 << escapeJson(crops[i].getCropName()) << "\",";
            cout << "\"quantity\":" << crops[i].getQuantity();
            cout << "}";
        }

        cout << "]}";
    }

    // OPERATION 2: Fetch farmer's profile
    else if (operation == "getFarmerProfile")
    {
        string farmerId = argv[2];

        Farmer farmer;

        string name, location;

        bool found = farmer.getFarmerDetails(
            farmerId, name, location
        );

        if (found)
        {
            cout << "{\"success\":true,\"farmer\":{";

            cout << "\"id\":\"" << escapeJson(farmerId) << "\",";
            cout << "\"name\":\"" << escapeJson(name) << "\",";
            cout << "\"location\":\"" << escapeJson(location) << "\","
                 << "\"phone\":\"" << escapeJson(readContactField(farmerId,1)) << "\"";

            cout << "}}";
        }
        else
        {
            cout << "{\"success\":false,"
                 << "\"message\":\"Farmer not found\"}";
        }
    }

    // Register farmer credentials and profile together.
    else if (operation == "registerFarmer")
    {
        if (argc < 7) { cout << "{\"success\":false,\"message\":\"Missing farmer details\"}"; return 1; }
        string id = argv[2], password = argv[3], name = argv[4], location = argv[5], phone=argv[6];
        UserAuthentication auth; auth.loadFarmers();
        Farmer existing; string oldName, oldLocation;
        if (auth.farmerUsernameExists(id)) { cout << "{\"success\":false,\"message\":\"Farmer account already exists\"}"; return 1; }
        if (existing.getFarmerDetails(id, oldName, oldLocation)) { cout << "{\"success\":false,\"message\":\"Farmer profile already exists\"}"; return 1; }
        if (!auth.registerFarmer(id, password)) { cout << "{\"success\":false,\"message\":\"Could not save farmer credentials\"}"; return 1; }
        Farmer farmer(id, password, name, location);
        if (!farmer.addFarmer()) { cout << "{\"success\":false,\"message\":\"Credentials saved but profile creation failed\"}"; return 1; }
        saveContact(id,"-",phone);
        cout << "{\"success\":true,\"message\":\"Farmer registered successfully\"}";
    }
    else if (operation == "loginFarmer" || operation == "loginMandi")
    {
        if (argc < 4) { cout << "{\"success\":false,\"message\":\"Username and password required\"}"; return 1; }
        UserAuthentication auth;
        auth.loadFarmers(); auth.loadMandis();
        bool ok = operation == "loginFarmer" ? auth.farmerLogin(argv[2], argv[3]) : auth.mandiLogin(argv[2], argv[3]);
        if (ok) cout << "{\"success\":true,\"message\":\"Login successful\"}";
        else cout << "{\"success\":false,\"message\":\"Invalid username or password\"}";
    }
    else if (operation == "recommendMandis")
    {
        if (argc < 4) { cout << "{\"success\":false,\"message\":\"Farmer ID and crop name required\"}"; return 1; }
        string farmerId = argv[2], cropName = argv[3];
        CropInfo cropInfo; vector<CropInfo> crops = cropInfo.getMyCrops(farmerId);
        int quantity = 0;
        for (auto &c : crops) if (sameName(c.getCropName(), cropName)) quantity = c.getQuantity();
        if (quantity <= 0) { cout << "{\"success\":false,\"message\":\"Crop listing not found\"}"; return 1; }

        Farmer farmerProfile; string farmerName, farmerLocation;
        if (!farmerProfile.getFarmerDetails(farmerId, farmerName, farmerLocation)) {
            cout << "{\"success\":false,\"message\":\"Farmer profile not found\"}"; return 1;
        }

        const double transportRate = 18.0; // Initial assumed rate in Rs per road kilometre
        Mandi mandi; vector<Mandi> allMandis = mandi.getAllMandis();
        vector<ProfitRecommendation> recommendations = getProfitRecommendations(
            allMandis, farmerLocation, cropName, quantity, transportRate);

        cout << fixed << setprecision(2);
        cout << "{\"success\":true,\"crop\":\"" << escapeJson(cropName) << "\",\"quantity\":" << quantity
             << ",\"transportRatePerKm\":" << transportRate << ",\"recommendations\":[";
        for (size_t i = 0; i < recommendations.size(); ++i)
        {
            if (i) cout << ",";
            auto &r = recommendations[i];
            Mandi &m = r.mandi;
            cout << "{\"rank\":" << (i + 1) << ",\"id\":\"" << escapeJson(m.getUsername())
                 << "\",\"name\":\"" << escapeJson(m.getMandiName()) << "\",\"location\":\""
                 << escapeJson(m.getLocation()) << "\",\"capacity\":" << m.getCapacity()
                 << ",\"price\":" << r.price << ",\"distanceKm\":" << r.distanceKm
                 << ",\"transportCost\":" << r.transportCost << ",\"estimatedRevenue\":" << r.estimatedRevenue
                 << ",\"netProfit\":" << r.netProfit << ",\"distanceEstimated\":false}";
        }
        cout << "]}";
    }

    // OPERATION 4: Update farmer profile
    else if (operation == "updateFarmerProfile")
    {
        if (argc < 5)
        {
            cout << "{\"success\":false,"
                 << "\"message\":\"Missing farmer details\"}";
            return 1;
        }

        string farmerId = argv[2];
        string name = argv[3];
        string location = argv[4];

        Farmer farmer;

        bool updated = farmer.updateFarmer(
            farmerId, name, location
        );

        if (updated)
        {
            cout << "{\"success\":true,"
                 << "\"message\":\"Farmer profile updated successfully\"}";
        }
        else
        {
            cout << "{\"success\":false,"
                 << "\"message\":\"Could not update farmer profile\"}";
        }
    }

    // OPERATION 5: Add crop
    else if (operation == "addCrop")
    {
        if (argc < 5)
        {
            cout << "{\"success\":false,"
                 << "\"message\":\"Missing crop details\"}";
            return 1;
        }

        string farmerId = argv[2];
        string cropName = argv[3];
        int quantity = atoi(argv[4]);

        CropInfo crop(farmerId, cropName, quantity);

        // Redirect messages from existing C++ function
        cout.rdbuf(cerr.rdbuf());

        bool added = crop.addCrop();

        // Restore cout for JSON response
        cout.rdbuf(originalCout);

        if (added)
        {
            cout << "{\"success\":true,"
                 << "\"message\":\"Crop added successfully\"}";
        }
        else
        {
            cout << "{\"success\":false,"
                 << "\"message\":\"Could not add crop\"}";
        }
    }
    
else if (operation == "updateCrop")
{
    if (argc < 5)
    {
        cout << "{\"success\":false,"
             << "\"message\":\"Missing crop details\"}";
        return 1;
    }

    string farmerId = argv[2];
    string cropName = argv[3];
    int quantity = atoi(argv[4]);

    // Create CropInfo object
    CropInfo crop;

    // Redirect messages from the existing function
    cout.rdbuf(cerr.rdbuf());

    bool updated = crop.updateCrop(
        farmerId, cropName, quantity
    );

    // Restore cout
    cout.rdbuf(originalCout);

    if (updated)
    {
        cout << "{\"success\":true,"
             << "\"message\":\"Crop updated successfully\"}";
    }
    else
    {
        cout << "{\"success\":false,"
             << "\"message\":\"Could not update crop\"}";
    }
}

else if (operation == "removeCrop")
{
    if (argc < 4)
    {
        cout << "{\"success\":false,"
             << "\"message\":\"Missing crop details\"}";
        return 1;
    }

    string farmerId = argv[2];
    string cropName = argv[3];

    CropInfo crop;

    cout.rdbuf(cerr.rdbuf());

    bool removed = crop.removeCrop(farmerId, cropName);

    cout.rdbuf(originalCout);

    if (removed)
    {
        cout << "{\"success\":true,"
             << "\"message\":\"Crop removed successfully\"}";
    }
    else
    {
        cout << "{\"success\":false,"
             << "\"message\":\"Could not remove crop\"}";
    }
}
else if (operation == "getAllMandis")
{
    Mandi mandi;
    vector<Mandi> mandis = mandi.getAllMandis();

    cout << "{\"success\":true,\"mandis\":[";

    for (int i = 0; i < mandis.size(); i++)
    {
        if (i > 0)
            cout << ",";

        cout << "{";
        cout << "\"id\":\"" << escapeJson(mandis[i].getUsername()) << "\",";
        cout << "\"name\":\"" << escapeJson(mandis[i].getMandiName()) << "\",";
        cout << "\"location\":\"" << escapeJson(mandis[i].getLocation()) << "\",";
        cout << "\"capacity\":" << mandis[i].getCapacity() << ",";
        cout << "\"crops\":[";

        vector<string> crops = mandis[i].getCrops();
        vector<double> prices = mandis[i].getBuyingPrices();

        for (int j = 0; j < crops.size(); j++)
        {
            if (j > 0)
                cout << ",";

            cout << "{";
            cout << "\"crop\":\"" << escapeJson(crops[j]) << "\",";
            cout << "\"price\":" << prices[j];
            cout << "}";
        }

        cout << "]}";
    }

    cout << "]}" << endl;
}
else if (operation == "getMandiProfile")
{
    if (argc < 3)
    {
        cout << "{\"success\":false,\"message\":\"Mandi ID required\"}";
        return 1;
    }

    string mandiId = argv[2];

    Mandi mandi;
    vector<Mandi> mandis = mandi.getAllMandis();

    bool found = false;

    for (int i = 0; i < mandis.size(); i++)
    {
        if (mandis[i].getUsername() == mandiId)
        {
            cout << "{\"success\":true,\"mandi\":{";

            cout << "\"id\":\"" << escapeJson(mandis[i].getUsername()) << "\",";
            cout << "\"name\":\"" << escapeJson(mandis[i].getMandiName()) << "\",";
            cout << "\"location\":\"" << escapeJson(mandis[i].getLocation()) << "\",";
            cout << "\"capacity\":" << mandis[i].getCapacity() << ",";
            cout << "\"totalCapacity\":" << readCapacityValue(mandiId,0,mandis[i].getCapacity()) << ",";
            cout << "\"occupiedCapacity\":" << readCapacityValue(mandiId,1,0) << ",";
            cout << "\"contactPerson\":\"" << escapeJson(readContactField(mandiId,0)) << "\",";
            cout << "\"phone\":\"" << escapeJson(readContactField(mandiId,1)) << "\"";

            cout << "}}";

            found = true;
            break;
        }
    }

    if (!found)
    {
        cout << "{\"success\":false,\"message\":\"Mandi not found\"}";
    }
}
else if (operation == "updateMandiCapacity")
{
    if (argc < 5)
    {
        cout << "{\"success\":false,\"message\":\"Mandi ID, total and occupied capacity required\"}";
        return 1;
    }

    string mandiId = argv[2];
    int totalCapacity = atoi(argv[3]); int occupiedCapacity=atoi(argv[4]);
    int newCapacity=totalCapacity-occupiedCapacity;

    if (totalCapacity <= 0 || occupiedCapacity < 0 || occupiedCapacity > totalCapacity)
    {
        cout << "{\"success\":false,\"message\":\"Capacity must be greater than zero\"}";
        return 1;
    }

    Mandi mandi;
    bool updated = mandi.updateMandiCapacity(mandiId, newCapacity);
    if(updated) saveCapacityData(mandiId,totalCapacity,occupiedCapacity);

    if (updated)
    {
        cout << "{\"success\":true,\"message\":\"Mandi capacity updated successfully\"}";
    }
    else
    {
        cout << "{\"success\":false,\"message\":\"Mandi not found or update failed\"}";
    }
}
else if (operation == "addMandiCrop")
{
    if (argc < 5) { cout << "{\"success\":false,\"message\":\"Mandi ID, crop and price required\"}"; return 1; }
    double price = atof(argv[4]);
    if (price <= 0) { cout << "{\"success\":false,\"message\":\"Price must be positive\"}"; return 1; }
    bool ok = modifyMandiCropListing(argv[2], argv[3], price, true);
    cout << (ok ? "{\"success\":true,\"message\":\"Crop added successfully\"}" : "{\"success\":false,\"message\":\"Mandi not found or crop already exists\"}");
}
else if (operation == "updateMandiCropPrice")
{
    if (argc < 5) { cout << "{\"success\":false,\"message\":\"Mandi ID, crop and price required\"}"; return 1; }
    double price = atof(argv[4]);
    if (price <= 0) { cout << "{\"success\":false,\"message\":\"Price must be positive\"}"; return 1; }
    bool ok = modifyMandiCropListing(argv[2], argv[3], price, false);
    cout << (ok ? "{\"success\":true,\"message\":\"Price updated successfully\"}" : "{\"success\":false,\"message\":\"Mandi or crop not found\"}");
}
else if (operation == "registerMandi")
{
    if (argc < 11 || (argc - 9) % 2 != 0) { cout << "{\"success\":false,\"message\":\"Invalid arguments\"}"; return 1; }
    string id=argv[2], password=argv[3], name=argv[4], location=argv[5];
    int capacity=atoi(argv[6]); string contactPerson=argv[7], phone=argv[8];
    if (capacity <= 0) { cout << "{\"success\":false,\"message\":\"Invalid capacity\"}"; return 1; }
    vector<string> cropNames; vector<double> cropPrices;
    for (int i=9;i<argc;i+=2) { double price=atof(argv[i+1]); if(price<=0) { cout << "{\"success\":false,\"message\":\"Invalid crop price\"}"; return 1; } cropNames.push_back(argv[i]); cropPrices.push_back(price); }
    UserAuthentication auth; auth.loadMandis();
    if (auth.mandiUsernameExists(id)) { cout << "{\"success\":false,\"message\":\"Mandi account already exists\"}"; return 1; }
    Mandi m; vector<Mandi> all=m.getAllMandis();
    for (auto &entry:all) if(entry.getUsername()==id) { cout << "{\"success\":false,\"message\":\"Mandi profile already exists\"}"; return 1; }
    if (!auth.registerMandi(id,password)) { cout << "{\"success\":false,\"message\":\"Could not save mandi credentials\"}"; return 1; }
    ofstream file("mandi_details.txt", ios::app);
    if(!file) { cout << "{\"success\":false,\"message\":\"Unable to open mandi details file\"}"; return 1; }
    file << id << " " << name << " " << location << " " << capacity << " ";
    for(size_t i=0;i<cropNames.size();i++){ if(i) file << ","; file << cropNames[i] << ":" << cropPrices[i]; }
    file << "\n"; file.close(); saveContact(id,contactPerson,phone);
    cout << "{\"success\":true,\"message\":\"Mandi registered successfully\"}";
}


    else if (operation == "placeOrder")
    {
        if (argc < 6) { cout << "{\"success\":false,\"message\":\"Farmer, mandi, crop and quantity are required\"}"; return 1; }
        string farmerId=argv[2], mandiId=argv[3], cropName=argv[4];
        int quantity=atoi(argv[5]);
        if(quantity<=0){cout << "{\"success\":false,\"message\":\"Quantity must be positive\"}"; return 1;}
        CropInfo farmerCrop; vector<CropInfo> listed=farmerCrop.getMyCrops(farmerId); int listedQuantity=0;
        for(auto &c:listed) if(sameName(c.getCropName(),cropName)) { listedQuantity=c.getQuantity(); cropName=c.getCropName(); }
        if(listedQuantity<quantity){cout << "{\"success\":false,\"message\":\"Order quantity exceeds your listed crop quantity\"}"; return 1;}
        Mandi mandiObj; vector<Mandi> all=mandiObj.getAllMandis();
        bool found=false; double price=0; int capacity=0;
        for(auto &m:all) if(m.getUsername()==mandiId){
            found=true; capacity=m.getCapacity();
            vector<string> names=m.getCrops(); vector<double> prices=m.getBuyingPrices();
            for(size_t i=0;i<names.size() && i<prices.size();i++) if(sameName(names[i],cropName)) price=prices[i];
            break;
        }
        if(!found){cout << "{\"success\":false,\"message\":\"Mandi not found\"}"; return 1;}
        if(price<=0){cout << "{\"success\":false,\"message\":\"This mandi does not accept the selected crop\"}"; return 1;}
        if(quantity>capacity){cout << "{\"success\":false,\"message\":\"Mandi does not have enough available capacity\"}"; return 1;}
        ifstream existing("orders.txt"); string line; int nextId=1;
        while(getline(existing,line)){ if(line.rfind("ORD-",0)==0){ size_t pos=line.find(' '); if(pos!=string::npos) nextId=max(nextId,atoi(line.substr(4,pos-4).c_str())+1); } }
        existing.close();
        ostringstream orderId; orderId<<"ORD-"<<nextId;
        double total=price*quantity;
        ofstream out("orders.txt",ios::app);
        if(!out){cout << "{\"success\":false,\"message\":\"Could not save order\"}"; return 1;}
        out<<orderId.str()<<" "<<farmerId<<" "<<mandiId<<" "<<cropName<<" "<<quantity<<" "<<price<<" "<<total<<" PLACED\n";
        out.close();
        // Reduce farmer-listed stock and mandi available capacity after the order is saved.
        cout.rdbuf(cerr.rdbuf());
        bool stockUpdated = (listedQuantity==quantity) ? farmerCrop.removeCrop(farmerId,cropName) : farmerCrop.updateCrop(farmerId,cropName,listedQuantity-quantity);
        cout.rdbuf(originalCout);
        bool capacityUpdated = mandiObj.updateMandiCapacity(mandiId,capacity-quantity);
        if(capacityUpdated) { int total=readCapacityValue(mandiId,0,capacity); int occupied=readCapacityValue(mandiId,1,0); saveCapacityData(mandiId,total,occupied+quantity); }
        if(!stockUpdated || !capacityUpdated){ cout << "{\"success\":false,\"message\":\"Order was saved, but stock or capacity could not be updated. Check order history before retrying.\"}"; return 1; }
        cout << "{\"success\":true,\"message\":\"Order placed successfully\",\"order\":{\"id\":\""<<orderId.str()<<"\",\"farmerId\":\""<<escapeJson(farmerId)<<"\",\"mandiId\":\""<<escapeJson(mandiId)<<"\",\"crop\":\""<<escapeJson(cropName)<<"\",\"quantity\":"<<quantity<<",\"price\":"<<price<<",\"total\":"<<total<<",\"status\":\"PLACED\"}}";
    }
    else if (operation == "getOrders")
    {
        if(argc<4){cout << "{\"success\":false,\"message\":\"Role and ID required\"}"; return 1;}
        string role=argv[2], id=argv[3];
        ifstream in("orders.txt"); string orderId, farmerId, mandiId, crop, status; int quantity; double price,total;
        bool first=true; cout << "{\"success\":true,\"orders\":[";
        while(in>>orderId>>farmerId>>mandiId>>crop>>quantity>>price>>total>>status){
            if((role=="farmer" && farmerId==id)||(role=="mandi" && mandiId==id)){
                if(!first) cout<<",";
                first=false;
                cout<<"{\"id\":\""<<escapeJson(orderId)<<"\",\"farmerId\":\""<<escapeJson(farmerId)<<"\",\"mandiId\":\""<<escapeJson(mandiId)<<"\",\"crop\":\""<<escapeJson(crop)<<"\",\"quantity\":"<<quantity<<",\"price\":"<<price<<",\"total\":"<<total<<",\"status\":\""<<escapeJson(status)<<"\"}";
            }
        }
        cout<<"]}";
    }

    // Handle unknown operations
    else
    {
        cout << "{\"success\":false,"
             << "\"message\":\"Unknown operation\"}";
    }

    return 0;
}
