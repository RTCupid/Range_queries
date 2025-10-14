#include "node.hpp"

#include <gtest/gtest.h>
#include <memory>

using namespace RB_tree;

TEST(NodeTest, DefaultConstructor) {
    Node<int> node;
    EXPECT_EQ(node.get_key(), int{});
    EXPECT_TRUE(node.is_red());
}

TEST(NodeTest, ConstructorWithKeyAndColor) {
    Node<int> node_int(42, Color::red);
    EXPECT_EQ(node_int.get_key(), 42);
    EXPECT_TRUE(node_int.is_red());
    
    Node<std::string> node_string("test", Color::black);
    EXPECT_EQ(node_string.get_key(), "test");
    EXPECT_TRUE(node_string.is_black());
}

TEST(NodeTest, MoveConstructor) {
    auto original = std::make_unique<Node<int>>(100, Color::black);
    EXPECT_EQ(original->get_key(), 100);
    EXPECT_TRUE(original->is_black());

    auto moved = std::move(original);
    EXPECT_EQ(moved->get_key(), 100);
    EXPECT_TRUE(moved->is_black());
}

TEST(NodeTest, MoveAssignment) {
    auto moved = std::make_unique<Node<int>>(100, Color::black);
    auto another = std::make_unique<Node<int>>(200, Color::red);
    
    another = std::move(moved);
    EXPECT_EQ(another->get_key(), 100);
    EXPECT_TRUE(another->is_black());
}

TEST(NodeTest, ColorMethods) {
    Node<int> node(42, Color::red);
    EXPECT_TRUE(node.is_red());
    EXPECT_FALSE(node.is_black());
    
    node.set_color(Color::black);
    EXPECT_TRUE(node.is_black());
    EXPECT_FALSE(node.is_red());
    
    node.set_color(Color::red);
    EXPECT_TRUE(node.is_red());
    EXPECT_FALSE(node.is_black());
}

TEST(NodeTest, GetColor) {
    Node<int> node_red(1, Color::red);
    EXPECT_EQ(node_red.get_color(), Color::red);
    
    Node<int> node_black(2, Color::black);
    EXPECT_EQ(node_black.get_color(), Color::black);
}

TEST(NodeTest, GetKey) {
    Node<int> node_int(42, Color::red);
    EXPECT_EQ(node_int.get_key(), 42);
    
    Node<std::string> node_string("test", Color::black);
    EXPECT_EQ(node_string.get_key(), "test");
}

TEST(NodeTest, SetKey) {
    Node<int> node(42, Color::red);
    node.set_key(100);
    EXPECT_EQ(node.get_key(), 100);
    
    Node<std::string> node_str("old", Color::black);
    node_str.set_key("modified");
    EXPECT_EQ(node_str.get_key(), "modified");
}

TEST(NodeTest, SetLeft) {
    Node<int> parent(42, Color::red);
    auto left_child = std::make_unique<Node<int>>(10, Color::red);
    parent.set_left(std::move(left_child));
    
    const Node<int>* left_ptr = parent.get_left_ptr();
    ASSERT_NE(left_ptr, nullptr);
    EXPECT_EQ(left_ptr->get_key(), 10);
    EXPECT_EQ(left_ptr->get_parent_ptr(), &parent);
}

TEST(NodeTest, SetRight) {
    Node<int> parent(42, Color::red);
    auto right_child = std::make_unique<Node<int>>(20, Color::black);
    parent.set_right(std::move(right_child));
    
    const Node<int>* right_ptr = parent.get_right_ptr();
    ASSERT_NE(right_ptr, nullptr);
    EXPECT_EQ(right_ptr->get_key(), 20);
    EXPECT_EQ(right_ptr->get_parent_ptr(), &parent);
}

TEST(NodeTest, SetParent) {
    Node<int> child(42, Color::red);
    Node<int> parent(99, Color::red);
    
    child.set_parent(&parent);
    EXPECT_EQ(child.get_parent_ptr(), &parent);
}

TEST(NodeTest, SetLeftRightWithNullptr) {
    Node<int> node(42, Color::red);
    node.set_left(std::unique_ptr<Node<int>>(nullptr));
    node.set_right(std::unique_ptr<Node<int>>(nullptr));
    
    EXPECT_EQ(node.get_left_ptr(), nullptr);
    EXPECT_EQ(node.get_right_ptr(), nullptr);
}

TEST(NodeTest, GetParentPtr) {
    Node<int> node(42, Color::red);
    EXPECT_EQ(node.get_parent_ptr(), nullptr);
    
    Node<int> parent(99, Color::red);
    node.set_parent(&parent);
    EXPECT_EQ(node.get_parent_ptr(), &parent);
}

TEST(NodeTest, GetLeftPtr) {
    Node<int> node(42, Color::red);
    EXPECT_EQ(node.get_left_ptr(), nullptr);
    
    auto left_child = std::make_unique<Node<int>>(10, Color::red);
    node.set_left(std::move(left_child));
    EXPECT_NE(node.get_left_ptr(), nullptr);
    EXPECT_EQ(node.get_left_ptr()->get_key(), 10);
}

