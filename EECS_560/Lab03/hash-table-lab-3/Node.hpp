#ifndef NODE_H
#define NODE_H

#include <string>

class Node{
  private:
    std::string m_value;    //stored value of type integer
    Node* m_next;   //pointer to next node in list
    Node* m_prev;

  public:
    Node();

    Node(std::string value);

    Node(std::string value, Node *nextNode, Node *prevNode);

    void setValue(std::string val);

    std::string getValue();

    void setNext(Node *prev);

    void setPrev(Node *prev);

    Node* getNext();

    Node* getPrev();
};

#endif
