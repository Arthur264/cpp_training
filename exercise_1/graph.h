#pragma once

#include <vector>
#include <iostream>
#include <memory>

struct Edge {
    int from{0};
    int to{0};
    int distance{0};
};

using VectorPair = std::vector<std::pair<int, int>>;
using VectorEdge = std::vector<Edge>;

class Graph {
public:
    Graph(VectorEdge const &edges, int vertices);

    ~Graph() = default;

    std::unique_ptr<VectorPair[]> adjVector;
    int vertices;

    std::vector<int> shortestPath(int src, int destination, int &path_length) const;

    friend std::ostream &operator<<(std::ostream &out, Graph const &graph);
};

