#include "list.hpp"
#include "util.hpp"
#include "Node.hpp"

DoublyLinkedList::DoublyLinkedList() {
  m_front = nullptr;
  m_size = 0;
  m_back = nullptr;
}

DoublyLinkedList::~DoublyLinkedList() {
  if (m_front != nullptr) {
    Node* curNode = m_front;
    Node* nextNode = curNode->getNext();

    while (curNode != nullptr) {
      delete curNode;
      curNode = nextNode;
      if (curNode != nullptr) {
        nextNode = nextNode->getNext();
      }
    }
  }
}

bool DoublyLinkedList::isEmpty() {
  if (m_front == nullptr) {
    return true;
  }

  return false;
}

int DoublyLinkedList::size(){
  return m_size;
}

void DoublyLinkedList::add(int elem, int position) {
  try {
    if (position < 0 || position > m_size) {
      throw std::out_of_range ("Position is out of range");
    }

    Node* newNode = new Node();
    newNode->setValue(elem);
    Node* temp = m_front;
    int ix = position - 1;

    if (m_front == nullptr) {           //if empty list
      m_front = newNode;
      m_back = newNode;
    } else if (position == 0) {         //if adding to the front
      newNode->setNext(m_front);
      m_front->setPrev(newNode);
      m_front = newNode;
    } else if (position == m_size) {    //if adding to the back
      m_back->setNext(newNode);
      newNode->setPrev(m_back);
      m_back = newNode;
    } else {
      for (int i = 0; i < m_size; i++) { //adding to middle
        if (i == ix) {
          newNode->setNext(temp->getNext());
          newNode->setPrev(temp);
          temp->setNext(newNode);
        }
        temp = temp->getNext();
      }
    }

    m_size++;
    //std::cout << m_size << " [" << elem << "]" << std::endl; //[FOR ERROR CHECKING PURPOSES]
  } catch (std::exception& e) {
    std::cout << "Position is out of bounds." << std::endl;
  }
}

void DoublyLinkedList::deleteAll(int elem) {
  Node* temp =  m_front;
  Node* prev = nullptr;
  Node* next = nullptr;

  while (temp->getNext() != nullptr) {
    if (elem == temp->getValue()) {
      //DELETE IT
      prev = temp->getPrev();
      next = temp->getNext();

      //if first index of linked list
      if (temp == m_front) {
        m_front = temp->getNext();
        m_front->setPrev(nullptr);
        delete temp;
        m_size--;
      } else {
        if (prev != nullptr) {
          prev->setNext(next);
        }

        if (next != nullptr) {
          next->setPrev(prev);
        }

        delete temp;
        temp = prev;
        m_size--;
      }
    }

    temp = temp->getNext();
  }
}

int DoublyLinkedList::find(int elem) {
  Node* temp = m_front;

  for (int i = 0; i < m_size; i++) {
    if (temp->getValue() == elem) {
      //return i;
      std::cout << "Element " << elem << " found at position " << i << "." << std::endl;
      return 0;  //if I wanted to find all occurances, comment out this line
    }
    temp = temp->getNext();
  }

  return -1;
}

void DoublyLinkedList::print() {
   Node* incr = m_front;    //incrementer

   do {
     std::cout << incr->getValue() << " ";
     incr = incr->getNext();
   } while (incr != nullptr);

   std::cout << std::endl;
}
