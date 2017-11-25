#ifndef NODE_H
#define NODE_H

class Node{
  private:
    int m_value;    //stored value of type integer
    Node* m_next;   //pointer to next node in list
    Node* m_prev;

  public:
    Node();

    Node(int value, Node *nextNode, Node *prevNode);

    void setValue(int val);

    int getValue();

    void setNext(Node *prev);

    void setPrev(Node *prev);

    Node* getNext();

    Node* getPrev();
};

#endif
