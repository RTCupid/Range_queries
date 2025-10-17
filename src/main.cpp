#include <iostream>
#include "range_query.hpp"
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
                range_query<Tree<int>, int>(tree, fst, snd);
            }
            break;
        default:
            std::cout << "unknown command\n";
        }
    }
}
