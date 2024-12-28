#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int src, dest, weight;
} Edge;

typedef struct {
    int parent;
    int rank;
} Subset;

void initializeSubsets(Subset subsets[], int vertices) {
    for (int v = 0; v < vertices; v++) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }
}

int find(Subset subsets[], int v) {
    if (subsets[v].parent != v) {
        subsets[v].parent = find(subsets, subsets[v].parent);
    }
    return subsets[v].parent;
}

void unionSubsets(Subset subsets[], int x, int y) {
    int xRoot = find(subsets, x);
    int yRoot = find(subsets, y);

    if (subsets[xRoot].rank < subsets[yRoot].rank) {
        subsets[xRoot].parent = yRoot;
    } else if (subsets[xRoot].rank > subsets[yRoot].rank) {
        subsets[yRoot].parent = xRoot;
    } else {
        subsets[yRoot].parent = xRoot;
        subsets[xRoot].rank++;
    }
}

int compareEdges(const void *a, const void *b) {
    return ((Edge *)a)->weight - ((Edge *)b)->weight;
}

void kruskal(Edge edges[], int vertices, int edgeCount) {
    Edge result[MAX];
    int resultIndex = 0;

    Subset subsets[vertices];
    initializeSubsets(subsets, vertices);

    qsort(edges, edgeCount, sizeof(Edge), compareEdges);

    for (int i = 0; i < edgeCount && resultIndex < vertices - 1; i++) {
        Edge nextEdge = edges[i];

        int x = find(subsets, nextEdge.src);
        int y = find(subsets, nextEdge.dest);

        if (x != y) {
            result[resultIndex++] = nextEdge;
            unionSubsets(subsets, x, y);
        }
    }

    printf("Edges in the Minimum Spanning Tree:\n");
    for (int i = 0; i < resultIndex; i++) {
        printf("%d -- %d == %d\n", result[i].src, result[i].dest, result[i].weight);
    }
}

int main() {
    int vertices = 6;
    int edgeCount = 8;

    Edge edges[] = {
        {0, 1, 4}, {0, 2, 4}, {1, 2, 2}, {1, 0, 4},
        {2, 3, 3}, {2, 5, 2}, {3, 4, 3}, {4, 5, 2}};

    kruskal(edges, vertices, edgeCount);

    return 0;
}
