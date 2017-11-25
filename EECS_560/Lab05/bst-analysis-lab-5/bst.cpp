#include "bst.hpp"
#include "util.hpp"

BST::BST() {
  rootPtr = nullptr;
}

BST::~BST() {
  this->destroyTree(rootPtr); // Call inherited method
}

bool BST::isEmpty() {
  return (rootPtr == nullptr);
}

void BST::addElem(int elem) {
  BinaryNode<int> *newNodePtr = new BinaryNode<int>(elem);

  if (rootPtr == nullptr) {   //base case
    rootPtr = newNodePtr;
  } else {
    insertInorder(rootPtr, newNodePtr);
  }
}

/*TODO: GOING TO BE DIFFICULT TO CHECK FOR HEIGHT VARIABLE AFTER DELETING ELEMENT
        COULD CREATE MEMBER VARIABLE POINTING TO ELEMENT OF LONGEST PATH

  NOTE: VERY important to use getParentToDeleteNode() as opposed to findNode()
        we need the parent node so that we can both delete the proper node
        AND avoid memory leaks by setting the parent's node children pointers

  NOTE: We use deleteNodeIsLeft and so that we dont have to call both
        getParentToDeleteNode() and findNode()
        Could also check the elements in the left and right children but whatever

  NOTE: wont actually delete nodeToDelete
        will copy a new value into it and delete a child node
*/

void BST::deleteElem(int elem) {
  if (rootPtr == nullptr) {
    return;
  }

  //Need to remove all instances of "elem"
  bool allElemsRemoved = false;

  while (!allElemsRemoved) {
    bool deleteNodeIsLeft = false;
    bool deletingRoot = false;
    BinaryNode<int>* parentToDeleteNode = getParentToDeleteNode(rootPtr, elem, deleteNodeIsLeft);

    if (parentToDeleteNode == nullptr && rootPtr->getItem() != elem) {      //no node to delete
      allElemsRemoved = true;
    } else {
      BinaryNode<int>* nodeToDelete = nullptr;
      if (rootPtr->getItem() == elem) {
        nodeToDelete = rootPtr;
        deletingRoot = true;
      } else {
        if (deleteNodeIsLeft) {
          nodeToDelete = parentToDeleteNode->getLeftChildPtr();
        } else {
          nodeToDelete = parentToDeleteNode->getRightChildPtr();
        }
      }

      BinaryNode<int>* leftChild = nullptr;
      BinaryNode<int>* rightChild = nullptr;
      int newVal = 0;

      //if (nodeToDelete == nullptr)
        //return;

      leftChild = nodeToDelete->getLeftChildPtr();
      rightChild = nodeToDelete->getRightChildPtr();

      if (leftChild == nullptr && rightChild == nullptr) {
        if (deletingRoot) {
          rootPtr = nullptr;
        } else {
          if (deleteNodeIsLeft) {
            parentToDeleteNode->setLeftChildPtr(nullptr);
          } else {
            parentToDeleteNode->setRightChildPtr(nullptr);
          }
        }

        delete nodeToDelete;
      } else if (leftChild == nullptr) {      //AND rightChild does not
        newVal = rightChild->getItem();
        nodeToDelete->setItem(newVal);
        nodeToDelete->setLeftChildPtr(rightChild->getLeftChildPtr());
        nodeToDelete->setRightChildPtr(rightChild->getRightChildPtr());

        delete rightChild;
      } else if (rightChild == nullptr) {     //AND leftChild does not
        newVal = leftChild->getItem();
        nodeToDelete->setItem(newVal);
        nodeToDelete->setLeftChildPtr(leftChild->getLeftChildPtr());
        nodeToDelete->setRightChildPtr(leftChild->getRightChildPtr());

        delete leftChild;
      } else {      //go right once, then left as far as you can
        //need tempFront and tempBack. we will delete tempFront,
        //but we need temp back so we can set children properly
        BinaryNode<int>* tempBack = rightChild;   //"Went right once"
        BinaryNode<int>* tempFront = tempBack->getLeftChildPtr();

        if (tempFront != nullptr) {
          while (tempFront->getLeftChildPtr() != nullptr) {
            tempFront = tempFront->getLeftChildPtr();
            tempBack = tempBack->getLeftChildPtr();
          }

          newVal = tempFront->getItem();
          nodeToDelete->setItem(newVal);

          //temp's left child is DEFINITELY nullptr, but we know nothing
          //about its right child and whether there exists a tree to the right
          //MUST account for the situation where there exists a tree to the right
          if (tempFront->getRightChildPtr() == nullptr) {      //just delete a leaf node
            tempBack->setLeftChildPtr(nullptr);
            delete tempFront;
          } else {
            BinaryNode<int>* tempFrontRight = tempFront->getRightChildPtr();
            int newTempVal = tempFrontRight->getItem();

            tempFront->setItem(newTempVal);
            tempFront->setLeftChildPtr(tempFrontRight->getLeftChildPtr());
            tempFront->setRightChildPtr(tempFrontRight->getRightChildPtr());

            delete tempFrontRight;
          }
        } else {
          nodeToDelete->setItem(tempBack->getItem());
          nodeToDelete->setRightChildPtr(tempBack->getRightChildPtr());

          delete tempBack;
        }
      }
    }

    if (rootPtr == nullptr)
      return;
  }
}

