Alonz1414@gmail.com

# K-ary_trees project

This project provides a versatile implementation of hierarchical data structures using templates in C++, capable of handling various data types including complex numbers. It supports visualization using SFML and includes iterators for traversal methods specific to different tree configurations.

## Features

- **Tree Structure**: Supports k-ary trees with a default arity of 2.
- **Node Types**: Handles any object or primitive type, including complex numbers with custom comparison operators.
- **Traversal Methods**: BFS and DFS iterators for general trees; in-order, pre-order, and post-order for binary trees (in-order, post-order, and pre-order for trees with k ≠ 2 perform regular DFS).
- **Heap Iterator**: Converts a binary tree into a minimum heap using the `make_heap` algorithm from the standard library algorithms.
- **SFML Visualization**: Provides a graphical representation of the tree structure using SFML.

## Libraries Used

- **Standard Template Library (STL)**: Utilizes data structures such as `queue` and `stack` for implementing iterators.
- **SFML (Simple and Fast Multimedia Library)**: Enables graphical visualization of the tree structure.

## Node Class

The `Node` class represents a node in the tree.

### Methods

- **Constructor**: `Node(const T& value);`
  - Initializes a node with a value of type `T`.

- **Copy Constructor**: `Node(const Node& other);`
  - Copies a node, including its children recursively.

- **Assignment Operator**: `Node& operator=(const Node& other);`
  - Assigns the value and copies children from another node.

- **Destructor**: `~Node();`
  - Cleans up node memory, including all child nodes.

- **Get Value**: `T& get_value();`
  - Returns a reference to the node's value.

- **Get Children**: `std::vector<Node*>& get_children();`
  - Returns a reference to the vector of child nodes.

## Tree Class

The `Tree` class manages the entire tree structure.

### Methods

- **Constructor**: `Tree();`
  - Initializes an empty tree.

- **Destructor**: `~Tree();`
  - Cleans up tree memory, including the root node.

- **Add Root**: `void add_root(Node<T>& node);`
  - Sets the root of the tree. If the tree already has a root, the new node replaces it, and the old root becomes a child of the new root.

- **Add Node**: `void add_child(Node<T>& parent, const Node<T>& child);`
  - Adds a child node to a parent node only if the parent node doesn't reach the children limit.

- **Count Nodes**: `size_t count_nodes() const;`
  - Counts the total number of nodes in the tree.

### Iterators

The `Tree` class provides iterators for different traversal methods:

- **BFS Iterator**: `class BFSIterator;`
  - Traverses nodes in breadth-first search (BFS) order using a queue.

- **DFS Iterator**: `class DFSIterator;`
  - Traverses nodes in depth-first search (DFS) order using a stack.

- **Pre-order Iterator**: `class PreOrderIterator;`
  - Traverses nodes in pre-order (for binary trees) using a stack.

- **Post-order Iterator**: `class PostOrderIterator;`
  - Traverses nodes in post-order (for binary trees) using two stacks.

- **In-order Iterator**: `class InOrderIterator;`
  - Traverses nodes in in-order (for binary trees) using a stack and pointer to the current node.

### Heap Iterator

Converts a binary tree into a minimum heap using the `make_heap` algorithm from the standard library algorithms.

### SFML Visualization

The project includes functionality to visualize the tree structure using SFML. The `operator<<` method is overloaded to draw the tree graphically.

## Complex Class

The `Complex` class handles complex numbers and provides comparison operators.

### Methods

- **Constructor**: `Complex(double r, double i);`
  - Initializes a complex number with real part `r` and imaginary part `i`.

- **Comparison Operators**: Overloads <, ==, <=, >=, >, and != to compare two complex numbers based on their real values; if the real values are equal, it compares their imaginary values.

- **Output Operator**: Overloads `<<` to print the complex number in a readable format.
