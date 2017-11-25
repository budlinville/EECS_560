#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include "BinaryNode.hpp"

//typedef Queue<int> Queue;
//typedef BinaryNode<int>* BinaryNode;

/**
 * Binary tree is tree like structure but with a special property
 * for each node - there are only 2 children. The left node and the
 * right node and it holds a data point with in the node.
 *
 * In our current implementation of binary tree we will use
 * to store our data as integers.
 */
class BinaryTree {

private:
  //Member fields
  BinaryNode<int>* rootPtr;
  //BinaryNode<int>* backPtr;
  int depth;


  //Member functions
  bool insertLevelOrder(BinaryNode<int>* treePtr, BinaryNode<int>* newNode);

  bool isFullTree(BinaryNode<int>* subTreePtr);

  int printElement(int x, int y);

  int add(int x, int y);

  bool checkElement(BinaryNode<int>* subTreePtr, int elem);

  int deleteLastElem(BinaryNode<int>* subTreePtr, bool &deleted);

  //helper recursive method for Destructor
  void destroyTree(BinaryNode<int>* subTreePtr);
public:
  //Member functions
  /**
   * Constructor to construct the BinaryTree.
   */
  BinaryTree();

  /**
   * Destructor to destroy the BinaryTree
   * Make sure you deallocate everything that you allocate on heap.
   */
  ~BinaryTree();

  /**
   * add and element to BinaryTree in last position of level order addition
   */
  void addElem(int elem);

  /**
   * Deletes the element that occurs at the "last position" according to
   * level order in the binary tree and returns the value that it has deleted
   */
  int deleteElem();

  /**
   * Should return true if the element exists otherwise return false
   */
  bool exists(int elem);

  /**
   * this function performs an in-order traversal over the existing
   * binary tree.
   *
   * The first argument to the function is the identity element or the base case
   * that can be used by the function (*operation) -- the second argument --
   * to start computation. eg. to multiply all the elements of
   * the tree identity = 1 and *operation = multiply(int a, int b){return a*b;}
   *
   */
  int inorderTraverse(BinaryNode<int>* treePtr, int identity, int (BinaryTree::*operation)(int, int));

  /**
   * this function performs an pre-order traversal over the existing
   * binary tree.
   *
   * The first argument to the function is the identity element or the base case
   * that can be used by the function (*operation) -- the second argument --
   * for  computation.
   *
   */
  int preorderTraverse(BinaryNode<int>* treePtr, int identity, int (BinaryTree::*operation)(int, int));

  /**
   * this function performs an post-order traversal over the existing
   * binary tree.
   *
   * The first argument to the function is the identity element or the base case
   * that can be used by the function (*operation) -- the second argument --
   * for computation.
   *
   */
   int postorderTraverse(BinaryNode<int>* treePtr, int identity, int (BinaryTree::*operation)(int, int));

  /**
   * returns the sum of all the nodes in the binary tree
   * HINT: can you make use of the traversal functions that you have implemented?
   */
  int sum();

  /**
   * Prints all the elements of the list with delimited with space
   * takes an argument printType that decides with type of traversal print
   * the function should run
   * HINT: Can you make use the traversal functions you have already implemented?
   */
  void print(int printType);
};

#endif //BINARY_TREE_H defined
