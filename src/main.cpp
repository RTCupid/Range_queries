#include "tree.hpp"
#include <iostream>

using namespace RB_tree;

int main() {
    Tree<int> tree;

    while (!std::cin.eof()) {
        char query;
        int key;
        int fst, snd;

        std::cin >> query;
        switch(query) {
            case 'k':
                std::cin >> key;
                if (std::cin.bad()) return 0;
                tree.insert(key);
                break;
            case 'q':
                std::cin >> fst >> snd;
                if (std::cin.bad()) return 0;
                //range_query(tree, fst, snd);
                break;
            default:
                std::cout << "unknown command\n";
        }
    }

    tree.dump_graph();
}
