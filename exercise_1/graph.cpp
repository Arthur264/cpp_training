#include <queue>
#include <set>
#include <unistd.h>
#include "graph.h"
#include "climits"


Graph::Graph(std::vector<Edge> const &edges, int vertices) : vertices{vertices} {
    adjVector = std::make_unique<VectorPair[]>(vertices);
    for (const auto &edge: edges) {
        adjVector[edge.from].emplace_back(std::make_pair(edge.to, edge.distance));
    }
}

void Graph::shortestPath(int src, int destination) const {
    std::vector<int> dist(vertices, INT_MAX);
    std::vector<int> pred(vertices, -1);
    std::vector<int> path;
    std::set<int> queue;

    queue.insert(src);
    dist[src] = 0;

    while (!queue.empty()) {
        auto vertex = *queue.begin();
        queue.erase(queue.begin());

        for (const auto &adj: adjVector[vertex]) {
            int adj_vertex = adj.first;
            int adj_distance = adj.second;

            if ((dist[vertex] != INT_MAX) && (dist[adj_vertex] > dist[vertex] + adj_distance)) {
                dist[adj_vertex] = dist[vertex] + adj_distance;
                pred[adj_vertex] = vertex;
                queue.insert(adj_vertex);
            }
        }
    }

    std::cout << "Shortest path length is: " << dist[destination] << std::endl;
    std::cout << "Shortest path is: " << destination;

    while (pred[destination] != -1) {
        std::cout << " -> " << pred[destination];
        destination = pred[destination];
    }

}

std::ostream &operator<<(std::ostream &out, Graph const &graph) {
    out << "Graph representation " << std::endl;
    for (int i = 0; i < graph.vertices; ++i) {
        out << i;
        for (auto adj: graph.adjVector[i]) {
            out << " (" << adj.first << "," << adj.second << ")";
        }
        out << std::endl;
    }
    return out;
}
