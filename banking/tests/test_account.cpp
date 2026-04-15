#include <gtest/gtest.h>
#include "Account.h"

TEST(AccountTest, ConstructorAndGetters) {
    Account acc(1, "John Doe", 1000.0);
    
    EXPECT_EQ(acc.getId(), 1);
    EXPECT_EQ(acc.getName(), "John Doe");
    EXPECT_DOUBLE_EQ(acc.getBalance(), 1000.0);
}

TEST(AccountTest, Deposit) {
    Account acc(1, "John Doe", 1000.0);
    acc.deposit(500.0);
    EXPECT_DOUBLE_EQ(acc.getBalance(), 1500.0);
}

TEST(AccountTest, DepositNegativeAmount) {
    Account acc(1, "John Doe", 1000.0);
    EXPECT_THROW(acc.deposit(-100.0), std::invalid_argument);
}

TEST(AccountTest, Withdraw) {
    Account acc(1, "John Doe", 1000.0);
    acc.withdraw(300.0);
    EXPECT_DOUBLE_EQ(acc.getBalance(), 700.0);
}

TEST(AccountTest, WithdrawInsufficientFunds) {
    Account acc(1, "John Doe", 100.0);
    EXPECT_THROW(acc.withdraw(200.0), std::runtime_error);
}

TEST(AccountTest, WithdrawNegativeAmount) {
    Account acc(1, "John Doe", 1000.0);
    EXPECT_THROW(acc.withdraw(-50.0), std::invalid_argument);
}

TEST(AccountTest, Transfer) {
    Account from(1, "John Doe", 1000.0);
    Account to(2, "Jane Smith", 500.0);
    
    from.transfer(to, 300.0);
    
    EXPECT_DOUBLE_EQ(from.getBalance(), 700.0);
    EXPECT_DOUBLE_EQ(to.getBalance(), 800.0);
}

TEST(AccountTest, TransferInsufficientFunds) {
    Account from(1, "John Doe", 100.0);
    Account to(2, "Jane Smith", 500.0);
    
    EXPECT_THROW(from.transfer(to, 200.0), std::runtime_error);
}