bool BST::exists(int elem) {
  bool isInTree = false;
  isInTree = checkElement(rootPtr, elem);
  return isInTree;
}

int BST::inorderTraverse(BinaryNode<int>* treePtr, int identity, int (BST::*operation)(int, int)){
  if (treePtr != nullptr) {
    identity = inorderTraverse(treePtr->getLeftChildPtr(), identity, operation);
    identity = (this->*operation)(identity, treePtr->getItem());
    identity = inorderTraverse(treePtr->getRightChildPtr(), identity, operation);
  }

  return identity;
}

int BST::postorderTraverse(BinaryNode<int>* treePtr, int identity, int (BST::*operation)(int, int)){
  if (treePtr != nullptr) {
    identity = postorderTraverse(treePtr->getLeftChildPtr(), identity, operation);
    identity = postorderTraverse(treePtr->getRightChildPtr(), identity, operation);
    identity = (this->*operation)(identity, treePtr->getItem());
  }

  return identity;
}

int BST::preorderTraverse(BinaryNode<int>* treePtr, int identity, int (BST::*operation)(int, int)){
  if (treePtr != nullptr) {
    identity = (this->*operation)(identity, treePtr->getItem());
    identity = preorderTraverse(treePtr->getLeftChildPtr(), identity, operation);
    identity = preorderTraverse(treePtr->getRightChildPtr(), identity, operation);
  }
  return identity;
}

int BST::levelorderTraverse(BinaryNode<int>* treePtr, int identity, int (BST::*operation)(int, int)){
  int h = getHeight(treePtr);

  for (int i = 0; i <= h; i++) {
    identity = levelorderHelper(treePtr, i, identity, operation);
  }

  return identity;
}

int BST::height(){
  return (getHeight(rootPtr));
}

void BST::print(int printType){
  if(printType == 1){
	   std::cout << "inorder traversal: ";
	    inorderTraverse(rootPtr, 0, &BST::printElement);
      std::cout << std::endl;
  } else if(printType == 2){
	   std::cout << "preorder traversal: ";
	    preorderTraverse(rootPtr, 0, &BST::printElement);
      std::cout << std::endl;
  } else if(printType == 3){
	   std::cout << "postorder traversal: ";
	    postorderTraverse(rootPtr, 0, &BST::printElement);
      std::cout << std::endl;
  } else if(printType == 4){
	   std::cout << "levelorder traversal: ";
	    levelorderTraverse(rootPtr, 0, &BST::printElement);
      std::cout << std::endl;
  }	else {
	   std::cout << "Error invalid print type. Please choose a correct option." << std::endl;
  }
}

