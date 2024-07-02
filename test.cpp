#include "doctest.h"
#include "complex.hpp"
#include "tree.hpp"
#include <iostream>
#include <vector>
using namespace std;

TEST_CASE("Complex numbers operators")
{
    Complex c1;
    Complex c2(0, 0);
    cout << "c1 - " << c1 << endl; // c1= 0
    cout << "c2 - " << c2 << endl; // c2= 0
    CHECK(c1 == c2);
    CHECK(c1 <= c2);
    CHECK(c1 >= c2);
    Complex c3(2, 1); // c3= 2+i
    cout << "c3 - " << c3 << endl;
    CHECK(c3 != c2);
    CHECK(c3 >= c2);
    CHECK(c3 > c2);
    CHECK(c2 < c3);
    CHECK(c2 <= c3);
    c3.setReal(0); // c3= i
    cout << "c3 - " << c3 << endl;
    CHECK(c3 != c2);
    CHECK(c3 >= c2);
    CHECK(c3 > c2);
    CHECK(c2 < c3);
    CHECK(c2 <= c3);
    c3.setImg(-2); // c3= -2i
    cout << "c3 - " << c3 << endl;
    CHECK(c2 != c3);
    CHECK(c3 <= c2);
    CHECK(c3 < c2);
    CHECK(c2 > c3);
    CHECK(c2 >= c3);
    c3.setReal(3.3); // c3= 3.3-2i
    cout << "c3 - " << c3 << endl;
    Complex c4(1.3); // c4= 1.3
    cout << "c4 - " << c4 << endl;
    CHECK(c3 != c4);
    CHECK(c3 >= c4);
    CHECK(c3 > c4);
    CHECK(c4 < c3);
    CHECK(c4 <= c3);
}
TEST_CASE("Nodes and tree building")
{
    Node<Complex> root_node(Complex(1.1, 1.1));
    Node<Complex> n1(Complex(1.2, 1.2));
    Node<Complex> n2(Complex(1.3, 1.3));
    Node<Complex> n3(Complex(1.4, 1.4));
    Node<Complex> n4(Complex(1.5, 1.5));
    Node<Complex> n5(Complex(1.6, 1.6));
    Tree<Complex, 3> three_ary_tree; // 3-ary tree.
    three_ary_tree.add_root(root_node);
    CHECK_THROWS(three_ary_tree.add_sub_node(n1, n2)); // Parent node not found in the tree.
    three_ary_tree.add_sub_node(root_node, n1);
    three_ary_tree.add_sub_node(root_node, n2);
    three_ary_tree.add_sub_node(root_node, n3);
    CHECK(three_ary_tree.get_root()->get_children().size() == 3);
    CHECK_THROWS(three_ary_tree.add_sub_node(root_node, n4)); //  Cannot add more children: the parent node already has 3 children.
    three_ary_tree.add_sub_node(n1, n4);
    three_ary_tree.add_sub_node(n2, n5);
    size_t count = three_ary_tree.count_nodes();
    CHECK(count == 6);
    Node<Complex> n6(Complex(1.7, 1.7));
    three_ary_tree.add_root(n6); // n6 is the new root. the old root now is a child of n6.
    count = three_ary_tree.count_nodes();
    CHECK(count == 7);
}
TEST_CASE("Pre order iterator")
{
    Node<double> root_node(1.1);
    Tree<double> tree; // Binary tree that contains doubles.
    tree.add_root(root_node);
    Node<double> n1(1.2);
    Node<double> n2(1.3);
    Node<double> n3(1.4);
    Node<double> n4(1.5);
    Node<double> n5(1.6);
    tree.add_sub_node(root_node, n1);
    tree.add_sub_node(root_node, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);

    auto it = tree.begin_pre_order();
    auto end = tree.end_pre_order();

    vector<double> preorder_values;
    while (it != end)
    {
        preorder_values.push_back(*it);
        ++it;
    }

    vector<double> expected_values = {1.1, 1.2, 1.4, 1.5, 1.3, 1.6};
    CHECK(preorder_values == expected_values);
}
TEST_CASE("Post order iterator")
{
    Node<double> root_node(1.1);
    Tree<double> tree; // Binary tree that contains doubles.
    tree.add_root(root_node);
    Node<double> n1(1.2);
    Node<double> n2(1.3);
    Node<double> n3(1.4);
    Node<double> n4(1.5);
    Node<double> n5(1.6);
    tree.add_sub_node(root_node, n1);
    tree.add_sub_node(root_node, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);

    auto it = tree.begin_post_order();
    auto end = tree.end_post_order();
    vector<double> postorder_values;
    while (it != end)
    {
        postorder_values.push_back(*it);
        it++;
    }
    std::vector<double> expected_values = {1.4, 1.5, 1.2, 1.6, 1.3, 1.1};
    CHECK(postorder_values == expected_values);
}
TEST_CASE("In order iterator")
{
    Node<double> root_node(1.1);
    Tree<double> tree; // Binary tree that contains doubles.
    tree.add_root(root_node);
    Node<double> n1(1.2);
    Node<double> n2(1.3);
    Node<double> n3(1.4);
    Node<double> n4(1.5);
    Node<double> n5(1.6);
    tree.add_sub_node(root_node, n1);
    tree.add_sub_node(root_node, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);

    auto it = tree.begin_in_order();
    auto end = tree.end_in_order();
    vector<double> inorder_values;
    while (it != end)
    {
        inorder_values.push_back(*it);
        ++it;
    }
    vector<double> expected_values = {1.4, 1.2, 1.5, 1.1, 1.6, 1.3};
    CHECK(inorder_values == expected_values);
}
TEST_CASE("BFS iterator")
{
    Node<Complex> root_node(Complex(1.1, 1.1));
    Node<Complex> n1(Complex(1.2, 1.2));
    Node<Complex> n2(Complex(1.3, 1.3));
    Node<Complex> n3(Complex(1.4, 1.4));
    Node<Complex> n4(Complex(1.5, 1.5));
    Node<Complex> n5(Complex(1.6, 1.6));
    Tree<Complex, 3> three_ary_tree; // 3-ary tree.
    three_ary_tree.add_root(root_node);
    three_ary_tree.add_sub_node(root_node, n1);
    three_ary_tree.add_sub_node(root_node, n2);
    three_ary_tree.add_sub_node(root_node, n3);
    three_ary_tree.add_sub_node(n1, n4);
    three_ary_tree.add_sub_node(n2, n5);
    auto it = three_ary_tree.begin_bfs_scan();
    auto end = three_ary_tree.end_bfs_scan();
    vector<Complex> bfs_values;
    while (it != end)
    {
        bfs_values.push_back(*it);
        ++it;
    }
    vector<Complex> expected_values = {Complex(1.1, 1.1), Complex(1.2, 1.2), Complex(1.3, 1.3), Complex(1.4, 1.4), Complex(1.5, 1.5), Complex(1.6, 1.6)};
    CHECK(bfs_values == expected_values);
}
TEST_CASE("DFS iterator")
{
    Node<Complex> root_node(Complex(1.1, 1.1));
    Node<Complex> n1(Complex(1.2, 1.2));
    Node<Complex> n2(Complex(1.3, 1.3));
    Node<Complex> n3(Complex(1.4, 1.4));
    Node<Complex> n4(Complex(1.5, 1.5));
    Node<Complex> n5(Complex(1.6, 1.6));
    Tree<Complex, 3> three_ary_tree; // 3-ary tree.
    three_ary_tree.add_root(root_node);
    three_ary_tree.add_sub_node(root_node, n1);
    three_ary_tree.add_sub_node(root_node, n2);
    three_ary_tree.add_sub_node(root_node, n3);
    three_ary_tree.add_sub_node(n1, n4);
    three_ary_tree.add_sub_node(n2, n5);
    auto it = three_ary_tree.begin_dfs_scan();
    auto end = three_ary_tree.end_dfs_scan();
    vector<Complex> dfs_values;
    while (it != end)
    {
        dfs_values.push_back(*it);
        it++;
    }
    vector<Complex> expected_values = {Complex(1.1, 1.1), Complex(1.2, 1.2), Complex(1.5, 1.5), Complex(1.3, 1.3), Complex(1.6, 1.6), Complex(1.4, 1.4)};
    CHECK(dfs_values == expected_values);
}
TEST_CASE("Heap iterator")
{
    Node<Complex> root_node(Complex(4.0, 0.0));
    Tree<Complex> tree; // Binary tree

    tree.add_root(root_node);

    Node<Complex> n1(Complex(2.0, 1.0));
    Node<Complex> n2(Complex(6.0, -1.0));
    Node<Complex> n3(Complex(1.0, 2.0));
    Node<Complex> n4(Complex(3.0, -2.0));
    Node<Complex> n5(Complex(5.0, 1.5));
    Node<Complex> n6(Complex(7.0, -1.5));

    tree.add_sub_node(root_node, n1);
    tree.add_sub_node(root_node, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);
    tree.add_sub_node(n2, n6);

    auto heapIterator = tree.myHeap();

    std::vector<Complex> heap_values;
    while (heapIterator != tree.myHeap())
    {
        heap_values.push_back(*heapIterator);
        ++heapIterator;
    }
    vector<Complex> expected_heap_values = {Complex(1.0, 2.0), Complex(2.0, 1.0), Complex(3.0, -2.0), Complex(4.0, 0.0), Complex(5.0, 1.5), Complex(6.0, -1.0), Complex(7.0, -1.5)};
    CHECK(heap_values == expected_heap_values);
}
TEST_CASE("PreOrder Iterator for 3-ary Tree")
{
    Node<Complex> root_node(Complex(1.1, 1.1));
    Node<Complex> n1(Complex(1.2, 1.2));
    Node<Complex> n2(Complex(1.3, 1.3));
    Node<Complex> n3(Complex(1.4, 1.4));
    Node<Complex> n4(Complex(1.5, 1.5));
    Node<Complex> n5(Complex(1.6, 1.6));
    Tree<Complex, 3> three_ary_tree; // 3-ary tree.
    three_ary_tree.add_root(root_node);
    three_ary_tree.add_sub_node(root_node, n1);
    three_ary_tree.add_sub_node(root_node, n2);
    three_ary_tree.add_sub_node(root_node, n3);
    three_ary_tree.add_sub_node(n1, n4);
    three_ary_tree.add_sub_node(n2, n5);

    // Using preorder iterator
    auto preOrderIt = three_ary_tree.begin_pre_order();
    auto preOrderEnd = three_ary_tree.end_pre_order();

    // Using DFS iterator for comparison
    auto dfsIt = three_ary_tree.begin_dfs_scan();
    auto dfsEnd = three_ary_tree.end_dfs_scan();

    vector<Complex> preOrderValues;
    while (preOrderIt != preOrderEnd)
    {
        preOrderValues.push_back(*preOrderIt);
        ++preOrderIt;
    }
    vector<Complex> dfsValues;
    while (dfsIt != dfsEnd)
    {
        dfsValues.push_back(*dfsIt);
        ++dfsIt;
    }
    CHECK(preOrderValues == dfsValues);
}

