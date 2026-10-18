#include<iostream>
#include<string>
#include<unordered_map>
#include<vector>
#include "mandi.h"
#include "farmer.h"

using namespace std;

class CropMatching{
    private:
        unordered_map<string, vector<Mandi>> cropMap;
        vector<Mandi> filterByCrop(string cropName);
        vector<Mandi> filterByCapacity(vector<Mandi>Mandis,int Quantity);
    public:
        vector<Mandi> getMatchedMandis(vector<Mandi>Mandis,int Quantity,string CropName);
};

class ScoreCalculator{
    public:
        double CalcScore();
};

class MaxHeap{};

