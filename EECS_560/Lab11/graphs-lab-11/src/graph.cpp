//#include "../include/graph.hpp"
#include "../include/graph.hpp"
#include "util/util.hpp"


/*********************************************************************
                          QUEUE STRUCTS STUFF
*******************************************************************/
void initQueue(queue_t* q) {
  q->m_front = nullptr;
  q->m_back = nullptr;
  q->size = 0;
}

void enqueue(queue_t* q, int i) {
  node_t* node = new node_t;
  node->item = i;
  node->nextNode = nullptr;
  node->prevNode = nullptr;

  if (q->size == 0) {
    q->m_front = node;
    q->m_back = node;
  } else {
    node->nextNode = q->m_back;
    q->m_back->prevNode = node;
    node->prevNode = nullptr;

    q->m_back = node;
  }
  q->size++;
}

int dequeue(queue_t* q) {
  if (q->size == 0)
    return -1;

  if (q->size == 1) {
    node_t* ret = q->m_front;
    q->size--;
    q->m_front = nullptr;
    q->m_back = nullptr;
    return ret->item;
  }

  node_t* ret = q->m_front;
  q->m_front = q->m_front->prevNode;
  q->m_front->nextNode = nullptr;
  q->size--;
  return ret->item;
}

int getQueueSize(queue_t* q) {
  return q->size;
}

bool isQueueEmpty(queue_t* q) {
  return (q->size == 0);
}

void printQueue(queue_t* q) {
  std::cout << "Printing from back to front: ";
  node_t* temp = q->m_back;
  while (temp != nullptr) {
    std::cout << temp->item << " ";
    temp = temp->nextNode;
  }
  std::cout << std::endl;
}

/*********************************************************************
                PRIOTITY QUEUE STRUCTS STUFF
*******************************************************************/
void initPriQueue(priority_queue_t *q) {
  q->m_front = nullptr;
  q->size = 0;
}

void addElem(priority_queue_t* q, Edge *e) {
  pq_node_t *newNode = new pq_node_t;
  newNode->item = e;

  //empty pq
  if (q->m_front == nullptr) {
    q->m_front = newNode;
    newNode->nextNode = nullptr;
    q->size++;
    return;
  }

  //less than front of pq
  if (newNode->item->getCost() < q->m_front->item->getCost()) {
    newNode->nextNode = q->m_front;
    q->m_front = newNode;
    q->size++;
    return;
  }

  pq_node_t *temp = q->m_front;
  pq_node_t *prev = q->m_front;
  while (temp != nullptr) {
    if (newNode->item->getCost() < temp->item->getCost()) {
      prev->nextNode = newNode;
      newNode->nextNode = temp;
      q->size++;
      return;
    }

    prev = temp;
    temp = temp->nextNode;
  }

  //adding to back of list
  prev->nextNode = newNode;
  newNode->nextNode = nullptr;
}

Edge* getTop(priority_queue_t* q) {
  if (q->m_front == nullptr) {
    return nullptr;
  }


  pq_node_t* retNode = q->m_front;
  q->m_front = q->m_front->nextNode;

  Edge* retEdge = retNode->item;
  delete retNode;

  q->size--;

  return retEdge;
}

bool isPriQueueEmpty(priority_queue_t* q) {
  return (q->m_front == nullptr);
}

void printPriQueue(priority_queue_t* q) {
  pq_node_t *n = q->m_front;

  std::cout << "PQ: ";
  while (n != nullptr) {
    n->item->print();
    n = n->nextNode;
  }
  std::cout << std::endl;
}


/****************************************************************
          GRAPH STUFF
*****************************************************************/
Graph::Graph(int** costs, int n){
  dll = new DoublyLinkedList();
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if ((costs[i][j] >= 0) && (i != j)) {
        Edge *e = new Edge(i, j, costs[i][j]);
        dll->addBack(e);
        numEdges++;
      }
    }
  }

  order = n;
}

/*
RETURNS: pointers to two doubly linked lists; first one contains list of tree edges from dfs
                                  second one contains list of back edges from dfs
*/
DoublyLinkedList** Graph::dfs() {
  DoublyLinkedList** edge_set = new DoublyLinkedList*[2];
  edge_set[0] = new DoublyLinkedList();
  edge_set[1] = new DoublyLinkedList();

  bool *visitedVertex = new bool[order];
  for (int i = 0; i < order; i++) {
    visitedVertex[i] = false;
  }

  //visit first vertex
  int vert = dll->getFront()->getValue()->getV1();
  int nextVert = dll->getFront()->getValue()->getV2();
  visitedVertex[vert] = true;
  edge_set[0]->addBack(dll->getFront()->getValue());

  //recurse
  dfs_recurse(edge_set, nextVert, visitedVertex);

  return edge_set;
}


DoublyLinkedList** Graph::bfs() {
  DoublyLinkedList** edge_set = new DoublyLinkedList*[2];
  edge_set[0] = new DoublyLinkedList();
  edge_set[1] = new DoublyLinkedList();

  queue_t *myQueue = new queue_t;
  initQueue(myQueue);

  bool *visitedVertex = new bool[order];
  for (int i = 0; i < order; i++) {
    visitedVertex[i] = false;
  }

  //visit first vertex
  int vert = dll->getFront()->getValue()->getV1();
  //int nextVert = dll->getFront()->getValue()->getV2();
  visitedVertex[vert] = true;
  enqueue(myQueue, vert);

  while (!isQueueEmpty(myQueue)) {
    //pop a vertex off the queue
    vert = dequeue(myQueue);

    //find all adjacent vertices
    Node* curNode = dll->getFront();
    while (curNode != nullptr) {
      //find vertices in doubly linked list that correspond to vert
      Edge *thisEdge = curNode->getValue();
      if (thisEdge->getV1() == vert) {
        //need to check if their v2 has been visited

        if (!visitedVertex[thisEdge->getV2()]) {
          visitedVertex[thisEdge->getV2()] = true;
          enqueue(myQueue, thisEdge->getV2());
          edge_set[0]->addBack(thisEdge);
        } else {
          edge_set[1]->addBack(thisEdge);
        }
      }
      curNode = curNode->getNext();
    }   //end loop finding all adjacent vertices
  }



  return edge_set;
}

