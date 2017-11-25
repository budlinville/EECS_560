#ifndef EDGE_HPP
#define EDGE_HPP
#include <iostream>

class Edge {
  /**
   * vertices
   */
  int v1, v2;
  /**
   * cost of the edge
   */
  int cost;
public:
  /**
   * Constructor
   */
  Edge(int a, int b, int c): v1(a), v2(b), cost(c) {}

  void print() { std::cout << "(" << v1 << ", " << v2 << ") { " << cost << " }"; }

  bool operator== (const Edge that) {return (v1 = that.v1 && v2 == that.v2 && cost == that.cost);}
};
#endif //EDGE_HPP defined
