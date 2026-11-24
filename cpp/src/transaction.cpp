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

Transaction::Transaction(string farmer, string buyer, string crop, float qty, float pr)
{
    static int nextId = 1;

    this->transactionId = nextId++;
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



void Transaction::completeTransaction(){

    this->status = "Completed";
    cout << "Transaction completed successfully." << endl;
}

TransactionManager::TransactionManager()
{
    head = nullptr;
}

TransactionManager::~TransactionManager()
{
    Node* current = head;

    while (current != nullptr)
    {
        Node* nextNode = current->next;
        delete current;
        current = nextNode;
    }
}

void TransactionManager::addTransaction(Transaction t)
{
    Node* newNode = new Node;

    newNode->data = t;
    newNode->next = head;

    head = newNode;
}

void TransactionManager::displayAllTransactions()
{
    if (head == nullptr)
    {
        cout << "No transactions found.\n";
        return;
    }

    Node* current = head;
    double totalRevenue = 0;

    while (current != nullptr)
    {
        current->data.displayTransaction();

        double revenue =
            current->data.getQuantity() * current->data.getPrice();

        totalRevenue += revenue;

        cout << "Total Revenue: Rs. " << revenue << endl;
        cout << "----------------------\n";

        current = current->next;
    }

    cout << "\n============================================================\n";
    cout << "Total Revenue from All Transactions: Rs. "
         << totalRevenue << endl;
    cout << "============================================================\n";
}

int Transaction::getTransactionId(){

    return this->transactionId;
}

string Transaction::getFarmerName(){
    return this->farmerName;
}

string Transaction::getBuyerName(){
    return this->buyerName;
}

string Transaction::getCropName(){
    return this->cropName;
}

float Transaction::getQuantity(){
    return this->quantity;
}

float Transaction::getPrice(){
    return this->price;
}

string Transaction::getStatus(){
    return this->status;
}




void TransactionManager::completeTransaction(int id)
{
    Node* current = head;

    while (current != nullptr)
    {
        if (current->data.getTransactionId() == id)
        {
            current->data.completeTransaction();
            return;
        }

        current = current->next;
    }

    cout << "Transaction not found.\n";
}

void TransactionManager::searchTransaction(int id)
{
    Node* current = head;

    while (current != nullptr)
    {
        if (current->data.getTransactionId() == id)
        {
            current->data.displayTransaction();
            return;
        }

        current = current->next;
    }

    cout << "Transaction not found.\n";
}

void TransactionManager::deleteTransaction(int id)
{
    if (head == nullptr)
    {
        cout << "No transactions found.\n";
        return;
    }

    if (head->data.getTransactionId() == id)
    {
        Node* temp = head;
        head = head->next;
        delete temp;

        cout << "Transaction deleted successfully.\n";
        return;
    }

    Node* current = head;

    while (current->next != nullptr)
    {
        if (current->next->data.getTransactionId() == id)
        {
            Node* temp = current->next;

            current->next = temp->next;

            delete temp;

            cout << "Transaction deleted successfully.\n";
            return;
        }

        current = current->next;
    }

    cout << "Transaction not found.\n";
}




