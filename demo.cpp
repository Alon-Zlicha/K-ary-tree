//Alonz1414@gmail.com
#include <iostream>
#include <string>
#include "node.hpp"
#include "tree.hpp"
#include "complex.hpp"


using namespace std;

int main()
{

    Node<double> root_node = Node(1.1);
    Tree<double> tree; // Binary tree that contains doubles.

    tree.add_root(root_node);

    Node<double> n1 = Node(1.2);
    Node<double> n2 = Node(1.3);
    Node<double> n3 = Node(1.4);
    Node<double> n4 = Node(1.5);
    Node<double> n5 = Node(1.6);

    tree.add_sub_node(root_node, n1);
    tree.add_sub_node(root_node, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);
    cout << "Binary Tree- " << endl;
    cout << tree; // Should print the graph using GUI.

    // The tree should look like:
    /**
     *        1.1
     *     /       \
     *    1.2      1.3
     *   /  \      /
     *  1.4  1.5  1.6
     */
    cout << "Pre-Order- " << endl;
    for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node)
    {
        cout << *node << " ";
    } // prints: 1.1, 1.2, 1.4, 1.5, 1.3, 1.6
    cout << endl;
    cout << "Post-Order- " << endl;
    for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node)
    {
        cout << *node << " ";
    } // prints: 1.4, 1.5, 1.2, 1.6, 1.3, 1.1
    cout << endl;
    cout << "In-Order-  " << endl;
    for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node)
    {
        cout << *node << " ";
    } // prints: 1.4, 1.2, 1.5, 1.1, 1.6, 1.3
    cout << endl;
    cout << "BFS- " << endl;
    for (auto node = tree.begin_bfs_scan(); node != tree.end_bfs_scan(); ++node)
    {
        cout << *node << " ";
    } // prints: 1.1, 1.2, 1.3, 1.4, 1.5, 1.6
    cout << endl;
    cout << "DFS- " << endl;
    for (auto node = tree.begin_dfs_scan(); node != tree.end_dfs_scan(); ++node)
    {
        cout << *node << " ";
    } // prints: 1.1, 1.2, 1.4, 1.5, 1.3, 1.6
    cout << endl;
    cout << "Heap- " << endl;
    for (auto node = tree.myHeap(); node != tree.myHeap(); ++node)
    {
        cout << *node << " ";
    } // prints: 1.1, 1.2, 1.4, 1.5, 1.3, 1.6
    cout << endl;
    cout << "***************************************************************************************************************" << endl;
    Node<Complex> c_root_node(Complex(1.1, 1.1));
    Node<Complex> c_n1(Complex(1.2, 1.2));
    Node<Complex> c_n2(Complex(1.3, 1.3));
    Node<Complex> c_n3(Complex(1.4, 1.4));
    Node<Complex> c_n4(Complex(1.5, 1.5));
    Node<Complex> c_n5(Complex(1.6, 1.6));

    Tree<Complex, 3> three_ary_tree; // 3-ary tree.
    three_ary_tree.add_root(c_root_node);
    three_ary_tree.add_sub_node(c_root_node, c_n1);
    three_ary_tree.add_sub_node(c_root_node, c_n2);
    three_ary_tree.add_sub_node(c_root_node, c_n3);
    three_ary_tree.add_sub_node(c_n1, c_n4);
    three_ary_tree.add_sub_node(c_n2, c_n5);
    cout << "3-ary-tree with complex numbers- " << endl;
    cout<<three_ary_tree;
    // The tree should look like:
    /**
     *       root = 1.1
     *     /      |     \
     *    1.2    1.3    1.4
     *   /        |
     *  1.5      1.6
     */
    cout << "BFS- " << endl;
    for (auto node = three_ary_tree.begin_bfs_scan(); node != three_ary_tree.end_bfs_scan(); ++node)
    {
        cout << *node << " ";
    } // prints: 1.1 + 1.1i, 1.2 + 1.2i, 1.3 + 1.3i, 1.4 + 1.4i, 1.5 + 1.5i, 1.6 + 1.6i
    cout << endl;
    cout << "DFS- " << endl;
    for (auto node = three_ary_tree.begin_dfs_scan(); node != three_ary_tree.end_dfs_scan(); ++node)
    {
        cout << *node << " ";
    } // prints: 1.1 + 1.1i, 1.2 + 1.2i, 1.5 + 1.5i, 1.3 + 1.3i, 1.6 + 1.6i, 1.4 + 1.4i
    cout << endl;
    cout << "In-Order- " << endl;
    for (auto node = three_ary_tree.begin_in_order(); node != three_ary_tree.end_in_order(); ++node)
    {
        cout << *node << " ";
    } // Same as DFS prints: 1.1 + 1.1i, 1.2 + 1.2i, 1.5 + 1.5i, 1.3 + 1.3i, 1.6 + 1.6i, 1.4 + 1.4i
    cout << endl;
    cout << "Pre-Order- " << endl;
    for (auto node = three_ary_tree.begin_pre_order(); node != three_ary_tree.end_pre_order(); ++node)
    {
        cout << *node << " ";
    } // Same as DFS prints: 1.1 + 1.1i, 1.2 + 1.2i, 1.5 + 1.5i, 1.3 + 1.3i, 1.6 + 1.6i, 1.4 + 1.4i
    cout << endl;
    cout << "Post-Order- " << endl;
    for (auto node = three_ary_tree.begin_post_order(); node != three_ary_tree.end_post_order(); ++node)
    {
        cout << *node << " ";
    } // Same as DFS prints: 1.1 + 1.1i, 1.2 + 1.2i, 1.5 + 1.5i, 1.3 + 1.3i, 1.6 + 1.6i, 1.4 + 1.4i
    cout << endl;
    cout << "***************************************************************************************************************" << endl;
    Node<Complex> c1_root_node(Complex(1.3, 1.3));
    Node<Complex> c1_n1(Complex(1.5, 1.5));
    Node<Complex> c1_n2(Complex(1.2, 1.2));
    Node<Complex> c1_n3(Complex(1.1, 1.1));
    Node<Complex> c1_n4(Complex(1.6, 1.6));
    Node<Complex> c1_n5(Complex(1.4, 1.4));
    Node<Complex> c1_n6(Complex(1.7, 1.7));
    Tree<Complex> b_tree;
    b_tree.add_root(c1_root_node);
    b_tree.add_sub_node(c1_root_node, c1_n1);
    b_tree.add_sub_node(c1_root_node, c1_n2);
    b_tree.add_sub_node(c1_n1, c1_n3);
    b_tree.add_sub_node(c1_n1, c1_n4);
    b_tree.add_sub_node(c1_n2, c1_n5);
    b_tree.add_sub_node(c1_n2, c1_n6);
    cout << "Binary Tree with complex numbers- " << endl;
    cout << b_tree;
    cout << "Pre-Order- " << endl;
    for (auto node = b_tree.begin_pre_order(); node != b_tree.end_pre_order(); ++node)
    {
        cout << *node << " ";
    } // prints: 1.3 + 1.3i, 1.5 + 1.5i, 1.1 + 1.1i, 1.6 + 1.6i, 1.2 + 1.2i, 1.4 + 1.4i, 1.7 + 1.7i
    cout << endl;
    cout << "Post-Order- " << endl;
    for (auto node = b_tree.begin_post_order(); node != b_tree.end_post_order(); ++node)
    {
        cout << *node << " ";
    } // prints: 1.1+1.1i, 1.6+1.6i, 1.5+1.5i, 1.4+1.4i, 1.7+1.7i, 1.2+1.2i, 1.3+1.3i
    cout << endl;
    cout << "In-Order-  " << endl;
    for (auto node = b_tree.begin_in_order(); node != b_tree.end_in_order(); ++node)
    {
        cout << *node << " ";
    } // prints: 1.1+1.1i, 1.5+1.5i, 1.6+1.6i, 1.3+1.3i, 1.4+1.4i, 1.2+1.2i, 1.7+1.7i
    cout << endl;
    cout << "BFS- " << endl;
    for (auto node = b_tree.begin_bfs_scan(); node != b_tree.end_bfs_scan(); ++node)
    {
        cout << *node << " ";
    } // prints: 1.3+1.3i, 1.5+1.5i, 1.2+1.2i, 1.1+1.1i, 1.6+1.6i, 1.4+1.4i, 1.7+1.7i
    cout << endl;
    cout << "DFS- " << endl;
    for (auto node = b_tree.begin_dfs_scan(); node != b_tree.end_dfs_scan(); ++node)
    {
        cout << *node << " ";
    } // prints: 1.3+1.3i, 1.5+1.5i, 1.1+1.1i, 1.6+1.6i, 1.2+1.2i, 1.4+1.4i, 1.7+1.7i
    cout << endl;
    cout << "Heap- " << endl;
    for (auto node = b_tree.myHeap(); node != b_tree.myHeap(); ++node)
    {
        cout << *node << " ";
    } // prints: 1.1+1.1i, 1.2+1.2i, 1.3+1.3i, 1.4+1.4i, 1.5+1.5i, 1.6+1.6i, 1.7+1.7i
    cout << endl;
}