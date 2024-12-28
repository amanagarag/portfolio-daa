#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
using namespace std;

class LandConsumptionNetwork {
private:
    int vertices;
    vector<vector<pair<int, int>>> adjList;

public:
    LandConsumptionNetwork(int v) : vertices(v), adjList(v) {}

    void addEdge(int u, int v, int consumptionRate) {
        adjList[u].push_back({v, consumptionRate});
        adjList[v].push_back({u, consumptionRate});
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

            for (auto& neighbor : adjList[node]) {
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

    void dfs(int start, vector<bool>& visited) {
        visited[start] = true;
        cout << start << " ";

        for (auto& neighbor : adjList[start]) {
            if (!visited[neighbor.first]) {
                dfs(neighbor.first, visited);
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

            for (auto& neighbor : adjList[node]) {
                if (!visited[neighbor.first]) {
                    visited[neighbor.first] = true;
                    q.push(neighbor.first);
                }
            }
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

    bool searchLandParcel(int parcel) {
        for (int i = 0; i < vertices; ++i) {
            if (i == parcel) {
                return true;
            }
        }
        return false;
    }

    bool searchLandConsumptionRate(int rate) {
        for (int i = 0; i < vertices; ++i) {
            for (auto& neighbor : adjList[i]) {
                if (neighbor.second == rate) {
                    return true;
                }
            }
        }
        return false;
    }
};

int main() {
    int vertices = 5;
    LandConsumptionNetwork network(vertices);

    network.addEdge(0, 1, 4);
    network.addEdge(0, 2, 1);
    network.addEdge(1, 2, 2);
    network.addEdge(1, 3, 5);
    network.addEdge(2, 3, 8);
    network.addEdge(2, 4, 10);
    network.addEdge(3, 4, 2);

    vector<int> dist = network.dijkstra(0);
    cout << "Shortest paths from source (0):\n";
    for (int i = 0; i < vertices; ++i) {
        cout << "To " << i << ": " << (dist[i] == INT_MAX ? "INF" : to_string(dist[i])) << endl;
    }

    vector<bool> visited(vertices, false);
    cout << "DFS Traversal: ";
    network.dfs(0, visited);
    cout << endl;

    cout << "BFS Traversal: ";
    network.bfs(0);
    cout << endl;

    vector<int> landConsumption = {5, 2, 9, 1, 5, 6};
    cout << "Original Land Consumption Rates: ";
    for (int rate : landConsumption) cout << rate << " ";

    network.mergeSort(landConsumption);

    cout << "\nSorted Land Consumption Rates: ";
    for (int rate : landConsumption) cout << rate << " ";
    cout << endl;

    int parcelToSearch = 3;
    if (network.searchLandParcel(parcelToSearch)) {
        cout << "Land Parcel " << parcelToSearch << " exists." << endl;
    } else {
        cout << "Land Parcel " << parcelToSearch << " does not exist." << endl;
    }

    int consumptionRateToSearch = 8;
    if (network.searchLandConsumptionRate(consumptionRateToSearch)) {
        cout << "Land Consumption Rate " << consumptionRateToSearch << " exists." << endl;
    } else {
        cout << "Land Consumption Rate " << consumptionRateToSearch << " does not exist." << endl;
    }

    return 0;
}
