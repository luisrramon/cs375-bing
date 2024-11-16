// Luis Ramon
#include <iostream>
#include <vector>
#include <string>

using namespace std;

// function to find the longest common subsequence of two strings
string longestCommonSubsequence(const string& s1, const string& s2)
{
    int m = s1.size(); // length of s1
    int n = s2.size(); // length of s2
    vector<vector<int>> dp(m +1, vector<int>(n + 1, 0)); // DP table to store lengths of LCS

    // fill the DP table
    for (int i = 1; i <= m; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            if (s1[i - 1] == s2[j - 1]) // characters match
            {
                dp[i][j] = dp[i - 1][j - 1] + 1; // increment the length of LCS
            }
            else // character don't match
            {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]); // take the maximum of ignoring one character from either string
            }
        }
    }

    string lcs; // store the LCS

    int i = m;
    int j = n;

    // trace back through the DP table to find the LCS
    while (i > 0 && j > 0)
    {
        if (s1[i - 1] == s2[j - 1]) // characters match
        {
            lcs = s1[i - 1] + lcs; // add character to LCS
            --i;
            --j;
        }
        else if (dp[i - 1][j] > dp[i][j - 1]) // move up in the DP table
        {
            --i;
        }
        else // move left in the DP table
        {
            --j;
        }
    }

    return lcs; // return the LCS
}

int main(int argc, char *argv[])
{    
    string s1;
    string s2;

    // read input strings
    cin >> s1 >> s2;

    // find the LCS of the input strings
    string lcs = longestCommonSubsequence(s1, s2);

    // output the LCS and its length
    cout << "LCS: " << lcs << endl;
    cout << "Length: " << lcs.size() << endl;

    return 0; 
}