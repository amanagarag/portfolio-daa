#include <iostream>
#include <vector>
#include <climits>
using namespace std;

bool bellmanFord(int vertices, int edges, vector<vector<int>> &graph, int source, vector<int> &dist) {
    dist[source] = 0;
    for (int i = 0; i < vertices - 1; ++i) {
        for (int j = 0; j < edges; ++j) {
            int u = graph[j][0];
            int v = graph[j][1];
            int weight = graph[j][2];
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
            }
        }
    }
    for (int j = 0; j < edges; ++j) {
        int u = graph[j][0];
        int v = graph[j][1];
        int weight = graph[j][2];
        if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
            return false;
        }
    }
    return true;
}

int main() {
    int vertices = 5;
    int edges = 8;
    vector<vector<int>> graph = {
        {0, 1, 4}, {0, 2, 1}, {1, 2, 2}, {1, 3, 5},
        {2, 3, 8}, {2, 4, 10}, {3, 4, 2}, {4, 3, -3}};

    vector<int> dist(vertices, INT_MAX);

    if (bellmanFord(vertices, edges, graph, 0, dist)) {
        cout << "Shortest paths from source (0):\n";
        for (int i = 0; i < vertices; ++i) {
            cout << "To " << i << ": " << (dist[i] == INT_MAX ? "INF" : to_string(dist[i])) << endl;
        }
    } else {
        cout << "Negative weight cycle detected. Solution not feasible.\n";
    }

    return 0;
}

