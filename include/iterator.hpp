#ifndef INCLUDE_INTERATOR_HPP
#define INCLUDE_INTERATOR_HPP

#include "node.hpp"
#include <utility>

namespace RB_tree {

template <typename KeyT> class Iterator final {
  private:
    const Node<KeyT> *node_{nullptr};

  public:
    using value_type = KeyT;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = const value_type &;
    using pointer = const value_type *;
    using iterator_category = std::bidirectional_iterator_tag;

    Iterator(const Node<KeyT> *node) noexcept : node_{node} {}

    reference operator*() const {
        assert(node_);
        return node_->get_key();
    }

    pointer operator->() const {
        assert(node_);
        return std::addressof(node_->get_key());
    }

    Iterator &operator++() {
        if (!node_->get_right()->is_nil()) {
            node_ = node_->get_right();
            while (!node_->get_left()->is_nil()) {
                node_ = node_->get_left();
            }
        } else {
            auto parent = node_->get_parent();
            while ((!parent->is_nil()) && parent->get_right() == node_) {
                node_ = std::exchange(parent, parent->get_parent());
            }
            node_ = parent;
        }
        return *this;
    }

    Iterator &operator--() {
        if (!node_->get_left()->is_nil()) {
            node_ = node_->get_left();
            while (!node_->get_right()->is_nil()) {
                node_ = node_->get_right();
            }
        } else {
            auto parent = node_->get_parent();
            while ((!parent->is_nil()) && parent->get_left() == node_) {
                node_ = std::exchange(parent, parent->get_parent());
            }
            node_ = parent;
        }
        return *this;
    }

    Iterator operator++(int) {
        auto tmp = *this;
        ++(*this);
        return tmp;
    }
    Iterator operator--(int) {
        auto tmp = *this;
        --(*this);
        return tmp;
    }

    bool operator==(const Iterator &) const = default;

    const Node<KeyT> *get() const noexcept {
        assert(node_);
        return node_;
    }
};

} // namespace RB_tree

#endif // INCLUDE_INTERATOR_HPP
