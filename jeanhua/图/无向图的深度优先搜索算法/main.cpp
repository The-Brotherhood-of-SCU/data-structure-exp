#include <iostream>
#include <vector>
using namespace std;

class Graph {
    int V; // ������
    vector<int> *adj; // �ڽӱ�
    void DFSUtil(int v, vector<bool> &visited); // ����DFS�ĸ�������

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
    // ����ͼ����˫���
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
    cout << "��������������Ӷ��� 2 ��ʼ��: ";
    g.DFS(2);
    system("pause");
    return 0;
}