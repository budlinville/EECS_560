#include "graph.hpp"
#include "util/util.hpp"

Graph::Graph(int** costs, int n){
  dll = new DoublyLinkedList();
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (costs[i][j] >= 0) {
        Edge e = Edge(i, j, costs[i][j]);
        dll->add();
      }
    }
  }
}

DoublyLinkedList** Graph::dfs() {
  DoublyLinkedList** edge_set = new DoublyLinkedList*[2];
  IMPLEMENT_ME();
  return edge_set;
}


DoublyLinkedList** Graph::bfs() {
  DoublyLinkedList** edge_set = new DoublyLinkedList*[2];
  IMPLEMENT_ME();
  return edge_set;
}

DoublyLinkedList* Graph::kruskal() {
  IMPLEMENT_ME();
  return new DoublyLinkedList();
}

DoublyLinkedList* Graph::prim(){
  IMPLEMENT_ME();
  return new DoublyLinkedList();
}
