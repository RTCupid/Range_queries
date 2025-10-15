#ifndef INCLUDE_TREE_HPP
#define INCLUDE_TREE_HPP

#include "node.hpp"
#include <cstddef>
#include <fstream>
#include <functional>
#include <memory>

namespace RB_tree {

const std::string dump_file_gv = "../dump/graph_dump.gv";
const std::string dump_file_svg = "../dump/graph_dump.svg";

template <typename KeyT, typename Compare = std::less<KeyT>> class Tree final {
  private:
    std::unique_ptr<Node<KeyT>> root_{nullptr};
    Compare comp_;

  public:
    Tree() = default;
    ~Tree() = default;
    Tree(const Tree &) = delete;
    Tree &operator=(const Tree &) = delete;
    Tree(Tree &&) = default;
    Tree &operator=(Tree &&) = default;

    std::unique_ptr<Node<KeyT>> &get_root_ref() noexcept { // TODO ___DELETE_IT___
        return root_;                                      // NOTE __THIS_IS_TEMP_METHOD__
    } // ANCHOR - FOR DEBUG GRAPH DUMP

    void dump_graph() const;

  private:
    [[nodiscard]] bool is_nil(const Node<KeyT> *node) const noexcept { return node == nullptr; }

    void dump_graph_list_nodes(const std::unique_ptr<Node<KeyT>> &node, std::ofstream &gv) const;
    void dump_graph_connect_nodes(const std::unique_ptr<Node<KeyT>> &node, std::ofstream &gv) const;
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
void Tree<KeyT, Compare>::dump_graph_list_nodes(const std::unique_ptr<Node<KeyT>> &node,
                                                std::ofstream &gv) const {
    if (!node)
        return;

    std::string fillcolor = node->is_red() ? "salmon" : "lightgray";

    gv << "node_" << node.get() << "[shape=Mrecord; style=filled; fillcolor=" << fillcolor
       << "; color=\"#000000\"; "
          "fontcolor=\"#000000\"; "
       << "label=\"{ node_" << node.get() << " | key: " << node->get_key()
       << " | parent: " << node->get_parent_ptr() << "| { left: " << node->get_left_ptr()
       << " | right: " << node->get_right_ptr() << " } }\"" << "];\n";

    if (node->get_left())
        dump_graph_list_nodes(node->get_left(), gv);
    if (node->get_right())
        dump_graph_list_nodes(node->get_right(), gv);
}

template <typename KeyT, typename Compare>
void Tree<KeyT, Compare>::dump_graph_connect_nodes(const std::unique_ptr<Node<KeyT>> &node,
                                                   std::ofstream &gv) const {
    if (!node)
        return;

    if (node->get_left())
        gv << "    node_" << node.get() << " -> node_" << node->get_left().get() << ";\n";
    else {
        gv << "    nil_" << node << "_L"
           << " [shape=Mrecord; style=filled; fillcolor=lightgray; color=\"#000000\"; "
              "fontcolor=\"#000000\"; label=\"nil_node\"];\n";
        gv << "    node_" << node << " -> nil_" << node << "_L;\n";
    }
    if (node->get_right())
        gv << "    node_" << node.get() << " -> node_" << node->get_right().get() << ";\n";
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
