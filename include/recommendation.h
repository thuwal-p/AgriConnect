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
        vector<Mandi> filterByCapacity(vector<Mandi>Mandis,int Quantity);//here how do we make sure that the filter by capapcity function is recieving the list of mandis which are already filtered by filterByCrop()?
    public:
        vector<Mandi> getMatchedMandis(vector<Mandi>Mandis,int Quantity,string CropName);
};

class ScoreCalculator{
    public:
        double CalcScore();//INCOMPLETE-confirm which attributes to pass
};

class MaxHeap{};

