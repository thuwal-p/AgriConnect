#ifndef CROP_H
#define CROP_H

#include <string>
using namespace std;

class Crop
{
private:
    int cropId;
    string cropName;
    float quantity;//this is float bc we will input the qty in kilos, so for eg 23.5 kgs
    string category;

public:
    Crop();
    Crop(int id, string name, float qty, string cat);

    void addCrop();
    void viewCrop();
    void updateCrop();
    int getCropId();
    string getCropName();
    float getQuantity();
    string getCategory();
};

#endif
