#include "../../../include/lib/doubly-linked-list/Node.hpp"

Node::Node(){
  m_value =  new Edge(0, 0, 0);
  m_next = nullptr;
  m_prev = nullptr;
  int position[2] = {0, 0};
  position[0] = position[0];  //to avoid warning message
}

Node::Node(Edge *value, Node *nextNode, Node *prevNode){
  m_value = value;
  m_next = nextNode;
  m_prev = prevNode;
  int position[2] = {0, 0};
  position[0] = position[0];  //to avoid warning message
}

Node::Node(Edge *value, Node *nextNode, Node *prevNode, int x, int y){
  m_value = value;
  m_next = nextNode;
  m_prev = prevNode;
  int position[2] = {x, y};
  position[0] = position[0];  //to avoid warning message
}

void Node::setValue(Edge *val){
  m_value = val;
}

Edge* Node::getValue() {
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
/*
int Node::getX() {
  return m_value->v1;
}

int Node::getY() {
  return m_value->v2;
}
*/
