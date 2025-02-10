#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <list>

class Graph {
    int V; // Number of vertices
    std::vector<std::list<int>> adj; // Adjacency list

public:
    Graph(int V);
    std::list<int> getAdj(int i);
    void addEdge(int v, int w);
    bool isEulerian();
    bool isConnected();
    void DFSUtil(int v, std::vector<bool>& visited);
    void printEulerianCircuit();

    void manualAddEdge(int v, int w);
    void displayGraph();
};

void generateRandomGraph(Graph& g, int vertexCount, int edgeCount, unsigned int seed);

#endif // GRAPH_HPP
