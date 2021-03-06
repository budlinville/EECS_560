#include "../../../include/priority-queue/leftist-heap/leftist-heap.hpp"

LeftistHeap::LeftistHeap(){
  rootPtr = nullptr;
  size = 0;
}

//constructor for a Priority Queue, given the rootPtr to a leftist heap
//ASSUMES that the rootPtr points to a properly ordered leftist heap
//USED in deleteMin(), to create two new priority queues that can then be concatenated back together
LeftistHeap::LeftistHeap(node_t* pq){
  rootPtr = pq;
}

LeftistHeap::LeftistHeap(Task** tasks, int taskSize){
  //No clue why, but tasks are coming in in an array with values at every even index with odd indices being nonsense values
  for (int i = 0; i < taskSize; i++) {
    //std::cout << "YUP: " << tasks[i]->getNice() << std::endl;
    if (rootPtr == nullptr) {   //empty tree
      node_t *newNode = new node_t;
      newNode->lChild = nullptr;
      newNode->rChild = nullptr;
      newNode->rank = 0;
      newNode->task = tasks[i];
      rootPtr = newNode;
    } else {
      this->addElem(tasks[i]);
    }
  }
}

LeftistHeap::~LeftistHeap() {
  destroyTree(rootPtr);
}

/*
3 STEPS
(1) Merging
(2) Labeling
(3) Swapping
*/
void LeftistHeap::concat(LeftistHeap* that){
  //no LeftistHeap yet
  if (that->rootPtr == nullptr) {         //dont need to do anything
    return;
  } else if (this->rootPtr == nullptr) {
    this->rootPtr = that->rootPtr;
    return;
  }

  node_t *thisNode = this->rootPtr;
  node_t *thatNode = that->rootPtr;
  node_t *temp = nullptr;

  bool inserted = false;

  /*****FIRST STEP - MERGING ********/
  while (thatNode != nullptr) {
    inserted = false;
    while (!inserted) {
      if (thatNode->task->getNice() < thisNode->task->getNice()) {   //should only really happen when thisNode == rootNode
        //lets just swap thisNode and thatNode and then go from there
        //change root first
        if (rootPtr == thisNode)    //should happen everytime we get here if my logic is correct - included "if" as a safety net
          rootPtr = thatNode;

        temp = thisNode;
        thisNode = thatNode;
        thatNode = temp;

        //done inserting
        inserted = true;
        temp = nullptr;
      } else if (thisNode->rChild != nullptr) {
        if ((thatNode->task->getNice() < thisNode->rChild->task->getNice())) {
          //insert thatNode into thisNode's position
          //easier to just change thisNode's values in practice

          //store thisNode's current right child in temp
          temp = thisNode->rChild;

          //set thisNode's new right child
          thisNode->rChild = thatNode;

          //set thatNode to thisNode's old right child for future merges
          thatNode = temp;

          //done inserting
          inserted = true;
          temp = nullptr;
        } else {    //if (thatNode->task->getNice() > thisNode->task->getNice())
          thisNode = thisNode->rChild;    //move downward
        }
      } else { //breaks second loop
        thisNode->rChild = thatNode;
        thatNode = nullptr;
        temp = nullptr;
        inserted = true;

      }
    }
  }

  /*****SECOND STEP - LABELING ********/
  /*****THIRD STEP - SWAPPING ********/
  //Can combine these two steps
  //inherently recursive
  checkRankAndSwap(rootPtr);
}

void LeftistHeap::addElem(Task* task) {
  Task ** taskArr = new Task*[1];
  taskArr[0] = task;
  size++;

  LeftistHeap *p = new LeftistHeap(taskArr, 1);

  concat(p);
}

