#include "../../include/simulator/application.hpp"
#include "../../include/priority-queue/priority-queue.hpp"

Application::Application(std::string str){
  Task** taskArr = nullptr;
  int numTasks = 0;

  //std::cout << "YUPPERS: {" << str.substr(0, (str.find_first_of(" ", 0))) << "}" <<std::endl;

  id =  stoi(str.substr(0, (str.find_first_of(" ", 0))));
  str = str.erase(0, (str.find_first_of(" ", 0) + 1));      //delete appID and " "

  name = str.substr(0, (str.find_first_of("(", 0)));
  name.pop_back();      //delete " "
  str = str.erase(0, (str.find_first_of("(", 0)));    //delete name and " "

  //get number of tasks
  for (unsigned int i = 0; i < str.size(); i++) {
    if (str.at(i) == ')')
      numTasks++;
  }

  //initialize task array
  taskArr = new Task*[numTasks];
  std::string temp = "";

  for (int i = 0; i < numTasks; i++) {
    temp = str.substr(0, (str.find_first_of(")", 0) + 1));
    taskArr[i] = new Task(temp);
    str = str.erase(0, (str.find_first_of(")", 0) + 2));      //delete ")" and " "
  }

  //initialize piorityqueue
  tasks = new PriorityQueue(taskArr, numTasks);

  /* TESTING
  std::cout << "ID: {" << id << "}" << std::endl;
  std::cout << "NAME: {" << name << "}" << std::endl;
  std::cout << "NUMBER OF TASKS: {" << numTasks << "}" << std::endl;
  */
}

Application::Application(int i,
                         std::string appName,
                         Task** ts,
                         int size){

  tasks = new PriorityQueue(ts, size);
  id = i;
  name = appName;
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
  node_t* pqRoot = tasks->getRootPtr();

  if (pqRoot == nullptr)
    return 0;

  int size = tasks->getSize();
  //int size = tasks->sizeTraversal(pqRoot, 0, &PriorityQueue::getSize);
  return size;
}
