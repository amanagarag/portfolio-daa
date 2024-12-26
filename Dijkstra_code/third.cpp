#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int maximizeLandUsage(vector<int>& land, int availableSpace) {
    sort(land.begin(), land.end(), greater<int>());
    int totalUsage = 0;
    for (int i = 0; i < land.size(); i++) {
        if (availableSpace >= land[i]) {
            availableSpace -= land[i];
            totalUsage += land[i];
        }
    }
    return totalUsage;
}

int maximizeLandPartition(vector<int>& land, int maxPartition) {
    vector<int> dp(maxPartition + 1, 0);
    
    for (int i = 1; i <= maxPartition; i++) {
        for (int j = 0; j < land.size(); j++) {
            if (i >= land[j]) {
                dp[i] = max(dp[i], dp[i - land[j]] + land[j]);
            }
        }
    }
    return dp[maxPartition];
}

int main() {
    vector<int> land = {4, 3, 7, 5, 2};
    int availableSpace = 15;
    
    int totalLandUsed = maximizeLandUsage(land, availableSpace);
    cout << "Maximum land used with Greedy Allocation: " << totalLandUsed << endl;

    int maxPartition = 10;
    int optimizedPartition = maximizeLandPartition(land, maxPartition);
    cout << "Optimized land partition using Dynamic Programming: " << optimizedPartition << endl;

    return 0;
}

