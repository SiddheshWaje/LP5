#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>

using namespace std;

// Graph class representing the adjacency list
class Graph {
    int V;  // Number of vertices
    vector<vector<int>> adj;  // Adjacency list

public:
    Graph(int V) : V(V), adj(V) {}

    // Add an edge to the graph
    void addEdge(int v, int w) {
        adj[v].push_back(w);
    }

    // Parallel Depth-First Search
    void parallelDFS(int startVertex) {
        vector<bool> visited(V, false);
        parallelDFSUtil(startVertex, visited);
    }
    void SEQparallelDFS(int startVertex){
        vector<bool> visited(V, false);
        SEQparallelDFSUtil(startVertex, visited);
    }

    // Parallel DFS utility function
    void SEQparallelDFSUtil(int v, vector<bool>& visited) {
        visited[v] = true;
        cout << v << " ";
        for (int i = 0; i < adj[v].size(); ++i) {
            int n = adj[v][i];
            if (!visited[n])
                SEQparallelDFSUtil(n, visited);
        }
    }
    void parallelDFSUtil(int v, vector<bool>& visited) {
        visited[v] = true;
        cout << v << " ";

        #pragma omp parallel for
        for (int i = 0; i < adj[v].size(); ++i) {
            int n = adj[v][i];
            if (!visited[n])
                parallelDFSUtil(n, visited);
        }
    }

};



int main() {
    // Create a graph
    Graph g(7);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 5);
    g.addEdge(2, 6);
    
    double startTime = omp_get_wtime();
    cout << "Depth-First Search (DFS): ";
    g.parallelDFS(0);
    cout << endl;
    double endTime = omp_get_wtime();
    printf("This task took %f seconds\n\n", endTime - startTime);

    startTime = omp_get_wtime();
    cout << "Depth-First Search (DFS): ";
    g.SEQparallelDFS(0);
    cout << endl;
     endTime = omp_get_wtime();
    printf("This task took %f seconds\n\n", endTime - startTime);


    return 0;
}