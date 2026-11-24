AGRICONNECT - EXISTING FULL-STACK PROJECT
=========================================

This archive preserves the original AgriConnect project and its C++ classes,
Express API, browser dashboards, and text-file data storage. No replacement
project was created.

STRUCTURE
---------
public/                                  Browser frontend files (HTML/CSS/JS)
cpp/api.cpp                              C++ command-line API adapter
cpp/main.cpp                             Original terminal application entry point
cpp/include/ and cpp/src/                Existing C++ classes and implementations
data/*.txt                               Existing text-file data
build/                                   Generated C++ executable (not committed)
server.js                                Express API + static frontend server

REQUIREMENTS (macOS + VS CODE)
------------------------------
- Xcode Command Line Tools (provides clang++)
- Node.js and npm
- VS Code (optional editor)

BUILD AND RUN
-------------
1. Extract the ZIP and open the AgriConnect folder in VS Code.
2. Open Terminal in the project folder.
3. Install the Node dependencies:

   npm install

4. Start the server (this automatically compiles the C++ API before launch):

   npm start

   The build command intentionally excludes cpp/main.cpp because it is the
   original terminal application's separate entry point and contains main(). The
server serves browser files from public/ and runs the C++ program with data/ as
its working directory so existing text-file paths continue to work.

5. Open:

   http://localhost:3000

Health check:
   http://localhost:3000/api/health

REBUILD AFTER C++ CHANGES
-------------------------
Stop the server, then run npm start again. The start script rebuilds the
C++ API automatically. On Windows, the server selects build/AgriConnectAPI.exe;
on macOS/Linux it selects build/AgriConnectAPI.

RECOMMENDATION IMPLEMENTATION
-----------------------------
- Uses an adjacency-list road graph and Dijkstra with a min-priority queue.
- The initial road graph contains predefined Uttarakhand / North India routes.
- Locations are matched by their normalized city name. If the farmer or mandi
  location is not represented in the road graph, that mandi is omitted rather
  than assigned a fabricated distance.
- Eligible mandis must list the requested crop and have enough available
  capacity.
- Revenue = quantity (quintals) * buying price (₹/quintal).
- Transportation is estimated as shortest road distance * ₹18 per kilometre.
  ₹18/km is an initial project assumption, not a live quote; adjust the
  transportRate constant in api.cpp when a better local rate is available.
- Net profit = revenue - estimated transport cost. Results are sorted by net
  profit, then shorter road distance when profits are effectively equal.

CAPACITY
--------
The mandi_details.txt capacity field continues to represent available capacity,
so existing order placement and recommendation checks remain compatible.
capacity_details.txt stores total and occupied capacity for registered/updated
mandis. Available capacity is total minus occupied. Existing records without
capacity_details.txt are treated as their existing capacity available and zero
occupied until the mandi edits capacity or places an order.

CONTACT DETAILS
---------------
contact_details.txt stores the farmer phone and mandi contact-person / phone
fields by account ID. New registrations write these fields, and profiles load
them from this file. Names and locations continue using underscore-separated
records to remain compatible with the existing data format.

DATA AND SECURITY NOTES
-----------------------
- The project uses local text files and plain-text credentials, as in the
  original demo. Do not use real passwords or deploy this prototype publicly.
- Back up farmers.txt, mandis.txt, farmer_details.txt, mandi_details.txt,
  crops.txt, orders.txt, contact_details.txt and capacity_details.txt before
  testing account creation, orders or capacity changes.
- Crop listing and order history remain stored in the existing files.
- The original terminal application and existing transaction module are kept.
- Mandi crop and price editing beyond the original registration flow is not
  implemented by this modification.
- Transactions use the existing order-file workflow; payment, delivery,
  cancellation and refunds are outside this prototype.
- Road distances are predefined estimates, not live map routing.

CHANGES IN THIS FIX
-------------------
- All .txt readers are now line-based and tolerate CRLF, a UTF-8 BOM, blank and
  malformed rows (previously one bad row stopped every later record from loading).
- Crop names are matched case-insensitively (Wheat = wheat) in recommendations and orders.
- Locations missing from the road graph (e.g. Mumbai, Nainital, Haldwani "hld") use an
  estimated distance (straight-line x 1.3) from a built-in city table and are labelled
  "Est. distance". Cities unknown to both tables are still skipped.
- Data files are normalised to LF line endings with a trailing newline, so new
  registrations never glue onto the previous record.
- server.js no longer serves .txt/.cpp/.h/.json files (farmers.txt held passwords).
- IDs/passwords with spaces are rejected at registration.
- Dark-green redesign; farmer dashboard has a farmer-in-field banner and the mandi
  dashboard a mandi-market banner.

CITY DROPDOWN (nearest major city)
----------------------------------
Registration now asks for the "Nearest major city" from a dropdown (list in script.js,
matching the coordinate table in api.cpp). The city is stored as the location and used for
distance. The optional village/town name is stored in village_details.txt and shown on the
profile. To add a city: add it to the table in api.cpp AND to CITIES in script.js.

CASE-INSENSITIVITY AND LOSS WARNING
-----------------------------------
- IDs (farmer/mandi usernames), crop names and city names are case-insensitive
  everywhere (login, registration duplicate check, add/update/remove crop,
  recommendations, orders). IDs are stored in lower case. Passwords stay case-sensitive.
- If transport cost exceeds revenue (negative net profit), the recommendation row is
  labelled "Transport cost exceeds revenue" and shows "Net loss". If every mandi is a
  loss, a warning banner appears. Placing a loss-making order asks for extra confirmation.
  The best-profit highlight is only given to a profitable mandi.
