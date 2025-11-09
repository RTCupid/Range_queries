#include <gtest/gtest.h>
#include "tree.hpp" 
#include <vector>
#include <algorithm>

TEST(RBTreeMoveTest, MoveConstructor) {
    RB_tree::Tree<int> t1;
    t1.insert(5);
    t1.insert(10);

    RB_tree::Tree<int> t2 = std::move(t1);

    auto it = t2.begin();
    EXPECT_NE(it, t2.end());
    EXPECT_EQ(*it, 5);
    ++it;
    EXPECT_NE(it, t2.end());
    EXPECT_EQ(*it, 10);
    ++it;
    EXPECT_EQ(it, t2.end());

    EXPECT_EQ(t1.begin(), t1.end());
}

TEST(RBTreeMoveTest, MoveAssignment) {
    RB_tree::Tree<int> t1;
    t1.insert(100);

    RB_tree::Tree<int> t2;
    t2.insert(1);
    t2.insert(2);

    t2 = std::move(t1);

    auto it = t2.begin();
    EXPECT_NE(it, t2.end());
    EXPECT_EQ(*it, 100);
    ++it;
    EXPECT_EQ(it, t2.end());

    EXPECT_EQ(t1.begin(), t1.end());
}

TEST(RBTreeTest, BeginOnEmptyTree) {
    RB_tree::Tree<int> tree;
    EXPECT_TRUE(tree.begin() == tree.end());
}

TEST(RBTreeTest, BeginAfterSingleInsert) {
    RB_tree::Tree<int> tree;
    tree.insert(42);
    EXPECT_TRUE(tree.begin() != tree.end());
    EXPECT_EQ(*tree.begin(), 42);
}

TEST(RBTreeTest, BeginReturnsMinimum) {
    RB_tree::Tree<int> tree;
    std::vector<int> keys = {10, 5, 15, 3, 7, 12, 20};
    for (int k : keys) {
        tree.insert(k);
    }
    EXPECT_EQ(*tree.begin(), 3);
}

TEST(RBTreeTest, BeginUpdatesWhenSmallerKeyInserted) {
    RB_tree::Tree<int> tree;
    tree.insert(10);
    tree.insert(20);
    EXPECT_EQ(*tree.begin(), 10);

    tree.insert(5); 
    EXPECT_EQ(*tree.begin(), 5);

    tree.insert(1);  
    EXPECT_EQ(*tree.begin(), 1);
}

TEST(RBTreeTest, BeginAfterInsertingInDescendingOrder) {
    RB_tree::Tree<int> tree;
    for (int i = 100; i >= 10; i -= 10) {
        tree.insert(i);
    }
    EXPECT_EQ(*tree.begin(), 10);
}

TEST(RBTreeTest, BeginConsistencyWithLowerBound) {
    RB_tree::Tree<int> tree;
    std::vector<int> keys = {20, 10, 30, 5, 15};
    for (int k : keys) {
        tree.insert(k);
    }
    auto it1 = tree.begin();
    auto it2 = tree.lower_bound(0); 
    EXPECT_TRUE(it1 == it2);
}
