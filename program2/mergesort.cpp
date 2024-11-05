#include <iostream>
#include <vector>
using namespace std;

void Merge(vector<int>& numbers, int low, int middle, int high)
{
    int left_size = middle - low + 1; //size of left subarray
    int right_size = high - middle; // size of right subarray
    
    // create temp vectors for left & right subarrays
    vector<int> L(left_size);
    vector<int> R(right_size);
    
    // copy data to temp vectors
    for (int i = 0; i < left_size; i++)
    {
        L[i] = numbers[low + i];
    }

    for (int j = 0; j < right_size; j++)
    {
        R[j] = numbers[middle + 1 + j];
    }

    int i = 0; // starting index of left subarray
    int j = 0; // starting index of right subarray
    int k = low; // starting index of merged array

    // merge temp vectors back into numbers vector
    while (i < left_size && j < right_size)
    {
        if (L[i] <= R[j])
        {
            numbers[k] = L[i];
            i++;
        }
        else
        {
            numbers[k] = R[j];
            j++;
        }
        k++;
    }

    // copy remaining elements of L vector
    while (i < left_size)
    {
       numbers[k] = L[i];
       i++;
       k++;
    }

    // copy remaining elements of R vector
    while (j < right_size)
    {
        numbers[k] = R[j];
        j++;
        k++;
    }
}

void MergeSort(vector<int>& numbers, int low, int high)
{
    if (low < high)
    {
        int middle = (low + high) / 2;
        MergeSort(numbers, low, middle); // sort first half of vector
        MergeSort(numbers, middle + 1, high); // sort second half of vector
        Merge(numbers, low, middle, high); // merge two sorted halves
    }
    return;
}

int main(int argc, char *argv[])
{
    int start = 0; // starting index for output
    int end = -1; // ending index for output
    int amount;

    cin >> amount;
    vector<int> numbers(amount);
    
    // read elements into vector
    for (int i = 0; i < amount; i++)
    {
        cin >> numbers[i];
    }

    MergeSort(numbers, 0, numbers.size() - 1);
    
    cout << amount << endl;

    // check if command-line arguments are provided
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
        cout << numbers[i] << endl;
    }
    
    return 0;
}