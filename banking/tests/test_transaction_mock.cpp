#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Account.h"
#include "Transaction.h"

class MockAccount : public Account {
public:
    MockAccount(int id, const std::string& name, double balance) 
        : Account(id, name, balance) {}
    
    MOCK_METHOD1(withdraw, void(double amount));
    MOCK_METHOD1(deposit, void(double amount));
};

TEST(TransactionMockTest, ExecuteCallsWithdrawAndDeposit) {
    MockAccount from(1, "From", 1000);
    MockAccount to(2, "To", 500);
    
    Transaction tx(&from, &to, 300);
    
    EXPECT_CALL(from, withdraw(300)).Times(1);
    EXPECT_CALL(to, deposit(300)).Times(1);
    
    tx.execute();
}

TEST(TransactionMockTest, RollbackCallsWithdrawAndDeposit) {
    MockAccount from(1, "From", 1000);
    MockAccount to(2, "To", 500);
    
    Transaction tx(&from, &to, 300);
    
    EXPECT_CALL(from, withdraw(300)).Times(1);
    EXPECT_CALL(to, deposit(300)).Times(1);
    tx.execute();
    
    EXPECT_CALL(to, withdraw(300)).Times(1);
    EXPECT_CALL(from, deposit(300)).Times(1);
    tx.rollback();
}

TEST(TransactionMockTest, ExecuteDoesNothingIfNotPending) {
    MockAccount from(1, "From", 1000);
    MockAccount to(2, "To", 500);
    
    Transaction tx(&from, &to, 300);
    tx.execute();
    
    EXPECT_CALL(from, withdraw(300)).Times(0);
    EXPECT_CALL(to, deposit(300)).Times(0);
    
    tx.execute();
}

TEST(TransactionMockTest, RollbackDoesNothingIfNotCompleted) {
    MockAccount from(1, "From", 1000);
    MockAccount to(2, "To", 500);
    
    Transaction tx(&from, &to, 300);
    
    EXPECT_CALL(to, withdraw(300)).Times(0);
    EXPECT_CALL(from, deposit(300)).Times(0);
    
    tx.rollback();
}