TEST(NodeTest, GetRightPtr) {
    Node<int> node(42, Color::red);
    EXPECT_EQ(node.get_right_ptr(), nullptr);
    
    auto right_child = std::make_unique<Node<int>>(20, Color::black);
    node.set_right(std::move(right_child));
    EXPECT_NE(node.get_right_ptr(), nullptr);
    EXPECT_EQ(node.get_right_ptr()->get_key(), 20);
}

TEST(NodeTest, ClearLeft) {
    Node<int> node(42, Color::red);
    auto left_child = std::make_unique<Node<int>>(10, Color::red);
    node.set_left(std::move(left_child));
    ASSERT_NE(node.get_left_ptr(), nullptr);
    
    node.clear_left();
    EXPECT_EQ(node.get_left_ptr(), nullptr);
}

TEST(NodeTest, ClearRight) {
    Node<int> node(42, Color::red);
    auto right_child = std::make_unique<Node<int>>(20, Color::black);
    node.set_right(std::move(right_child));
    ASSERT_NE(node.get_right_ptr(), nullptr);
    
    node.clear_right();
    EXPECT_EQ(node.get_right_ptr(), nullptr);
}

TEST(NodeTest, ClearParent) {
    Node<int> node(42, Color::red);
    Node<int> parent(99, Color::red);
    node.set_parent(&parent);
    ASSERT_NE(node.get_parent_ptr(), nullptr);
    
    node.clear_parent();
    EXPECT_EQ(node.get_parent_ptr(), nullptr);
}

TEST(NodeTest, TreeStructureIntegrity) {
    auto parent = std::make_unique<Node<int>>(100, Color::black);
    auto left_child = std::make_unique<Node<int>>(50, Color::red);
    auto right_child = std::make_unique<Node<int>>(150, Color::red);
    
    parent->set_left(std::move(left_child));
    parent->set_right(std::move(right_child));
    
    const Node<int>* left_ptr = parent->get_left_ptr();
    const Node<int>* right_ptr = parent->get_right_ptr();
    
    ASSERT_NE(left_ptr, nullptr);
    ASSERT_NE(right_ptr, nullptr);
    
    EXPECT_EQ(left_ptr->get_key(), 50);
    EXPECT_EQ(right_ptr->get_key(), 150);
    EXPECT_EQ(left_ptr->get_parent_ptr(), parent.get());
    EXPECT_EQ(right_ptr->get_parent_ptr(), parent.get());
}

TEST(NodeTest, DifferentKeyTypes) {
    Node<double> double_node(3.14, Color::red);
    EXPECT_DOUBLE_EQ(double_node.get_key(), 3.14);
    
    Node<char> char_node('A', Color::black);
    EXPECT_EQ(char_node.get_key(), 'A');
}

TEST(NodeTest, EmptyKey) {
    Node<std::string> empty_key_node("", Color::red);
    EXPECT_TRUE(empty_key_node.get_key().empty());
}

TEST(NodeTest, ZeroKey) {
    Node<int> zero_key_node(0, Color::black);
    EXPECT_EQ(zero_key_node.get_key(), 0);
}

TEST(NodeTest, MoveWithChildren) {
    auto parent = std::make_unique<Node<int>>(100, Color::black);
    auto left_child = std::make_unique<Node<int>>(50, Color::red);
    auto right_child = std::make_unique<Node<int>>(150, Color::red);
    
    parent->set_left(std::move(left_child));
    parent->set_right(std::move(right_child));
    
    auto moved_parent = std::move(parent);
    
    ASSERT_NE(moved_parent->get_left_ptr(), nullptr);
    ASSERT_NE(moved_parent->get_right_ptr(), nullptr);
    EXPECT_EQ(moved_parent->get_left_ptr()->get_key(), 50);
    EXPECT_EQ(moved_parent->get_right_ptr()->get_key(), 150);
    EXPECT_EQ(moved_parent->get_left_ptr()->get_parent_ptr(), moved_parent.get());
    EXPECT_EQ(moved_parent->get_right_ptr()->get_parent_ptr(), moved_parent.get());
}

TEST(NodeTest, RvalueKeyConstructor) {
    std::string key = "temporary";
    Node<std::string> node(std::move(key), Color::red);
    EXPECT_EQ(node.get_key(), "temporary");
}

TEST(NodeTest, ParentChildChain) {
    auto grandparent = std::make_unique<Node<int>>(100, Color::black);
    auto parent = std::make_unique<Node<int>>(50, Color::red);
    auto child = std::make_unique<Node<int>>(25, Color::red);
    
    grandparent->set_left(std::move(parent));
    grandparent->get_left_ptr()->set_left(std::move(child));
    
    const Node<int>* left_ptr = grandparent->get_left_ptr();
    ASSERT_NE(left_ptr, nullptr);
    EXPECT_EQ(left_ptr->get_key(), 50);
    EXPECT_EQ(left_ptr->get_parent_ptr(), grandparent.get());
    
    const Node<int>* left_left_ptr = left_ptr->get_left_ptr();
    ASSERT_NE(left_left_ptr, nullptr);
    EXPECT_EQ(left_left_ptr->get_key(), 25);
    EXPECT_EQ(left_left_ptr->get_parent_ptr(), left_ptr);
}