TEST_CASE("PostOrder Iterator for 3-ary Tree")
{
    Node<Complex> root_node(Complex(1.1, 1.1));
    Node<Complex> n1(Complex(1.2, 1.2));
    Node<Complex> n2(Complex(1.3, 1.3));
    Node<Complex> n3(Complex(1.4, 1.4));
    Node<Complex> n4(Complex(1.5, 1.5));
    Node<Complex> n5(Complex(1.6, 1.6));
    Tree<Complex, 3> three_ary_tree; // 3-ary tree.
    three_ary_tree.add_root(root_node);
    three_ary_tree.add_sub_node(root_node, n1);
    three_ary_tree.add_sub_node(root_node, n2);
    three_ary_tree.add_sub_node(root_node, n3);
    three_ary_tree.add_sub_node(n1, n4);
    three_ary_tree.add_sub_node(n2, n5);

    // Using postOrder iterator
    auto postOrderIt = three_ary_tree.begin_post_order();
    auto postOrderEnd = three_ary_tree.end_post_order();

    // Using DFS iterator for comparison
    auto dfsIt = three_ary_tree.begin_dfs_scan();
    auto dfsEnd = three_ary_tree.end_dfs_scan();

    vector<Complex> postOrderValues;
    while (postOrderIt != postOrderEnd)
    {
        postOrderValues.push_back(*postOrderIt);
        ++postOrderIt;
    }
    vector<Complex> dfsValues;
    while (dfsIt != dfsEnd)
    {
        dfsValues.push_back(*dfsIt);
        ++dfsIt;
    }
    CHECK(postOrderValues == dfsValues);
}
TEST_CASE("InOrder Iterator for 3-ary Tree")
{
    Node<Complex> root_node(Complex(1.1, 1.1));
    Node<Complex> n1(Complex(1.2, 1.2));
    Node<Complex> n2(Complex(1.3, 1.3));
    Node<Complex> n3(Complex(1.4, 1.4));
    Node<Complex> n4(Complex(1.5, 1.5));
    Node<Complex> n5(Complex(1.6, 1.6));
    Tree<Complex, 3> three_ary_tree; // 3-ary tree.
    three_ary_tree.add_root(root_node);
    three_ary_tree.add_sub_node(root_node, n1);
    three_ary_tree.add_sub_node(root_node, n2);
    three_ary_tree.add_sub_node(root_node, n3);
    three_ary_tree.add_sub_node(n1, n4);
    three_ary_tree.add_sub_node(n2, n5);

    // Using inorder iterator
    auto inOrderIt = three_ary_tree.begin_in_order();
    auto inOrderEnd = three_ary_tree.end_in_order();

    // Using DFS iterator for comparison
    auto dfsIt = three_ary_tree.begin_dfs_scan();
    auto dfsEnd = three_ary_tree.end_dfs_scan();

    vector<Complex> inOrderValues;
    while (inOrderIt != inOrderEnd)
    {
        inOrderValues.push_back(*inOrderIt);
        ++inOrderIt;
    }
    vector<Complex> dfsValues;
    while (dfsIt != dfsEnd)
    {
        dfsValues.push_back(*dfsIt);
        ++dfsIt;
    }
    CHECK(inOrderValues == dfsValues);
}
TEST_CASE("Heap Iterator for 3-ary Tree"){
    Node<Complex> root_node(Complex(1.1, 1.1));
    Node<Complex> n1(Complex(1.2, 1.2));
    Node<Complex> n2(Complex(1.3, 1.3));
    Node<Complex> n3(Complex(1.4, 1.4));
    Node<Complex> n4(Complex(1.5, 1.5));
    Node<Complex> n5(Complex(1.6, 1.6));
    Tree<Complex, 3> three_ary_tree; // 3-ary tree.
    three_ary_tree.add_root(root_node);
    three_ary_tree.add_sub_node(root_node, n1);
    three_ary_tree.add_sub_node(root_node, n2);
    three_ary_tree.add_sub_node(root_node, n3);
    three_ary_tree.add_sub_node(n1, n4);
    three_ary_tree.add_sub_node(n2, n5);
    CHECK_THROWS(three_ary_tree.myHeap());
}
