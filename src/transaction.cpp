#include "../include/transaction.h"

Transaction::Transaction(){
    transactionId = 0;
    farmerName = "";
    buyerName = "";
    cropName = "";
    quantity = 0;
    price = 0;
    status = "Pending";
}

Transaction::Transaction(int id, string farmer, string buyer, string crop, float qty, float pr ){
    this->transactionId = id;
    this->farmerName = farmer;
    this->buyerName = buyer;
    this->cropName = crop;
    this->quantity = qty;
    this->price = pr;
    this->status = "Pending";
}

void Transaction::displayTransaction(){
    cout<<"details are:"<<endl;
    cout << "Transaction ID: " << this->transactionId << endl;
    cout << "Farmer Name: " << this->farmerName << endl;
    cout << "Buyer Name: " << this->buyerName << endl;
    cout << "Crop Name: " << this->cropName << endl;
    cout << "Quantity: " << this->quantity << endl;
    cout << "Price: " << this->price << endl;
    cout << "Status: " << this->status << endl;
}

void Transaction::updateStatus(string newStatus){
    this->status = newStatus;

    cout << "Status updated successfully." << endl;
    cout << "Updated status: " << this->status << endl;
}


void Transaction::completeTransaction(){

    this->status = "Completed";
    cout << "Transaction completed successfully." << endl;
}

void TransactionManager::addTransaction(Transaction t){

    this->transactions.push_back(t);
    cout << "Transaction added successfully." << endl;
}

void TransactionManager::displayAllTransactions(){
    int n = this->transactions.size();

    for(int i = 0; i < n; i++){
        this->transactions[i].displayTransaction();
        cout << endl;
    }
}