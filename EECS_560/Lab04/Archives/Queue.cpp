/*
File: Queue.hpp
Author: Bud Linville
Date: February 28th 2016
Purpose: implementation of queue
*/

#include <iostream>

template <typename T>
Queue<T>::Queue() {
  front = nullptr;
  rear = nullptr;
}

template <typename T>
Queue<T>::~Queue() {
  Node<T> *tempNode = nullptr;
  while(front != nullptr){
    tempNode = front;
    front = front->getNext();
    delete tempNode;
  }
}

template <typename T>
bool Queue<T>::isEmpty() const {
  return (front == nullptr);
}

template <typename T>
void Queue<T>::enqueue(const T &value) {
  Node<T> *newItem = new Node<T>(value);
  if (newItem == nullptr) {
    std::cout <<"Heap memory full" << std::endl; //unlikely but should be accounted for all the same
  } else {
    if (rear == nullptr) {
      rear = newItem;
      front = newItem;
    } else {
      rear->setNext(newItem);
      rear = newItem;
    }
  }
}

template <typename T>
void Queue<T>::dequeue() {
  if (front == nullptr) {
    std::cout << "dequeue attempted on an empty queue" << std::endl;
  } else {
    Node<T> *h = front;
    front = front->getNext();
    delete h;
    if (front == nullptr) {
      rear = nullptr;
    }
  }
}

template <typename T>
T Queue<T>::peekFront() const {
  if (front == nullptr) {
    std::cout<< "peekFront attempted on an empty queue" << std::endl;
  } else {
    return front->getValue();
  }
}

template <typename T>
Node<T>* Queue<T>::nextNode() const {
  if (front == nullptr) {
    std::cout << "nextNode attempted on too small of a queue." << std::endl;
  } else if (front == rear) {
    return nullptr;
  } else {
    Node<T>* tempNode = front;
    return tempNode->getNext();
  }
}

template <typename T>
T Queue<T>::nextValue() const {
  if (front == nullptr) {
    std::cout << "nextValue attempted on too small of a queue." << std::endl;
  } else if (front == rear) {
    std::cout<< "nextValue attempted on too small of a queue." << std::endl;
  } else {
    Node<T>* tempNode = front->getNext();
    return tempNode->getValue();
  }
}
