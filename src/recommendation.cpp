#include "../include/recommendation.h"
vector<Mandi> CropMatching :: filterByCrop(string cropName,const vector<Mandi>&Mandis)
{
    vector<Mandi>result;
    for(auto m : Mandis)
    {
        for(string cn : m.getCrops())
        {
            if(cn==cropName)
            {

                result.push_back(m);
                break;
            }
        }
    }
    return result;
}

vector<Mandi> CropMatching :: filterByCapacity(int Quantity,const vector<Mandi>&Mandis)
{
    vector<Mandi> result;
    for(auto m : Mandis)
    {
        if(m.getCapacity() >= Quantity)
        {
            result.push_back(m);
        }
    }
    return result;
}

vector<Mandi> CropMatching:: getMatchedMandis(const vector<Mandi>&Mandis,int Quantity,string CropName)
{
    vector<Mandi>filter_crop = filterByCrop( CropName, Mandis);
    vector<Mandi>filter_cap = filterByCapacity(Quantity,filter_crop);
    return filter_cap;
}

double ScoreCalculator:: CalcScore(int quantity, double buyingPrice)
{
    return quantity*buyingPrice;
}

vector<double> ScoreCalculator::calculateScores(
    const vector<Mandi>& Mandis,
    string CropName,
    int Quantity)
{
    vector<double> scores;

    for (const Mandi& mandi : Mandis)
    {
        vector<string> crops = mandi.getCrops();
        vector<double> prices = mandi.getBuyingPrices();

        for (int i = 0; i < crops.size(); i++)
        {
            if (crops[i] == CropName)
            {
                double price = prices[i];

                double score = CalcScore(Quantity, price);

                scores.push_back(score);

                break;
            }
        }
    }

    return scores;
}