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

	// Parallel Breadth-First Search
    void SEQparallelBFS(int startVertex) {
        vector<bool> visited(V, false);
        queue<int> q;

        visited[startVertex] = true;
        q.push(startVertex);

        while (!q.empty()) {
            int v = q.front();
            q.pop();
            cout << v << " ";
            for (int i = 0; i < adj[v].size(); ++i) {
                int n = adj[v][i];
                if (!visited[n]) {
                    visited[n] = true;
                    q.push(n);
                }
            }
        }
    }

    void parallelBFS(int startVertex) {
        vector<bool> visited(V, false);
        queue<int> q;

        visited[startVertex] = true;
        q.push(startVertex);

        while (!q.empty()) {
            int v = q.front();
            q.pop();
            cout << v << " ";

            #pragma omp parallel for
            for (int i = 0; i < adj[v].size(); ++i) {
                int n = adj[v][i];
                if (!visited[n]) {
                    visited[n] = true;
                    q.push(n);
                }
            }
        }
    }
};

int main() {
    // Create a graph
int n;
cout<<"enter no. of vertices:";

cin>>n;
int e;
cout<<"enter no. of edges:";
cin>>e;

Graph g(n);

for(int i=0;i<e;i++){
	int a,b;
	cout<<"Add edges:";
	cin>>a>>b;
	g.addEdge(a,b);
}

    double startTime = omp_get_wtime();
    cout << "Breadth-First Search (BFS): ";
    g.parallelBFS(0);
    cout << endl;
    double endTime = omp_get_wtime();
    printf("This task took %f seconds\n", endTime - startTime);

    startTime = omp_get_wtime();
    cout << "Breadth-First Search (BFS): ";
    g.SEQparallelBFS(0);
    cout << endl;
    endTime = omp_get_wtime();
    printf("This task took %f seconds\n", endTime - startTime);

    return 0;
}