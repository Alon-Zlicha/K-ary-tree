#ifndef TREE_HPP
#define TREE_HPP

#include "node.hpp"
#include <queue>
#include <stack>
#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

template <typename T, int k = 2>
class Tree
{
private:
    Node<T> *root;

    // Avoid copying
    Tree(const Tree &other);
    Tree &operator=(const Tree &other);

    // Helper function to count the number of nodes in the tree
    size_t count_nodes_recursive(Node<T> *node) const
    {
        if (node == nullptr)
        {
            return 0;
        }
        size_t count = 1; // Count the current node
        for (Node<T> *child : node->get_children())
        {
            count += count_nodes_recursive(child); // Recursively count the children
        }
        return count;
    }

    // Helper function to find a node in the tree
    Node<T> *find_node(Node<T> *current, const T &value) const
    {
        if (current == nullptr)
        {
            return nullptr;
        }
        if (current->get_value() == value)
        {
            return current;
        }
        for (Node<T> *child : current->get_children())
        {
            Node<T> *result = find_node(child, value);
            if (result != nullptr)
            {
                return result;
            }
        }
        return nullptr;
    }

public:
    // Constructor
    Tree() : root(nullptr) {}

    // Destructor
    ~Tree()
    {
        delete root;
    }

    Node<T> *get_root() const
    {
        return root;
    }

    void add_root(Node<T> &node)
    {
        if (root != nullptr)
        {
            if (node.get_children().size() >= k)
            {
                throw std::runtime_error("Cannot add root: the node already has " + std::to_string(k) + " children.");
            }

            if (node.get_children().size() + 1 > k)
            {
                throw std::runtime_error("Cannot add root: the new root cannot accommodate the existing root as its child.");
            }

            Node<T> *new_root = new Node<T>(node);
            new_root->get_children().push_back(root);
            root = new_root;
        }
        else
        {
            root = new Node<T>(node);
        }
    }

    void add_sub_node(Node<T> &parent, const Node<T> &child)
    {
        Node<T> *parent_node = find_node(root, parent.get_value());
        if (parent_node == nullptr)
        {
            throw std::runtime_error("Parent node not found in the tree.");
        }

        if (parent_node->get_children().size() >= k)
        {
            throw std::out_of_range("Cannot add more children: the parent node already has " + std::to_string(k) + " children.");
        }

        Node<T> *child_node = new Node<T>(child);
        parent_node->get_children().push_back(child_node);
    }

    size_t count_nodes() const
    {
        return count_nodes_recursive(root);
    }

    // Pre-order iterator
    class PreOrderIterator
    {
    private:
        std::stack<Node<T> *> stack;

    public:
        PreOrderIterator(Node<T> *root)
        {
            if (root != nullptr)
            {
                stack.push(root);
            }
        }

        Node<T> *operator++()
        {
            if (stack.empty())
            {
                return nullptr;
            }

            Node<T> *current = stack.top();
            stack.pop();

            auto &children = current->get_children();
            for (auto it = children.rbegin(); it != children.rend(); ++it)
            {
                stack.push(*it);
            }
            return current;
        }

        Node<T> *operator++(int)
        {
            Node<T> *current = stack.empty() ? nullptr : stack.top();
            ++(*this);
            return current;
        }

        bool operator!=(const PreOrderIterator &other) const
        {
            return !stack.empty() || !other.stack.empty();
        }

        const T &operator*() const
        {
            Node<T> *node = stack.top();
            return node->get_value();
        }

        const T *operator->() const
        {
            Node<T> *node = stack.top();
            return &(node->get_value());
        }
    };

    // Post-order iterator
    class PostOrderIterator
    {
    private:
        std::stack<Node<T> *> stack1;
        std::stack<Node<T> *> stack2;

    public:
        PostOrderIterator(Node<T> *root)
        {
            if (root != nullptr)
            {
                stack1.push(root);
                while (!stack1.empty())
                {
                    Node<T> *node = stack1.top();
                    stack1.pop();
                    stack2.push(node);
                    for (auto &child : node->get_children())
                    {
                        stack1.push(child);
                    }
                }
            }
        }

        Node<T> *operator++()
        {
            if (stack2.empty())
            {
                return nullptr;
            }
            Node<T> *node = stack2.top();
            stack2.pop();
            return node;
        }

        Node<T> *operator++(int)
        {
            Node<T> *current = stack2.empty() ? nullptr : stack2.top();
            ++(*this);
            return current;
        }

