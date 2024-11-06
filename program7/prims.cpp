#include <iostream>
#include <vector>
#include <climits>

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

int primMST (int V, vector<vector<pair<int, int>>>& adj)
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

        for (int i = 0; i < adj[u].size(); i++)
        {
            pair<int, int> neighbor = adj[u][i];
            int v = neighbor.first;
            int weight = neighbor.second;

            // if the adjacent vertex is not in the MST and the weight of edge is less than the current key
            if (!inMST[v]) 
            {
                int currentWeight = INT_MAX;
                if (minHeap.getPos(v) > minHeap.getSize())
                {
                    currentWeight = minHeap.getHeapElement(minHeap.getPos(v)).first;
                }
                if (weight < currentWeight)
                {
                    // update the key (distance) of the adjacent vertex
                    minHeap.decreaseKey(v, weight);
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