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

    // #ifndef RB_TREE_LOG_RUN
    return std::distance(start, fin);
    // #else
    // return s.log_distance(start, fin);
    // #endif
}

} // namespace RB_tree

#endif // INCLUDE_RANGE_QUERY_HPP
