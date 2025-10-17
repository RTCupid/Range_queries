#ifndef INCLUDE_INTERATOR_HPP
#define INCLUDE_INTERATOR_HPP

#include "node.hpp"
#include <iterator>

namespace RB_tree {

template <typename KeyT> class Iterator final {
  private:
    const Node<KeyT> *node_;

  public:
    explicit Iterator(const Node<KeyT> *node) noexcept : node_{node} {}

    const KeyT &operator*() const {
        assert(node_);
        return node_->get_key();
    }

    const KeyT *operator->() const {
        assert(node_);
        return &node_->get_key();
    }

    Iterator &operator++() {
        if (node_->get_right()) {
            node_ = node_->get_right();
            while (node_->get_left()) {
                node_ = node_->get_left();
            }
        } else {
            auto parent = node_->get_parent();
            while (parent && parent->get_right() == node_) {
                node_ = parent;
                parent = node_->get_parent();
            }
            node_ = parent;
        }
        return *this;
    }

    Iterator &operator--() {
        if (node_->get_left()) {
            node_ = node_->get_left();
            while (node_->get_right()) {
                node_ = node_->get_right();
            }
        } else {
            auto parent = node_->get_parent();
            while (parent && parent->get_left() == node_) {
                node_ = parent;
                parent = node_->get_parent();
            }
            node_ = parent;
        }
        return *this;
    }

    bool operator==(const Iterator &it) const { return node_ == it.node_; }
    bool operator!=(const Iterator &it) const { return !(*this == it); }
};

} // namespace RB_tree

#endif // INCLUDE_INTERATOR_HPP