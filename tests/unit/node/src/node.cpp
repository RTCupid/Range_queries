#include <gtest/gtest.h>
#include <string>
#include <type_traits>

#include "node.hpp"

using RB_tree::Color;
using RB_tree::Node;

static_assert(!std::is_copy_constructible_v<Node<int>>);
static_assert(!std::is_copy_assignable_v<Node<int>>);
static_assert(std::is_move_constructible_v<Node<int>>);
static_assert(std::is_move_assignable_v<Node<int>>);

TEST(NodeTest, NilSentinelDefaults) {
    Node<int> nil; 

    EXPECT_TRUE(nil.is_nil());
    EXPECT_EQ(nil.get_parent(), &nil);
    EXPECT_EQ(nil.get_left(), &nil);
    EXPECT_EQ(nil.get_right(), &nil);

    EXPECT_TRUE(nil.is_black());
    EXPECT_FALSE(nil.is_red());
    EXPECT_EQ(Node<int>::try_get_color(&nil), Color::black);
}

TEST(NodeTest, LvalueConstructorRedByDefault) {
    const int k = 42;
    Node<int> n(k); 

    EXPECT_FALSE(n.is_nil());
    EXPECT_EQ(&k, &k); 
    EXPECT_TRUE(n.is_red());
    EXPECT_FALSE(n.is_black());
    EXPECT_EQ(n.get_key(), 42);
}

TEST(NodeTest, RvalueConstructorKeepsValue) {
    Node<std::string> n(std::string("hello"));
    EXPECT_TRUE(n.is_red());
    EXPECT_EQ(n.get_key(), "hello");
}

TEST(NodeTest, ExplicitColorBlack) {
    Node<int> n(7, Color::black);
    EXPECT_TRUE(n.is_black());
    EXPECT_FALSE(n.is_red());
    EXPECT_EQ(n.get_key(), 7);
}

TEST(NodeTest, TryGetColorHandlesNullptr) {
    EXPECT_EQ(Node<int>::try_get_color(nullptr), Color::black);
}

TEST(NodeTest, TryGetColorReadsNodeColor) {
    Node<int> a(1);            
    Node<int> b(2, Color::black);
    EXPECT_EQ(Node<int>::try_get_color(&a), Color::red);
    EXPECT_EQ(Node<int>::try_get_color(&b), Color::black);

    a.color_ = Color::black;
    EXPECT_EQ(Node<int>::try_get_color(&a), Color::black);
}

TEST(NodeTest, ParentLeftRightSetAndGet) {
    Node<int> p(10);
    Node<int> l(5);
    Node<int> r(15);

    EXPECT_EQ(p.get_parent(), nullptr);
    EXPECT_EQ(p.get_left(), nullptr);
    EXPECT_EQ(p.get_right(), nullptr);

    p.set_left(&l);
    p.set_right(&r);
    l.set_parent(&p);
    r.set_parent(&p);

    EXPECT_EQ(p.get_left(), &l);
    EXPECT_EQ(p.get_right(), &r);
    EXPECT_EQ(l.get_parent(), &p);
    EXPECT_EQ(r.get_parent(), &p);
}

TEST(NodeTest, ConstQualifiedGetters) {
    Node<int> p(1);
    Node<int> l(0);
    p.set_left(&l);
    l.set_parent(&p);

    const Node<int>& cp = p;
    const Node<int>& cl = l;

    EXPECT_EQ(cp.get_left(), &l);
    EXPECT_EQ(cl.get_parent(), &p);
}

TEST(NodeTest, IsNilTrueWhenParentSelf) {
    Node<int> n(3);
    EXPECT_FALSE(n.is_nil()); 

    n.set_parent(&n); 
    EXPECT_TRUE(n.is_nil());
}

TEST(NodeTest, MoveConstructionAndAssignment) {
    Node<std::string> a(std::string("x"));
    Node<std::string> b(std::move(a)); 
    EXPECT_EQ(b.get_key(), "x");

    Node<std::string> c(std::string("y"));
    c = std::move(b);
    EXPECT_EQ(c.get_key(), "x");
}
