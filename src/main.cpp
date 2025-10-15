#include "node.hpp"
#include "tree.hpp"
#include <iostream>

using namespace RB_tree;

int main() {
    Tree<int> tree;

    auto root = std::make_unique<Node<int>>(10, Color::black);
    auto left = std::make_unique<Node<int>>(5, Color::black);
    auto right = std::make_unique<Node<int>>(15, Color::red);
    auto left_l = std::make_unique<Node<int>>(7, Color::black);
    auto left_r = std::make_unique<Node<int>>(4, Color::red);

    left->set_left(std::move(left_l));
    left->set_right(std::move(left_r));

    root->set_left(std::move(left));
    root->set_right(std::move(right));
    
    tree.get_root_ref() = std::move(root);

    tree.dump_graph();
    
}
