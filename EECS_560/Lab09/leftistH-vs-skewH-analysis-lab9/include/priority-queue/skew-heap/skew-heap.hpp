#ifndef SKEW_HEAP_HPP
#define SKEW_HEAP_HPP

#include <iostream>
#include <fstream>
#include <string>

#include "../../simulator/task.hpp"

/////////////////////////////////////////////////////////////////
// You may not add any public methods in this class            //
// You may add only private member fields and private methods  //
// The public methods will be used to test your implementation //
/////////////////////////////////////////////////////////////////

/**
 * A priority queue is an ADT which supports fast access to the
 * highest priority element. i.e. minimum element on the top
 * This priority queue supports ordering tasks. Ordering logic being
 * task of minimum nice value on top.
 */

#ifndef NODE
#define NODE
 typedef struct node_t {
   node_t * lChild;
   node_t * rChild;
   int rank;
   Task * task;
 } node_t;
 #endif

class SkewHeap {

private:
  // Member fields
  // IMPLEMENT ME
  // Add any private member variables here that you might need
  node_t *rootPtr;
  int size;

  // Member functions
  // IMPLEMENT ME
  // Add any other private functions you might need

  //recursive function for deleting tree
  void destroyTree(node_t* treePtr);

  node_t* merge(node_t* p, node_t* q);

  //used solely for concatention
  void setSize(int s);

public:
  //Member functions
  /**
   * Constructor to construct the priority queue given an array of tasks
   */
  SkewHeap(Task** tasks, int taskSize);

  /**
   * Constructor to construct an empty priority queue.
   */
  SkewHeap();

  /**constructor for a Priority Queue, given the rootPtr to a leftist heap
   *ASSUMES that the rootPtr points to a properly ordered leftist heap
   *USED in deleteMin(), to create two new priority queues that can then be concatenated back together
   */
  SkewHeap(node_t* pq);

  /**
   * Destructor to destroy the priority queue
   * Make sure you destroy everything that you allocate on memory-heap space
   */
  ~SkewHeap();

  /**
   * This function merges the two SkewHeaps into one queue
   *
   * There are 2 ways of doing it: deep copy `that` and then concatenate
   * `this` and `that` to update `this`. Or use `that` as is to merge
   * into `this`. You will have to make an appropriate design decision accordingly
   * to make sure there is no scope of memory leak
   */
  void concat(SkewHeap* that);

  /**
   * Adds one task element to SkewHeap and restructures the heap to
   * maintain the heap property.
   * HINT: Can you use concat to do this?
   */
  void addElem(Task* task);

  /**
   * Deletes the min element from the priority queue and possibly restructures it
   * after the delete operation and returns the element that is deleted
   * HINT: Can you use concat to do this?
   */
  Task* deleteMinElem();

  /**
   * This function performs an inorder traversal over the elements of
   * the priority queue and applies the operation *op on each of the elements.
   */
  int inorderTraversal(node_t* treePtr, int identity, int (SkewHeap::*op)(Task*));

  /**
   * This function performs a post traversal over the elements of
   * the priority queue and applies the operation *op on each of the elements.
   */
  int postorderTraversal(node_t* treePtr, int identity, int (SkewHeap::*op)(Task*));

  /**
   * This function performs a pre traversal over the elements of
   * the priority queue and applies the operation *op on each of the elements.
   */
  int preorderTraversal(node_t* treePtr, int identity, int (SkewHeap::*op)(Task*));

  int getSize();

  node_t* getRootPtr();

  int sizeTraversal(node_t *treePtr, int identity, int (SkewHeap::*op)(int));

  //helper recursive function for debugging
  int printElement(Task* t);




};

#endif
