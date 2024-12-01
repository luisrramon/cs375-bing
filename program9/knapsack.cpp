// Luis Ramon
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to hold the result of the knapsack problem
struct KnapsackResult
{
    int totalValue; // Total value of the selected items
    vector<int> selectedItems; // Indices of the selected items
};

class Knapsack
{
    public:
        // Initalize the knapsack problem
        Knapsack(int numItems, int maxWeight, const vector<pair<int, int>>& items)
        {
            this->numItems = numItems; // Number of items
            this->maxWeight = maxWeight; // Maximum weight capacity of the knapsack
            this->items = items; // List of items (weight, value)
        }

        // Function to find the maximum value to store in the knapsack 
        KnapsackResult findMaxValue()
        {
            // DP table to store maximum value at each item and weight
            vector<vector<int>> dp(numItems + 1, vector<int>(maxWeight + 1, 0));
            // Table to keep track of items included in the knapsack
            vector<vector<bool>> keep(numItems + 1, vector<bool>(maxWeight + 1, false));

            // Iterate through each item
            for (int i = 1; i <= numItems; i++)
            {
                // Iterate through each weight capacity
                for (int w = 1; w <= maxWeight; w++)
                {
                    // Check if the current item can be included
                    if (items[i - 1].first <= w)
                    {
                        // Include the item if it gives a better value
                        if (items[i - 1].second + dp[i - 1][w - items[i - 1].first] > dp[i - 1][w])
                        {
                            dp[i][w] = items[i - 1].second + dp[i - 1][w - items[i - 1].first];
                            keep[i][w] = true; // Mark item as included
                        }
                        else
                        {
                            dp[i][w] = dp[i - 1][w]; // Exclude the item
                        }
                    }
                    else
                    {
                        dp[i][w] = dp[i - 1][w]; // Exclude the item if it can't be included
                    }
                }
            }

            // Backtrack to find the items to be included in the knapsack
            int totalValue = dp[numItems][maxWeight];
            vector<int> selectedItems;
            int w = maxWeight;

            for (int i = numItems; i > 0; i--)
            {
                if (keep[i][w])
                {
                    selectedItems.push_back(i);
                    w -= items[i - 1].first;
                }
            }
            reverse(selectedItems.begin(), selectedItems.end()); // Reverse to maintain the order of items
            return {totalValue, selectedItems}; // Return the result
        }
    
    private:
        int numItems; // Number of items
        int maxWeight; // Maximum weight capacity of the knapsack
        vector<pair<int, int>> items; // List of items (weight, value)
    
};

// Create a Knapsack object and find the maximum value to store in the knapsack
KnapsackResult knapsack(int numItems, int maxWeight, const vector<pair<int, int>>& items)
{
    Knapsack knapsack(numItems, maxWeight, items);
    return knapsack.findMaxValue();
}

int main(int argc, char *argv[])
{
    int numItems;
    int maxWeight;
    vector<pair<int, int>> items;

    // Read the number of items and maximum weight
    cin >> numItems >> maxWeight;

    // Read the items (weight, value)
    for (int i = 0; i < numItems; i++)
    {
        int weight;
        int value;
        cin >> weight >> value;
        items.emplace_back(weight, value);
    }

    KnapsackResult result = knapsack(numItems, maxWeight, items);

    // Output the result
    cout << "Total value: " << result.totalValue << endl;
    for (int i = 0; i < result.selectedItems.size(); i++)
    {
        cout << "Item " << result.selectedItems[i] << endl;
    }

    return 0;
}