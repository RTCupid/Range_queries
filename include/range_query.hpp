#ifndef INCLUDE_RANGE_QUERY_HPP
#define INCLUDE_RANGE_QUERY_HPP

#include <cstdlib>
#include <iterator>

namespace RB_tree {

template <typename It>
typename std::iterator_traits<It>::difference_type my_distance(It start, It fin) {
    int count = 0;

    while (start != fin) {
        ++count;
        ++start;
    }
    return count;
}

template <typename C, typename KeyT>
std::iterator_traits<typename C::iterator>::difference_type range_query(const C &s, const KeyT &fst,
                                                                        const KeyT &snd) {
    auto comp = s.key_comp();
    if (!comp(fst, snd))
        return 0;

    auto start = s.lower_bound(fst);

    auto fin = s.upper_bound(snd);

    return my_distance(start, fin);
}

} // namespace RB_tree

#endif // INCLUDE_RANGE_QUERY_HPP
