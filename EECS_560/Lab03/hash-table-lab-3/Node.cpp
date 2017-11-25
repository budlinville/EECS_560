#include "Node.hpp"

Node::Node(){
  m_value = "";
  m_next = nullptr;
  m_prev = nullptr;
}

Node::Node(std::string value){
  m_value = value;
  m_next = nullptr;
  m_prev = nullptr;
}

Node::Node(std::string value, Node *nextNode, Node *prevNode){
  m_value = value;
  m_next = nextNode;
  m_prev = prevNode;
}

void Node::setValue(std::string val){
  m_value = val;
}

std::string Node::getValue() {
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
