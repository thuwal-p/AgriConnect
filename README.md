# AgriConnect – Smart Agricultural Marketplace System

## Project Title and Brief Description

AgriConnect is a digital platform that connects farmers with mandis, helping farmers find suitable markets for their crops based on buying prices, available capacity, and transportation costs.

Built using C++ and web technologies, the system provides farmer and mandi dashboards, profit-based recommendations, crop management, and order placement.

## Problem Statement / Objective

### Problem Statement

Farmers often face difficulties in finding suitable buyers, comparing prices at different mandis, maintaining harvest records, and calculating their expected profit. Traditional methods involve manual record keeping and limited organized market information, making it difficult for farmers to decide where to sell their crops.

### Objective

The main objective of AgriConnect is to provide a centralized digital platform that connects farmers with mandis and simplifies the process of selecting suitable selling options.

The system aims to:

- Manage farmer, mandi, and crop information.
- Match crops with suitable mandis.
- Compare offered prices and available capacity.
- Generate mandi recommendations based on estimated net profit.
- Calculate transportation costs using road distances.
- Allow farmers to place orders and maintain transaction records.
- Demonstrate the practical application of Data Structures and Object-Oriented Programming.

## Team Members

**Team Name:** Team Geek Coders  
**Team ID:** T068

| Team Member | Contribution |
|---|---|
| Lavanya Rawat | User Authentication |
| Kumud Singh | Farmer & Mandi Management |
| Pranavi Thuwal | Recommendation System |
| Rishika Gupta | Transaction & Record Management |

## Technologies / Tools Used

### Programming Languages
- C++
- JavaScript
- HTML
- CSS

### Frameworks and Tools
- Node.js
- Express.js
- Visual Studio Code
- Git and GitHub
- GCC / G++ compiler

### Data Storage
- Text-file-based storage

## Data Structures and Algorithms Used

- **Hash Maps:** Managing and accessing structured information.
- **Graphs:** Representing road networks using adjacency lists.
- **Priority Queues:** Efficiently selecting the next closest location in Dijkstra's algorithm.
- **Dijkstra's Algorithm:** Finding shortest road distances between farmers and mandis.
- **Sorting:** Ranking mandi recommendations by estimated net profit.
- **Queues and Linked Lists:** Used in the underlying C++ implementation.

## Key Features

### Farmer Module
- Farmer registration and login.
- Profile management.
- Adding and managing crop details.
- Viewing mandi recommendations.
- Comparing estimated revenue, transportation costs, and net profit.
- Placing orders and viewing order history.

### Mandi Module
- Mandi registration and login.
- Profile management.
- Managing crop information and buying prices through the supported management flow.
- Maintaining available capacity.
- Viewing and managing orders.

### Recommendation System

The recommendation system identifies suitable mandis based on crop compatibility, buying price, available capacity, and transportation costs.

It uses a weighted adjacency-list road graph and Dijkstra's shortest-path algorithm with a min-priority queue.

**Profit Calculation:**

- Revenue = Quantity × Buying Price
- Transportation Cost = Distance × Transport Rate
- Net Profit = Revenue − Transportation Cost

The initial transportation rate is assumed to be ₹18/km. Recommendations are sorted by descending net profit, with shorter distance used as a tie-breaker.

For locations not present in the predefined road graph, the system can use estimated distances from a built-in city coordinate table. These are estimates, not live road distances.

### Capacity and Order Management
- Tracks total, occupied, and available mandi capacity.
- Prevents orders from exceeding available capacity.
- Maintains order and transaction records using text files.

### Data Handling
- Case-insensitive matching for user IDs, crop names, and city names.
- Handles blank and malformed text-file records.
- Normalizes text-file line endings.
- Rejects IDs and passwords containing spaces.

## System Architecture

AgriConnect follows a modular architecture:

1. **Frontend:** HTML, CSS, and JavaScript provide the landing page and separate farmer and mandi dashboards.
2. **Backend:** Node.js and Express.js handle API requests and communication with the C++ application.
3. **C++ Application:** Handles core logic, user management, recommendations, road graph operations, and transactions.
4. **Data Storage:** Text files store user, crop, mandi, capacity, contact, and order information.

The Express backend executes the compiled C++ API and processes its JSON output.

## Project Structure

```text
AgriConnect/
│
├── public/             # Frontend HTML, CSS and JS
├── cpp/
│   ├── api.cpp
│   ├── main.cpp
│   ├── include/        # Header files
│   └── src/            # C++ implementations
│
├── data/               # Local text-file databases
├── build/              # Compiled executable
├── server.js           # Express server
├── package.json
├── package-lock.json
├── .gitignore
└── README.md
```

## Installation and Execution

### Prerequisites
- C++ compiler supporting C++17.
- Node.js and npm.
- Git (optional).

### Steps

**1. Clone the repository**

```bash
git clone https://github.com/thuwal-p/AgriConnect.git
cd AgriConnect
```

**2. Install dependencies**

```bash
npm install
```

**3. Start the application**

```bash
npm start
```

The start command automatically compiles the C++ API and launches the Express server.

Open the application at:

```text
http://localhost:3000
```

Health check:

```text
http://localhost:3000/api/health
```

## Limitations and Future Scope

- Text files are currently used instead of a centralized database.
- Passwords are stored in plain text; the current implementation is intended as a demonstration prototype.
- Road distances and transportation rates are predefined or estimated.
- Online payment, delivery tracking, order cancellation, and refunds are not implemented.
- Future improvements include database integration, secure authentication, live map routing, real-time market prices, and cloud deployment.

## Conclusion

AgriConnect demonstrates the use of Data Structures, Algorithms, Object-Oriented Programming, and web technologies to address challenges in agricultural marketing. By connecting farmers and mandis and providing profit-based recommendations, the system aims to make crop-selling decisions more organized and informed.