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
    explicit Node_base(Color color = Color::red) noexcept : color_{color} {}

    /*____________creation_of_sentinel____________*/
    void create_nil() noexcept {
        parent_ = left_ = right_ = this;
        color_ = Color::black;
    }

    virtual ~Node_base() = default;
};

template<typename Key_T>
class Node : Node_base {
private:
    Key_T key_;

public:
    explicit Node(const Key_T& key) : Node_base(), key_{key} {}
    explicit Node(const Key_T& key, Color color) : Node_base(color), key_{key} {}
};

} // namespace RB_tre 

#endif // INCLUDE_NODE_HPP