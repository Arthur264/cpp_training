#include <iostream>
#include <fstream>
#include "graph.h"
#include "set"

int load_edges_from_file(const std::string &file_path, VectorEdge &edges) {
    Edge edge;
    std::set<int> unique_vertices;
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
        exit(EXIT_FAILURE);
    }

    int src, destination;

    std::cout << "Please enter start vertex: ";
    std::cin >> src;

    std::cout << "Please enter end vertex: ";
    std::cin >> destination;


    if (src == destination) {
        std::cerr << "Start and end is one vertices" << std::endl;
        exit(EXIT_FAILURE);
    }

    VectorEdge edges;
    int vertices = load_edges_from_file(argv[1], edges);

    Graph graph(edges, vertices);

    std::cout << graph;

    graph.shortestPath(src, destination);
    return EXIT_SUCCESS;
}