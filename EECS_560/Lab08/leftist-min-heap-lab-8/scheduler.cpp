#include "scheduler.hpp"
#include "task.hpp"
#include "util.hpp"

Scheduler::Scheduler(){
  this->schedule = new PriorityQueue();
}

void Scheduler::addApplicationToSchedule(Application* app){
  schedule->concat(app->getTasks());

  /* FOR DEBUGGING
  node_t *rootPtr = schedule->getRootPtr();
  std::cout << "--------" << std::endl;
  std::cout << "IN: ";
  schedule->inorderTraversal(rootPtr, 0, &PriorityQueue::printElement);
  std::cout << std::endl;
  std::cout << "POST: ";
  schedule->postorderTraversal(rootPtr, 0, &PriorityQueue::printElement);
  std::cout << std::endl;
  std::cout << "PRE: ";
  schedule->preorderTraversal(rootPtr, 0, &PriorityQueue::printElement);
  std::cout << "\n--------" << std::endl;
  */
}

Task* Scheduler::executeNextOnProcessor(){
  Task* nextTask = schedule->deleteMinElem();
  return nextTask;
}

bool Scheduler::isEmpty(){
  return (schedule->getRootPtr() == nullptr);
}

int Scheduler::scheduleSize(){
  node_t* myRoot = schedule->getRootPtr();

  if (myRoot == nullptr)
    return 0;

  int size = schedule->getSize();
  //int size = schedule->sizeTraversal(myRoot, 0, &PriorityQueue::getSize);
  //std::cout << "SIZE IS " << size << std::endl;
  return size;
}
