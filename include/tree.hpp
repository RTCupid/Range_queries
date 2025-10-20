#ifndef INCLUDE_TREE_HPP
#define INCLUDE_TREE_HPP

#include <cassert>
#include <fstream>
#include <functional>
#include <iostream>
#include <stack>

#include "iterator.hpp"
#include "node.hpp"

namespace RB_tree {

const std::string dump_file_gv = "../dump/graph_dump.gv";   // FIXME delete hardcode
const std::string dump_file_svg = "../dump/graph_dump.svg"; //

template <typename KeyT, typename Compare = std::less<KeyT>> class Tree final {
  private:
    Node<KeyT> *nil_;
    Node<KeyT> *root_;
    Compare comp_;

  public:
    Tree() : nil_(new Node<KeyT>()), root_(nil_) {}

    ~Tree() {
        std::cout << "destructor\n";
        destroy_subtree(root_);
        delete nil_;
    }

    Tree(const Tree &) = delete;
    Tree(Tree &&) = default;
    Tree &operator=(const Tree &) = delete;
    Tree &operator=(Tree &&) = default;

    void dump_graph() const;

    bool insert(const KeyT &key) {
        auto *new_node = new Node<KeyT>(key);

        Node<KeyT> *parent = nil_;
        auto current = root_;

        if (!tree_descent(current, parent, key))
            return false;

        new_node->set_parent(parent);

        if (parent->is_nil())
            root_ = new_node;
        else if (comp_(key, parent->get_key()))
            parent->set_left(new_node);
        else
            parent->set_right(new_node);

        new_node->set_left(nil_);
        new_node->set_right(nil_);

        fix_insert(new_node);

        return true;
    }

    using iterator = RB_tree::Iterator<KeyT>;

    iterator lower_bound(const KeyT &key) const {
        const Node<KeyT> *candidate = nil_;
        const Node<KeyT> *current = root_;

        while (!current->is_nil()) {
            if (comp_(current->get_key(), key)) {
                current = current->get_right();
            } else {
                candidate = current;
                current = current->get_left();
            }
        }
        return iterator(candidate);
    }

    iterator upper_bound(const KeyT &key) const {
        const Node<KeyT> *candidate = nil_;
        const Node<KeyT> *current = root_;

        while (!current->is_nil()) {
            if (comp_(key, current->get_key())) {
                candidate = current;
                current = current->get_left();
            } else {
                current = current->get_right();
            }
        }
        return iterator(candidate);
    }

    iterator end() const { return iterator(nil_); }

  private:
    bool tree_descent(Node<KeyT> *&current, Node<KeyT> *&parent, const KeyT &key) const {
        while (!current->is_nil()) {
            parent = current;

            if (comp_(key, current->get_key()))
                current = current->get_left();
            else if (comp_(current->get_key(), key))
                current = current->get_right();
            else
                return false;
        }
        return true;
    }

    void destroy_subtree(Node<KeyT> *node) {
        std::cout << "start destroy tree\n";
        if (!node || node->is_nil())
            return;

        std::stack<Node<KeyT> *> stack;
        Node<KeyT> *current = node;
        Node<KeyT> *last_visited = nullptr;

        while (current || !stack.empty()) {
            if (current) {
                stack.push(current);
                current = current->get_left();
            } else {
                Node<KeyT> *peek = stack.top();

                if (peek->get_right() && !peek->get_right()->is_nil() &&
                    peek->get_right() != last_visited) {
                    current = peek->get_right();
                } else {
                    stack.pop();
                    delete peek;
                    last_visited = peek;
                }
            }
        }
    }

    void fix_insert(Node<KeyT> *new_node) {
        assert(new_node && !new_node->is_nil());

        while (new_node->get_parent() &&
               Node<KeyT>::try_get_color(new_node->get_parent()) == Color::red) {
            auto grand_father = new_node->get_parent()->get_parent();
            if (new_node->get_parent() == grand_father->get_left()) {
                auto uncle = grand_father->get_right();

                if (Node<KeyT>::try_get_color(uncle) == Color::red) {
                    new_node->get_parent()->color_ = Color::black;
                    if (uncle)
                        uncle->color_ = Color::black;

                    grand_father->color_ = Color::red;
                    new_node = grand_father;
                } else {
                    if (new_node == new_node->get_parent()->get_right()) {
                        new_node = new_node->get_parent();
                        left_rotate(new_node);
                    }

                    new_node->get_parent()->color_ = Color::black;

                    auto grand_father = new_node->get_parent()->get_parent();
                    grand_father->color_ = Color::red;
                    right_rotate(grand_father);
                }
            } else {
                auto uncle = grand_father->get_left();

                if (Node<KeyT>::try_get_color(uncle) == Color::red) {
                    new_node->get_parent()->color_ = Color::black;
                    if (uncle)
                        uncle->color_ = Color::black;

                    grand_father->color_ = Color::red;
                    new_node = grand_father;
                } else {
                    if (new_node == new_node->get_parent()->get_left()) {
                        new_node = new_node->get_parent();
                        right_rotate(new_node);
                    }

                    new_node->get_parent()->color_ = Color::black;
                    grand_father->color_ = Color::red;
                    left_rotate(grand_father);
                }
            }
        }

        if (root_)
            root_->color_ = Color::black;
    }

    void right_rotate(Node<KeyT> *node) { // FIXME "двоится в глазах" Постараться убрать копипасту
        assert(node);
        assert(node->get_left());

        auto left_node = node->get_left();
        node->set_left(left_node->get_right());

        if (!left_node->get_right()->is_nil())
            left_node->get_right()->set_parent(node);

        left_node->set_parent(node->get_parent());

        if (node->get_parent()->is_nil())
            root_ = left_node;
        else if (node == node->get_parent()->get_left())
            node->get_parent()->set_left(left_node);
        else
            node->get_parent()->set_right(left_node);

        left_node->set_right(node);
        node->set_parent(left_node);
    }

    void left_rotate(Node<KeyT> *node) {
        assert(node);
        assert(node->get_right());

        auto right_node = node->get_right();
        node->set_right(right_node->get_left());

        if (!right_node->get_left()->is_nil())
            right_node->get_left()->set_parent(node);

        right_node->set_parent(node->get_parent());

        if (node->get_parent()->is_nil())
            root_ = right_node;
        else if (node == node->get_parent()->get_right())
            node->get_parent()->set_right(right_node);
        else
            node->get_parent()->set_left(right_node);

        right_node->set_left(node);
        node->set_parent(right_node);
    }

    void dump_graph_list_nodes(const Node<KeyT> *node, std::ofstream &gv) const;
    void dump_graph_connect_nodes(const Node<KeyT> *node, std::ofstream &gv) const;
};

template <typename KeyT, typename Compare> void Tree<KeyT, Compare>::dump_graph() const {
    std::ofstream gv(dump_file_gv);
    if (!gv)
        throw std::runtime_error("open gv file - error");

    gv << "digraph G {\n"
       << "    rankdir=TB;\n"
       << "    node [style=filled, fontname=\"Helvetica\", fontcolor=darkblue, "
          "fillcolor=peachpuff, color=\"#252A34\", penwidth=2.5];\n"
       << "    bgcolor=\"lemonchiffon\";\n\n";

    dump_graph_list_nodes(root_, gv);
    gv << "\n";
    dump_graph_connect_nodes(root_, gv);

    gv << "}\n";
    gv.close();

    std::system(("dot " + dump_file_gv + " -Tsvg -o " + dump_file_svg).c_str());
}

template <typename KeyT, typename Compare>
void Tree<KeyT, Compare>::dump_graph_list_nodes(const Node<KeyT> *node, std::ofstream &gv) const {
    if (!node)
        return;

    std::string fillcolor = node->is_red() ? "salmon" : "lightgray";

    gv << "    node_" << node << "[shape=Mrecord; style=filled; fillcolor=" << fillcolor
       << "; color=\"#000000\"; "
          "fontcolor=\"#000000\"; "
       << "label=\"{ node_" << node << " | key: " << node->get_key()
       << " | parent: " << node->get_parent() << "| { left: " << node->get_left()
       << " | right: " << node->get_right() << " } }\"" << "];\n";

    if (!node->get_left()->is_nil())
        dump_graph_list_nodes(node->get_left(), gv);
    if (!node->get_right()->is_nil())
        dump_graph_list_nodes(node->get_right(), gv);
}

template <typename KeyT, typename Compare>
void Tree<KeyT, Compare>::dump_graph_connect_nodes(const Node<KeyT> *node,
                                                   std::ofstream &gv) const {
    if (!node)
        return;

    if (!node->get_left()->is_nil())
        gv << "    node_" << node << " -> node_" << node->get_left() << ";\n";
    else {
        gv << "    nil_" << node << "_L"
           << " [shape=Mrecord; style=filled; fillcolor=lightgray; color=\"#000000\"; "
              "fontcolor=\"#000000\"; label=\"nil_node\"];\n";
        gv << "    node_" << node << " -> nil_" << node << "_L;\n";
    }
    if (!node->get_right()->is_nil())
        gv << "    node_" << node << " -> node_" << node->get_right() << ";\n";
    else {
        gv << "    nil_" << node << "_R"
           << " [shape=Mrecord; style=filled; fillcolor=lightgray; color=\"#000000\"; "
              "fontcolor=\"#000000\"; label=\"nil_node\"];\n";
        gv << "    node_" << node << " -> nil_" << node << "_R;\n";
    }

    if (!node->get_left()->is_nil())
        dump_graph_connect_nodes(node->get_left(), gv);
    if (!node->get_right()->is_nil())
        dump_graph_connect_nodes(node->get_right(), gv);
}

} // namespace RB_tree

#endif // INCLUDE_TREE_HPP
