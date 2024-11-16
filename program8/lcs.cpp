// Luis Ramon
#include <iostream>
#include <vector>
#include <string>

using namespace std;

string longestCommonSubsequence(const string& s1, const string& s2)
{
    int m = s1.size(); // length of s1
    int n = s2.size(); // length of s2
    vector<vector<int>> dp(m +1, vector<int>(n + 1, 0));

    for (int i = 1; i <= m; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            if (s1[i - 1] == s2[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }
            else
            {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    string lcs;

    int i = m;
    int j = n;

    while (i > 0 && j > 0)
    {
        if (s1[i - 1] == s2[j - 1])
        {
            lcs = s1[i - 1] + lcs;
            --i;
            --j;
        }
        else if (dp[i - 1][j] > dp[i][j - 1])
        {
            --i;
        }
        else
        {
            --j;
        }
    }

    return lcs;
}

int main(int argc, char *argv[])
{    
    string s1;
    string s2;

    cin >> s1 >> s2;

    string lcs = longestCommonSubsequence(s1, s2);

    cout << "LCS: " << lcs << endl;
    cout << "Length: " << lcs.size() << endl;

    return 0;
}