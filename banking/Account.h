#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <stdexcept>

class Account {
private:
    int id;
    std::string name;
    double balance;

public:
    Account(int id, const std::string& name, double initialBalance = 0.0);
    
    int getId() const;
    std::string getName() const;
    double getBalance() const;
    
    virtual void deposit(double amount);
    virtual void withdraw(double amount);
    void transfer(Account& to, double amount);
};

#endif
