#include <iostream>
#include <stdlib.h>   //for rand and srand
#include <time.h>     //for time to pass into srand for better random number generation
#include "timer.hpp"
#include "list.hpp"
#include "util.hpp"

int  main() {
  Timer* t = new Timer();

  int MAX_INT[9] = {10, 50, 100, 500, 1000, 5000, 10000, 50000, 100000};

  //loop to iterate through all doubly linked lists of all MAX_INT[] sizes
  for (int i = 0; i < 9; i++) {
    std::cout << "MAX_INT value: " << MAX_INT[i] << std::endl;

    //loop for 10 test cases
    for (int j = 0; j < 10; j++) {
      std::cout << "\tTest " << (j + 1) << ": ";

      DoublyLinkedList *dll = new DoublyLinkedList(); //initialize linked list
      int randNum = 0;  //randomly generated number using rand()

      srand(time(NULL));  //generate random succession of rand

      //loop to create double linked list of size MAX_INT[i]
      for (int k = 0; k < MAX_INT[i]; k++) {
        //generate random number between 1 and MAX_INT[i]
        randNum = rand() % MAX_INT[i] + 1;

        //add random number to linked list
        dll->add(randNum, dll->size());
      }

      randNum = rand() % MAX_INT[i] + 1;
      t->start(); //start timer

      dll->deleteAll(randNum); //delete all occurances of randNum

      t->printTime(t->stop());
    }
  }

  return 0;
}
