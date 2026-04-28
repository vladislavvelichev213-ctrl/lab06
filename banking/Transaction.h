#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <ctime>
#include "Account.h"

class Transaction {
private:
    Account* fromAccount;
    Account* toAccount;
    double amount;
    std::time_t timestamp;
    std::string status;

public:
    Transaction(Account* from, Account* to, double amount);
    
    Account* getFromAccount() const;
    Account* getToAccount() const;
    double getAmount() const;
    std::time_t getTimestamp() const;
    std::string getStatus() const;
    
    void execute();
    void rollback();
};

#endif
