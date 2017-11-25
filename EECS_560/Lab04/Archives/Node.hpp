/*
File: main.cpp
Author: Bud Linville
Date: February 14th, 2016
Purpose: implementation of node class
*/

template<typename T>
Node<T>::Node(){
  m_next = nullptr;
}

template<typename T>
Node<T>::Node(T value, Node *nextNode){
  m_value = value;
  m_next = nextNode;
}

template<typename T>
Node<T>::Node(T value){
  m_value = value;
  m_next = nullptr;
}

template<typename T>
void Node<T>::setValue(T val){
  m_value = val;
}

template<typename T>
T Node<T>::getValue() const{
  return m_value;
}

template<typename T>
void Node<T>::setNext(Node *prev){
  m_next = prev;
}

template<typename T>
Node<T>* Node<T>::getNext() const{
  return m_next;
}
