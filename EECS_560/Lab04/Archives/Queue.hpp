/*
File: Queue.h
Author: Bud Linville
Date: February 228th 2016
Purpose: houses nodes in a queue (FIFO) fashion
*/

#ifndef QUEUE_H
#define QUEUE_H
#include "Node.h"
#include "QueueInterface.h"
#include <iostream>

template <typename T>
class Queue:public QueueInterface<T>{
  private:
    Node<T> *front;
    Node<T> *rear;

  public:
    //appropriate constructor and destructor
     Queue();

     ~Queue();

     /*
     pre: checks to see if top element of stack is a null pointer (stack empty)
     post: if so, returns true; false otherwise
     */
     bool isEmpty() const;

     /*
     pre: pushes all values down the queue and adds a new element to the back
     post:
     */
     void enqueue(const T &value);

     /*
     pre: deletes front element of the queue and pulls all other elements forward
     post:
     */
     void dequeue();
     /*
     pre:
     post: peeks at front of queue
     */
     T peekFront() const;


     /*
     pre: atypical Queue method used to see if the next Node is a nullptr
     post: returns nexd Node
     */
     Node<T>* nextNode() const;

     /*
     pre: another atypical queue method
     post: returns value of next node method
     */
     T nextValue() const;
};
#include "Queue.cpp"
#endif
