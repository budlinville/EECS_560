#include "../../../include/priority-queue/skew-heap/skew-heap.hpp"

SkewHeap::SkewHeap(){
  rootPtr = nullptr;
  size = 0;
}

//constructor for a Priority Queue, given the rootPtr to a skew heap
//ASSUMES that the rootPtr points to a properly ordered skew heap
//USED in deleteMin(), to create two new priority queues that can then be concatenated back together
SkewHeap::SkewHeap(node_t* pq){
  rootPtr = pq;
}

SkewHeap::SkewHeap(Task** tasks, int taskSize){
  //No clue why, but tasks are coming in in an array with values at every even index with odd indices being nonsense values
  for (int i = 0; i < taskSize; i++) {
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

SkewHeap::~SkewHeap() {
  destroyTree(rootPtr);
}


void SkewHeap::concat(SkewHeap* that) {
  /*
  node_t *thisNode = this->rootPtr;
  node_t *thatNode = that->rootPtr;
  node_t *newNode = nullptr;

  int sizeLocal = this->getSize() + that->getSize();

  //no LeftistHeap yet
  if (thatNode == nullptr) {         //dont need to do anything
    return;
  } else if (thisNode == nullptr) {
    thisNode = thatNode;
    return;
  }

  /*
  std::cout << "\n--------" << std::endl;
  std::cout << "IN: ";
  inorderTraversal(rootPtr, 0, &SkewHeap::printElement);
  std::cout << std::endl;
  std::cout << "POST: ";
  postorderTraversal(rootPtr, 0, &SkewHeap::printElement);
  */
  /*
  //make sure thisNode points to heap with lowest root node
  if (thatNode->task->getNice() < thisNode->task->getNice()) {
    node_t *temp = thisNode;
    thisNode = thatNode;
    thatNode = temp;
    temp = nullptr;
  }

  newNode = thisNode;
  newNode->rChild = thisNode->lChild;
  newNode->lChild = merge(thisNode->rChild, thatNode);

  this->rootPtr = newNode;
  size = sizeLocal;
  */

  this->rootPtr = merge(this->rootPtr, that->rootPtr);
}

void SkewHeap::addElem(Task* task) {
  Task ** taskArr = new Task*[1];
  taskArr[0] = task;
  size++;

  SkewHeap *p = new SkewHeap(taskArr, 1);

  concat(p);
}

Task* SkewHeap::deleteMinElem(){
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

  SkewHeap *pqRight = new SkewHeap(rootPtr->rChild);
  rootPtr = rootPtr->lChild;

  delete temp;
  temp = nullptr;
  concat(pqRight);
  size--;

  return ret;
}

int SkewHeap::inorderTraversal(node_t *treePtr, int identity, int (SkewHeap::*op)(Task*)){
  if (treePtr != nullptr) {
    identity = inorderTraversal(treePtr->lChild, identity, op);
    identity = (this->*op)(treePtr->task);
    identity = inorderTraversal(treePtr->rChild, identity, op);
  }

  return identity;
}

int SkewHeap::postorderTraversal(node_t *treePtr, int identity, int (SkewHeap::*op)(Task*)){
  if (treePtr != nullptr) {
    identity = postorderTraversal(treePtr->lChild, identity, op);
    identity = postorderTraversal(treePtr->rChild, identity, op);
    identity = (this->*op)(treePtr->task);
  }

  return identity;
}

int SkewHeap::preorderTraversal(node_t *treePtr, int identity, int (SkewHeap::*op)(Task*)){
  if (treePtr != nullptr) {
    identity = (this->*op)(treePtr->task);
    identity = preorderTraversal(treePtr->lChild, identity, op);
    identity = preorderTraversal(treePtr->rChild, identity, op);
  }

  return identity;
}

int SkewHeap::printElement(Task* t) {
  std::cout << t->getNice() << " ";
  return 0;
}

void SkewHeap::destroyTree(node_t* treePtr) {
  if(treePtr != nullptr) {
    destroyTree(treePtr->lChild);
    destroyTree(treePtr->rChild);

    delete treePtr->task;
    delete treePtr;
  }
}

int SkewHeap::getSize() {return 0;
  return size;
}

node_t* SkewHeap::getRootPtr() {
  return rootPtr;
}

int SkewHeap::sizeTraversal(node_t *treePtr, int identity, int (SkewHeap::*op)(int)){
  if (treePtr != nullptr) {
    identity = sizeTraversal(treePtr->lChild, identity, op);
    identity = (this->*op)(identity);
    identity = sizeTraversal(treePtr->rChild, identity, op);
  }
  return identity;
}

/*
THE FOLLOWING ARE GOOD DEBUGGING TECHNIQUES:

std::cout << "\n--------" << std::endl;
std::cout << "IN: ";
inorderTraversal(rootPtr, 0, &SkewHeap::printElement);
std::cout << std::endl;
std::cout << "POST: ";
postorderTraversal(rootPtr, 0, &SkewHeap::printElement);

std::cout << "P: " << ((p != nullptr) ? std::to_string(p->task->getNice()) : "NULL") << "; Q: " << ((q != nullptr) ? std::to_string(q->task->getNice()) : "NULL") << std::endl;
std::cout << "\n--------" << std::endl;
*/
node_t* SkewHeap::merge(node_t *p, node_t *q) {
  if (p == nullptr)
    return q;

  if (q == nullptr)
    return p;

  if (p->task != nullptr && q->task != nullptr) {
    if (p->task->getNice() <= q->task->getNice()) {
      node_t* temp = p->rChild;
      p->rChild = p->lChild;
      p->lChild = merge(q, temp);
      return p;
    }
  }

  return merge(q, p);
}

void SkewHeap::setSize(int s) {
  size = s;
}
