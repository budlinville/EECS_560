#include "min3-heap.hpp"
#include "util.hpp"


//////////////////////////////////
// Private Functions Definition //
//////////////////////////////////
void Min3Heap::buildHeap(){
  bool swapped = true;
  int firstIndex = actualHeapSize/3;  //technically lastIndex
  int firstChild = 0;     //first child index
  int secondChild = 0;    //seond child index
  int thirdChild = 0;     //third child index
  int minChild = 0;
  std::string temp = "";

  while (swapped) {
    swapped = false;
    for (int i = firstIndex; i >= 0; i--) {
      firstChild = 3 * i + 1;
      secondChild = 3 * i + 2;
      thirdChild = 3 * i + 3;

      //check if tri-node has 1, 2, or 3 children
      if (heap[thirdChild] == "" && heap[secondChild] == "") {
        //std::cout << "a" << std::endl;
        minChild = firstChild;
      } else if (heap[thirdChild] == "") {
        //std::cout << "b" << std::endl;
        minChild = (heap[firstChild] < heap[secondChild]) ? firstChild : secondChild;
      } else {
        //std::cout << "c" << std::endl;
        minChild = (heap[firstChild] < heap[secondChild]) ? firstChild : secondChild;
        minChild = (heap[minChild] < heap[thirdChild]) ? minChild : thirdChild;
      }

      if (heap[minChild] < heap[i]) {
        //SWAP
        swapped = true;
        temp = heap[minChild];
        heap[minChild] = heap[i];
        heap[i] = temp;
      }
    }
  }
}

/////////////////////////////////
// Public functions definition //
/////////////////////////////////

Min3Heap::Min3Heap(){
  for (int i =0; i < HEAP_SIZE; i++) {
    heap[i] = "";
  }
}

Min3Heap::Min3Heap(std::string *arr){
  //form initial trinary tree
  int i = 0;
  while (arr[i] != "") {
    heap[i] = arr[i];
    i++;
  }

  actualHeapSize = i;

  //fill remaining elements in with empty strings
  for (int j = i; j < HEAP_SIZE; j++) {
    heap[j] = "";
  }

  buildHeap();
}


Min3Heap::~Min3Heap() {
  //No dynamically allocated data
}

void Min3Heap::addElem(std::string elem) {
  heap[actualHeapSize] = elem;
  actualHeapSize++;

  buildHeap();
}

void Min3Heap::deleteElem(std::string elem) {
  for (int i = 0; i < actualHeapSize; i++) {
    if (heap[i] == elem) {
      heap[i] = heap[actualHeapSize - 1];
      heap[actualHeapSize - 1] = "";
      actualHeapSize--;

      heapify();
    }
  }
}

bool Min3Heap::exists(std::string elem){
  for (int i = 0; i < actualHeapSize; i++) {
    if (heap[i] == elem)
      return true;
  }
  return false;
}

std::string Min3Heap::deleteMinElem(){
  if (heap[0] == "")
    return "";

  std::string retVal = heap[0];
  heap[0] = heap[actualHeapSize - 1];
  heap[actualHeapSize - 1] = "";
  actualHeapSize--;

  heapify();
  return retVal;
}

std::string Min3Heap::deleteMaxElem() {
  if (heap[0] == "")
    return "";

  std::string max = heap[0];
  int maxIndex = 0;

  for (int i= 0; i < actualHeapSize; i++) {
    if (heap[i] > max) {
      max = heap[i];
      maxIndex = i;
    }
  }

  //WORKING HERE
  heap[maxIndex] = heap[actualHeapSize - 1];
  heap[actualHeapSize - 1] = "";
  actualHeapSize--;

  heapify();
  return max;
}

void Min3Heap::levelOrderPrint(){
  int lastRowIndex = 0;
  std::cout << std::endl;

  for (int i = 0; i < actualHeapSize; i++) {
    std::cout << heap[i] << "  ";

    if (i == lastRowIndex) {
      std::cout << std::endl;
      lastRowIndex = 3 * lastRowIndex + 3;
    }
  }
  std::cout << "\n" << std::endl;
}

void Min3Heap::heapify(){
  int firstIndex = actualHeapSize/3 - 1;  //technically lastIndex
  int firstChild = 0;     //first child index
  int secondChild = 0;    //seond child index
  int thirdChild = 0;     //third child index
  int minChild = 0;
  std::string temp = "";

  for (int i = firstIndex; i >= 0; i--) {
    firstChild = 3 * i + 1;
    secondChild = 3 * i + 2;
    thirdChild = 3 * i + 3;

    //check if tri-node has 1, 2, or 3 children
    if (heap[thirdChild] == "" && heap[secondChild] == "") {
      //std::cout << "a" << std::endl;
      minChild = firstChild;
    } else if (heap[thirdChild] == "") {
      //std::cout << "b" << std::endl;
      minChild = (heap[firstChild] < heap[secondChild]) ? firstChild : secondChild;
    } else {
      //std::cout << "c" << std::endl;
      minChild = (heap[firstChild] < heap[secondChild]) ? firstChild : secondChild;
      minChild = (heap[minChild] < heap[thirdChild]) ? minChild : thirdChild;
    }

    if (heap[minChild] < heap[i]) {
      //SWAP
      temp = heap[minChild];
      heap[minChild] = heap[i];
      heap[i] = temp;
    }
  }
}
