#include "application.hpp"
#include "priority-queue.hpp"

Application::Application(std::string){
  IMPLEMENT_ME();
}


Application::Application(int i,
                         std::string appName,
                         Task* ts,
                         int size){
  IMPLEMENT_ME();
}

int Application::getId(){
  return this->id;
}


std::string Application::getName(){
  return this->name;
}



PriorityQueue* Application::getTasks(){
  return this->tasks;
}



int Application::getSize(){
  IMPLEMENT_ME();
  return 0;
}
