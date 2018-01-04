#include "avl.hpp"
#include "util.hpp"
#include <cmath>

AVL::AVL() {
  rootPtr = nullptr;
}

AVL::~AVL() {
  destroyTree(rootPtr);
}


bool AVL::isEmpty() {
  return (rootPtr == nullptr);
}


void AVL::addBook(Book* book) {
  node_t* newNode = new node_t;
  newNode->book = book;
  newNode->lChild = nullptr;
  newNode->rChild = nullptr;
  newNode->lChildHeight = 0;
  newNode->rChildHeight = 0;

  if (rootPtr == nullptr) {
    rootPtr = newNode;
    return;
  }

  insertInorder(rootPtr, newNode);
  updateHeights(rootPtr);           //not efficient, only need to update heights along path... but whatever

  postorderCheckHeightsAndSwap(rootPtr);

  //levelorderTraverse(&AVL::printBook);

}

Book* AVL::search(int id) {
  //levelorderTraverse(&AVL::printBook);
  return(checkElement(rootPtr, id));
}

void AVL::levelorderTraverse(void (AVL::*operation)(Book*)) {
  if (rootPtr == nullptr)
    return;

  int h = (rootPtr->lChildHeight > rootPtr->rChildHeight) ? (rootPtr->lChildHeight + 1) : (rootPtr->rChildHeight + 1);    //may be wrong by a difference of one

  for (int i = 0; i <= h; i++) {
    std::cout << i << ": ";
    levelorderHelper(rootPtr, i, operation);
    std::cout << std::endl;
  }
}

void AVL::doLeftLeft(node_t* curNode) {
  //create new node that holds curNode's values
  //will then copy lChild's values into curNode
  node_t* newRightChild = new node_t;
  newRightChild->book = curNode->book;
  newRightChild->lChild = curNode->lChild->rChild;
  newRightChild->rChild = curNode->rChild;
  //newRightChild->lChildHeight = curNode->lChild->rChildHeight;
  //newRightChild->rChildHeight = curNode->rChildHeight;

  //copy lChild's values into curNode
  node_t* temp = curNode->lChild;   //so i can delete this node
  curNode->book = curNode->lChild->book;
  curNode->rChild = newRightChild;
  //curNode->rChildHeight = (curNode->rChildHeight > curNode->lChild->rChildHeight) ? (curNode->rChildHeight + 1) : ()
  curNode->lChild = temp->lChild;

  delete temp;
}

void AVL::doRightRight(node_t* curNode) {
  node_t* newLeftChild = new node_t;
  newLeftChild->book = curNode->book;
  newLeftChild->rChild = curNode->rChild->lChild;
  newLeftChild->lChild = curNode->lChild;

  node_t *temp = curNode->rChild;
  curNode->book = curNode->rChild->book;
  curNode->lChild = newLeftChild;
  curNode->rChild = temp->rChild;

  delete temp;
}

int AVL::updateHeights(node_t* curNode) {
  if (curNode == nullptr) {
    return 0;
  }

  int lHeight = updateHeights(curNode->lChild);
  int rHeight = updateHeights(curNode->rChild);

  curNode->lChildHeight = lHeight;
  curNode->rChildHeight = rHeight;

  return (lHeight > rHeight) ? (lHeight + 1) : (rHeight + 1);
}

void AVL::insertInorder(node_t* subTreePtr, node_t* newNodePtr) {
  if (subTreePtr->book->getId() <= newNodePtr->book->getId()) {
    if (subTreePtr->rChild == nullptr) {
      subTreePtr->rChild = newNodePtr;
    } else {
      insertInorder(subTreePtr->rChild, newNodePtr);
    }
  } else {
    if (subTreePtr->lChild == nullptr) {
      subTreePtr->lChild = newNodePtr;
    } else {
      insertInorder(subTreePtr->lChild, newNodePtr);
    }
  }
}

void AVL::postorderCheckHeightsAndSwap(node_t* subTreePtr) {
  if (subTreePtr == nullptr)
    return;

  postorderCheckHeightsAndSwap(subTreePtr->lChild);
  postorderCheckHeightsAndSwap(subTreePtr->rChild);

  int lHeight = subTreePtr->lChildHeight;
  int rHeight = subTreePtr->rChildHeight;

  if (std::abs(lHeight - rHeight) > 1) {      //will need to swap
    if (lHeight > rHeight) {                  //will do a L-? swap
      if (subTreePtr->lChild->lChildHeight >= subTreePtr->lChild->rChildHeight) {  //will do a L-L swap
        doLeftLeft(subTreePtr);
      } else {    //will do a L-R swap
        doRightRight(subTreePtr->lChild);
        doLeftLeft(subTreePtr);
      }
    } else {      //will to a R-? swap
      if (subTreePtr->rChild->rChildHeight >= subTreePtr->rChild->lChildHeight) { //will do a R-R swap
        doRightRight(subTreePtr);
      } else {    //will do a r-L swap
        doLeftLeft(subTreePtr->rChild);
        doRightRight(subTreePtr);
      }
    }

    updateHeights(rootPtr);   //inefficient - only need to update nodes along path, not every node in the tree
  }

}

Book* AVL::checkElement(node_t* subTreePtr, int id) {
  Book* tempBook = nullptr;

  if (subTreePtr == nullptr)
    return nullptr;

  if (subTreePtr->book->getId() == id)
    return subTreePtr->book;

  tempBook = checkElement(subTreePtr->lChild, id);
  if (tempBook != nullptr) {
    if (tempBook->getId() == id)
      return tempBook;

  }

  tempBook = checkElement(subTreePtr->rChild, id);
  if (tempBook != nullptr) {
    if (tempBook->getId() == id)
      return tempBook;
  }

  return nullptr;
}

void AVL::destroyTree(node_t* subTreePtr) {
  if(subTreePtr != nullptr) {
    destroyTree(subTreePtr->lChild);
    destroyTree(subTreePtr->rChild);
    delete subTreePtr;
  }
}

void AVL::levelorderHelper(node_t* subTreePtr, int level, void (AVL::*operation)(Book*)) {
  if (subTreePtr == nullptr)
    return;

  if (level == 0) {
    (this->*operation)(subTreePtr->book);
  } else if (level > 0) {
    levelorderHelper(subTreePtr->lChild, (level - 1), operation);
    levelorderHelper(subTreePtr->rChild, (level - 1), operation);
  }
}


void AVL::printBook(Book* thisBook) {
  //std::cout << " {(Name = " << thisBook->getName() << ") (Publisher = " << thisBook->getPublisher() << ")} ";
  std::cout << "{ID: (" << thisBook->getId() << ") COPIES: (" << thisBook->getCurrentCount() << ")}";
}
