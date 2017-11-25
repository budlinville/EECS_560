#include "task.hpp"
#include "util.hpp"

Task::Task(int id, int p, int aid, int t): tid(id), nice(p), appId(aid), ttl(t) {}

Task::Task(std::string){
  IMPLEMENT_ME();
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
