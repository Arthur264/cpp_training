#include <climits>
#include <unordered_set>

#include "graph.h"

Graph::Graph(std::vector<Edge> const &edges, int vertices) : vertices{vertices},
                                                             adjVector{std::make_unique<VectorPair[]>(vertices)} {
    for (auto const &edge: edges) {
        adjVector[edge.from].emplace_back(edge.to, edge.distance);
    }
}

std::vector<int> Graph::shortestPath(int src, int destination, int &path_length) const {
    std::vector<int> dist(vertices, INT_MAX);
    std::vector<int> pred(vertices, -1);
    std::vector<int> path;
    std::unordered_set<int> queue;

    queue.insert(src);
    dist[src] = 0;

    while (!queue.empty()) {
        auto vertex = *queue.begin();
        queue.erase(queue.begin());

        for (auto const &adj: adjVector[vertex]) {
            int adj_vertex = adj.first;
            int adj_distance = adj.second;

            if ((dist[vertex] != INT_MAX) && (dist[adj_vertex] > dist[vertex] + adj_distance)) {
                dist[adj_vertex] = dist[vertex] + adj_distance;
                pred[adj_vertex] = vertex;
                queue.insert(adj_vertex);
            }
        }
    }

    path_length = dist[destination];
    path.push_back(destination);

    while (pred[destination] != -1) {
        destination = pred[destination];
        path.push_back(destination);
    }

    return path;
}

std::ostream &operator<<(std::ostream &out, Graph const &graph) {
    out << "Graph representation " << std::endl;
    for (int i = 0; i < graph.vertices; ++i) {
        out << i;
        for (auto const &adj: graph.adjVector[i]) {
            out << " (" << adj.first << "," << adj.second << ")";
        }
        out << std::endl;
    }
    return out;
}
