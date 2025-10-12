#ifndef INCLUDE_TREE_HPP
#define INCLUDE_TREE_HPP

#include <cstddef>
#include <functional>
#include <memory>
#include "node.hpp"

namespace RB_tree {

template <typename Key_T, typename Compare = std::less<Key_T>>
class tree final {
private:
    Node_base* root_{nullptr};
    Node_base* nil_{nullptr};
    std::size_t size{0};
    Compare    comp_{};

public:
    tree() { init_nil(); }
    ~tree() {destroy_tree(); destroy_nil();}

private:
    void init_nil() {
        nil_ = new Node_base(Color::black);
        nil_->set_parent(nil_); 
        nil_->set_left  (nil_, nil_);
        nil_->set_right (nil_, nil_);
        root_ = nil_;
    }

    void destroy_nil() {
        delete nil_;
    }

    Node* create_node(const Key& key) {
        Node* node = new Node(key, Color::red);
        return node;
    }

    void destroy_node(Node_base* node) noexcept {
        delete node;
    }

    void destroy_tree() {
        destroy_tree_recursively(root_);
        root_ = nil_;
        size_ = 0;
    }

    void destroy_tree_recursively(Node_base* node) {
        if (node->is_nil()) return;

        destroy_tree_recursively(node->get_left());
        destroy_tree_recursively(node->get_right());

        destroy_node(node);
    }
};


} // namespace RB_tree

#endif