        bool operator!=(const PostOrderIterator &other) const
        {
            return !stack2.empty() || !other.stack2.empty();
        }

        const T &operator*() const
        {
            Node<T> *node = stack2.top();
            return node->get_value();
        }

        const T *operator->() const
        {
            Node<T> *node = stack2.top();
            return &(node->get_value());
        }
    };

    // In-order iterator
    class InOrderIterator
    {
    private:
        std::stack<Node<T> *> stack;
        Node<T> *current;

        void pushLeft(Node<T> *node)
        {
            while (node)
            {
                stack.push(node);
                if (!node->get_children().empty())
                    node = node->get_children()[0];
                else
                    node = nullptr;
            }
        }

    public:
        InOrderIterator(Node<T> *root) : current(nullptr)
        {
            pushLeft(root);
            if (!stack.empty())
                current = stack.top();
        }

        InOrderIterator &operator++()
        {
            if (stack.empty())
            {
                current = nullptr;
                return *this;
            }

            Node<T> *node = stack.top();
            stack.pop();

            if (!node->get_children().empty() && node->get_children().size() > 1)
                pushLeft(node->get_children()[1]);

            current = stack.empty() ? nullptr : stack.top();
            return *this;
        }

        Node<T> *operator++(int)
        {
            Node<T> *current = stack.empty() ? nullptr : stack.top();
            ++(*this);
            return current;
        }

        bool operator!=(const InOrderIterator &other) const
        {
            return current != other.current;
        }

        const T &operator*() const
        {
            return current->get_value();
        }

        const T *operator->() const
        {
            return &(current->get_value);
        }
    };

    // BFS iterator
    class BFSIterator
    {
    private:
        std::queue<Node<T> *> queue;

    public:
        BFSIterator(Node<T> *root)
        {
            if (root != nullptr)
            {
                queue.push(root);
            }
        }

        Node<T> *operator++()
        {
            if (queue.empty())
            {
                return nullptr;
            }

            Node<T> *current = queue.front();
            queue.pop();

            // Enqueue children for BFS
            auto &children = current->get_children();
            for (auto &child : children)
            {
                queue.push(child);
            }

            return current;
        }

        Node<T> *operator++(int)
        {
            Node<T> *current = queue.empty() ? nullptr : queue.front();
            ++(*this);
            return current;
        }

        bool operator!=(const BFSIterator &other) const
        {
            return !queue.empty() || !other.queue.empty();
        }

        const T &operator*() const
        {
            Node<T> *node = queue.front();
            return node->get_value();
        }

        const T *operator->() const
        {
            Node<T> *node = queue.front();
            return &(node->get_value());
        }
    };

    // DFS iterator
    class DFSIterator
    {
    private:
        std::stack<Node<T> *> stack;

    public:
        DFSIterator(Node<T> *root)
        {
            if (root != nullptr)
            {
                stack.push(root);
            }
        }

        Node<T> *operator++()
        {
            if (stack.empty())
            {
                return nullptr;
            }

            Node<T> *current = stack.top();
            stack.pop();

            // Push children to stack for DFS
            auto &children = current->get_children();
            for (auto it = children.rbegin(); it != children.rend(); ++it)
            {
                stack.push(*it);
            }

            return current;
        }

        Node<T> *operator++(int)
        {
            Node<T> *current = stack.empty() ? nullptr : stack.top();
            ++(*this);
            return current;
        }

        bool operator!=(const DFSIterator &other) const
        {
            return !stack.empty() || !other.stack.empty();
        }

        const T &operator*() const
        {
            Node<T> *node = stack.top();
            return node->get_value();
        }

        const T &operator->() const
        {
            Node<T> *node = stack.top();
            return &(node->get_value());
        }
    };
    
    // Heap iterator
    class HeapIterator
    {
    private:
        std::vector<T> heap;
        void tree_to_vector(Node<T> *node)
        {
            if (node)
            {
                heap.push_back(node->get_value()); // Collect current node's value
                for (auto child : node->get_children())
                {
                    tree_to_vector(child); // Recursively collect children nodes
                }
            }
        }
    public:
        HeapIterator(Node<T> *node)
        {
            tree_to_vector(node); // Collect all nodes for heap
            std::make_heap(heap.begin(), heap.end(), std::greater<T>());
        }

        bool operator!=(const HeapIterator &other) const
        {
            return !heap.empty();
        }

