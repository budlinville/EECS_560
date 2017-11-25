#include <iostream>
#include <stdlib.h>   //for rand and srand
#include <time.h>     //for time to pass into srand for better random number generation
#include <fstream>
#include <cstdlib>
#include <string>
#include <unistd.h>

#include "util/timer.hpp"
#include "../include/priority-queue/leftist-heap/leftist-heap.hpp"
#include "../include/priority-queue/skew-heap/skew-heap.hpp"
#include "../include/simulator/task.hpp"

int  main() {


  Timer* t1 = new Timer();
  Timer* t2 = new Timer();

  int MAX_INT[9] = {10, 50, 100, 500, 1000, 5000, 10000, 50000, 100000};

  //loop to iterate through all doubly linked lists of all MAX_INT[] sizes
  for (int i = 0; i < 9; i++) {
    std::cout << "MAX_INT value: " << MAX_INT[i] << std::endl;

    int randNum = 0;  //randomly generated number using rand()

    //loop to create double linked list of size MAX_INT[i]
    Task **taskArr = new Task*[MAX_INT[i]];
    for (int k = 0; k < MAX_INT[i]; k++) {
      //generate random number between 1 and MAX_INT[i]
      randNum = rand() % MAX_INT[i] + 1;
      taskArr[k] = new Task(randNum, randNum, randNum, randNum);
    }
    LeftistHeap *ss = new LeftistHeap(taskArr, MAX_INT[i]);

    LeftistHeap *l = new LeftistHeap(taskArr, MAX_INT[i]);
    SkewHeap *s = new SkewHeap(taskArr, MAX_INT[i]);
    //loop for 10 test cases
    for (int j = 0; j < 10; j++) {
      std::cout << "\tTest " << (j + 1) << ": " << std::endl;
      s = s;

      //fix the random number generator seed for reproducable results
      srand(157341);

      randNum = rand() % MAX_INT[i] + 1;
      Task *myTask = new Task(randNum, randNum, randNum, randNum);

      std::cout << "\t\tLeftistHeap: ";
      t1->start(); //start timer
      l->addElem(myTask); //add random number to linked list
      t1->printTime(t1->stop());
      std::cout << std::endl;

      std::cout << "\t\tSkewHeap: ";
      t2->start(); //start timer
      ss->addElem(myTask); //add random number to linked list
      t2->printTime(t2->stop());
      std::cout << std::endl;
    }
  }


  return 0;
}

/*
  int randNum = 0;

  Timer* t1 = new Timer();
  SkewHeap *s = new SkewHeap();
  //srand(157341);
  srand(time(NULL));  //generate random succession of rand

  for (int i = 0; i < 70000; i++) {
    randNum = rand() % 10 + 1;
    Task *myTask = new Task(randNum, randNum, randNum, randNum);
    s->addElem(myTask);
  }

  randNum = rand() % 10 + 1;
  Task *myTask = new Task(randNum, randNum, randNum, randNum);

  std::cout << "\t\tSkewHeap: ";
  t1->start(); //start timer
  s->addElem(myTask); //add random number to linked list
  t1->printTime(t1->stop());
  std::cout << std::endl;
*/
