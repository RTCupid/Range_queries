#ifndef INCLUDE_TREE_HPP
#define INCLUDE_TREE_HPP

#include "iterator.hpp"
#include "node.hpp"
#include <cassert>
#include <fstream>
#include <functional>
#include <iostream>

namespace RB_tree {

const std::string dump_file_gv = "../dump/graph_dump.gv";
const std::string dump_file_svg = "../dump/graph_dump.svg";

enum class CompResult { less, equal, greater };

template <typename T, typename Compare> CompResult compare(const T &first, const T &second) {
    if (Compare{}(first, second))
        return CompResult::less;
    else if (Compare{}(second, first))
        return CompResult::greater;

    return CompResult::equal;
}

template <typename KeyT, typename Compare = std::less<KeyT>> class Tree final {
  private:
    Node<KeyT> *nil_;
    Node<KeyT> *root_;
    Compare comp_;

  public:
    Tree() : nil_(new Node<KeyT>()), root_(nil_) {}

    ~Tree() {
        destroy_subtree(root_);
        delete nil_;
    }

    Tree(const Tree &) = delete;
    Tree(Tree &&) = default;
    Tree &operator=(const Tree &) = delete;
    Tree &operator=(Tree &&) = default;

    void dump_graph() const;

    void insert(const KeyT &key) {
        auto *new_node = new Node<KeyT>(key);

        Node<KeyT> *parent = nil_;
        auto current = root_;

        while (!current->is_nil()) {
            parent = current;

            switch (compare<KeyT, Compare>(key, current->get_key())) {
            case CompResult::less:
                current = current->get_left();
                break;
            case CompResult::greater:
                current = current->get_right();
                break;
            default:
                return;
            }
        }

        new_node->set_parent(parent);

        if (parent->is_nil())
            root_ = new_node;
        else if (compare<KeyT, Compare>(key, parent->get_key()) == CompResult::less)
            parent->set_left(new_node);
        else
            parent->set_right(new_node);

        new_node->set_left(nil_);
        new_node->set_right(nil_);

        fix_insert(new_node);
    }

    using iterator = RB_tree::Iterator<KeyT>;

    iterator lower_bound(const KeyT &key) const {
        const Node<KeyT> *candidate = nil_;
        const Node<KeyT> *current = root_;

        while (!current->is_nil()) {
            if (current->get_key() >= key) {
                candidate = current;
                current = current->get_left();
            } else {
                current = current->get_right();
            }
        }
        return iterator(candidate);
    }

    iterator upper_bound(const KeyT &key) const {
        const Node<KeyT> *candidate = nil_;
        const Node<KeyT> *current = root_;

        while (!current->is_nil()) {
            if (current->get_key() > key) {
                candidate = current;
                current = current->get_left();
            } else {
                current = current->get_right();
            }
        }
        return iterator(candidate);
    }

  private:
    void destroy_subtree(Node<KeyT> *node) {
        if (!node || node->is_nil())
            return;

        destroy_subtree(node->get_left());
        destroy_subtree(node->get_right());
        delete node;
    }
    void fix_insert(Node<KeyT> *new_node) {
        assert(new_node && !new_node->is_nil());

        auto color_of = [](const Node<KeyT> *n) noexcept { return n ? n->color_ : Color::black; };

        while (new_node->get_parent() && color_of(new_node->get_parent()) == Color::red) {
            auto grand_father = new_node->get_parent()->get_parent();
            if (new_node->get_parent() == grand_father->get_left()) {
                auto uncle = grand_father->get_right();

                if (color_of(uncle) == Color::red) {
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

                if (color_of(uncle) == Color::red) {
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

    void right_rotate(Node<KeyT> *node) {
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
