#include "../../include/priority-queue/priority-queue.hpp"
#include "../../include/util/util.hpp"


///////////////////////////////////
// Private Functions Definitions //
///////////////////////////////////

//////////////////////////////////
// Public functions Definitions //
//////////////////////////////////

PriorityQueue::PriorityQueue(){
  myHeap = new SkewHeap;
}

PriorityQueue::PriorityQueue(Task** tasks, int taskSize){
  myHeap = new SkewHeap(tasks, taskSize);
}

PriorityQueue::~PriorityQueue() {
  delete myHeap;
}


void PriorityQueue::concat(PriorityQueue* that){
  myHeap->concat(that->getHeap());
}

void PriorityQueue::addElem(Task* task) {
  myHeap->addElem(task);
}

Task* PriorityQueue::deleteMinElem(){
  return myHeap->deleteMinElem();
}

int PriorityQueue::inorderTraversal(node_t *treePtr, int identity, int (SkewHeap::*op)(Task*)){
  return myHeap->inorderTraversal(treePtr, identity, op);
}

int PriorityQueue::postorderTraversal(node_t *treePtr, int identity, int (SkewHeap::*op)(Task*)){
  return myHeap->postorderTraversal(treePtr, identity, op);
}

node_t* PriorityQueue::getRootPtr() {
  return myHeap->getRootPtr();
}

int PriorityQueue::getSize() {
  return myHeap->getSize();
}

SkewHeap* PriorityQueue::getHeap() {
  return myHeap;
}
