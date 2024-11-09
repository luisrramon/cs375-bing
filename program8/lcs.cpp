#include <iostream>
#include <vector>

using namespace std;

int longestCommonSubstring(string s1, string s2, string substring)
{
    return 0;
}

int main(int argc, char *argv[])
{    
    string s1;
    string s2;
    string substring;

    cin >> s1 >> s2;

    int length = longestCommonSubstring(s1, s2, substring);

    cout << length << endl;
    cout << substring << endl;

    return 0;
}