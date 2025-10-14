#ifndef INCLUDE_NODE_HPP
#define INCLUDE_NODE_HPP

#include <memory>

namespace RB_tree {

enum class Color { red, black };

template <typename KeyT> class Node {
  private:
    Node *parent_{nullptr};
    std::unique_ptr<Node> left_{nullptr};
    std::unique_ptr<Node> right_{nullptr};
    Color color_{Color::red};
    KeyT key_{0};

  public:
    Node() = default;
    Node(const Node &) = delete;
    Node &operator=(const Node &) = delete;
    Node(Node &&) = default;
    Node &operator=(Node &&) = default;
    ~Node() = default;

    explicit Node(const KeyT &key, Color color = Color::red) : color_{color}, key_{key} {}
    explicit Node(KeyT &&key, Color color = Color::red) : color_(color), key_(std::move(key)) {}

    [[nodiscard]] bool is_red() const noexcept { return color_ == Color::red; }
    [[nodiscard]] bool is_black() const noexcept { return color_ == Color::black; }

    void set_left(std::unique_ptr<Node> node) noexcept {
        left_ = std::move(node);
        if (left_)
            left_->parent_ = this;
    }
    void set_right(std::unique_ptr<Node> node) noexcept {
        right_ = std::move(node);
        if (right_)
            right_->parent_ = this;
    }
    void set_parent(Node *node) noexcept { parent_ = node; }

    [[nodiscard]] Node *get_parent_ptr() noexcept { return parent_; }
    [[nodiscard]] Node *get_left_ptr() noexcept { return left_.get(); }
    [[nodiscard]] Node *get_right_ptr() noexcept { return right_.get(); }

    [[nodiscard]] const Node *get_parent_ptr() const noexcept { return parent_; }
    [[nodiscard]] const Node *get_left_ptr() const noexcept { return left_.get(); }
    [[nodiscard]] const Node *get_right_ptr() const noexcept { return right_.get(); }

    void clear_left() noexcept { left_.reset(); }
    void clear_right() noexcept { right_.reset(); }
    void clear_parent() noexcept { parent_ = nullptr; }

    [[nodiscard]] Color get_color() const noexcept { return color_; }
    void set_color(Color color) noexcept { color_ = color; }

    [[nodiscard]] const KeyT &get_key() const noexcept { return key_; }
    void set_key(const KeyT &key) noexcept { key_ = key; }

  private:
};

} // namespace RB_tree

#endif // INCLUDE_NODE_HPP
