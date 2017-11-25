#include "scheduler.hpp"
#include "task.hpp"
#include "util.hpp"

Scheduler::Scheduler(){
  this->schedule = new PriorityQueue();
  IMPLEMENT_ME();
}

void Scheduler::addApplicationToSchedule(Application* app){
  IMPLEMENT_ME();
}

Task* Scheduler::executeNextOnProcessor(){
  IMPLEMENT_ME();
  return new Task(0, 0, 0, 0);
}

bool Scheduler::isEmpty(){
  IMPLEMENT_ME();
  return true;
}

int Scheduler::scheduleSize(){
  IMPLEMENT_ME();
  return 0;
}
