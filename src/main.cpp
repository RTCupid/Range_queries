#include <iostream>

#include "tree.hpp"

using namespace RB_tree;

int main() {
    Tree<int> tree;

    char query;

    while (std::cin >> query) {
        int key;
        int fst, snd;

        switch (query) {
        case 'k':
            if (std::cin >> key) {
                tree.insert(key);
            }
            break;
        case 'q':
            if (std::cin >> fst >> snd) {
                range_query(tree, fst, snd);
            }
            break;
        default:
            std::cout << "unknown command\n";
        }
    }
}
