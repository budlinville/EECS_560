#include "Node.hpp"

Node::Node(){
  m_value = 0;
  m_next = nullptr;
  m_prev = nullptr;
}

Node::Node(int value, Node *nextNode, Node *prevNode){
  m_value = value;
  m_next = nextNode;
  m_prev = prevNode;
}

void Node::setValue(int val){
  m_value = val;
}

int Node::getValue() {
  return m_value;
}

void Node::setNext(Node *next){
  m_next = next;
}

void Node::setPrev(Node *prev){
  m_prev = prev;
}

Node* Node::getNext() {
  return m_next;
}

Node* Node::getPrev() {
  return m_prev;
}
