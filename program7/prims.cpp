#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#include <utility>

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
            heap[size] = make_pair(dist, v);
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
            cout << "Decreased key of vertex: " << v << " to new distance: " << dist << endl;
        }
        // extract the minimum element (vertex with the smallest distance) from the heap
        pair<int, int> extractMin()
        {
            if (size == 0)
            {
                return make_pair(INT_MAX, -1);
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

        // get the position of a vertex in the heap
        int getPos(int v)
        {
            return pos[v];
        }

        // get the size of the heap
        int getSize()
        {
            return size;
        }

        // get the heap element at a given poistion
        pair<int, int> getHeapElement(int i)
        {
            return heap[i];
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

int primMST (int V, const vector<vector<pair<int, int> > >& adj)
{
    MinHeap minHeap(V); // initialize the MinHeap

    vector<bool> inMST(V, false); // use boolean array to track which vertices are inclueded in the MST

    int totalCost = 0; // initalize total cost of the MST to zero

    minHeap.push(0, 0); // start from the first vertex (vertex 0)

    while(!minHeap.isEmpty())
    {
        pair<int, int> minNode = minHeap.extractMin(); // extract the vertex with the smallest distance
        int u = minNode.second; // get the vertex number

        if (inMST[u]) // if the vertiex is already in the MST, skip it
        {
            continue;
        }

        inMST[u] = true; // mark the vertex as included in the MST
        totalCost += minNode.first; // add the distance to the total cost

        cout << "Included vertex: " << u << " with cost: " << minNode.first << endl;

        for (auto &neighbor : adj[u])
        {
            int v = neighbor.first;
            int weight = neighbor.second;
            
            cout << "Processing neighbor: " << v << " with weight: " << weight << endl;
            if (!inMST[v])
            {
                int currentWeight = INT_MAX;
                if (minHeap.getPos(v) < minHeap.getSize())
                {
                    currentWeight = minHeap.getHeapElement(minHeap.getPos(v)).first;
                }
                cout << "Current weight of vertex: " << v << " is " << currentWeight << endl;
                if (weight < currentWeight)
                {
                    minHeap.decreaseKey(v, weight);
                    cout << "Updated vertex: " << v << " with new weight: " << weight << endl;
                }
            }
            
        }
    }

    return totalCost; // return the total cost of the MST
}

int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        cout << "Optional to provide <start vertex> and <end vertex>" << endl;
    }
    int V; // number of vertices
    int E; // number of edges

    cin >> V >> E; // read the numbers of vertices & edges

    vector<vector<pair<int, int> > > adj(V);
    
    for (int i = 0; i < E; i++)
    {
        int u; // start vertex
        int v; // end vertex
        int l; // length of edge
        cin >> u >> v >> l;
        adj[u].emplace_back(v, l);
        adj[v].emplace_back(u, l);
    }

    // debug print to verify adjacency list
    cout << "AL:" << endl;
    for (int i = 0; i < V; i++)
    {
        cout << i << ": ";
        for (auto &neighbor : adj[i])
        {
            cout << "(" << neighbor.first << ", " << neighbor.second <<  ")";
        }
        cout << endl;
    }
    
    int totalCost = primMST(V, adj); // calculate the total cost of the MST

    cout << totalCost << endl;

    return 0;
}