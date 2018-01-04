#include "book.hpp"
#include "util.hpp"


Book::Book(int id, std::string name, std::string publisher, int copyCount) {
  this->id = id;
  this->name = name;
  this->publisher = publisher;
  currentCount = copyCount;
  totalCount = copyCount;
}


int Book::getId() {
  return id;
}


std::string Book::getName(){
  return name;
}


std::string Book::getPublisher(){
  return publisher;
}


int Book::getCurrentCount(){
  return currentCount;
}


void Book::setCurrentCount(int count){
  currentCount = count;
}


int Book::getTotalCount(){
  return totalCount;
}


void Book::setTotalCount(int count){
  totalCount = count;
}
