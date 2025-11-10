#include "range_query.hpp"
#include "tree.hpp"
#include <chrono>
#include <iostream>
#include <set>

using namespace RB_tree;

static void driver();

int main() { driver(); }

static void driver() {

#ifdef STD_SET_RUN
    std::set<int> tree;
#else
    Tree<int> tree;
#endif

    char query;

#ifdef TIMING_RUN
    double msf = 0;
    using clock = std::chrono::steady_clock;
#endif

    while (std::cin >> query) {
        int key;
        int fst, snd;

        switch (query) {
        case 'k':
            if (std::cin >> key) {
                tree.insert(key);
            } else {
                std::cerr << "Error: invalid input for 'k' command. Expected integer.\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            break;
        case 'q':
            if (std::cin >> fst >> snd) {
                std::size_t result = 0;
#ifdef TIMING_RUN
                auto t0 = clock::now();
                result = range_query(tree, fst, snd);
                asm volatile("" : : "r"(result));
                auto t1 = clock::now();
                msf += std::chrono::duration<double, std::milli>(t1 - t0).count();
#else
                std::cout << result << ' ';
#endif
            } else {
                std::cerr << "Error: invalid input for 'q' command. Expected two integers.\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            break;
        default:
            std::cerr << "unknown command\n";
        }
    }

#ifdef TIMING_RUN
    std::cout << "Total time: " << msf << " ms\n";
#endif
    std::cout << std::endl;
}
