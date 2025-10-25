#include "range_query.hpp"
#include "tree.hpp"
#include <chrono>
#include <iostream>
#include <set>

using namespace RB_tree;

static void driver();

int main() { driver(); }

static void driver() {

#if RB_TREE_RUN
    Tree<int> tree;
#endif

#if STD_SET_RUN
    std::set<int> set;
#endif

    char query;

#if TIMING_RUN
    using clock = std::chrono::steady_clock;
    auto t0 = clock::now();
#endif

    while (std::cin >> query) {
        int key;
        int fst, snd;

        switch (query) {
        case 'k':
            if (std::cin >> key) {
#if RB_TREE_RUN
                tree.insert(key);
#endif

#if STD_SET_RUN
                set.insert(key);
#endif
            }
            break;
        case 'q':
            if (std::cin >> fst >> snd) {
                std::size_t result = 0;
#if RB_TREE_RUN
                result = range_query(tree, fst, snd);
#endif
#if STD_SET_RUN
                result = range_query(set, fst, snd);
#endif

#if !TIMING_RUN
                std::cout << result << ' ';
#endif
            }
            break;
        default:
            std::cerr << "unknown command\n";
        }
    }

#if TIMING_RUN
    auto t1 = clock::now();
    double msf = std::chrono::duration<double, std::milli>(t1 - t0).count();
    std::cout << "Total time: " << msf << " ms";
#endif

    std::cout << std::endl;
}
