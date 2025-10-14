#ifndef INCLUDE_TREE_HPP
#define INCLUDE_TREE_HPP

#include "node.hpp"
#include <cstddef>
#include <functional>
#include <memory>

namespace RB_tree {

template <typename Key_T, typename Compare = std::less<Key_T>> class Tree final {
  private:
    std::unique_ptr<Node<Key_T>> root_{nullptr};
    std::unique_ptr<Node<Key_T>> nil_{nullptr};

  public:
    Tree() {
        init_nil();
        // TODO build tree
    }
    ~Tree() = default;
    tree(const tree &) = delete;
    tree &operator=(const tree &) = delete;
    tree(tree &&) = default;
    tree &operator=(tree &&) = default;

  private:
    void init_nil() {
        nil_ = std::make_unique<Node<Key_T>>(Key_T{});
        nil_->set_color(Color::black);
    }

    [[nodiscard]] bool is_nil(const Node<Key_T> *node) const noexcept { return node == nil_.get(); }
};

} // namespace RB_tree

#endif