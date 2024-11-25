#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Graph {
    int V; // 顶点数
    vector<int> *adj; // 邻接表

public:
    Graph(int V);
    void addEdge(int v, int w);
    void BFS(int s);
};

Graph::Graph(int V) {
    this->V = V;
    adj = new vector<int>[V];
}

void Graph::addEdge(int v, int w) {
    adj[v].push_back(w);
    adj[w].push_back(v);
}

void Graph::BFS(int s) {
    vector<bool> visited(V, false);
    queue<int> queue;

    visited[s] = true;
    queue.push(s);

    while (!queue.empty()) {
        s = queue.front();
        cout << s << " ";
        queue.pop();

        for (int i : adj[s]) {
            if (!visited[i]) {
                visited[i] = true;
                queue.push(i);
            }
        }
    }
}

int main() {
    Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    cout << "广度优先搜索（从顶点 2 开始）: ";
    g.BFS(2);
    system("pause");
    return 0;
}