#include <iostream>
#include <vector>
#include <climits>
#include <queue>
#include <stack>
#include <algorithm>
#include <map>
using namespace std;

class TrafficNetwork {
private:
    int vertices;
    vector<vector<int>> adjList;

public:
    TrafficNetwork(int v) : vertices(v), adjList(v) {}

    void addEdge(int u, int v, int weight) {
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    bool bellmanFord(int edges, vector<vector<int>> &graph, int source, vector<int> &dist) {
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

    void dfs(int start, vector<bool> &visited) {
        visited[start] = true;
        cout << start << " ";

        for (int i = 0; i < adjList[start].size(); i++) {
            if (!visited[adjList[start][i]]) {
                dfs(adjList[start][i], visited);
            }
        }
    }

    void bfs(int start) {
        vector<bool> visited(vertices, false);
        queue<int> q;
        visited[start] = true;
        q.push(start);

        while (!q.empty()) {
            int node = q.front();
            q.pop();
            cout << node << " ";

            for (int i = 0; i < adjList[node].size(); i++) {
                int neighbor = adjList[node][i];
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
    }

    void bubbleSort(vector<int> &arr) {
        int n = arr.size();
        for (int i = 0; i < n-1; i++) {
            for (int j = 0; j < n-i-1; j++) {
                if (arr[j] > arr[j+1]) {
                    swap(arr[j], arr[j+1]);
                }
            }
        }
    }

    void selectionSort(vector<int> &arr) {
        int n = arr.size();
        for (int i = 0; i < n-1; i++) {
            int minIdx = i;
            for (int j = i+1; j < n; j++) {
                if (arr[j] < arr[minIdx]) {
                    minIdx = j;
                }
            }
            swap(arr[i], arr[minIdx]);
        }
    }

    void mergeSort(vector<int>& arr) {
        if (arr.size() <= 1) return;

        int mid = arr.size() / 2;
        vector<int> left(arr.begin(), arr.begin() + mid);
        vector<int> right(arr.begin() + mid, arr.end());

        mergeSort(left);
        mergeSort(right);

        merge(left.begin(), left.end(), right.begin(), right.end(), arr.begin());
    }

    void heapSort(vector<int> &arr) {
        make_heap(arr.begin(), arr.end());
        sort_heap(arr.begin(), arr.end());
    }
};

int main() {
    int vertices = 5;
    int edges = 8;
    vector<vector<int>> graph = {
        {0, 1, 4}, {0, 2, 1}, {1, 2, 2}, {1, 3, 5},
        {2, 3, 8}, {2, 4, 10}, {3, 4, 2}, {4, 3, -3}};
    
    TrafficNetwork network(vertices);

    vector<int> dist(vertices, INT_MAX);
    clock_t start = clock();
    if (network.bellmanFord(edges, graph, 0, dist)) {
        cout << "Shortest paths from source (0):\n";
        for (int i = 0; i < vertices; ++i) {
            cout << "To " << i << ": " << (dist[i] == INT_MAX ? "INF" : to_string(dist[i])) << endl;
        }
    } else {
        cout << "Negative weight cycle detected\n";
    }
    clock_t end = clock();
    cout << "Bellman-Ford execution time: " << double(end - start) / CLOCKS_PER_SEC << " seconds\n";

    vector<bool> visited(vertices, false);
    cout << "DFS Traversal: ";
    start = clock();
    network.dfs(0, visited);
    cout << endl;
    end = clock();
    cout << "DFS execution time: " << double(end - start) / CLOCKS_PER_SEC << " seconds\n";

    cout << "BFS Traversal: ";
    start = clock();
    network.bfs(0);
    cout << endl;
    end = clock();
    cout << "BFS execution time: " << double(end - start) / CLOCKS_PER_SEC << " seconds\n";

    vector<int> data = {5, 2, 9, 1, 5, 6};
    cout << "Original Data: ";
    for (int num : data) cout << num << " ";
    
    start = clock();
    network.bubbleSort(data);
    cout << "\nBubble Sorted Data: ";
    for (int num : data) cout << num << " ";
    end = clock();
    cout << "\nBubble Sort execution time: " << double(end - start) / CLOCKS_PER_SEC << " seconds\n";
    
    data = {5, 2, 9, 1, 5, 6};
    start = clock();
    network.selectionSort(data);
    cout << "\nSelection Sorted Data: ";
    for (int num : data) cout << num << " ";
    end = clock();
    cout << "\nSelection Sort execution time: " << double(end - start) / CLOCKS_PER_SEC << " seconds\n";
    
    data = {5, 2, 9, 1, 5, 6};
    start = clock();
    network.mergeSort(data);
    cout << "\nMerge Sorted Data: ";
    for (int num : data) cout << num << " ";
    end = clock();
    cout << "\nMerge Sort execution time: " << double(end - start) / CLOCKS_PER_SEC << " seconds\n";

    data = {5, 2, 9, 1, 5, 6};
    start = clock();
    network.heapSort(data);
    cout << "\nHeap Sorted Data: ";
    for (int num : data) cout << num << " ";
    end = clock();
    cout << "\nHeap Sort execution time: " << double(end - start) / CLOCKS_PER_SEC << " seconds\n";
    
    return 0;
}
