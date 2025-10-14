#include "node.hpp"
#include <iostream>

int main() {
    int key = 8;
    RB_tree::Node<int> n(8);
    std::cout << "color = ";
    if (n.is_black())
        std::cout << "black\n";
    if (n.is_red())
        std::cout << "red\n";
}
