#include "driver.hpp"
#include "range_query.hpp"
#include "tree.hpp"
#include <chrono>
#include <iostream>
#include <set>

using namespace RB_tree;

void driver() {
#if TIMING_RUN
    using clock = std::chrono::steady_clock;
    auto t0 = clock::now();
#endif

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
#if TIMING_RUN
#if RB_TREE_RUN
                range_query<Tree<int>, int>(tree, fst, snd);
#endif

#if STD_SET_RUN
                range_query<std::set<int>, int>(set, fst, snd);
#endif
#else
#if RB_TREE_RUN
                std::cout << range_query<Tree<int>, int>(tree, fst, snd) << ' ';
#endif

#if STD_SET_RUN
                std::cout << range_query<std::set<int>, int>(set, fst, snd) << ' ';
#endif
#endif
            }
            break;
        default:
            std::cout << "unknown command\n";
        }
    }

#if TIMING_RUN
    auto t1 = clock::now();
    double msf = std::chrono::duration<double, std::milli>(t1 - t0).count();
    std::cout << "Total time: " << msf << " ms";
#endif

    std::cout << std::endl;
}