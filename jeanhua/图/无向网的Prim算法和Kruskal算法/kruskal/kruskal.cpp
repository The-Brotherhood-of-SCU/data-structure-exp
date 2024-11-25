#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int src, dest, weight;
};

struct Graph {
    int V, E;
    vector<Edge> edges;

    void addEdge(int src, int dest, int weight) {
        edges.push_back({src, dest, weight});
        E++;
    }

    int find(int parent[], int i) {
        if (parent[i] == -1)
            return i;
        return find(parent, parent[i]);
    }

    void Union(int parent[], int x, int y) {
        int xset = find(parent, x);
        int yset = find(parent, y);
        if(xset != yset){
            parent[xset] = yset;
        }
    }

    void kruskalMST() {
        sort(edges.begin(), edges.end(), [](Edge a, Edge b) {
            return a.weight < b.weight;
        });

        int parent[100];
        for (int i = 0; i < V; ++i)
            parent[i] = -1;

        for (auto &i : edges) {
            int x = find(parent, i.src);
            int y = find(parent, i.dest);

            if (x != y) {
                cout << i.src << " - " << i.dest << " \n";
                Union(parent, x, y);
            }
        }
    }
};

int main() {
    Graph g;
    g.V = 5;
    g.E = 7;

    g.addEdge(0, 1, 2);
    g.addEdge(0, 3, 6);
    g.addEdge(0, 4, 1);
    g.addEdge(1, 3, 8);
    g.addEdge(1, 4, 5);
    g.addEdge(2, 3, 7);
    g.addEdge(3, 4, 9);
    g.kruskalMST();
    system("pause");
    return 0;
}