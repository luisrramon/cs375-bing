// Luis Ramon
#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

// MinHeap class to implement a priority queue with decrease key functionality
class MinHeap
{
    public:
        // constructor to initialize the heap with a given capacity
        MinHeap (int capacity) : size(0)
        {
            heap.resize(capacity);
            pos.resize(capacity);
        }
        // push a new vertex with its distance into the heap
        void push(int v, int dist)
        {
            heap[size] = {dist, v};
            pos[v] = size;
            size++;
            decreaseKey(v, dist);
        }
        // decrease the key (distance) of a given vertex
        void decreaseKey(int v, int dist)
        {
            int i = pos[v];
            heap[i].first = dist;
            while(i && heap[i].first < heap[(i - 1) / 2].first)
            {
                swap(heap[i], heap[(i - 1) / 2]);
                pos[heap[i].second] = i;
                pos[heap[(i - 1) / 2].second] = (i - 1) / 2;
                i = (i - 1) / 2;
            }
        }
        // extract the minimum element (vertex with the smallest distance) from the heap
        pair<int, int> extractMin()
        {
            if (size == 0)
            {
                return {INT_MAX, -1};
            }
            if (size == 1)
            {
                size--;
                return heap[0];
            }
            pair<int, int> root = heap[0];
            heap[0] = heap[size - 1];
            pos[heap[0].second] = 0;
            size--;
            minHeapify(0);
            return root;
        }
        // check if the heap is empty
        bool isEmpty()
        {
            return size == 0;
        }
    private:
        vector<pair<int, int> > heap; // vector to store the heap elements
        vector<int> pos; // vector to store the positions of the vertices in the heap
        int size; // current size of the heap

        // maintain the min-heap property
        void minHeapify(int idx)
        {
            int smallest = idx;
            int left = 2 * idx + 1;
            int right = 2 * idx + 2;

            if (left < size && heap[left].first < heap[smallest].first)
            {
                smallest = left;
            }
            if (right < size && heap[right].first < heap[smallest].first)
            {
                smallest = right;
            }
            if (smallest != idx)
            {
                swap(heap[idx], heap[smallest]);
                pos[heap[idx].second] = idx;
                pos[heap[smallest].second] = smallest;
                minHeapify(smallest);
            }
        }
};

void dijkstra(int startVertex, int endVertex, int V, vector<vector<pair<int, int>>> &adj)
{
    vector<int> dist(V, INT_MAX); // vector to store the shortest distance from startVertex to each vertex
    vector<int> pred(V, -1); // vector to store the predecessor of each
    MinHeap minHeap(V); // create a MinHeap with capacity V
    
    dist[startVertex] = 0; // distance to start vertex is 0
    minHeap.push(startVertex, 0); // push the start vertex into the heap

    while (!minHeap.isEmpty())
    {
        int u = minHeap.extractMin().second; // extract the vertex with the smallest distance

        // iterate through all the adjacent vertices of u
        for (auto& neighbor : adj[u])
        {
            int v = neighbor.first;
            int weight = neighbor.second;
            
            // if there is a shorter path to v through u
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
            {
                dist[v] = dist[u] + weight;
                pred[v] = u;
                minHeap.push(v, dist[v]); // push the updated distance of v into the heap
            }
        }
    }
    
    // if the end vertex is not reachable
    if (dist[endVertex] == INT_MAX) 
    {
        cout << "not connected" << endl;
    } 
    else 
    {
        // print the shortest disntance and path from startVertex to endVertex
        cout << "Distance: " << dist[endVertex] << endl;
        vector<int> path;
        for (int v = endVertex; v != -1; v = pred[v])
            path.push_back(v);
        reverse(path.begin(), path.end());
        cout << "Path: ";
        for (int v : path)
            cout << v << " ";
        cout << endl;
    }
}

int main(int argc, char* argv[])
{
    // check if the correct number of arguments is provided
    if (argc < 3)
    {
        cout << "Must include <start vertex> <end vertex>" << endl;
        return -1;
    }

    int startVertex = atoi(argv[1]); // get the start vertex from the command line
    int endVertex = atoi(argv[2]); // get the end vertex from the command line

    int V, E;

    cin >> V >> E; // read the number of vertices and edges

    vector<vector<pair<int, int>>> adj(V); // adjacency list to store the graph
    for (int i = 0; i < E; i++)
    {
        int u, v, w;
        cin >> u >> v >> w; // read each edge (start vertex, end vertex, weight)
        adj[u].emplace_back(make_pair(v, w)); // add the edge to the adjacency list
    }
    dijkstra(startVertex, endVertex, V, adj);

    return 0;
}
