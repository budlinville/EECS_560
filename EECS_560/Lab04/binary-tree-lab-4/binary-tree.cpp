#include "binary-tree.hpp"
#include "util.hpp"

BinaryTree::BinaryTree(){
  rootPtr = nullptr;
  //backPtr = nullptr;
  depth = 0;
}

BinaryTree::~BinaryTree() {
  this->destroyTree(rootPtr); // Call inherited method
}

//MAYBE OKAY
//remember to set "level" variable... super important
void BinaryTree::addElem(int elem) {
  BinaryNode<int>* newNode = new BinaryNode<int>(elem);
  bool wasSet = false;

  if (rootPtr == nullptr) {
    //std::cout << "(E) Tree is empty Adding element: " << elem << " to rootPtr. Depth is " << depth << std::endl;
    rootPtr = newNode;
    //depth still equals zero
  } else {
    wasSet = insertLevelOrder(rootPtr, newNode);

    //if full tree
    if (!wasSet) {
      BinaryNode<int>* temp = rootPtr;

      while (temp->getLeftChildPtr() != nullptr) {
        temp = temp->getLeftChildPtr();
      }

      temp->setLeftChildPtr(newNode);
      newNode->setIsFront(true);      //is front of row -> needed for easier deletion implementation
      depth++;
      //std::cout << "(F) Tree is full. Adding element: " << elem << ". Depth is " << depth << std::endl;
    }

    //backPtr = newNode;          //pointer to back of tree for simple delete implementation
    newNode->setLevel(depth);   //binary nodes hold depth value for easy implementation
  }
}

int BinaryTree::deleteElem() {
  if (depth == 0) {
    //std::cout << "Deleting root node. Tree is now empty." << std::endl;
    delete rootPtr;
    rootPtr = nullptr;
    return 0;
  }

  if (depth == 1) {
    int val = 0;
    BinaryNode<int>* temp = nullptr;

    if (rootPtr->getRightChildPtr() != nullptr) {
      temp = rootPtr->getRightChildPtr();
      val = temp->getItem();
      delete temp;
      rootPtr->setRightChildPtr(nullptr);
    } else {
      temp = rootPtr->getLeftChildPtr();
      val = temp->getItem();
      delete temp;
      rootPtr->setLeftChildPtr(nullptr);
      depth--;
    }

    return val;
  }

  bool del = false;
  int val = deleteLastElem(rootPtr, del);

  //std::cout << "Depth is: " << depth << std::endl;

  return val;
}

bool BinaryTree::exists(int elem) {
  bool isInTree = false;
  isInTree = checkElement(rootPtr, elem);
  return isInTree;
}

int BinaryTree::inorderTraverse(BinaryNode<int>* treePtr, int identity, int (BinaryTree::*operation)(int, int)){
  if (treePtr != nullptr) {
    identity = inorderTraverse(treePtr->getLeftChildPtr(), identity, operation);
    identity = (this->*operation)(identity, treePtr->getItem());
    identity = inorderTraverse(treePtr->getRightChildPtr(), identity, operation);
  }

  return identity;
}

int BinaryTree::preorderTraverse(BinaryNode<int>* treePtr, int identity, int (BinaryTree::*operation)(int, int)){
  if (treePtr != nullptr) {
    identity = (this->*operation)(identity, treePtr->getItem());
    identity = preorderTraverse(treePtr->getLeftChildPtr(), identity, operation);
    identity = preorderTraverse(treePtr->getRightChildPtr(), identity, operation);
  }
  return identity;
}

int BinaryTree::postorderTraverse(BinaryNode<int>* treePtr, int identity, int (BinaryTree::*operation)(int, int)){
  if (treePtr != nullptr) {
    identity = postorderTraverse(treePtr->getLeftChildPtr(), identity, operation);
    identity = postorderTraverse(treePtr->getRightChildPtr(), identity, operation);
    identity = (this->*operation)(identity, treePtr->getItem());
  }

  return identity;
}

int BinaryTree::sum(){
  int sum = inorderTraverse(rootPtr, 0, &BinaryTree::add);
  return sum;
}

void BinaryTree::print(int printType) {
  if(printType == 1){
    std::cout << "inorder traversal: " << std::endl;
    int arbitrary = inorderTraverse(rootPtr, 0, &BinaryTree::printElement);
    arbitrary = arbitrary; //to avoid warning message
    std::cout << std::endl;
  } else if (printType == 2){
    std::cout << "preorder traversal: " << std::endl;
    int arbitrary = preorderTraverse(rootPtr, 0, &BinaryTree::printElement);
    arbitrary = arbitrary; //to avoid warning message
    std::cout << std::endl;
  } else if (printType == 3){
    std::cout << "postorder traversal: " << std::endl;
    int arbitrary = postorderTraverse(rootPtr, 0, &BinaryTree::printElement);
    arbitrary = arbitrary; //to avoid warning message
    std::cout << std::endl;
  } else {
    std::cout << "Error invalid print type. Please choose a correct option."
              << std::endl;
  }
}

