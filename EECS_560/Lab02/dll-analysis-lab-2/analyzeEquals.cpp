#include <iostream>
#include <stdlib.h>   //for rand and srand
#include <time.h>     //for time to pass into srand for better random number generation
#include "timer.hpp"
#include "list.hpp"
#include "util.hpp"
#include "sparse-matrix.hpp"
#include "modNode.hpp"

int  main() {
  Timer* t = new Timer();

  int MAX_INT[5] = {100, 500, 1000, 5000, 10000};
  //int MAX_INT[5] = {10, 20, 50, 80, 100};

  //loop to iterate through all doubly linked lists of all MAX_INT[] sizes
  for (int i = 0; i < 5; i++) {
    std::cout << "MAX_INT value: " << MAX_INT[i] << std::endl;

    //loop for 5 test cases
    for (int j = 0; j < 5; j++) {
      std::cout << "\tTest " << (j + 1) << ": " << std::endl;

      SparseMatrix *m1 = new SparseMatrix(); //initialize matrix 1
      SparseMatrix *m2 = new SparseMatrix(); //initialize matrix 2

      //std::cout << "Matrices of size: " << MAX_INT[i] << " initialized" <<  std::endl;

      srand(time(NULL));  //generate random succession of rand

      //loop to create 2 NxN matrices where N = MAX_INT[i]
      for (int k = 0; k < MAX_INT[i]; k++) {
        for (int l = 0; l < MAX_INT[i]; l++) {
          m1->matrixAdd(0, m1->size(), k, l);
          m2->matrixAdd(0, m2->size(), k, l);

          //std::cout << "Filling matrix: x: " << k << " y: " << l <<  std::endl;
        }

        //add random number to linked list
        //dll->add(randNum, dll->size());
      }

      //loop to fill <10% of both matrices with values ranging from 1 to MAX_INT[i]
      int elementsNeeded = MAX_INT[i] / 10;

      //std::cout << "Upper bound creaded: " << elementsNeeded <<  std::endl;
      //node for iterating through matrices implemented as doubly linked lists
      Node *curNode1 = m1->getFront();
      Node *curNode2 = m2->getFront();
      //int skipVal1 = 0;
      //int skipVal2 = 0;
      int randValM1 = 0;
      int randValM2 = 0;
      int randPosM1 = 0;
      int randPosM2 = 0;
      int count = 0;

      //loop to fill <10% of both matrices with values ranging from 1 to MAX_INT[i]
      //for (int m = 0; m < upperBound; m++)
      while (count <= elementsNeeded) {
        randValM1 = rand() % MAX_INT[i] + 1;
        randValM2 = rand() % MAX_INT[i] + 1;
        randPosM1 = rand() % MAX_INT[i] + 1;
        randPosM2 = rand() % MAX_INT[i] + 1;
        //skipVal = rand() % elementsNeeded + 1;
        //skipVal2 = rand() % elementsNeeded + 1;

        //std::cout << "Adding random values (outer loop)" <<  std::endl;

        curNode1 = m1->getFront();
        for (int n = 0; n < randPosM1; n++) {
          curNode1 = curNode1->getNext();
        }
        curNode1->setValue(randValM1);
        //std::cout << "Adding random values (inner loop 1)" <<  std::endl;

        curNode2 = m2->getFront();
        for (int n = 0; n < randPosM2; n++) {
          curNode2 = curNode2->getNext();
        }
        curNode2->setValue(randValM2);
        //std::cout << "Adding random values (outer loop 2)" <<  std::endl;

        count++;
      }

      //timing for checking if m1 = m2;
      std::cout << "\t\tM1 = M2: ";
      t->start(); //start timer
      m1->equals(m2);
      t->printTime(t->stop());

      //timing for checking if m1 = m1;
      std::cout << "\t\tM1 = M1: ";
      t->start(); //start timer
      m1->equals(m1);
      t->printTime(t->stop());

    }
  }

  return 0;
}
