#include <iostream>
#include <vector>
using namespace std;

class Graph {
    int V; // 顶点数
    vector<int> *adj; // 邻接表
    void DFSUtil(int v, vector<bool> &visited); // 用于DFS的辅助函数

public:
    Graph(int V);
    void addEdge(int v, int w);
    void DFS(int v);
};

Graph::Graph(int V) {
    this->V = V;
    adj = new vector<int>[V];
}

void Graph::addEdge(int v, int w) {
    // 无向图，加双向边
    adj[v].push_back(w);
    adj[w].push_back(v);
}

void Graph::DFSUtil(int v, vector<bool> &visited) {
    visited[v] = true;
    cout << v << " ";
    for (int i : adj[v]) {
        if (!visited[i]) {
            DFSUtil(i, visited);
        }
    }
}

void Graph::DFS(int v) {
    vector<bool> visited(V, false);
    DFSUtil(v, visited);
}

int main() {
    Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    cout << "深度优先搜索（从顶点 2 开始）: ";
    g.DFS(2);
    system("pause");
    return 0;
}