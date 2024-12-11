#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>

using namespace std;

typedef pair<int, int> pii;

void dijkstra(int source, vector<vector<pii>>& graph, vector<int>& distances) {
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    distances[source] = 0;
    pq.push({0, source});
    
    while (!pq.empty()) {
        int current_distance = pq.top().first;
        int current_vertex = pq.top().second;
        pq.pop();
        
        if (current_distance > distances[current_vertex]) {
            continue;
        }
        
        for (auto& neighbor : graph[current_vertex]) {
            int neighbor_vertex = neighbor.first;
            int edge_weight = neighbor.second;
            int new_distance = current_distance + edge_weight;
            
            if (new_distance < distances[neighbor_vertex]) {
                distances[neighbor_vertex] = new_distance;
                pq.push({new_distance, neighbor_vertex});
            }
        }
    }
}

int main() {
    int n, m;
    cout << "Enter the number of vertices and edges: ";
    cin >> n >> m;
    
    vector<vector<pii>> graph(n);
    
    cout << "Enter the edges in the format (u, v, weight):\n";
    for (int i = 0; i < m; ++i) {
        int u, v, weight;
        cin >> u >> v >> weight;
        graph[u].push_back({v, weight});
    }
    
    int source;
    cout << "Enter the source vertex: ";
    cin >> source;
    
    vector<int> distances(n, INT_MAX);
    dijkstra(source, graph, distances);
    
    cout << "Shortest distances from source " << source << ":\n";
    for (int i = 0; i < n; ++i) {
        cout << "Vertex " << i << " : " << distances[i] << "\n";
    }
    
    return 0;
}
