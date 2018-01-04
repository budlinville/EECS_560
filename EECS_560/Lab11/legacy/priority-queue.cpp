#include "../../../include/lib/priority-queue/priority-queue.hpp"


///////////////////////////////////
// Private Functions Definitions //
///////////////////////////////////

//////////////////////////////////
// Public functions Definitions //
//////////////////////////////////

PriorityQueue::PriorityQueue(){
  rootPtr = nullptr;
  size = 0;
}

//constructor for a Priority Queue, given the rootPtr to a leftist heap
//ASSUMES that the rootPtr points to a properly ordered leftist heap
//USED in deleteMin(), to create two new priority queues that can then be concatenated back together
PriorityQueue::PriorityQueue(pq_node_t* pq){
  rootPtr = pq;
}

PriorityQueue::PriorityQueue(Edge** edges, int edgeSize){
  //No clue why, but edges are coming in in an array with values at every even index with odd indices being nonsense values
  /*
  for (int i = 0; i < edgeSize; i++) {
    std::cout << "(ii = " << i << "): " << edges[i]->getCost() << std::endl;
  }
  */
  for (int i = 0; i < edgeSize; i++) {
    //std::cout << "YUP: " << edges[i]->getCost() << std::endl;
    if (rootPtr == nullptr) {   //empty tree
      pq_node_t *newNode = new pq_node_t;
      newNode->lChild = nullptr;
      newNode->rChild = nullptr;
      newNode->rank = 0;
      newNode->edge = edges[i];
      rootPtr = newNode;
    } else {
      this->addElem(edges[i]);
    }
  }
}

PriorityQueue::~PriorityQueue() {
  destroyTree(rootPtr);
}

/*
3 STEPS
(1) Merging
(2) Labeling
(3) Swapping
*/
void PriorityQueue::concat(PriorityQueue* that){
  //no PriorityQueue yet
  if (that->rootPtr == nullptr) {         //dont need to do anything
    return;
  } else if (this->rootPtr == nullptr) {
    this->rootPtr = that->rootPtr;
    return;
  }

  pq_node_t *thisNode = this->rootPtr;
  pq_node_t *thatNode = that->rootPtr;
  pq_node_t *temp = nullptr;

  bool inserted = false;

  /*****FIRST STEP - MERGING ********/
  while (thatNode != nullptr) {
    inserted = false;
    while (!inserted) {
      if (thatNode->edge->getCost() < thisNode->edge->getCost()) {   //should only really happen when thisNode == rootNode
        //std::cout << "\nAAAAAAAAAAAAAAAAAAAAA" << std::endl;
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
        //std::cout << "\nBBBBBBBBBBBBBBBBBBBBBB" << std::endl;
        if ((thatNode->edge->getCost() < thisNode->rChild->edge->getCost())) {
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
        } else {    //if (thatNode->edge->getCost() > thisNode->edge->getCost())
          thisNode = thisNode->rChild;    //move downward
        }
      } else { //breaks second loop
        //std::cout << "\nCCCCCCCCCCCCCCCCCCCCCC" << std::endl;
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

  /*
  std::cout << "\n--------" << std::endl;
  inorderTraversal(rootPtr, 0, &PriorityQueue::printElement);
  std::cout << std::endl;
  postorderTraversal(rootPtr, 0, &PriorityQueue::printElement);
  std::cout << "\n--------" << std::endl;
  */
}

void PriorityQueue::addElem(Edge* edge) {
  Edge ** edgeArr = new Edge*[1];
  edgeArr[0] = edge;
  size++;

  PriorityQueue *p = new PriorityQueue(edgeArr, 1);

  concat(p);
}

Edge* PriorityQueue::deleteMinElem(){
  pq_node_t* temp = nullptr;
  Edge *ret = nullptr;

  if (rootPtr == nullptr) {
    //Error
    size = 0;
    return nullptr;
  }

  if ((rootPtr->lChild == nullptr) && (rootPtr->rChild == nullptr)) {
    temp = rootPtr;
    ret = temp->edge;
    rootPtr = nullptr;
    size = 0;
    delete temp;
    temp = nullptr;
    return ret;
  } else if (rootPtr->lChild == nullptr) {  //shouldnt happen
    temp = rootPtr;
    rootPtr = rootPtr->rChild;
    ret = temp->edge;
    size--;
    delete temp;
    temp = nullptr;
    return ret;
  } else if (rootPtr->rChild == nullptr) {
    temp = rootPtr;
    rootPtr = rootPtr->lChild;
    ret = temp->edge;
    size--;
    delete temp;temp = nullptr;
    return ret;
  }

  temp = rootPtr;
  ret = temp->edge;

  PriorityQueue *pqRight = new PriorityQueue(rootPtr->rChild);
  rootPtr = rootPtr->lChild;

  delete temp;
  temp = nullptr;
  concat(pqRight);
  size--;

  return ret;
}

int PriorityQueue::inorderTraversal(pq_node_t *treePtr, int identity, int (PriorityQueue::*op)(Edge*)){
  if (treePtr != nullptr) {
    identity = inorderTraversal(treePtr->lChild, identity, op);
    identity = (this->*op)(treePtr->edge);
    identity = inorderTraversal(treePtr->rChild, identity, op);
  }

  return identity;
}

int PriorityQueue::postorderTraversal(pq_node_t *treePtr, int identity, int (PriorityQueue::*op)(Edge*)){
  if (treePtr != nullptr) {
    identity = postorderTraversal(treePtr->lChild, identity, op);
    identity = postorderTraversal(treePtr->rChild, identity, op);
    identity = (this->*op)(treePtr->edge);
  }

  return identity;
}

int PriorityQueue::preorderTraversal(pq_node_t *treePtr, int identity, int (PriorityQueue::*op)(Edge*)){
  if (treePtr != nullptr) {
    identity = (this->*op)(treePtr->edge);
    identity = preorderTraversal(treePtr->lChild, identity, op);
    identity = preorderTraversal(treePtr->rChild, identity, op);
  }

  return identity;
}

int PriorityQueue::printElement(Edge* t) {
  std::cout << t->getCost() << " ";
  return 0;
}

int PriorityQueue::checkRankAndSwap(pq_node_t* treePtr) {
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
      pq_node_t *temp = treePtr->lChild;
      treePtr->lChild = treePtr->rChild;
      treePtr->rChild = temp;
      temp = nullptr;
    }
  }

  return rank;
}

void PriorityQueue::destroyTree(pq_node_t* treePtr) {
  if(treePtr != nullptr) {
    destroyTree(treePtr->lChild);
    destroyTree(treePtr->rChild);

    delete treePtr->edge;
    delete treePtr;
  }
}

int PriorityQueue::getSize() {
  return size;
}

pq_node_t* PriorityQueue::getRootPtr() {
  return rootPtr;
}

int PriorityQueue::sizeTraversal(pq_node_t *treePtr, int identity, int (PriorityQueue::*op)(int)){
  if (treePtr != nullptr) {
    identity = sizeTraversal(treePtr->lChild, identity, op);
    identity = (this->*op)(identity);
    identity = sizeTraversal(treePtr->rChild, identity, op);
  }

  return identity;
}
