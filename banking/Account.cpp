#include "Account.h"

Account::Account(int id, const std::string& name, double initialBalance)
    : id(id), name(name), balance(initialBalance) {}

int Account::getId() const { return id; }
std::string Account::getName() const { return name; }
double Account::getBalance() const { return balance; }

void Account::deposit(double amount) {
    if (amount <= 0) {
        throw std::invalid_argument("Deposit amount must be positive");
    }
    balance += amount;
}

void Account::withdraw(double amount) {
    if (amount <= 0) {
        throw std::invalid_argument("Withdrawal amount must be positive");
    }
    if (amount > balance) {
        throw std::runtime_error("Insufficient funds");
    }
    balance -= amount;
}

void Account::transfer(Account& to, double amount) {
    withdraw(amount);
    to.deposit(amount);
}
// minor change
