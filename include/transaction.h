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

    Transaction(string farmer, string buyer, string crop, float qty, float pr);

    //transaction operations
    void displayTransaction();
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

    struct Node
    {
        Transaction data;
        Node* next;
    };

    Node* head;

public:

    TransactionManager();

    void addTransaction(Transaction t);

    void displayAllTransactions();

    void completeTransaction(int id);

    void searchTransaction(int id);

    void deleteTransaction(int id);

    ~TransactionManager();
};

#endif