#ifndef NODE_H
#define NODE_H

#include "../../edge.hpp"

class Node{
  private:
    Edge *m_value;    //stored value of type integer
    Node* m_next;   //pointer to next node in list
    Node* m_prev;
    int position[2];

  public:
    Node();

    Node(Edge *value, Node *nextNode, Node *prevNode);

    Node(Edge *value, Node *nextNode, Node *prevNode, int x, int y);

    void setValue(Edge *val);

    Edge* getValue();

    void setNext(Node *prev);

    void setPrev(Node *prev);

    Node* getNext();

    Node* getPrev();

    //void setXY(int val1, int val2);

    //void setX(int val);

    //int getX();

    //void setY(int val);

    //int getY();
};

#endif
