#include <iostream>
#include <cstdlib>
#include <unistd.h> // getopt
#include <vector>
#include <set>
#include <sstream> 
#include "graph.hpp"

using namespace std;

// Function to randomly add missing edges
void addRandomEdges(Graph& g, int vertexCount, size_t edgeCount, set<pair<int, int>>& edgesAdded) {
    while (edgesAdded.size() < edgeCount) {
        int u = rand() % vertexCount;
        int v = rand() % vertexCount;
        if (u != v) {
            pair<int, int> edge = make_pair(min(u, v), max(u, v)); // To avoid duplicates
            if (edgesAdded.find(edge) == edgesAdded.end()) { // If the edge is not in edgesAdded
                edgesAdded.insert(edge);
                g.addEdge(u, v);
                cout << "Randomly added edge: " << u << " - " << v << endl;  
            }
        }
    }
}

// Main function to receive parameters from command line and run the algorithm
int main(int argc, char* argv[]) {

    int vertexCount = 0;
    size_t edgeCount = 0;  
    int option;
    vector<pair<int, int>> userEdges;  // List of edges provided by the user
    set<pair<int, int>> edgesAdded;    // List of edges added in the end (including random ones)

 
    // Use getopt to read parameters from command line
    while ((option = getopt(argc, argv, "v:e:s:a:")) != -1) {
        switch (option) {
        case 'v': vertexCount = atoi(optarg); break;
        case 'e': edgeCount = atoi(optarg); break;
        case 's': { 
            unsigned int seed = atoi(optarg);  // Add seed if needed later
            srand(seed);  // Set the seed for randomness
            break;
        }
        case 'a': {
            // Split the edges provided by the user
            string input = optarg;
            stringstream ss(input);
            string edge;
            while (getline(ss, edge, ',')) { // Split the edges by commas
                int u, v;
                // Check if the edges are in the correct format (e.g., "0-1")
                if (sscanf(edge.c_str(), "%d-%d", &u, &v) == 2) { // Correctly read the edge
                    if (u != v) {  // Check if the vertices are different
                        userEdges.push_back(make_pair(u, v));
                    } else {
                        cerr << "Invalid edge: " << u << "," << v << " (same vertex)" << endl;
                    }
                } else {
                    cerr << "Invalid edge format: " << edge << endl;  // If the edge is not correct
                }
            }
            break;
        }
        default:
            cerr << "Usage: " << argv[0] << " -v <vertices> -e <edges> -s <seed> -a <edges>" << endl;
            return 1;
        }
    }

    if (vertexCount <= 0 || edgeCount <= 0) {
        cerr << "Error: Number of vertices and edges must be greater than 0." << endl;
        return 1;
    }

    if (userEdges.size() > edgeCount){
        cerr << "Error: The number of edges received is greater than the number entered." << endl;
        return 1;
    }
    
    // Create the graph
    Graph g(vertexCount);

    // Add the edges provided by the user
    for (auto& edge : userEdges) {
        int u = edge.first;
        int v = edge.second;
        if (u >= 0 && v >= 0 && u < vertexCount && v < vertexCount) {
            g.addEdge(u, v);
            edgesAdded.insert(make_pair(min(u, v), max(u, v)));
            cout << "User added edge: " << u << " - " << v << endl;  // Print the edges added by the user
            
        } else {
            cerr << "Invalid edge: " << u << " - " << v << endl;
        }
    }

    // If the number of edges provided by the user is less than the minimum, add random edges
    if (edgesAdded.size() < edgeCount) {
        addRandomEdges(g, vertexCount, edgeCount, edgesAdded);
    }

    // Check for Eulerian circuit
    g.printEulerianCircuit();

    return 0;
}