#include <iostream>
#include <stdlib.h>   //for rand and srand
#include <time.h>     //for time to pass into srand for better random number generation
#include <fstream>
#include "timer.hpp"
#include "min3-heap.hpp"
#include "util.hpp"

#define LIST_SIZE 10000

using namespace std;

int bounded_random_generator(){
  return (rand() % LIST_SIZE);
}

std::string* getRandomWordArray(int size) {
  fstream wordListFile;
  string* wordList = new string[LIST_SIZE];
  string* heapArray = new string[size + 1];     //need to pass in array of size + 1

  wordListFile.open("word-list.txt", fstream::in);
  for(int i = 0; i < LIST_SIZE; i++){
    wordListFile >> wordList[i];
  }
  wordListFile.close();

  //fix the random number generator seed for reproducable results
  srand(157341);

  for(int i = 0; i < size; i++){
    heapArray[i] = wordList[bounded_random_generator()];
  }

  return heapArray;
}

std::string getRandomWord() {
  fstream wordListFile;
  string* wordList = new string[LIST_SIZE];
  string word = "";

  wordListFile.open("word-list.txt", fstream::in);
  for(int i = 0; i < LIST_SIZE; i++){
    wordListFile >> wordList[i];
  }
  wordListFile.close();

  srand(time(NULL));  //generate random succession of rand

  word = wordList[bounded_random_generator()];
  return word;
}

//WORKING HERE - measuring how long it takes to build a max heap, so need to make sure im not building a tree initially
int  main() {
  Timer* t = new Timer();

  int MAX_INT[11] = {10, 50, 100, 250, 500, 750, 1000, 2500, 5000, 7500, 10000};

  //loop to iterate through all heaps of all MAX_INT[] sizes
  for (int i = 0; i < 11; i++) {
    std::cout << "MAX_INT value: " << MAX_INT[i] << std::endl;

    //loop for 10 test cases
    for (int j = 0; j < 10; j++) {
      std::cout << "\tTest " << (j + 1) << ": ";

      Min3Heap *heap = nullptr;
      //std::string randWord = "";  //randomly generated word using getRandomWord()
      std::string* inputDataArr = getRandomWordArray(MAX_INT[i]);
      heap = new Min3Heap(inputDataArr);

      t->start(); //start timer

      std::string s = heap->deleteMinElem();
      s = s;

      t->printTime(t->stop());
    }
  }

  return 0;
}
