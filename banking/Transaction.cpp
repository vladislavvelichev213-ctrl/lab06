#include "Transaction.h"
#include <iostream>

Transaction::Transaction(Account* from, Account* to, double amount)
    : fromAccount(from), toAccount(to), amount(amount), status("pending") {
    timestamp = std::time(nullptr);
}

Account* Transaction::getFromAccount() const { return fromAccount; }
Account* Transaction::getToAccount() const { return toAccount; }
double Transaction::getAmount() const { return amount; }
std::time_t Transaction::getTimestamp() const { return timestamp; }
std::string Transaction::getStatus() const { return status; }

void Transaction::execute() {
    if (status == "pending") {
        fromAccount->withdraw(amount);
        toAccount->deposit(amount);
        status = "completed";
        std::cout << "Transaction executed: " << fromAccount->getId() << " -> " 
                  << toAccount->getId() << " amount: " << amount << std::endl;
    }
}

void Transaction::rollback() {
    if (status == "completed") {
        toAccount->withdraw(amount);
        fromAccount->deposit(amount);
        status = "rolled_back";
        std::cout << "Transaction rolled back: " << fromAccount->getId() << " -> " 
                  << toAccount->getId() << " amount: " << amount << std::endl;
    }
}
