#ifndef LEFTIST_HEAP_HPP
#define LEFTIST_HEAP_HPP

#include <iostream>
#include <fstream>
#include <string>

#include "../../edge.hpp"

/////////////////////////////////////////////////////////////////
// You may not add any public methods in this class            //
// You may add only private member fields and private methods  //
// The public methods will be used to test your implementation //
/////////////////////////////////////////////////////////////////

/**
 * A priority queue is an ADT which supports fast access to the
 * highest priority element. i.e. minimum element on the top
 * This priority queue supports ordering edges. Ordering logic being
 * edge of minimum nice value on top.
 */
#ifndef NODE
#define NODE
 typedef struct lh_node_t {
   lh_node_t * lChild;
   lh_node_t * rChild;
   int rank;
   Edge * edge;
 } lh_node_t;
#endif

class LeftistHeap {

private:
  // Member fields
  // IMPLEMENT ME
  // Add any private member variables here that you might need
  lh_node_t *rootPtr;
  int size;

  // Member functions
  // IMPLEMENT ME
  // Add any other private functions you might need

  //recursive function for swapping a child's right tree with its left if its rank is greater than its left
  //RETURNS: rank of node
  int checkRankAndSwap(lh_node_t* treePtr);

  //recursive function for deleting tree
  void destroyTree(lh_node_t* treePtr);

public:
  //Member functions
  /**
   * Constructor to construct the priority queue given an array of edges
   */
  LeftistHeap(Edge** edges, int edgeSize);
  
  /**
   * Constructor to construct an empty priority queue.
   */
  LeftistHeap();

  /**constructor for a Priority Queue, given the rootPtr to a leftist heap
   *ASSUMES that the rootPtr points to a properly ordered leftist heap
   *USED in deleteMin(), to create two new priority queues that can then be concatenated back together
   */
  LeftistHeap(lh_node_t* pq);

  /**
   * Destructor to destroy the priority queue
   * Make sure you destroy everything that you allocate on memory-heap space
   */
  ~LeftistHeap();

  /**
   * This function merges the two LeftistHeaps into one queue
   *
   * There are 2 ways of doing it: deep copy `that` and then concatenate
   * `this` and `that` to update `this`. Or use `that` as is to merge
   * into `this`. You will have to make an appropriate design decision accordingly
   * to make sure there is no scope of memory leak
   */
  void concat(LeftistHeap* that);

  /**
   * Adds one edge element to LeftistHeap and restructures the heap to
   * maintain the heap property.
   * HINT: Can you use concat to do this?
   */
  void addElem(Edge* edge);

  /**
   * Deletes the min element from the priority queue and possibly restructures it
   * after the delete operation and returns the element that is deleted
   * HINT: Can you use concat to do this?
   */
  Edge* deleteMinElem();

  /**
   * This function performs an inorder traversal over the elements of
   * the priority queue and applies the operation *op on each of the elements.
   */
  int inorderTraversal(lh_node_t* treePtr, int identity, int (LeftistHeap::*op)(Edge*));

  /**
   * This function performs a post traversal over the elements of
   * the priority queue and applies the operation *op on each of the elements.
   */
  int postorderTraversal(lh_node_t* treePtr, int identity, int (LeftistHeap::*op)(Edge*));

  /**
   * This function performs a pre traversal over the elements of
   * the priority queue and applies the operation *op on each of the elements.
   */
  int preorderTraversal(lh_node_t* treePtr, int identity, int (LeftistHeap::*op)(Edge*));

  int getSize();

  lh_node_t* getRootPtr();

  int sizeTraversal(lh_node_t *treePtr, int identity, int (LeftistHeap::*op)(int));

  //helper recursive function for debugging
  int printElement(Edge* t);


};

#endif //PRIORITY_QUEUE_HPP defined
