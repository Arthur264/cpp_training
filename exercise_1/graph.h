#pragma once

#include "vector"
#include <set>
#include <list>
#include <iostream>
#include <memory>

struct Edge {
    int from{0};
    int to{0};
    int distance{0};
};

typedef std::vector<std::pair<int, int>> VectorPair;
typedef std::vector<Edge> VectorEdge;

class Graph {
public:
    Graph(VectorEdge const &edges, int vertices);
    ~Graph() = default;

    std::unique_ptr<VectorPair[]> adjVector;
    int vertices;

    void shortestPath(int src, int destination) const;

};

std::ostream &operator<<(std::ostream &out, Graph const &graph);