#ifndef INCLUDE_RANGE_QUERY_HPP
#define INCLUDE_RANGE_QUERY_HPP

#include "iterator.hpp"
#include <cstdlib>

namespace RB_tree {

template <typename C>
std::size_t distance(const C & /*s*/, typename C::iterator start, typename C::iterator fin) {
    int count = 0;
    while (start != fin) {
        ++count;
        ++start;
    }
    return count;
}

template <typename C, typename KeyT> int range_query(const C &s, KeyT fst, KeyT snd) {
    using itt = typename C::iterator;
    itt start = s.lower_bound(fst);
    itt fin = s.upper_bound(snd);
    return distance(s, start, fin);
}

} // namespace RB_tree

#endif // INCLUDE_RANGE_QUERY_HPP