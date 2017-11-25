#include "modNode.hpp"

Node::Node(){
  m_value = 0;
  m_next = nullptr;
  m_prev = nullptr;
  int position[2] = {0, 0};
  position[0] = position[0];  //to avoid warning message
}

Node::Node(int value, Node *nextNode, Node *prevNode){
  m_value = value;
  m_next = nextNode;
  m_prev = prevNode;
  int position[2] = {0, 0};
  position[0] = position[0];  //to avoid warning message
}

Node::Node(int value, Node *nextNode, Node *prevNode, int x, int y){
  m_value = value;
  m_next = nextNode;
  m_prev = prevNode;
  int position[2] = {x, y};
  position[0] = position[0];  //to avoid warning message
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

void Node::setXY(int val1, int val2){
  position[0] = val1;
  position[1] = val2;
}

void Node::setX(int val){
  position[0] = val;
}

int Node::getX() {
  return position[0];
}

void Node::setY(int val){
  position[1] = val;
}

int Node::getY() {
  return position[1];
}
