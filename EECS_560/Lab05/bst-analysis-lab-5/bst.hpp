#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "BinaryNode.h"

/**
 * Binary search tree (BST) is a binary tree but with a special property:
 * for each node, the left child is smaller than the current node and the
 * right child is greater than the current node.
 */
class BST {

private:
    //Member fields
    BinaryNode<int>* rootPtr;
    //int treeHeight;

    //Member functions
    void destroyTree(BinaryNode<int>* subTreePtr);
    void insertInorder(BinaryNode<int>* subTreePtr, BinaryNode<int>* newNodePtr);
    bool checkElement(BinaryNode<int>* subTreePtr, int elem);
    int printElement(int x, int y);
    BinaryNode<int>* findNode(BinaryNode<int>* treePtr, const int target) const;
    BinaryNode<int>* getParentToDeleteNode(BinaryNode<int>* subTreePtr, const int target, bool &isLeft);
    int getHeight(BinaryNode<int>* subTreePtr);
    int levelorderHelper(BinaryNode<int>* subTreePtr, int level, int identity, int (BST::*operation)(int, int));

public:
    //Member functions
    /**
     * Constructor to construct the binary search tree.
     */
    BST();

    /**
     * Destructor to destroy the binary search tree
     * Make sure you destroy everything that you allocate on heap.
     */
    ~BST();

    /**
     * Returns true if the BST is empty or returns false
     */
    bool isEmpty();

    /**
     * add and element to BST and maintains the BST property.
     */
    void addElem(int elem);

    /**
     * Deletes all the occurances of the element
     * and if needed restructures the tree to maintain the
     * BST property. The operation does not do any state change if elem is not
     * present in the binary search tree.
     * when removing a node that has two child nodes,
     * use the smallest data node in the right subtree of the data
     * that should be removed in order to replace the removed data.
     */
    void deleteElem(int elem);

    /**
     * Should return true if the element exists, return false otherwise
     */
    bool exists(int elem);

    /**
     * this function performs an inorder traversal over the existing
     * binary search tree.
     */
    int inorderTraverse(BinaryNode<int>* treePtr, int identity, int (BST::*operation)(int, int));

    /**
     * this function performs a postorder traversal over the existing
     * binary search tree.
     */
    int postorderTraverse(BinaryNode<int>* treePtr, int identity, int (BST::*operation)(int, int));

    /**
     * this function performs a preorder traversal over the existing
     * binary search tree.
     */
    int preorderTraverse(BinaryNode<int>* treePtr, int identity, int (BST::*operation)(int, int));

    /**
     * this function performs a levelorder traversal over the existing
     * binary search tree.
     */
    int levelorderTraverse(BinaryNode<int>* treePtr, int identity, int (BST::*operation)(int, int));

    /**
     * This function returns the longest path between the root node and
     * the leaf node
     */
    int height();

    /**
     * Prints all the elements of the list with delimited with space
     * HINT: Can you make use the traversal function you have implemented?
     */
    void print(int printType);
};

#endif //BINARY_SEARCH_TREE_H defined
