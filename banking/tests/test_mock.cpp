#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Account.h"

class MockAccount : public Account {
public:
    MockAccount(int id, const std::string& name, double balance) 
        : Account(id, name, balance) {}
    
    MOCK_METHOD(void, deposit, (double amount), (override));
    MOCK_METHOD(void, withdraw, (double amount), (override));
};

TEST(MockAccountTest, WithdrawIsCalled) {
    MockAccount acc(1, "Test", 1000);
    EXPECT_CALL(acc, withdraw(500)).Times(1);
    acc.withdraw(500);
}

TEST(MockAccountTest, DepositIsCalled) {
    MockAccount acc(1, "Test", 1000);
    EXPECT_CALL(acc, deposit(200)).Times(1);
    acc.deposit(200);
}
