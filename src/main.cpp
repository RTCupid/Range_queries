#include "node.hpp"
#include "tree.hpp"
#include <iostream>

using namespace RB_tree;

int main() {
    Tree<int> tree;

    auto* root  = new Node<int>(10, Color::black);
    auto* left  = new Node<int>(5,  Color::black);
    auto* right = new Node<int>(15, Color::red);

    root->set_left(left);
    root->set_right(right);

    left->set_parent(root);
    right->set_parent(root);

    tree.debug_set_root(root); 
    
    tree.dump_graph();
    
}
