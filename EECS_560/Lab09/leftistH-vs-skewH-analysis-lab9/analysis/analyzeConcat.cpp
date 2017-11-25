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

    //loop for 10 test cases
    for (int j = 0; j < 10; j++) {
      std::cout << "\tTest " << (j + 1) << ": " << std::endl;

      Task **taskArr1 = new Task*[MAX_INT[i]];
      Task **taskArr2 = new Task*[MAX_INT[i]];
      for (int k = 0; k < MAX_INT[i]; k++) {
        //generate random number between 1 and MAX_INT[i]
        randNum = rand() % MAX_INT[i] + 1;
        taskArr1[k] = new Task(randNum, randNum, randNum, randNum);
        taskArr2[k] = new Task(randNum, randNum, randNum, randNum);
      }

      LeftistHeap *l1 = new LeftistHeap(taskArr1, MAX_INT[i]);
      LeftistHeap *l2 = new LeftistHeap(taskArr2, MAX_INT[i]);
      LeftistHeap *s1 = new LeftistHeap(taskArr1, MAX_INT[i]);
      LeftistHeap *s2 = new LeftistHeap(taskArr2, MAX_INT[i]);
      SkewHeap *s_1 = new SkewHeap(taskArr1, MAX_INT[i]);
      SkewHeap *s_2 = new SkewHeap(taskArr2, MAX_INT[i]);

      //fix the random number generator seed for reproducable results
      srand(157341);

      std::cout << "\t\tLeftistHeap: ";
      t1->start(); //start timer
      l1->concat(l2); //add random number to linked list
      t1->printTime(t1->stop());
      std::cout << std::endl;

      std::cout << "\t\tSkewHeap: ";
      t2->start(); //start timer
      s1->concat(s2); //add random number to linked list
      t2->printTime(t2->stop());
      std::cout << std::endl;
      s_1 = s_1;
      s_2 = s_2;
    }
  }


  return 0;
}
