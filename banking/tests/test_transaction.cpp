#include <gtest/gtest.h>
#include "Transaction.h"
#include "Account.h"

TEST(TransactionTest, ConstructorAndGetters) {
    Account from(1, "From", 1000);
    Account to(2, "To", 500);
    Transaction tx(&from, &to, 500.0);
    
    EXPECT_EQ(tx.getFromAccount(), &from);
    EXPECT_EQ(tx.getToAccount(), &to);
    EXPECT_DOUBLE_EQ(tx.getAmount(), 500.0);
    EXPECT_EQ(tx.getStatus(), "pending");
}

TEST(TransactionTest, Execute) {
    Account from(1, "From", 1000);
    Account to(2, "To", 500);
    Transaction tx(&from, &to, 300);
    
    tx.execute();
    EXPECT_EQ(tx.getStatus(), "completed");
    EXPECT_DOUBLE_EQ(from.getBalance(), 700);
    EXPECT_DOUBLE_EQ(to.getBalance(), 800);
}

TEST(TransactionTest, Rollback) {
    Account from(1, "From", 1000);
    Account to(2, "To", 500);
    Transaction tx(&from, &to, 300);
    
    tx.execute();
    tx.rollback();
    EXPECT_EQ(tx.getStatus(), "rolled_back");
    EXPECT_DOUBLE_EQ(from.getBalance(), 1000);
    EXPECT_DOUBLE_EQ(to.getBalance(), 500);
}

TEST(TransactionTest, CannotRollbackPending) {
    Account from(1, "From", 1000);
    Account to(2, "To", 500);
    Transaction tx(&from, &to, 300);
    
    tx.rollback();
    EXPECT_EQ(tx.getStatus(), "pending");
    EXPECT_DOUBLE_EQ(from.getBalance(), 1000);
    EXPECT_DOUBLE_EQ(to.getBalance(), 500);
}
