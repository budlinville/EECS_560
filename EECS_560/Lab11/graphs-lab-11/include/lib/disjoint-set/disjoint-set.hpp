#ifndef DISJOINT_SET_HPP
#define DISJOINT_SET_HPP

#include <iostream>

//////////////////////////////////////////////////////////////
// You may not add any public methods for this class	    //
// The pre-defined public methods will be used to test your //
// implementation					    //
//////////////////////////////////////////////////////////////

 typedef struct set_node_t {
   set_node_t *parentNode;
   int value;
   int rank;
 } set_node_t;

class DisjointSet {

private:
    //Add any private variables/member functions here
    set_node_t *setArray;
    int setSize;

public:
    /**
     * Creates a disjoint set of the given size
     */
    DisjointSet(int size);

    /**
     * merges the 2 given values a and b into a single set
     * using `union by rank` heuristic
     */
    void union_set(int a, int b);

    /**
     * returns the represenative element of the set the argument element belongs to
     * returns -1 if `a` is out of bounds
     * This function should use path compression technique
     */
    int find(int a);

    /**
     * Prints the disjoint set elements and its parent element.
     * _Caution_ : It should not mutate the set in any way
     * if the disjoint set looks like {{1, 2, 3}, {4, 5}, {7, 8, 9}, {10}} and assuming the first element is
     * the representative element and subsequent elements have child parent relationship, then the print function should print:
     * 1(1) 2(1) 3(2) 4(4) 5(4) 7(7) 8(9) 9(8) 10(10)
     */
    void print();
};

#endif // DISJOINT_SET_HPP defined
