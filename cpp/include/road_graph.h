#ifndef ROAD_GRAPH_H
#define ROAD_GRAPH_H

#include <string>
#include <map>
#include <vector>
#include <utility>

using namespace std;

class RoadGraph
{
private:
    map<string, vector<pair<string, double>>> graph;
    void addRoad(string city1, string city2, double distanceKm);
    string normalizeCity(string city);
public:
    RoadGraph();
    bool hasCity(string city);
    double shortestDistance(string source, string destination);
};

#endif
