#ifndef INCLUDE_RANGE_QUERY_HPP
#define INCLUDE_RANGE_QUERY_HPP

#include <cstdlib>

namespace RB_tree {

template <typename It>
std::size_t distance(It start, It fin) {
    int count = 0;

    while (start != fin) {
        ++count;
        ++start;
    }
    return count;
}

template <typename C, typename KeyT> int range_query(const C &s, KeyT fst, KeyT snd) {
    if (fst > snd)
        return 0;

    auto start = s.lower_bound(fst);
    auto fin = s.upper_bound(snd);
    auto end = s.end();

    if (start == end)
        return 0;

    return distance(start, fin);
}

} // namespace RB_tree

#endif // INCLUDE_RANGE_QUERY_HPP
