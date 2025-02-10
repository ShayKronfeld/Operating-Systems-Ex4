
#include <iostream>
#include <vector>
#include <list>
#include <cstdlib>
#include <ctime>
#include "graph.hpp"

// Constructor - create a graph with V vertices
Graph::Graph(int V) {
    this->V = V;
    adj.resize(V);
}

std::list<int> Graph::getAdj(int i) {
    return adj[i];
}


// Add an edge to the graph
void Graph::addEdge(int v, int w) {
    adj[v].push_back(w);
    adj[w].push_back(v); // Undirected graph
}

// Helper function for DFS to check connectivity
void Graph::DFSUtil(int v, std::vector<bool>& visited) {
    visited[v] = true;
    for (auto i = adj[v].begin(); i != adj[v].end(); ++i) {
        if (!visited[*i]) {
            DFSUtil(*i, visited);
        }
    }
}

// Check if all vertices with non-zero degree are connected
bool Graph::isConnected() {
    std::vector<bool> visited(V, false);
    int nonZeroDegree = -1;

    for (int i = 0; i < V; i++) {
        if (!adj[i].empty()) {
            nonZeroDegree = i;
            break;
        }
    }

    if (nonZeroDegree == -1) return true;

    DFSUtil(nonZeroDegree, visited);

    for (int i = 0; i < V; i++) {
        if (!visited[i] && !adj[i].empty()) {
            return false;
        }
    }

    return true;
}

// Function to check for an Euler circuit
bool Graph::isEulerian() {
    if (!isConnected()) return false;

    int odd = 0;
    for (int i = 0; i < V; i++) {
        if (adj[i].size() % 2 != 0) {
            odd++;
        }
    }

    return (odd == 0);
}

// Print the Eulerian circuit if it exists
void Graph::printEulerianCircuit() {
    if (!isEulerian()) {
        std::cout << "The graph does not have an Euler circuit." << std::endl;
        return;
    }
    std::cout << "The graph has an Euler circuit." << std::endl;
}

// Generate a random graph
void generateRandomGraph(Graph& g, int vertexCount, int edgeCount, unsigned int seed) {
    srand(seed);
    for (int i = 0; i < edgeCount; i++) {
        int u = rand() % vertexCount;
        int v = rand() % vertexCount;
        if (u != v) {
            g.addEdge(u, v);
        }
    }
}



// Function to manually add edges
void Graph::manualAddEdge(int v, int w) {
    if (v >= 0 && v < V && w >= 0 && w < V) {
        addEdge(v, w);
        std::cout << "Added edge between " << v << " and " << w << std::endl;
    } else {
        std::cout << "Invalid vertex number!" << std::endl;
    }
}

// Function to display the graph
void Graph::displayGraph() {
    std::cout << "Graph adjacency list:" << std::endl;
    for (int i = 0; i < V; i++) {
        std::cout << i << ": ";
        for (const int& neighbor : adj[i]) {
            std::cout << neighbor << " ";
        }
        std::cout << std::endl;
    }
}
