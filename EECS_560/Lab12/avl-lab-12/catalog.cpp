#include "catalog.hpp"
#include "util.hpp"

Catalog::Catalog(){
  inventory = new AVL();
}


Catalog::~Catalog(){
  delete inventory;
}



void Catalog::addBook(int id, std::string bookName, std::string publisher, int copyCount){
  Book* thisBook = inventory->search(id);

  if (thisBook == nullptr) {
    thisBook = new Book(id, bookName, publisher, copyCount);
    inventory->addBook(thisBook);
    return;
  }

  thisBook->setCurrentCount(thisBook->getCurrentCount() + copyCount);
  thisBook->setTotalCount(thisBook->getTotalCount() + copyCount);
}


Book* Catalog::checkoutBook(int id){
  Book* thisBook = inventory->search(id);

  if (thisBook == nullptr) {
    std::cout << "I am sorry. We do not own any copies of this book." << std::endl;
    return nullptr;
  }

  if (thisBook->getCurrentCount() <= 0) {
    std::cout << "I am sorry. All copies of this book have already been checked out. Please try again later." << std::endl;
    return thisBook;
  }

  thisBook->setCurrentCount(thisBook->getCurrentCount() - 1);

  return thisBook;
}


void Catalog::returnBook(int id){
  Book* thisBook = inventory->search(id);

  if (thisBook == nullptr) {
    std::cout << "I am sorry. We do not have records of this book in our system. I believe it belongs elsewhere." << std::endl;
    return;
  }

  if (thisBook->getCurrentCount() >= thisBook->getTotalCount()) {
    std::cout << "I am sorry. We already have all of our copies of this book. I believe this belongs elsewhere." << std::endl;
    return;
  }

  thisBook->setCurrentCount(thisBook->getCurrentCount() + 1);
}
