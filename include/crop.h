#ifndef CROP_H
#define CROP_H

#include <string>

class Crop
{
private:
    int cropId;
    std::string cropName;
    float quantity;
    std::string category;

public:
    Crop();
    Crop(int id, std::string name, float qty, std::string cat);

    void addCrop();
    void viewCrop();
    void updateCrop();

    int getCropId();
    std::string getCropName();
    float getQuantity();
    std::string getCategory();
};

#endif