Task* LeftistHeap::deleteMinElem(){
  node_t* temp = nullptr;
  Task *ret = nullptr;

  if (rootPtr == nullptr) {
    //Error
    size = 0;
    return nullptr;
  }

  if ((rootPtr->lChild == nullptr) && (rootPtr->rChild == nullptr)) {
    temp = rootPtr;
    ret = temp->task;
    rootPtr = nullptr;
    size = 0;
    delete temp;
    temp = nullptr;
    return ret;
  } else if (rootPtr->lChild == nullptr) {  //shouldnt happen
    temp = rootPtr;
    rootPtr = rootPtr->rChild;
    ret = temp->task;
    size--;
    delete temp;
    temp = nullptr;
    return ret;
  } else if (rootPtr->rChild == nullptr) {
    temp = rootPtr;
    rootPtr = rootPtr->lChild;
    ret = temp->task;
    size--;
    delete temp;temp = nullptr;
    return ret;
  }

  temp = rootPtr;
  ret = temp->task;

  LeftistHeap *pqRight = new LeftistHeap(rootPtr->rChild);
  rootPtr = rootPtr->lChild;

  delete temp;
  temp = nullptr;
  concat(pqRight);
  size--;

  return ret;
}

int LeftistHeap::inorderTraversal(node_t *treePtr, int identity, int (LeftistHeap::*op)(Task*)){
  if (treePtr != nullptr) {
    identity = inorderTraversal(treePtr->lChild, identity, op);
    identity = (this->*op)(treePtr->task);
    identity = inorderTraversal(treePtr->rChild, identity, op);
  }

  return identity;
}

int LeftistHeap::postorderTraversal(node_t *treePtr, int identity, int (LeftistHeap::*op)(Task*)){
  if (treePtr != nullptr) {
    identity = postorderTraversal(treePtr->lChild, identity, op);
    identity = postorderTraversal(treePtr->rChild, identity, op);
    identity = (this->*op)(treePtr->task);
  }

  return identity;
}

int LeftistHeap::preorderTraversal(node_t *treePtr, int identity, int (LeftistHeap::*op)(Task*)){
  if (treePtr != nullptr) {
    identity = (this->*op)(treePtr->task);
    identity = preorderTraversal(treePtr->lChild, identity, op);
    identity = preorderTraversal(treePtr->rChild, identity, op);
  }

  return identity;
}

int LeftistHeap::printElement(Task* t) {
  std::cout << t->getNice() << " ";
  return 0;
}

int LeftistHeap::checkRankAndSwap(node_t* treePtr) {
  int rank = 0;

  if (treePtr == nullptr)
    return 0;

  if (treePtr->lChild == nullptr && treePtr->rChild == nullptr) {
    rank = 0;
    //no children - dont need to check if I need to swap
  } else if (treePtr->lChild == nullptr) {  //lchild = nullptr, rchild does not - will need to swap
    rank = 0;
    treePtr->lChild = treePtr->rChild;
    treePtr->rChild = nullptr; //dont need a tempPtr
  } else if (treePtr->rChild == nullptr) {    //no swap, rankLeft >= rankRight
    rank = 0;
  } else {
    int rankLeft = checkRankAndSwap(treePtr->lChild);
    int rankRight = checkRankAndSwap(treePtr->rChild);

    rank = (rankLeft > rankRight) ? (rankLeft + 1) : (rankRight + 1);
    treePtr->rank = rank;

    if (rankRight > rankLeft) {
      //swap
      node_t *temp = treePtr->lChild;
      treePtr->lChild = treePtr->rChild;
      treePtr->rChild = temp;
      temp = nullptr;
    }
  }

  return rank;
}

void LeftistHeap::destroyTree(node_t* treePtr) {
  if(treePtr != nullptr) {
    destroyTree(treePtr->lChild);
    destroyTree(treePtr->rChild);

    delete treePtr->task;
    delete treePtr;
  }
}

int LeftistHeap::getSize() {
  return size;
}

node_t* LeftistHeap::getRootPtr() {
  return rootPtr;
}

int LeftistHeap::sizeTraversal(node_t *treePtr, int identity, int (LeftistHeap::*op)(int)){
  if (treePtr != nullptr) {
    identity = sizeTraversal(treePtr->lChild, identity, op);
    identity = (this->*op)(identity);
    identity = sizeTraversal(treePtr->rChild, identity, op);
  }

  return identity;
}
