#include <gtest/gtest.h>
#include "Transaction.h"

TEST(TransactionTest, ConstructorAndGetters) {
    Transaction tx(1, 2, 500.0);
    
    EXPECT_EQ(tx.getFromId(), 1);
    EXPECT_EQ(tx.getToId(), 2);
    EXPECT_DOUBLE_EQ(tx.getAmount(), 500.0);
    EXPECT_EQ(tx.getStatus(), "pending");
}

TEST(TransactionTest, Execute) {
    Transaction tx(1, 2, 500.0);
    tx.execute();
    EXPECT_EQ(tx.getStatus(), "completed");
}

TEST(TransactionTest, Rollback) {
    Transaction tx(1, 2, 500.0);
    tx.execute();
    tx.rollback();
    EXPECT_EQ(tx.getStatus(), "rolled_back");
}

TEST(TransactionTest, CannotRollbackPending) {
    Transaction tx(1, 2, 500.0);
    tx.rollback();
    EXPECT_EQ(tx.getStatus(), "pending");
}
