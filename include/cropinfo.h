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
    double expectedPrice;

public:
    CropInfo();
    CropInfo(string id, string crop, int qty, double price);

    void setCropName(string crop);
    void setQuantity(int qty);
    void setExpectedPrice(double price);

    string getFarmerID();
    string getCropName();
    int getQuantity();
    double getExpectedPrice();

    bool addCrop();
    void viewMyCrops(string id);
    void viewAllCrops();
    bool searchCrop(string target);
    bool updateCrop(string id, string target, int qty, double price);
    bool removeCrop(string id, string target);
};

#endif