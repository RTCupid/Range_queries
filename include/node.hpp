#ifndef INCLUDE_NODE_HPP
#define INCLUDE_NODE_HPP

#include <cassert>
#include <utility>

namespace RB_tree {

enum class Color : bool { red, black };

template <typename KeyT> class Node {
  private:
    Node *parent_{nullptr};
    Node *left_{nullptr};
    Node *right_{nullptr};
    KeyT key_;

  public:
    Color color_{Color::red};

    Node(const Node &) = delete;
    Node(Node &&) = default;
    Node &operator=(const Node &) = delete;
    Node &operator=(Node &&) = default;
    ~Node() = default;

    /// constructor for nil-sentinel
    Node() : parent_(this), left_(this), right_(this), key_(0), color_(Color::black) {}

    explicit Node(const KeyT &key, Color color = Color::red) : key_(key), color_(color) {}
    explicit Node(KeyT &&key, Color color = Color::red) : key_(std::move(key)), color_(color) {}

    [[nodiscard]] bool is_red() const noexcept { return color_ == Color::red; }
    [[nodiscard]] bool is_black() const noexcept { return color_ == Color::black; }

    void set_left(Node *node) noexcept { left_ = node; }
    void set_right(Node *node) noexcept { right_ = node; }

    void set_parent(Node *node) noexcept { parent_ = node; }

    [[nodiscard]] Node *get_parent() noexcept { return parent_; }
    [[nodiscard]] Node *get_left() noexcept { return left_; }
    [[nodiscard]] Node *get_right() noexcept { return right_; }

    [[nodiscard]] const Node *get_parent() const noexcept { return parent_; }
    [[nodiscard]] const Node *get_left() const noexcept { return left_; }
    [[nodiscard]] const Node *get_right() const noexcept { return right_; }

    [[nodiscard]] const KeyT &get_key() const { return key_; }

    static Color try_get_color(const Node *n) noexcept {
        return n ? n->color_ : Color::black;
    };

    bool is_nil() const noexcept { return this == parent_; }
};

} // namespace RB_tree

#endif // INCLUDE_NODE_HPP
