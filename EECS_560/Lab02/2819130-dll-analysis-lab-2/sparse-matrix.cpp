#include "list.hpp"
#include "sparse-matrix.hpp"
#include "util.hpp"

SparseMatrix::SparseMatrix() : DoublyLinkedList() {}

SparseMatrix::~SparseMatrix() {}

void SparseMatrix::matrixAdd(int elem, int position, int x, int y) {
  try {
    if (position < 0 || position > m_size) {
      throw std::out_of_range ("Position is out of range");
    }

    Node* newNode = new Node();
    newNode->setValue(elem);
    newNode->setX(x);
    newNode->setY(y);
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

bool SparseMatrix::equals(const SparseMatrix* that){
  int thisVal = 0;
  int thatVal = 0;
  int thisX = 0;
  int thatX = 0;
  int thisY = 0;
  int thatY = 0;
  bool equal = true;
  Node* thisCurNode = this->m_front;
  Node* thatCurNode = that->m_front;

  //std::cout<< "a" << std::endl;

  //account for empty lists
  if (this->m_front == nullptr && that->m_front == nullptr) {
    equal = true;

    //std::cout<< "b" << std::endl;
  } else if ((this->m_front == nullptr && that->m_front != nullptr)) {
    equal = false;

    //std::cout<< "c" << std::endl;
  } else if ((this->m_front != nullptr && that->m_front == nullptr)) {
    equal = false;

    //std::cout<< "d" << std::endl;
  } else if (this->m_size != that->m_size) {      //if "matrices" are not same size, they are not equal
    equal = false;

    //std::cout<< "e" << std::endl;
  } else {

    //std::cout<< "f" << std::endl;
    while (thisCurNode != nullptr && thatCurNode != nullptr) {
      thisVal = thisCurNode->getValue();
      thatVal = thatCurNode->getValue();
      thisX = thisCurNode->getX();
      thatX = thatCurNode->getX();

      thisY = thisCurNode->getY();
      thatY = thatCurNode->getY();

      //std::cout<< "g" << std::endl;
      if ((thisVal == thatVal) && (thisX == thatX) && (thisY == thatY)) {
        equal = true;
      } else {
        return false;
      }
      thisCurNode = thisCurNode->getNext();
      thatCurNode = thatCurNode->getNext();
    }
  }

  return equal;
}

//CAN BE O(n^2)
SparseMatrix* SparseMatrix::transpose(){
  int x = 0;
  int y = 0;
  Node* curNode = m_front;
  Node* placeHolder = nullptr;
  int tempVal = 0;

  while (curNode != nullptr) {
    //dont need to switch if x = y, because it is already in correct spot
    //dont need to switch if x > y, because it has already been switched
    if (curNode->getX() < curNode->getY()) {

      placeHolder = curNode;
      tempVal = curNode->getValue();
      x = curNode->getX();
      y = curNode->getY();

      //iterate until I find the transposition of curNode
      while ((curNode->getY() != x) && (curNode->getX() != y)) {
        curNode = curNode->getNext();
      }
      //replace values
      curNode->setValue(placeHolder->getValue());
      placeHolder->setValue(tempVal);

      curNode = placeHolder->getNext();
    }

    curNode = curNode->getNext();
  }

  return new SparseMatrix();
}
