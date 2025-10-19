#ifndef INCLUDE_RANGE_QUERY_HPP
#define INCLUDE_RANGE_QUERY_HPP

#include <cstdlib>

namespace RB_tree {

template <typename C>
std::size_t distance(const C &s, typename C::iterator start, typename C::iterator fin) {
    int count = 0;
    auto end = s.end();

    while (start != fin && start != end) {
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

    return distance(s, start, fin);
}

} // namespace RB_tree

#endif // INCLUDE_RANGE_QUERY_HPP
