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

int Transaction::getTransactionId(){

    return this->transactionId;
}

string Transaction::getStatus(){
    return this->status;
}

void TransactionManager::updateTransactionStatus(int id, string status){
    int n =this->transactions.size();
    for(int i = 0; i < n; i++)
    {
        if(this->transactions[i].getTransactionId() == id) {
            cout<<"transaction found";
            this->transactions[i].updateStatus(status);
            return;
        }
    }
    cout << "Transaction not found." << endl;
}


void TransactionManager::completeTransaction(int id){
    int n =this->transactions.size();
    for(int i = 0; i < n; i++){
        if(this->transactions[i].getTransactionId() == id){
            this->transactions[i].completeTransaction();
            return;
        }
    }
    cout << "Transaction not found." << endl;
}

void TransactionManager::searchTransaction(int id){
    int n = this->transactions.size();

    for(int i = 0; i < n; i++){
        if(this->transactions[i].getTransactionId() == id){
            cout << "Transaction found." << endl;
            this->transactions[i].displayTransaction();
            return;
        }
    }

    cout << "Transaction not found";
}

void TransactionManager::deleteTransaction(int id){
    int n = this->transactions.size();

    for(int i = 0; i < n; i++){
        if(this->transactions[i].getTransactionId() == id){
            for(int j = i; j < n - 1; j++){
                this->transactions[j] = this->transactions[j + 1];
            }

            cout << "Transaction deleted successfully." << endl;
            return;
        }
    }

    cout << "Transaction not found." << endl;
}




