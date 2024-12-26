#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <map>
using namespace std;

class TrafficNetwork {
private:
    int vertices;
    map<int, vector<pair<int, int>>> adjList;

public:
    TrafficNetwork(int v) : vertices(v) {}

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

    void divideAndConquer(int start, int end) {
        if (start == end) return;

        int mid = (start + end) / 2;
        divideAndConquer(start, mid);
        divideAndConquer(mid + 1, end);
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

    for (int i = 0; i < shortestPaths.size(); ++i) {
        cout << "To node " << i << ": " << shortestPaths[i] << " minutes\n";
    }

    network.divideAndConquer(0, vertices - 1);

    return 0;
}

