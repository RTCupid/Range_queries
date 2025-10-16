#ifndef INCLUDE_TREE_HPP
#define INCLUDE_TREE_HPP

#include <cassert>
#include <fstream>
#include <functional>
#include <iostream>

#include "node.hpp"

namespace RB_tree {

const std::string dump_file_gv = "../dump/graph_dump.gv";
const std::string dump_file_svg = "../dump/graph_dump.svg";

template <typename KeyT, typename Compare = std::less<KeyT>> class Tree final {
  private:
    Node<KeyT> *root_{nullptr};
    Compare comp_;

  public:
    Tree() {
        root_ = nullptr;
    }

    ~Tree() {
        destroy_subtree(root_);
    }

    Tree(const Tree &) = delete;
    Tree &operator=(const Tree &) = delete;
    Tree(Tree &&) = default;
    Tree &operator=(Tree &&) = default;

    void debug_set_root(Node<KeyT> *new_root) noexcept {
        root_ = new_root;
    } // NOTE - FOR DEBUG GRAPH DUMP

    void dump_graph() const;

    void insert(const KeyT &key) {
        auto *new_node = new Node<KeyT>(key);

        Node<KeyT> *parent = nullptr;
        auto current = root_;

        while (current) {
            parent = current;
            auto curr_key = current->get_key();

            if (key < curr_key)
                current = current->get_left();
            else if (key > curr_key)
                current = current->get_right();
            else
                return;
        }

        new_node->set_parent(parent);

        if (parent == nullptr)
            root_ = new_node;
        else if (key < parent->get_key())
            parent->set_left(new_node);
        else
            parent->set_right(new_node);

        fix_insert(new_node);
    }

  private:

    void destroy_subtree(Node<KeyT> *node) {
        if (!node)
            return;

        destroy_subtree(node->get_left());
        destroy_subtree(node->get_right());
        delete node;
    }
    void fix_insert(Node<KeyT> *new_node) {
        assert(new_node);

        while (new_node->get_parent() && new_node->get_parent()->color_ == Color::red) {
            if (new_node->get_parent() == new_node->get_parent()->get_parent()->get_left()) {
                auto uncle = new_node->get_parent()->get_parent()->get_right();

                if (uncle->color_ == Color::red) {
                    new_node->get_parent()->color_ = Color::black;

                    auto grand_father = new_node->get_parent()->get_parent();
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
                auto uncle = new_node->get_parent()->get_parent()->get_left();

                if (uncle->color_ == Color::red) {
                    new_node->get_parent()->color_ = Color::black;

                    auto grand_father = new_node->get_parent()->get_parent();
                    grand_father->color_ = Color::red;
                    new_node = grand_father;
                } else {
                    if (new_node == new_node->get_parent()->get_left()) {
                        new_node = new_node->get_parent();
                        right_rotate(new_node);
                    }

                    auto grand_father = new_node->get_parent()->get_parent();
                    grand_father->color_ = Color::red;
                    left_rotate(grand_father);
                }
            }
        }

        root_->color_ = Color::black;
    }

    void right_rotate(Node<KeyT> *node) {
        assert(node);
        assert(node->get_left());

        auto left_node = node->get_left();
        node->set_left(left_node->get_right());

        if (left_node->get_right())
            left_node->get_right()->set_parent(node);

        left_node->set_parent(node->get_parent());

        if (!node->get_parent())
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

        if (right_node->get_left())
            right_node->get_left()->set_parent(node);

        right_node->set_parent(node->get_parent());

        if (!node->get_parent())
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

    if (node->get_left())
        dump_graph_list_nodes(node->get_left(), gv);
    if (node->get_right())
        dump_graph_list_nodes(node->get_right(), gv);
}

template <typename KeyT, typename Compare>
void Tree<KeyT, Compare>::dump_graph_connect_nodes(const Node<KeyT> *node,
                                                   std::ofstream &gv) const {
    if (!node)
        return;

    if (node->get_left())
        gv << "    node_" << node << " -> node_" << node->get_left() << ";\n";
    else {
        gv << "    nil_" << node << "_L"
           << " [shape=Mrecord; style=filled; fillcolor=lightgray; color=\"#000000\"; "
              "fontcolor=\"#000000\"; label=\"nil_node\"];\n";
        gv << "    node_" << node << " -> nil_" << node << "_L;\n";
    }
    if (node->get_right())
        gv << "    node_" << node << " -> node_" << node->get_right() << ";\n";
    else {
        gv << "    nil_" << node << "_R"
           << " [shape=Mrecord; style=filled; fillcolor=lightgray; color=\"#000000\"; "
              "fontcolor=\"#000000\"; label=\"nil_node\"];\n";
        gv << "    node_" << node << " -> nil_" << node << "_R;\n";
    }

    if (node->get_left())
        dump_graph_connect_nodes(node->get_left(), gv);
    if (node->get_right())
        dump_graph_connect_nodes(node->get_right(), gv);
}

} // namespace RB_tree

#endif // INCLUDE_TREE_HPP
