#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <random>
#include <algorithm>
#include <functional>

int main() {
    const int total_commands = 15;
    const int max_key = 1000;
    const int max_queries = total_commands / 3;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> key_dist(1, max_key);
    std::uniform_int_distribution<int> query_dist(1, max_key);

    std::ofstream data_file("../tests/end_to_end/data/0.dat");
    std::ofstream answ_file("../tests/end_to_end/answ/0.res");

    if (!data_file.is_open() || !answ_file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    std::set<int> tree;
    std::vector<int> keys;

    int query_count = 0;
    for (int i = 0; i < total_commands; ++i) {
        bool is_query = (query_count < max_queries) && (i > 0) && (gen() % 3 == 0);

        if (!is_query) {
            int key = key_dist(gen);
            if (tree.insert(key).second) {
                keys.push_back(key);
                data_file << "k " << key << "\n";
            } else {
                --i;
            }
        } else {
            int left = query_dist(gen);
            int right = query_dist(gen);
            if (left > right) std::swap(left, right);

            data_file << "q " << left << " " << right << "\n";

            int count = 0;
            for (int k : keys) {
                if (k >= left && k <= right) {
                    ++count;
                }
            }

            answ_file << count << "\n";
            ++query_count;
        }
    }

    data_file.close();
    answ_file.close();

    std::cout << "Generated " << total_commands << " commands (" << query_count << " queries)\n";
    std::cout << "Input saved to ./data\n";
    std::cout << "Output saved to ./answ\n";

    return 0;
}
