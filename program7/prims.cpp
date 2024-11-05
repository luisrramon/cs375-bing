#include <iostream>
#include <vector>

using namespace std;
int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        cout << "Optional to provide <start vertex> and <end vertex>" << endl;
    }
    int V; // number of vertices
    int E; // number of edges

    cin >> V >> E; // read the numbers of vertices & edges

    vector<vector<pair<int, int>>> adj(V);
    for (int i = 0; i < E; i++)
    {
        int u; // start vertex
        int v; // end vertex
        int l; // length of edge
        cin >> u >> v >> l;
        adj[u].emplace_back(v, l);
    }
    
    return 0;
}