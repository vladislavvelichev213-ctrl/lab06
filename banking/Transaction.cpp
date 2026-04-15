#include "Transaction.h"
#include <iostream>

Transaction::Transaction(int fromId, int toId, double amount)
    : fromId(fromId), toId(toId), amount(amount), status("pending") {
    timestamp = std::time(nullptr);
}

int Transaction::getFromId() const { return fromId; }
int Transaction::getToId() const { return toId; }
double Transaction::getAmount() const { return amount; }
std::time_t Transaction::getTimestamp() const { return timestamp; }
std::string Transaction::getStatus() const { return status; }

void Transaction::execute() {
    if (status == "pending") {
        status = "completed";
        std::cout << "Transaction executed: " << fromId << " -> " << toId 
                  << " amount: " << amount << std::endl;
    }
}

void Transaction::rollback() {
    if (status == "completed") {
        status = "rolled_back";
        std::cout << "Transaction rolled back: " << fromId << " -> " << toId 
                  << " amount: " << amount << std::endl;
    }
}
