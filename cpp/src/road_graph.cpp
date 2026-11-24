#include "../include/road_graph.h"
#include <algorithm>
#include <cctype>
#include <limits>
#include <queue>


string RoadGraph::normalizeCity(string city)
{
    transform(city.begin(), city.end(), city.begin(), [](unsigned char c) { return (char)tolower(c); });
    replace(city.begin(), city.end(), '_', ' ');
    size_t first = city.find_first_not_of(" \t\r\n");
    if (first == string::npos) return "";
    size_t last = city.find_last_not_of(" \t\r\n");
    return city.substr(first, last - first + 1);
}


void RoadGraph::addRoad(string city1, string city2, double distanceKm)
{
    city1 = normalizeCity(city1);
    city2 = normalizeCity(city2);
    graph[city1].push_back({city2, distanceKm});
    graph[city2].push_back({city1, distanceKm});
}


RoadGraph::RoadGraph()
{
    // Predefined road network. Distances are approximate road kilometres.
    addRoad("Dehradun","Haridwar",52); addRoad("Dehradun","Rishikesh",45);
    addRoad("Haridwar","Rishikesh",25); addRoad("Haridwar","Roorkee",32);
    addRoad("Roorkee","Saharanpur",45); addRoad("Saharanpur","Meerut",75);
    addRoad("Meerut","Delhi",72); addRoad("Roorkee","Delhi",175);
    addRoad("Dehradun","Saharanpur",75); addRoad("Haridwar","Delhi",190);
    addRoad("Dehradun","Haldwani",165); addRoad("Haldwani","Rudrapur",35);
    addRoad("Rudrapur","Kashipur",50); addRoad("Kashipur","Haridwar",115);
    addRoad("Haldwani","Almora",90); addRoad("Rishikesh","Srinagar Garhwal",105);
    addRoad("Srinagar Garhwal","Pauri",35); addRoad("Dehradun","Mussoorie",34);
    addRoad("Delhi","Ghaziabad",25); addRoad("Ghaziabad","Meerut",45);
}


bool RoadGraph::hasCity(string city)
{
    city = normalizeCity(city);
    return graph.count(city) > 0;
}


 double RoadGraph::shortestDistance(string source, string destination)
{
    source = normalizeCity(source);
    destination = normalizeCity(destination);
    if (!hasCity(source) || !hasCity(destination)) return -1.0;
    if (source == destination) return 0.0;

    map<string, double> dist;
    for (const auto &node : graph) dist[node.first] = numeric_limits<double>::infinity();
    dist[source] = 0.0;

    priority_queue<pair<double, string>, vector<pair<double, string>>, greater<pair<double, string>>> pq;
    pq.push({0.0, source});
    while (!pq.empty())
    {
        auto current = pq.top(); pq.pop();
        double d = current.first;
        string city = current.second;
        if (d > dist[city]) continue;
        if (city == destination) return d;
        for (const auto &edge : graph[city])
        {
            double newDistance = d + edge.second;
            if (newDistance < dist[edge.first])
            {
                dist[edge.first] = newDistance;
                pq.push({newDistance, edge.first});
            }
        }
    }
    return -1.0;
}
