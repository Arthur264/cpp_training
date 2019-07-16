#include <iostream>
#include <fstream>
#include <unordered_set>
#include "graph.h"

int load_edges_from_file(const std::string &file_path, VectorEdge &edges) {
    Edge edge;
    std::unordered_set<int> unique_vertices;
    std::ifstream infile(file_path);

    if (infile.fail()) {
        std::cerr << "File not exist" << std::endl;
        exit(EXIT_FAILURE);
    }

    while (infile >> edge.from >> edge.to >> edge.distance) {
        edges.push_back(edge);
        unique_vertices.insert(edge.from);
        unique_vertices.insert(edge.to);
    }
    return unique_vertices.size();
}

int main(int argc, char **argv) {
    if (argc == 1) {
        std::cerr << "Please pass path to graph file" << std::endl;
        return EXIT_FAILURE;
    }

    int src, destination, path_length;
    std::vector<int> path;

    std::cout << "Please enter start vertex: ";
    std::cin >> src;

    std::cout << "Please enter end vertex: ";
    std::cin >> destination;


    if (src == destination) {
        std::cerr << "Start and end is one vertices" << std::endl;
        return EXIT_FAILURE;
    }

    VectorEdge edges;
    int vertices = load_edges_from_file(argv[1], edges);

    Graph graph(edges, vertices);

    std::cout << graph;

    path = graph.shortestPath(src, destination, path_length);

    std::cout << "Shortest path length is: " << path_length << std::endl;
    std::cout << "Shortest path is: ";

    for (auto const &i: path)
        std::cout << " -> " << i;

    return EXIT_SUCCESS;
}