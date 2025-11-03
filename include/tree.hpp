#ifndef INCLUDE_TREE_HPP
#define INCLUDE_TREE_HPP

#include "iterator.hpp"
#include "node.hpp"
#include <cassert>
#include <filesystem>
#include <fstream>
#include <functional>

struct Dump_paths {
    std::filesystem::path gv;
    std::filesystem::path svg;
};

inline std::filesystem::path default_dump_dir() {
    if (const char *p = std::getenv("DUMP_DIR"); p && *p)
        return std::filesystem::path(p);

    std::error_code ec;
    auto cwd = std::filesystem::current_path(ec);
    if (!ec)
        return cwd / "dump";

    return std::filesystem::temp_directory_path() / "dump";
}

inline Dump_paths make_dump_paths(std::string_view basename = "graph_dump",
                                  std::filesystem::path base = default_dump_dir()) {
    std::filesystem::create_directories(base);
    std::string s(basename);
    return {base / (s + ".gv"), base / (s + ".svg")};
}

namespace RB_tree {

template <typename KeyT, typename Compare = std::less<KeyT>> class Tree final {
  private:
    Node<KeyT> *nil_;
    Node<KeyT> *root_;
    Node<KeyT> *begin_node;
    Compare comp_;

  public:
    Tree() : nil_(new Node<KeyT>()), root_(nil_), begin_node(nil_) {}

    ~Tree() {
        destroy_subtree(root_);
        delete nil_;
    }

    Compare key_comp() const { return comp_; }

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

        if (begin_node->is_nil() || comp_(key, begin_node->get_key())) {
            begin_node = new_node;
        }

        return true;
    }

    using iterator = RB_tree::Iterator<KeyT>;

    iterator begin() { return begin_node; }

    iterator begin() const { return begin_node; }

    iterator end() { return nil_; }

    iterator end() const { return nil_; }

    iterator lower_bound(const KeyT &key) const {
        const Node<KeyT> *candidate = nil_;
        const Node<KeyT> *current = root_;

        while (!current->is_nil()) {
            if (comp_(current->get_key(), key))
                current = current->get_right();
            else
                candidate = std::exchange(current, current->get_left());
        }
        return candidate;
    }

    iterator upper_bound(const KeyT &key) const {
        const Node<KeyT> *candidate = nil_;
        const Node<KeyT> *current = root_;

        while (!current->is_nil()) {
            if (comp_(key, current->get_key()))
                candidate = std::exchange(current, current->get_left());
            else
                current = current->get_right();
        }
        return candidate;
    }

  private:
    bool tree_descent(Node<KeyT> *&current, Node<KeyT> *&parent,
                      const KeyT &key) const { // NOTE comment it
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
        if (!node || node->is_nil())
            return;

        Node<KeyT> *current = node;

        while (current && !current->is_nil()) {
            if (current->get_left() && !current->get_left()->is_nil()) {
                Node<KeyT> *left_child = current->get_left();
                Node<KeyT> *right_child = current->get_right();

                if (right_child && !right_child->is_nil()) {
                    Node<KeyT> *rightmost = left_child;
                    while (rightmost->get_right() && !rightmost->get_right()->is_nil()) {
                        rightmost = rightmost->get_right();
                    }

                    rightmost->set_right(right_child);
                }

                Node<KeyT> *to_delete = current;
                current = left_child;
                delete to_delete;
            } else {
                Node<KeyT> *to_delete = current;
                current = current->get_right();
                delete to_delete;
            }
        }
    }

    void fix_insert(Node<KeyT> *new_node) { // TODO split
        assert(new_node && !new_node->is_nil());

        while (new_node->get_parent() &&
               Node<KeyT>::try_get_color(new_node->get_parent()) == Color::red) {
            auto parent = new_node->get_parent();
            auto grand_parent = parent->get_parent();

            bool parent_is_left = (parent == grand_parent->get_left());

            auto uncle = parent_is_left ? grand_parent->get_right() : grand_parent->get_left();

            if (Node<KeyT>::try_get_color(uncle) == Color::red) {
                new_node->get_parent()->color_ = Color::black;
                if (uncle)
                    uncle->color_ = Color::black;

                grand_parent->color_ = Color::red;
                new_node = grand_parent;
            } else {
                if (parent_is_left && new_node == parent->get_right()) {
                    new_node = parent;
                    left_rotate(new_node);
                    parent = new_node->get_parent();
                } else if (!parent_is_left && new_node == parent->get_left()) {
                    new_node = parent;
                    right_rotate(new_node);
                    parent = new_node->get_parent();
                }

                parent->color_ = Color::black;
                grand_parent->color_ = Color::red;

                if (parent_is_left) {
                    right_rotate(grand_parent);
                } else {
                    left_rotate(grand_parent);
                }
            }
        }

        if (root_)
            root_->color_ = Color::black;
    }

    template <typename GetChild, typename SetChild, typename GetOtherChild, typename SetOtherChild>
    void rotate(Node<KeyT> *node, GetChild get_child, SetChild set_child,
                GetOtherChild get_other_child, SetOtherChild set_other_child) {
        assert(node);
        auto child = get_child(node);
        assert(child && !child->is_nil());

        set_child(node, get_other_child(child));

        if (!get_other_child(child)->is_nil())
            get_other_child(child)->set_parent(node);

        child->set_parent(node->get_parent());

        if (node->get_parent()->is_nil())
            root_ = child;
        else if (node == get_child(node->get_parent()))
            set_child(node->get_parent(), child);
        else
            set_other_child(node->get_parent(), child);

        set_other_child(child, node);
        node->set_parent(child);
    }

    void right_rotate(Node<KeyT> *node) {
        rotate(
            node, [](Node<KeyT> *n) { return n->get_left(); },
            [](Node<KeyT> *n, Node<KeyT> *v) { n->set_left(v); },
            [](Node<KeyT> *n) { return n->get_right(); },
            [](Node<KeyT> *n, Node<KeyT> *v) { n->set_right(v); });
    }

    void left_rotate(Node<KeyT> *node) {
        rotate(
            node, [](Node<KeyT> *n) { return n->get_right(); },
            [](Node<KeyT> *n, Node<KeyT> *v) { n->set_right(v); },
            [](Node<KeyT> *n) { return n->get_left(); },
            [](Node<KeyT> *n, Node<KeyT> *v) { n->set_left(v); });
    }

    void dump_graph_list_nodes(const Node<KeyT> *node, std::ofstream &gv) const;
    void dump_graph_connect_nodes(const Node<KeyT> *node, std::ofstream &gv) const;
};

template <typename KeyT, typename Compare> void Tree<KeyT, Compare>::dump_graph() const {
    const auto paths = make_dump_paths();
    const std::string gv_file = paths.gv.string();
    const std::string svg_file = paths.svg.string();

    std::ofstream gv(gv_file);
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

    std::system(("dot " + gv_file + " -Tsvg -o " + svg_file).c_str());
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
