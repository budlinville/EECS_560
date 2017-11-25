#include "priority-queue.hpp"
#include "util.hpp"


///////////////////////////////////
// Private Functions Definitions //
///////////////////////////////////

//////////////////////////////////
// Public functions Definitions //
//////////////////////////////////

PriorityQueue::PriorityQueue(){
  IMPLEMENT_ME();
}

PriorityQueue::PriorityQueue(Task* tasks, int taskSize){
  IMPLEMENT_ME();
}

PriorityQueue::~PriorityQueue() {
  IMPLEMENT_ME();
}


void PriorityQueue::concat(PriorityQueue* that){
  IMPLEMENT_ME();
}

void PriorityQueue::addElem(Task* task) {
  IMPLEMENT_ME();
}

Task* PriorityQueue::deleteMinElem(){
  IMPLEMENT_ME();
  return nullptr;
}

int PriorityQueue::inorderTraversal(int identity, int (*op)(Task*)){
  IMPLEMENT_ME();
  return 0;
}

int PriorityQueue::postorderTraversal(int identity, int (*op)(Task*)){
  IMPLEMENT_ME();
  return 0;
}
