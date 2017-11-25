#include "task.hpp"
#include "util.hpp"

#include <algorithm>

Task::Task(int id, int p, int aid, int t): tid(id), nice(p), appId(aid), ttl(t) {}

Task::Task(std::string str){
  std::string pieces[4];
  int piecesInt[4];

  //std::cout << "IN TASK: {" << str << "}" << std::endl;

  str = str.erase(0, 1);    //delete "("
  for (int i = 0; i < 4; i++) {
    pieces[i] = str.substr(0, (str.find_first_of(",)", 0)));
    str = str.erase(0, (str.find_first_of(",", 0) + 2));      //delete "," and " "
    piecesInt[i] = stoi(pieces[i]);
  }

  tid = piecesInt[0];
  nice = piecesInt[1];
  appId = piecesInt[2];
  ttl = piecesInt[3];
}

int Task::getTid() {
  return this->tid;
}

int Task::getNice() {
  return this->nice;
}

int Task::getAppId(){
  return this->appId;
}

int Task::getTtl(){
  return this->ttl;
}
