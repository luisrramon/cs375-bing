// Luis Ramon
#include <iostream>
#include <vector>
using namespace std;

int binary_search(const vector<int>&sortedNums, int query)
{
    // Create index pointers for the boundaries of search
    int left_pointer = 0;
    int right_pointer = sortedNums.size() - 1;

    // Continue process of comparing query and splitting search in halves
    while (left_pointer <= right_pointer){
        int middle = left_pointer + (right_pointer - left_pointer) / 2;

        // Check if the query is at the middle index
        if (sortedNums[middle] == query) {
        return middle;
        }

        // Search in the right half if query is greater than value at middle index
        if (sortedNums[middle] < query) {
        left_pointer = middle + 1;
        }

        // Search in the left half if query is less than value at middle index
        if (sortedNums[middle] > query) {
        right_pointer = middle - 1;
        }
    }
    return -1; // indicates that no query found
}

int main()
{
    int nums; // Number of pre-sorted integers
    cin >> nums;
    vector<int> sortedNums(nums); // Vector to store pre-sorted integers

    // Read the sorted integers into vector
    for (int i = 0; i < nums; i++) {
        cin >> sortedNums[i];
    }
    
    int queries; // Number of query integers
    cin >> queries; 
    vector<int> queryList(queries); // Vector to store query integers

    // Read the query integers into the vector
    for (int i = 0; i < queries; i++) {
        cin >> queryList[i];
    }

    // Process each query into binary search
    for (int i = 0; i < queries; i++) {
        int index = binary_search(sortedNums, queryList[i]);
        // Prints index if query found
        if (index != -1) {
        cout << index << endl;
        }
        // Otherwise
        else {
        cout << "Not found" << endl;
        }
    }

    return 0;
}