bool BinaryTree::insertLevelOrder(BinaryNode<int>* treePtr, BinaryNode<int>* newNode) {
  bool wasSet = false;
  //std::cout << "(BEG) SET VALUE: " << wasSet << std::endl;

  //singular case for tree with one node in it (the root node)
  if (depth == 0) {
    //std::cout << "(1) TREE HAS ONE NODE. ADDING (" << newNode->getItem() << ") TO LEFT CHILD." << std::endl;
    treePtr->setLeftChildPtr(newNode);
    depth++;
    return true;
  }

  if (treePtr->getLevel() == depth - 1) {
    if (treePtr->getLeftChildPtr() == nullptr) {
      //std::cout << "(L) Setting Left Child Ptr to " << newNode->getItem() << ". Depth is " << depth << std::endl;
      treePtr->setLeftChildPtr(newNode);
      return true;
      //return;
    } else if (treePtr->getRightChildPtr() == nullptr) {
      //std::cout << "(R) Setting Right Child Ptr to " << newNode->getItem() << ". Depth is " << depth << std::endl;
      treePtr->setRightChildPtr(newNode);
      return true;
      //return;
    }
  } else {
    wasSet = insertLevelOrder(treePtr->getLeftChildPtr(), newNode);

    if (!wasSet)
      wasSet = insertLevelOrder(treePtr->getRightChildPtr(), newNode);
  }

  //std::cout << "(END) SET VALUE: " << wasSet << std::endl;
  return wasSet;
}




/*
            BAD ALGORITHM
          *
        /  \
       *   *
     /  \
    *   *

This scenario returns true when clearly it is not a full treePtr

Was initially going to use this for the special case of adding an element to a full tree
Later realized this could be done more easily without checking this condition up front

*/
bool BinaryTree::isFullTree(BinaryNode<int>* subTreePtr) {
  //empty tree
  if (subTreePtr == nullptr)
    return true;

  //leaf node
  if (subTreePtr->getLeftChildPtr() == nullptr && subTreePtr->getRightChildPtr() == nullptr)
    return true;

  //check that left and right children are not nullptr's
  //if left and right subtrees are full, will return true
  if ((subTreePtr->getLeftChildPtr() != nullptr) && subTreePtr->getRightChildPtr() != nullptr)
    return (isFullTree(subTreePtr->getLeftChildPtr()) && isFullTree(subTreePtr->getRightChildPtr()));

  //if none of the above conditions hold:
  return false;
}

//x and y are arbitrary and just follow convention
int BinaryTree::printElement(int x, int y) {
  std::cout << y << " ";

  return 0;
}

int BinaryTree::add(int x, int y) {
  return (x + y);
}

bool BinaryTree::checkElement(BinaryNode<int>* subTreePtr, int elem) {
  bool found = false;

  if (subTreePtr == nullptr)
    return false;

  if (subTreePtr->getItem() == elem)
    return true;

  found = checkElement(subTreePtr->getLeftChildPtr(), elem);

  if (found)
    return true;

  found = checkElement(subTreePtr->getRightChildPtr(), elem);

  if (found)
    return true;

  return false;
}

//NEED TO FINISH THIS
int BinaryTree::deleteLastElem(BinaryNode<int>* subTreePtr, bool &deleted) {
  int value = 0;
  BinaryNode<int>* temp = nullptr;

  if (subTreePtr->getLevel() == depth - 1) {
    if (subTreePtr->getRightChildPtr() != nullptr) {
      temp = subTreePtr->getRightChildPtr();
      subTreePtr->setRightChildPtr(nullptr);
      value = temp->getItem();
      delete temp;
      deleted = true;

      return value;

    } else if (subTreePtr->getLeftChildPtr() != nullptr) {
      temp = subTreePtr->getLeftChildPtr();
      subTreePtr->setLeftChildPtr(nullptr);

      value = temp->getItem();
      if (temp->getIsFront())     //deleted first element of row; now have full tree
        depth--;

      delete temp;
      deleted = true;

      return value;
    }
  }

  if (subTreePtr->getRightChildPtr() != nullptr)
    value = deleteLastElem(subTreePtr->getRightChildPtr(), deleted);

  if (deleted == true) {
    return value;
  } else {
    if (subTreePtr->getLeftChildPtr() != nullptr)
      value = deleteLastElem(subTreePtr->getLeftChildPtr(), deleted);

      if (deleted == true)
        return value;
  }

  return 0;
}

void BinaryTree::destroyTree(BinaryNode<int>* subTreePtr) {
  if(subTreePtr != nullptr) {
    destroyTree(subTreePtr->getLeftChildPtr());
    destroyTree(subTreePtr->getRightChildPtr());
    delete subTreePtr;
  }
}
