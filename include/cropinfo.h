
#ifndef CROPINFO_H
#define CROPINFO_H

#include <string>
using namespace std;

class CropInfo
{
private:
    string farmerID;
    string cropName;
    int quantity;

public:
    CropInfo();
    CropInfo(string id, string crop, int qty);

    void setCropName(string crop);
    void setQuantity(int qty);

    string getFarmerID();
    string getCropName();
    int getQuantity();

    bool addCrop();
    void viewMyCrops(string id);
    bool updateCrop(string id, string target, int qty);
    bool removeCrop(string id, string target);
};

#endif

