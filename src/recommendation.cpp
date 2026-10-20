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

vector<double> ScoreCalculator::calculateScores(const vector<Mandi>& Mandis, string CropName, int Quantity)
{
    vector<double> scores;

    for (auto mandi : Mandis)
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

void MaxHeap::insert(Mandi mandi, double score)
{
    mandis.push_back(mandi);
    scores.push_back(score);

    int i = scores.size() - 1;

    while (i > 0)
    {
        int parent = (i - 1) / 2;

        if (scores[parent] >= scores[i])
            break;

        swap(scores[parent], scores[i]);
        swap(mandis[parent], mandis[i]);

        i = parent;
    }
}

Mandi MaxHeap::extractMax()
{
    if (mandis.empty())
    {
    throw runtime_error("Heap is empty");
    }
    Mandi maxMandi = mandis[0];

    mandis[0] = mandis.back();
    scores[0] = scores.back();

    mandis.pop_back();
    scores.pop_back();

    int i = 0;

    while (true)
    {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int largest = i;

        if (left < scores.size() && scores[left] > scores[largest])
        {
            largest = left;
        }

        if (right < scores.size() && scores[right] > scores[largest])
        {
            largest = right;
        }

        if (largest == i)
        {
            break;
        }

        swap(scores[i], scores[largest]);
        swap(mandis[i], mandis[largest]);

        i = largest;
    }

    return maxMandi;
}

vector<Mandi> MaxHeap::getTopMandis(const vector<Mandi>& Mandis,const vector<double>& scores,int n)
{
    vector<Mandi> result;

    for (int i = 0; i < Mandis.size(); i++)
    {
        insert(Mandis[i], scores[i]);
    }

    for (int i = 0; i < n && !mandis.empty(); i++)
    {
        Mandi bestMandi = extractMax();
        result.push_back(bestMandi);
    }

    return result;
}