        HeapIterator &operator++()
        {
            std::pop_heap(heap.begin(), heap.end(), std::greater<T>());
            heap.pop_back();
            return *this;
        }

        HeapIterator operator++(int)
        {
            HeapIterator tmp = *this;
            ++(*this);
            return tmp;
        }

        const T &operator*() const
        {
            return heap.front();
        }

        const T *operator->() const
        {
            return &heap.front();
        }
    };

    auto begin_pre_order()
    {
        if constexpr (k > 2)
        {
            return DFSIterator(root);
        }
        else
        {
            return PreOrderIterator(root);
        }
    }

    auto end_pre_order()
    {
        if constexpr (k > 2)
        {
            return DFSIterator(nullptr);
        }
        else
        {
            return PreOrderIterator(nullptr);
        }
    }

    auto begin_post_order()
    {
        if constexpr (k > 2)
        {
            return DFSIterator(root);
        }
        else
        {
            return PostOrderIterator(root);
        }
    }

    auto end_post_order()
    {
        if constexpr (k > 2)
        {
            return DFSIterator(nullptr);
        }
        else
        {
            return PostOrderIterator(nullptr);
        }
    }

    auto begin_in_order()
    {
        if constexpr (k > 2)
        {
            return DFSIterator(root);
        }
        else
        {
            return InOrderIterator(root);
        }
    }

    auto end_in_order()
    {
        if constexpr (k > 2)
        {
            return DFSIterator(nullptr);
        }
        else
        {
            return InOrderIterator(nullptr);
        }
    }

    BFSIterator begin_bfs_scan() const
    {
        return BFSIterator(root);
    }

    BFSIterator end_bfs_scan() const
    {
        return BFSIterator(nullptr);
    }

    DFSIterator begin_dfs_scan()
    {
        return DFSIterator(root);
    }

    DFSIterator end_dfs_scan()
    {
        return DFSIterator(nullptr);
    }

    HeapIterator myHeap()
    {
        if (k > 2)
        {
            throw std::runtime_error("Heap is valid only on Binary trees");
        }
        else
        {
            return HeapIterator(root);
        }
    }

    void drawTree(sf::RenderWindow &window, Node<T> *node, int x, int y, int horizontal_gap, sf::Font &font)
    {
        if (!node)
        {
            return;
        }
        sf::CircleShape circle(40);
        circle.setFillColor(sf::Color::White);
        circle.setOutlineThickness(1);
        circle.setOutlineColor(sf::Color::Black);
        circle.setPosition(x, y);
        window.draw(circle);
        std::ostringstream oss;
        oss.precision(1);
        oss << std::fixed << node->get_value();
        sf::Text textObject(oss.str(), font, 15);
        textObject.setFillColor(sf::Color::Blue);
        sf::FloatRect textBounds = textObject.getLocalBounds();
        textObject.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
        textObject.setPosition(x + circle.getRadius(), y + circle.getRadius());
        window.draw(textObject);
        auto children = node->get_children();
        int numOfChildren = children.size();
        if (numOfChildren > 0)
        {
            for (int i = 0; i < numOfChildren; ++i)
            {
                int child_x = x - horizontal_gap / 2 + i * horizontal_gap;
                int child_y = y + 150;

                sf::Vertex line[] = {
                    sf::Vertex(sf::Vector2f(x + circle.getRadius(), y + 2 * circle.getRadius())),
                    sf::Vertex(sf::Vector2f(child_x + circle.getRadius(), child_y))};
                line[0].color = sf::Color::Black;
                line[1].color = sf::Color::Black;
                window.draw(line, 2, sf::Lines);
                drawTree(window, children[i], child_x, child_y, horizontal_gap / 2, font);
            }
        }
    }

    template <typename U, int N>
    friend std::ostream &operator<<(std::ostream &os, Tree<U, N> &tree);
};
template <typename T, int k>
std::ostream &operator<<(std::ostream &os, Tree<T, k> &tree)
{
    sf::RenderWindow window(sf::VideoMode(1000, 500), "Tree GUI");
    sf::Font font;
    if (!font.loadFromFile("./Roboto-BlackItalic.ttf"))
    {
        std::cerr << "Failed to load font!" << std::endl;
    }
    else
    {
        window.clear(sf::Color::White);
        tree.drawTree(window, tree.get_root(), 500, 10, 185, font);
        window.display();
        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }
            }
        }
    }
    return os;
}
#endif
