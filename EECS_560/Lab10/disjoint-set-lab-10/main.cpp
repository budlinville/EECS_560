#include <iostream>

#include "disjoint-set.hpp"
#include <string>

/////////////////////////////////////////
// You may not change this main file. //
// You can create a new main file for //
// your debugging purposes            //
////////////////////////////////////////

using namespace std;

void cleanUp(DisjointSet* &mySet);
void printMenu();

/**
 * This is the main entry point to the program for simulating disjoint set
 * Make use of the parent pointer implementation for disjoint-set
 * The disjoint set should use union by rank and path compression for its operations
 *
 * This program first creates k disjoint sets of single elements where k is a 
 * number that is passed into the main function as a program argument (./main k)
 * Once the set is created the size of the set remains constant.
 */
int main(int argc, char** argv){

    int a, b;
    int option;

    int size = 15;
    if(argc < 2){
	cout << "Using the default disjoint set size of 15" << endl;
    } else {
	size = atoi(argv[1]);
	cout << "Setting set size to " << size << endl;
    }

    DisjointSet *mySet = new DisjointSet(size);

    printMenu();
    cin >> option;

    while(option != 4){
	switch(option){
	case 1:
	    //find an element
	    cout << "Enter element to be found: ";
	    cin >> a;
	    cout << mySet->find(a);
	    cout << endl;
	    break;
	case 2:
	    // 2: union of 2 elements in same set
            cout << "Enter elements to combine sets: " << endl;
	    cout << "Enter first element: ";
	    cin >> a;
	    cout << "Enter second element: ";
	    cin >> b;
	    mySet->union_set(a, b);
	    break;
	case 3:
	    //3: print
	    cout << "Printing set: ";
	    mySet->print();
	    break;
	default:
	    cout << "Invalid argument." << endl;
	    break;
	}
	printMenu();
	cin >> option;
    }

    cleanUp(mySet);
    return 0;
}

/**
 * Prints the menu of choices to the user
 */
void printMenu(){
    cout << "Please choose one of the following commands:" << endl;
    cout << "1: find element" << endl;
    cout << "2: union" << endl;
    cout << "3: print" << endl;
    cout << "4: exit" << endl;
    cout << ">> ";
}

/**
 * cleans up the environment before exiting
 */
void cleanUp(DisjointSet* &mySet){
  //IMPLEMENT ME
  delete mySet;
}

