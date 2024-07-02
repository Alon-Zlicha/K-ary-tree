//Alonz1414@gmail.com
#ifndef NODE_HPP
#define NODE_HPP
#include <vector>
#include <cstddef>
#include <iostream>

template <typename T>
class Node
{
private:
    T value;
    std::vector<Node *> children;

    void copy_children(const std::vector<Node *> &other_children)
    {
        for (Node *child : other_children)
        {
            children.push_back(new Node(*child));
        }
    }

    void clear_children()
    {
        for (Node *child : children)
        {
            delete child;
        }
        children.clear();
    }

public:
    // Constructor
    Node(const T &value) : value(value) {}

    // Destructor
    ~Node()
    {
        clear_children();
    }

    // Copy constructor
    Node(const Node &other) : value(other.value)
    {
        copy_children(other.children);
    }

    // Assignment operator
    Node &operator=(const Node &other)
    {
        if (this == &other)
            return *this;

        value = other.value;
        clear_children();
        copy_children(other.children);

        return *this;
    }

    T &get_value()
    {
        return value;
    }

    const T &get_value() const
    {
        return value;
    }

    void set_value(T& val){
        value=val;
    }

    std::vector<Node *> &get_children()
    {
        return children;
    }

    const std::vector<Node *> &get_children() const
    {
        return children;
    }

};

#endif
