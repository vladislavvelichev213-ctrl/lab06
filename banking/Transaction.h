#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <ctime>

class Transaction {
private:
    int fromId;
    int toId;
    double amount;
    std::time_t timestamp;
    std::string status;

public:
    Transaction(int fromId, int toId, double amount);
    
    int getFromId() const;
    int getToId() const;
    double getAmount() const;
    std::time_t getTimestamp() const;
    std::string getStatus() const;
    
    void execute();
    void rollback();
};

#endif
