// Luis Ramon
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

// Graph structure to represent a graph using an adjacency list
struct Graph
{
    int numVertices; // num of vertices in the graph
    vector<vector<int> > adjList; // adjacency list to store edges
    Graph(int n)
    {
        numVertices = n;
        adjList.resize(n);
    }
    void addEdge(int u, int v) // function to add an edge from vertex u to vertex v
    {
        adjList[u].push_back(v);
    }
};

int bfs(Graph& graph, int startVertex, int endVertex, int vertices)
{
    // handle edge case where startVertex and endVertex are the same
    if (startVertex == endVertex)
    {
        return 0;
    }

    vector<bool> visited(vertices, false); //vector to keep track of visited vertices
    vector<int> distance(vertices, -1); //vector to store distances from startVertex
    queue<int> q; //queue for BFS

    // initialize the start vertex
    visited[startVertex] = true;
    distance[startVertex] = 0;
    q.push(startVertex);

    while (!q.empty())
    {
        int u = q.front(); // get the next vertex from the queue
        q.pop();
        // explore all adjacent vertices of u
        for (size_t i = 0; i < graph.adjList[u].size(); i++)
        {
            int v = graph.adjList[u][i]; // get the adjacent vertex
            if (!visited[v])
            {
                visited[v] = true; // mark the vertex as visited
                distance[v] = distance[u] + 1; // update the distance of 
                q.push(v); // add the vertex to the queue

                // if we have reached the end vertex, return the distance
                if (v == endVertex)
                {
                    return distance[v];
                }
            }
        }
    }
    return -1; // return -1 if there is no path between startVertex to endVertex
}



int main (int argc, char* argv[])
{
    if (argc < 3) // check if the correct number of CLI arguments are provided
    {
        cout << "Usage: " << argv[0] << " <start vertex> <end vertex>" << endl;
        return 1;
    }
     // convert cli arguments to integers
    int startVertex = atoi(argv[1]);
    int endVertex = atoi(argv[2]);

    int numVertices;
    int numEdges;

    // read the number of vertices and edges
    cin >> numVertices >> numEdges;

    
    // create a graph with numVertices
    Graph graph(numVertices);

    // read the edges and add them to the graph
    for (int i = 0; i < numEdges; i++)
    {
        int u, v;
        cin >> u >> v;
        graph.addEdge(u, v);
    }

    // perform BFS to find the shortest path
    int distance = bfs(graph, startVertex, endVertex, numVertices);

    // output the result
    if (distance != -1)
    {
        cout << "Shortest distance is: " << distance << endl;
    }
    else
    {
        cout << "not connected" << endl;
    }

    return 0;
}
