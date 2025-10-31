#include <gtest/gtest.h>
#include "tree.hpp" 
#include <vector>
#include <algorithm>

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
    // Минимум — 3
    EXPECT_EQ(*tree.begin(), 3);
}

TEST(RBTreeTest, BeginUpdatesWhenSmallerKeyInserted) {
    RB_tree::Tree<int> tree;
    tree.insert(10);
    tree.insert(20);
    EXPECT_EQ(*tree.begin(), 10);

    tree.insert(5);  // новый минимум
    EXPECT_EQ(*tree.begin(), 5);

    tree.insert(1);  // ещё меньше
    EXPECT_EQ(*tree.begin(), 1);
}

TEST(RBTreeTest, BeginAfterInsertingInDescendingOrder) {
    RB_tree::Tree<int> tree;
    // Вставляем 100, 90, 80, ..., 10 — минимум будет 10
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
    // begin() должен совпадать с lower_bound(минимальное_значение)
    auto it1 = tree.begin();
    auto it2 = tree.lower_bound(0); // 0 < всех ключей → первый >= 0 — это минимум
    EXPECT_TRUE(it1 == it2);
}