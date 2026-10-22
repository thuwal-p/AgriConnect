#include<iostream>
#include<string>
#include<unordered_map>
#include<vector>
#include <stdexcept>
#include "mandi.h"
#include "farmer.h"

using namespace std;

class CropMatching{
    private:
        vector<Mandi> filterByCrop(string cropName,const vector<Mandi>&Mandis);
        vector<Mandi> filterByCapacity(int Quantity,const vector<Mandi>&Mandis);
    public:
        vector<Mandi> getMatchedMandis(const vector<Mandi>&Mandis,int Quantity,string CropName);
};

class ScoreCalculator{
    public:
        double CalcScore(int Quantity, double buyingPrice);
        vector<double> calculateScores (const vector<Mandi>& Mandis,string CropName,int Quantity);
};

class MaxHeap
{
private:
    vector<Mandi> mandis;
    vector<double> scores;

public:
    void insert(Mandi mandi, double score);
    Mandi extractMax();
    vector<Mandi> getTopMandis(const vector<Mandi>& Mandis,const vector<double>& scores,int n);//this will return the top n mandis extracted from maxheap

};



