#include <iostream>
#include <vector>
#include <climits>

using namespace std;

// MinHeap class to implement a priority queue with decrease key functionality
class MinHeap
{
    vector<pair<int, int>> heap; // vector to store the heap elements
    vector<int> pos; // vector to store the positions of the vertices in the heap
    int size; // current size of the heap

    int parent(int i)
    {
        return (i - 1) / 2;
    }

    int leftChild(int i)
    {
        return 2 * i + 1;
    }

    int rightChild(int i)
    {
        return 2 * i + 2;
    }

    void swap(int i, int j)
    {
        pos[heap[i].second] = j;
        pos[heap[j].second] = i;
        std::swap(heap[i], heap[j]);
    }
    // maintain the min-heap property
    void minHeapify(int i)
    {
        int l = leftChild(i);
        int r = rightChild(i);
        int smallest = i;

        if (l < size && heap[l].first < heap[smallest].first)
        {
            smallest = l;
        }
        if (r < size && heap[r].first < heap[smallest].first)
        {
            smallest = r;
        }
        if (smallest != i)
        {
            swap(i, smallest);
            minHeapify(smallest);
        }
    }

    public:
        // constructor to initialize the heap with a given capacity
        MinHeap (int capacity) : size(0)
        {
            heap.resize(capacity);
            pos.resize(capacity);
        }
        // push a new vertex with its distance into the heap
        void insert(int v, int dist)
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
            while(i && heap[i].first < heap[parent(i)].first)
            {
                swap(i, parent(i));
                i = parent(i);
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
        bool isEmpty()
        {
            return size == 0;
        }        
};

int primMST (vector<vector<pair<int, int>>> &adj, int V)
{
    vector<int> key(V, INT_MAX);
    vector<bool> inMST(V, false); // use boolean array to track which vertices are inclueded in the MST
    MinHeap minHeap(V); // initialize the MinHeap
    int totalCost = 0; // initalize total cost of the MST to zero

    key[0] = 0;
    minHeap.insert(0, 0); // start from the first vertex (vertex 0)
    

    while(!minHeap.isEmpty())
    {
        int u = minHeap.extractMin().second;
        if (inMST[u])
        {
            continue;
        }
        inMST[u] = true; // mark the vertex as included in the MST
        totalCost += key[u]; // add the distance to the total cost
        
        for (auto& edge : adj[u])
        {
            int v = edge.first;
            int weight = edge.second;
            if (!inMST[v] && key[v] > weight)
            {
                key[v] = weight;
                minHeap.decreaseKey(v, key[v]);
            }
        }
    }

    return totalCost; // return the total cost of the MST
}

int main(int argc, char *argv[])
{
    int V, E; // number of vertices and edges

    cin >> V >> E; // read the numbers of vertices & edges

    vector<vector<pair<int, int>>> adj(V);

    for (int i = 0; i < E; i++)
    {
        int u, v, w; // start vertex, end vertex, length of edge
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }
    
    int totalCost = primMST(adj, V); // calculate the total cost of the MST
    cout << totalCost << endl;

    return 0;
}