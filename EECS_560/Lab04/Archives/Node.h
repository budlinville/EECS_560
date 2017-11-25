/*
File: Node.h
Author: Bud Linville
Date: February 21st, 2016
Purpose: houses a single value (of unknown type at compilation) and a pointer to the following node

taken from lab 3 modified to become a templated version
*/

#ifndef NODE_H
#define NODE_H

template <typename T>
class Node {
  private:
    T m_value;    //stored value of type T
    Node* m_next;   //pointer to next node in list

  public:

    //constructors with differing parameters based on intended use
    Node();

    Node(T value, Node *nextNode);

    Node(T value);


    /*
    pre: passes an templated value as parameter
    post: updates m_value to new value
    */
    void setValue(T val);

    /*
    pre:
    post: returns node's m_value
    */
    T getValue() const;

    /*
    pre: passes a node in as a parameter
    post: updates node's pointer to that of the next node
    */
    void setNext(Node *prev);

    /*
    pre:
    post: returns node's m_next value
    */
    Node<T>* getNext() const;
};

#include "Node.hpp"
#endif
