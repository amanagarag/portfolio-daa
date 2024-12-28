#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <climits>
#include <map>
#include <algorithm>
using namespace std;

class BinaryTree {
public:
    int data;
    BinaryTree* left;
    BinaryTree* right;

    BinaryTree(int val) : data(val), left(nullptr), right(nullptr) {}
};

class TrafficNetwork {
private:
    int vertices;
    map<int, vector<pair<int, int>>> adjList;
    BinaryTree* root;

public:
    TrafficNetwork(int v) : vertices(v), root(nullptr) {}

    void addEdge(int u, int v, int weight) {
        adjList[u].push_back({v, weight});
        adjList[v].push_back({u, weight});
    }

    vector<int> dijkstra(int start) {
        vector<int> dist(vertices, INT_MAX);
        dist[start] = 0;

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        pq.push({0, start});

        while (!pq.empty()) {
            int d = pq.top().first;
            int node = pq.top().second;
            pq.pop();

            for (auto &neighbor : adjList[node]) {
                int nextNode = neighbor.first;
                int weight = neighbor.second;

                if (dist[node] + weight < dist[nextNode]) {
                    dist[nextNode] = dist[node] + weight;
                    pq.push({dist[nextNode], nextNode});
                }
            }
        }

        return dist;
    }

    void breadthFirstTraversal(int start) {
        vector<bool> visited(vertices, false);
        queue<int> q;

        q.push(start);
        visited[start] = true;

        cout << "BFS Traversal: ";

        while (!q.empty()) {
            int node = q.front();
            q.pop();
            cout << node << " ";

            for (auto &neighbor : adjList[node]) {
                int nextNode = neighbor.first;
                if (!visited[nextNode]) {
                    q.push(nextNode);
                    visited[nextNode] = true;
                }
            }
        }
        cout << endl;
    }

    void mergeSort(vector<int>& arr, int left, int right) {
        if (left >= right) return;

        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }

    void merge(vector<int>& arr, int left, int mid, int right) {
        vector<int> temp;
        int i = left, j = mid + 1;

        while (i <= mid && j <= right) {
            if (arr[i] <= arr[j]) temp.push_back(arr[i++]);
            else temp.push_back(arr[j++]);
        }

        while (i <= mid) temp.push_back(arr[i++]);
        while (j <= right) temp.push_back(arr[j++]);

        for (int k = left; k <= right; ++k) arr[k] = temp[k - left];
    }

    BinaryTree* insertBinaryTree(BinaryTree* root, int data) {
        if (!root) return new BinaryTree(data);
        if (data < root->data) root->left = insertBinaryTree(root->left, data);
        else root->right = insertBinaryTree(root->right, data);
        return root;
    }
};

int main() {
    int vertices = 6;
    TrafficNetwork network(vertices);

    network.addEdge(0, 1, 4);
    network.addEdge(0, 2, 2);
    network.addEdge(1, 2, 5);
    network.addEdge(1, 3, 10);
    network.addEdge(2, 3, 3);
    network.addEdge(3, 4, 1);
    network.addEdge(4, 5, 7);

    int startNode = 0;
    vector<int> shortestPaths = network.dijkstra(startNode);

    cout << "Shortest paths from node " << startNode << ":\n";
    for (int i = 0; i < shortestPaths.size(); ++i) {
        cout << "To node " << i << ": " << shortestPaths[i] << " minutes\n";
    }

    network.breadthFirstTraversal(0);

    vector<int> data = {4, 3, 7, 1, 9, 5};
    network.mergeSort(data, 0, data.size() - 1);

    cout << "Sorted data: ";
    for (int num : data) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}