DoublyLinkedList* Graph::kruskal() {
  DoublyLinkedList* mst = new DoublyLinkedList();
  int mstWeight = 0;    //wont actually use but good to keep track of

  //disjoint set for vertices to check for cycles
  DisjointSet *mySet = new DisjointSet(order);

  //Priority Queue (leftist heap) to organize edges
  priority_queue_t *priQueue = new priority_queue_t;
  initPriQueue(priQueue);

  Node* temp = dll->getFront();
  while (temp != nullptr) {
    addElem(priQueue, temp->getValue());
    temp = temp->getNext();
  }

  while (!isPriQueueEmpty(priQueue)) {
    Edge* e = getTop(priQueue);
    int u = e->getV1();
    int v = e->getV2();

    int uSet = mySet->find(u);
    int vSet = mySet->find(v);

    if (uSet != vSet) {
      mst->addBack(e);
      mstWeight++;
      mySet->union_set(uSet, vSet);
    }
  }

  return mst;
}

DoublyLinkedList* Graph::prim(){
  DoublyLinkedList* mst = new DoublyLinkedList();

  //Priority Queue (leftist heap) to organize edges
  priority_queue_t *priQueue = new priority_queue_t;
  initPriQueue(priQueue);

  //array corresponding to vertices that were hit
  bool* visited = new bool[order];
  for (int i = 0; i < order; i++) {
    visited[i] = false;
  }

  /*
    NEED starting point
    this visits first vertex and adds all edjacent edges to Priority Queue
  */
  /**********************************************************/
  int curVertex = dll->getFront()->getValue()->getV1();
  visited[curVertex] = true;
  Node* curNode = dll->getFront();
  while (curNode != nullptr) {
    Edge *curEdge = curNode->getValue();
    if (curEdge->getV1() == curVertex) {
      addElem(priQueue, curEdge);
    }
    curNode = curNode->getNext();
  }
  /**********************************************************/


  int count = 0;    //holds onto how many vertices have been visited
  while (count < order) {
    if (!visited[curVertex]) {
      visited[curVertex] = true;
      //push edges to Priority Queue
      /**************************************/
      curNode = dll->getFront();
      while (curNode != nullptr) {
        Edge *curEdge = curNode->getValue();
        if (curEdge->getV1() == curVertex) {
          addElem(priQueue, curEdge);
        }
        curNode = curNode->getNext();
      }
      /****************************************/

      Edge* minEdge = getTop(priQueue);

      if (!(visited[minEdge->getV2()])) {
        mst->addBack(minEdge);
        curVertex = minEdge->getV2();
        count++;
      }


    } else {
      //get minimum edge from priority queue again
      Edge* minEdge = getTop(priQueue);

      if (minEdge == nullptr) {
        break;
      }

      if (!(visited[minEdge->getV2()])) {
        mst->addBack(minEdge);
        curVertex = minEdge->getV2();
        count++;
      }
    }
  }



  return mst;
}

//working here getting correct tree edge path but back edge list is not correct
void Graph::dfs_recurse(DoublyLinkedList ** edgeSet, int thisVertex, bool *visited) {
  //has visited this vertex
  visited[thisVertex] = true;

  Node* curNode = dll->getFront();
  while (curNode != nullptr) {
    Edge *curEdge = curNode->getValue();
    if (curEdge->getV1() == thisVertex) {
      if (visited[curEdge->getV2()]) {
        edgeSet[1]->addBack(curEdge);
      } else {  //have not visited
        edgeSet[0]->addBack(curEdge);
        dfs_recurse(edgeSet, curEdge->getV2(), visited);

        /*bool keepGoing = false;
        for (int i = 0; i < order; i++) {
          if (visited[i] == false) {
            keepGoing = true;
            break;
          }
        }

        if (!keepGoing) {
          return;
        }
        */
      }
    }

    curNode = curNode->getNext();
  }

  //gets here if there are no more vertices to visit.
  return;
}

/*

DoublyLinkedList* mst = new DoublyLinkedList();

//array corresponding to vertices that were hit
bool visited[order];
for (int i = 0; i < order; i++) {
  visited[i] = false;
}

//Priority Queue (leftist heap) to organize edges
priority_queue_t *priQueue = new priority_queue_t;
initPriQueue(priQueue);

//visit arbitrary first two vertices
Edge *thisEdge = getTop(priQueue);
visited[thisEdge->getV1()] = true;
visited[thisEdge->getV2()] = true;

bool allVerticesVisited = false;
while (!(allVerticesVisited)) {
  //pick arbitrary vertex
  Node* curNode = dll->getFront();
  int v = curNode->getValue()->getV1();
  while (curNode != nullptr) {
    Edge* curEdge = curNode->getValue();
    if (curEdge->getV1() == v) {
      addElem(priQueue, curEdge);
    }

    //get valid minEdge
    bool valid = false;
    while (!valid) {
      Edge* minEdge = getTop(priQueue);

      if (minEdge) {}
    }


    curNode = curNode->getNext();
  }



  allVerticesVisited = true;
  for (int i = 0; i < order; i++) {
    if (visited[i] = false) {
      allVerticesVisited = false;
      break;
    }
  }
}



*/
