#ifndef INCLUDE_TREE_HPP
#define INCLUDE_TREE_HPP

#include <cstddef>
#include <functional>
#include <memory>
#include "node.hpp"

namespace RB_tree {

template <typename KeyT, typename Compare = std::less<KeyT>>
class Tree final {
private:
    std::unique_ptr<Node<KeyT>> root_{nullptr};
    std::unique_ptr<Node<KeyT>> nil_{nullptr};

public:
    Tree() { 
        init_nil();
        // TODO build tree
    }
    ~Tree() = default;
    Tree(const Tree&) = delete;
    Tree& operator=(const Tree&) = delete;
    Tree(Tree&&) = default;
    Tree& operator=(Tree&&) = default;        

    
    
private:
    void init_nil() {
        nil_ = std::make_unique<Node<KeyT>>(KeyT{});
        nil_->set_color(Color::black);
        nil_->set_parent(nil_.get());
        nil_->set_left(std::unique_ptr<Node<KeyT>>(nullptr));
        nil_->set_right(std::unique_ptr<Node<KeyT>>(nullptr));
    }

    [[nodiscard]] bool is_nil (const Node<KeyT>* node) const noexcept { return node == nil_.get(); }
};


} // namespace RB_tree

#endif