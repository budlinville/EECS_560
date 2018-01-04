#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "lib/doubly-linked-list/list.hpp"
#include "lib/disjoint-set/disjoint-set.hpp"

typedef struct node_t {
	int item;
	node_t * nextNode;
  node_t * prevNode;
} node_t;

typedef struct queue_t {
	node_t * m_front;
  node_t * m_back;
  int size;
} queue_t;

void initQueue(queue_t *q);
void enqueue(queue_t* q, int i);
int dequeue(queue_t* q);
int getQueueSize(queue_t* q);
bool isQueueEmpty(queue_t* q);
void printQueue(queue_t* q);

typedef struct pq_node_t {
	Edge *item;
	pq_node_t * nextNode;
} pq_node_t;

typedef struct priority_queue_t {
	pq_node_t * m_front;
  int size;
} priority_queue_t;

void initPriQueue(priority_queue_t *q);
void addElem(priority_queue_t* q, Edge *e);
Edge* getTop(priority_queue_t* q);
bool isPriQueueEmpty(priority_queue_t* q);
void printPriQueue(priority_queue_t* q);

class Graph {
private:

  DoublyLinkedList *dll;
  int numEdges;
  int order;

  void dfs_recurse(DoublyLinkedList** edgeSet, int thisVertex, bool *visited);

public:
  /**
   * Initializes the graph
   */
  Graph(int** cost, int n);

  /**
   * performs a dfs over the graph
   */
  DoublyLinkedList** dfs();

  /**
   * performs a bfs over the graph
   */
  DoublyLinkedList** bfs();

  /**
   * Generates a minimum spanning tree using kruskals algorithm
   */
  DoublyLinkedList* kruskal();

  /**
   * Generates a minimum spanning tree using prims algorithm
   */
  DoublyLinkedList* prim();

};

#endif //GRAPH_HPP defined
