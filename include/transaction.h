#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Transaction
{
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

    Transaction(int id, string farmer, string buyer,
                string crop, float qty, float p);

    void displayTransaction();
    void updateStatus(string newStatus);
    void completeTransaction();

    int getTransactionId();
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
};

#endif