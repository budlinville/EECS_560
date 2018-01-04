#ifndef AVL_HPP
#define AVL_HPP
#include "book.hpp"
#include <string>

typedef struct node_t {
  Book* book;
  node_t* rChild;
  node_t* lChild;
  int lChildHeight;
  int rChildHeight;
} node_t;



/**
 * AVL tree is a self balanced binary search tree
 */
class AVL {

private:
  //Member fields
  node_t* rootPtr;

  //Member functions
  void doLeftLeft(node_t* curNode);
  void doRightRight(node_t* curNode);
  int updateHeights(node_t* curNode);
  void insertInorder(node_t* subTreePtr, node_t* newNodePtr);
  void postorderCheckHeightsAndSwap(node_t* subTreePtr);
  Book* checkElement(node_t* subTreePtr, int id);
  void destroyTree(node_t* subTreePtr);
  void levelorderHelper(node_t* subTreePtr, int level, void (AVL::*operation)(Book*));
  void printBook(Book* thisBook);

public:
  //Member functions
  /**
   * Constructor to construct the binary search tree.
   */
  AVL();

  /**
   * Destructor to destroy the binary search tree
   * Make sure you destroy everything that you allocate on heap.
   */
  ~AVL();

  /**
   * Returns true if the AVL tree is empty or returns false
   */
  bool isEmpty();

  /**
   * add a book instance to the AVL Tree and balance it if necessary
   */
  void addBook(Book*);

  /**
   * Searches for the book given its id
   */
  Book* search(int id);

  /**
   * this function performs a levelorder traversal over the existing
   * AVL tree and performs the operation op on each of the Book instance
   * stored in the AVL tree.
   */
  void levelorderTraverse(void (AVL::*operation)(Book*));


};

#endif //AVL_HPP defined
