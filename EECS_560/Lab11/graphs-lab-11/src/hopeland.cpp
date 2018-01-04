#include <iostream>
#include <fstream>
#include <string>

#include "util/util.hpp"
#include "graph.hpp"
#include "lib/doubly-linked-list/list.hpp"

using namespace std;

int* parseString(std::string str, int numElements) {
  int * intArr = new int[numElements];
  //first remove first 3 characters because they are meaningless
  str.erase(0, 3);

  //add comma to back for consistant string parsing
  str.push_back(',');

  std::string elemString = "";
  for (int i = 0; i < numElements; i++) {
    elemString = str.substr(0, str.find_first_of(",", 0));
    str.erase(0, str.find_first_of("-0123456789", str.find_first_of(" ", 0)));
    intArr[i] = std::stoi(elemString);
  }

  return intArr;
}

int main(int argc, char** argv){
  fstream inputData;

  if(argc < 2){
    cout << "No input file given, using default test/hl-data.txt" << endl;
    inputData.open("test/hl-data.txt", ifstream::in);
  } else {
    cout << "Using data from " << argv[1] << endl;
    inputData.open(argv[1], ifstream::in);
  }

  // How can you use the graph data structre you have implemented to
  // find minimum number of roads to connect all the areas with minumum cost?

  int numVertices = 0;
  std::string thisLine = "";
  inputData >> numVertices;
  int** costs = new int*[numVertices];
  for (int i = 0; i < numVertices; i++) {
    costs[i] = nullptr;
  }

  //do once to clear line cache above
  std::getline(inputData, thisLine);

  for (int i = 0; i < numVertices; i++) {
    std::getline(inputData, thisLine);
    costs[i] = parseString(thisLine, numVertices);
  }

  Graph* hopeland = new Graph(costs, numVertices);
  DoublyLinkedList* roads = hopeland->prim();
  int totalCost = 0;

  Node* curNode = roads->getFront();
  while (curNode != nullptr) {
    totalCost += curNode->getValue()->getCost();
    curNode = curNode->getNext();
  }

  cout << "Roads: ";
  roads->print();
  cout << "Total Cost: " << totalCost << endl;

  inputData.close();

  return 0;
}
