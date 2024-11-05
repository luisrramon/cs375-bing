#include <iostream>
#include <vector>

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

int primMST (int V, vector<vector<pair<int, int>>>& adj)
{
    return 0;
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