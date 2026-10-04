#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Transaction{
private:
    int transactionId;
    string farmerName;
    string buyerName;
    string cropName;
    float quantity;
    float price;
    string status;

public:
    Transaction();

    Transaction(int id, string farmer, string buyer, string crop, float qty, float pr);

    //transaction operations
    void displayTransaction();
    void updateStatus(string newStatus);
    void completeTransaction();

    //getters
    int getTransactionId();
    string getFarmerName();
    string getBuyerName();
    string getCropName();
    float getQuantity();
    float getPrice();
    string getStatus();
};

class TransactionManager
{
private:
    vector<Transaction> transactions;

public:
    void addTransaction(Transaction t);

    void displayAllTransactions();

    void updateTransactionStatus(int id, string status);

    void completeTransaction(int id);

    void searchTransaction(int id);

    void deleteTransaction(int id);
};

#endif