//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

/** @file BinaryNode.cpp */

#include <cstddef>

template<typename NodeItemType>
BinaryNode<NodeItemType>::BinaryNode() : item(nullptr), leftChildPtr(nullptr), rightChildPtr(nullptr), isFront(false), level(0)
{
}  // end default constructor

template<typename NodeItemType>
BinaryNode<NodeItemType>::BinaryNode(const NodeItemType& anItem) : item(anItem), leftChildPtr(nullptr), rightChildPtr(nullptr), isFront(false), level(0)
{
}  // end constructor

template<typename NodeItemType>
BinaryNode<NodeItemType>::BinaryNode(const NodeItemType& anItem, BinaryNode<NodeItemType>* leftPtr,
                             BinaryNode<NodeItemType>* rightPtr) : item(anItem), leftChildPtr(leftPtr), rightChildPtr(rightPtr), isFront(false), level(0)
{
}  // end constructor

template<typename NodeItemType>
void BinaryNode<NodeItemType>::setItem(const NodeItemType& anItem)
{
   item = anItem;
}  // end setItem

template<typename NodeItemType>
NodeItemType BinaryNode<NodeItemType>::getItem() const
{
   return item;
}  // end getItem

template<typename NodeItemType>
bool BinaryNode<NodeItemType>::isLeaf() const
{
   return ((leftChildPtr == nullptr) && (rightChildPtr == nullptr));
}

template<typename NodeItemType>
void BinaryNode<NodeItemType>::setLeftChildPtr(BinaryNode<NodeItemType>* leftPtr)
{
   leftChildPtr = leftPtr;
}  // end setLeftChildPtr

template<typename NodeItemType>
void BinaryNode<NodeItemType>::setRightChildPtr(BinaryNode<NodeItemType>* rightPtr)
{
   rightChildPtr = rightPtr;
}  // end setRightChildPtr

template<typename NodeItemType>
BinaryNode<NodeItemType>* BinaryNode<NodeItemType>::getLeftChildPtr() const
{
   return leftChildPtr;
}  // end getLeftChildPtr

template<typename NodeItemType>
BinaryNode<NodeItemType>* BinaryNode<NodeItemType>::getRightChildPtr() const
{
   return rightChildPtr;
}  // end getRightChildPtr

template<typename NodeItemType>
void BinaryNode<NodeItemType>::setLevel(int l) {
   level = l;
}  // end setLevel

template<typename NodeItemType>
int BinaryNode<NodeItemType>::getLevel() {
   return level;
}  // end getLevel

template<typename NodeItemType>
void BinaryNode<NodeItemType>::setIsFront(bool f) {
  isFront = f;
} // end setIsFront

template<typename NodeItemType>
bool BinaryNode<NodeItemType>::getIsFront() {
  return isFront;
} // end getIsFront