/************************************************
*                                               *
*                MY FUNCTIONS                   *
*                                               *
************************************************/
void BST::destroyTree(BinaryNode<int>* subTreePtr) {
  if(subTreePtr != nullptr) {
    destroyTree(subTreePtr->getLeftChildPtr());
    destroyTree(subTreePtr->getRightChildPtr());
    delete subTreePtr;
  }
}

void BST::insertInorder(BinaryNode<int>* subTreePtr, BinaryNode<int>* newNodePtr) {
  if (subTreePtr->getItem() <= newNodePtr->getItem()) {
    if (subTreePtr->getRightChildPtr() == nullptr) {
      subTreePtr->setRightChildPtr(newNodePtr);
    } else {
      insertInorder(subTreePtr->getRightChildPtr(), newNodePtr);
    }
  } else {
    if (subTreePtr->getLeftChildPtr() == nullptr) {
      subTreePtr->setLeftChildPtr(newNodePtr);
    } else {
      insertInorder(subTreePtr->getLeftChildPtr(), newNodePtr);
    }
  }
}

bool BST::checkElement(BinaryNode<int>* subTreePtr, int elem) {
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

int BST::printElement(int x, int y) {
  std::cout << y << " ";
  return 0;
}

/*
  RETURNS: Node that contains "target"
           nullptr if not found
  NOTE: Originally used with delete() to delete particular elements
  NOTE: Not actually used because it became more important to get the parent
        to the node being deleted to avoid memory leaks
*/
BinaryNode<int>* BST::findNode(BinaryNode<int>* subTreePtr, const int target) const {
  if (subTreePtr == nullptr) {    //base case 1.... failure case
    return nullptr;
  } else if (subTreePtr->getItem() == target) {  //base case 2...found target
    return subTreePtr;
  } else if (target < subTreePtr->getItem()) {
    return findNode(subTreePtr->getLeftChildPtr(), target);
  } else {
    return findNode(subTreePtr->getRightChildPtr(), target);
  }
}
/*
  RETURNS: The parent to a node that contains "target"
  NOTE: contains byreference variable "isLeft". This is because this functions
        is used in the delete method and we need to know whether we are
        deleting the left or right child of the "parent to the node being deleted"
*/
BinaryNode<int>* BST::getParentToDeleteNode(BinaryNode<int>* subTreePtr, const int target, bool &isLeft) {
  if (subTreePtr == nullptr) {    //base case 1.... failure case
    return nullptr;
  } else {

    if (subTreePtr->getLeftChildPtr() != nullptr) {
      if (subTreePtr->getLeftChildPtr()->getItem() == target) {
        isLeft = true;
        return subTreePtr;
      }
    }

    if (subTreePtr->getRightChildPtr() != nullptr) {
      if (subTreePtr->getRightChildPtr()->getItem() == target) {
        isLeft = false;
        return subTreePtr;
      }
    }

    if (target < subTreePtr->getItem()) {
      return getParentToDeleteNode(subTreePtr->getLeftChildPtr(), target, isLeft);
    } else {
      return getParentToDeleteNode(subTreePtr->getRightChildPtr(), target, isLeft);
    }
  }
}

int BST::getHeight(BinaryNode<int>* subTreePtr) {
  if (subTreePtr == nullptr)
    return -1;

  int leftHeight = getHeight(subTreePtr->getLeftChildPtr());
  int rightHeight = getHeight(subTreePtr->getRightChildPtr());

  if (leftHeight > rightHeight) {
    return (leftHeight + 1);
  } else {
    return (rightHeight + 1);
  }
}

int BST::levelorderHelper(BinaryNode<int>* subTreePtr, int level, int identity, int (BST::*operation)(int, int)) {
  if (subTreePtr == nullptr)
    return identity;

  if (level == 0) {
    identity = (this->*operation)(identity, subTreePtr->getItem());
  } else if (level > 0) {
    identity = levelorderHelper(subTreePtr->getLeftChildPtr(), (level - 1), identity, operation);
    identity = levelorderHelper(subTreePtr->getRightChildPtr(), (level - 1), identity, operation);
  }

  return identity;
}
