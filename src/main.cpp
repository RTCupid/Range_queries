#include "node.hpp"
#include "tree.hpp"
#include <iostream>

using namespace RB_tree;

int main() {
    Tree<int> tree;

    tree.insert(5);
    tree.insert(6);
    tree.insert(4);
    tree.insert(3);
    tree.insert(31);
    tree.insert(34);
    tree.insert(65);
    tree.insert(75);
    tree.insert(85);
    tree.insert(95);

    tree.dump_graph();
}
