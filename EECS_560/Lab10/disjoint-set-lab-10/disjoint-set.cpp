#include "disjoint-set.hpp"
#include "util.hpp"

DisjointSet::DisjointSet(int size) {
  setSize = size;
  setArray = new node_t[setSize];

  for (int i = 0; i < setSize; i++) {
    setArray[i].value = i;
    setArray[i].parentNode = &setArray[i];
    setArray[i].rank = 0;
  }
}

int DisjointSet::find(int elem) {
  if (elem < 0 || elem > setSize)
    return -1;

  node_t *tracer = &(setArray)[elem];
  node_t *representative = nullptr;

  while (tracer->parentNode != tracer) {
    tracer = tracer->parentNode;
  }

  //PATH COMPRESSION:: now set the parent node of all nodes in the path to the representative
  representative = tracer;
  tracer = &(setArray)[elem];
  while (tracer->parentNode != tracer) {
    tracer->parentNode = representative;
    tracer = tracer->parentNode;
  }

  return tracer->value;
}

void DisjointSet::union_set(int a, int b) {
  node_t *repA = &(setArray)[a];
  node_t *repB = &(setArray)[b];

  while (repA->parentNode != repA) {
    repA = repA->parentNode;
  }

  while (repB->parentNode != repB) {
    repB = repB->parentNode;
  }

  if (repA->rank > repB->rank) {
    repB->parentNode = repA;
  } else if (repA->rank < repB->rank) {
    repA->parentNode = repB;
  } else {    //equal
    if (repA->value > repB->value) {
      repA->rank++;
      repB->parentNode = repA;
    } else {
      repB->rank++;
      repA->parentNode = repB;
    }
  }
}


void DisjointSet::print() {
  int rep = 0;
  node_t *tracer = nullptr;

  for (int i = 0; i < setSize; i++) {
    tracer = &(setArray)[i];
    while (tracer->parentNode != tracer) {
      tracer = tracer->parentNode;
    }

    rep = tracer->value;

    std::cout << i << "(" << rep << ") ";
  }
  std::cout << std::endl;
}
