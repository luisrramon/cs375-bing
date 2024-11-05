// Luis Ramon
/*
1 million
    Heap sort - 0m0.937s
    Merge sort - 0m0.941s

10 million
    Heap sort - 0m11.360s
    Merge sort - 0m9.774s

Heap sort is faster when running 1M, however merge is faster when running 10M.
Based on the run times, it is roughly a constant factor to some degree

Ran on remote machine via ssh
*/
#include <iostream>
#include <vector>
using namespace std;


void heapify(vector<int>& heap_array, int index, int heap_size)
{
    int largest = index; // initialize largest as root
    int left = (2 * index) + 1; // left child index
    int right = (2 * index) + 2; // right child index

    // check if left child exists and is greater than root
    if (left < heap_size && heap_array[left] > heap_array[largest])
    {
        largest = left;
    }

    // check if right child exists and is greated than largest
    if (right < heap_size && heap_array[right] > heap_array[largest])
    {
        largest = right;
    }

    // if largest is not root, swap and continue heapifying 
    if (largest !=  index)
    {
        swap(heap_array[index], heap_array[largest]);
        heapify(heap_array, largest, heap_size);
    }
}

void build_heap(vector<int>& heap_array, int n)
{
    int heap_size = n;
    for (int i = n/2; i >=0; i--)
    {
        heapify(heap_array, i, heap_size); // heapify each node starting from the last non-leaf node
    }
}

void heap_sort(vector<int>& heap_array)
{
    int n = heap_array.size();

    build_heap(heap_array, n);

    // iteratively extract elements from the heap
    for (int i = n - 1; i > 0; i--)
    {
        swap(heap_array[0], heap_array[i]); // move the current root to the end
        heapify(heap_array, 0, i); // call heapify on the reduced heap
    }
}


int main(int argc, char *argv[])
{
    int start = 0; // starting index for output
    int end = -1; // ending index for output
    int amount;

    cin >> amount;
    vector<int> heap_array(amount);

    // read elements in vector
    for (int i = 0; i < amount; i++)
    {
        cin >> heap_array[i];
    }

    heap_sort(heap_array);

    cout << amount << endl;

    // check if commandline arguments are provided
    if (argc > 1)
    {
        start = atoi(argv[1]);
        
        if (argc > 2)
        {
            end = atoi(argv[2]);
        }
        else
        {
            end = amount;
        }
    }
    else
    {
        end = amount;
    }

    // output sorted elements within specific range
    for (int i = start; i < end && i < amount; i++)
    {
        cout << heap_array[i] << endl;
    }

    return 0;
}
