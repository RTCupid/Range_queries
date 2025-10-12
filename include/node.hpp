#ifndef INCLUDE_NODE_HPP
#define INCLUDE_NODE_HPP

namespace RB_tree {

enum class Color { red = 0, black = 1};

class Node_base {
protected:
    Node_base* parent_{nullptr};
    Node_base* left_{nullptr};
    Node_base* right_{nullptr};
    Color color_{Color::red};

public:
    Node_base() = default;
    explicit Node_base(Color color) noexcept : color_{color} {}
    virtual ~Node_base() = default;

    Node_base*       get_parent()       noexcept { return parent_; }
    const Node_base* get_parent() const noexcept { return parent_; }
    Node_base*       get_left()         noexcept { return left_; }
    const Node_base* get_left()   const noexcept { return left_; }
    Node_base*       get_right()        noexcept { return right_; }
    const Node_base* get_right()  const noexcept { return right_; }

    Color get_color() const noexcept { return color_; }
    void  set_color(Color color) noexcept { color_ = color; }

    [[nodiscard]] bool is_red  () const noexcept { return color_ == Color::red;   }
    [[nodiscard]] bool is_black() const noexcept { return color_ == Color::black; }
    [[nodiscard]] bool is_nil  (const Node_base* node) const noexcept { return this == node; }

    void set_left  (Node_base* node) noexcept { left_ = node; }
    void set_right (Node_base* node) noexcept { right_ = node; }
    void set_parent(Node_base* node) noexcept { parent_ = node; }
};

template<typename Key_T>
class Node : public Node_base {
private:
    Key_T key_;

public:
    explicit Node(const Key_T& key, Color color = Color::red) : Node_base{color}, key_{key} {}
    explicit Node(Key_T&& key, Color color = Color::red) : Node_base(color), key_(std::move(key)) {}
};

} // namespace RB_tree 

#endif // INCLUDE_NODE_HPP
