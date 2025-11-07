#ifndef INCLUDE_RANGE_QUERY_HPP
#define INCLUDE_RANGE_QUERY_HPP

#include <cstdlib>
#include <iterator>

namespace RB_tree {

template <typename C, typename KeyT>
auto range_query(const C &s, const KeyT &fst, const KeyT &snd) {
    if (!s.key_comp()(fst, snd))
        return 0l;

    auto start = s.lower_bound(fst);

    auto fin = s.upper_bound(snd);

    return std::distance(start, fin);
}

} // namespace RB_tree

#endif // INCLUDE_RANGE_QUERY_HPP
