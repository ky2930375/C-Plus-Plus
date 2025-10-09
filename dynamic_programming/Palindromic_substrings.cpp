// Problem Statement
// Given a string s, return the number of palindromic substrings in it.
// A substring is palindromic if it reads the same backward and forward.

#include <bits/stdc++.h>
using namespace std;

int countSubstrings(string s) {
    int n = s.size();
    vector<vector<bool>> dp(n, vector<bool>(n, false));
    int count = 0;

    // Fill dp table
    for (int len = 1; len <= n; len++) {
        for (int i = 0; i + len - 1 < n; i++) {
            int j = i + len - 1;

            if (s[i] == s[j]) {
                if (len <= 2 || dp[i + 1][j - 1]) {
                    dp[i][j] = true;
                    count++;
                }
            }
        }
    }

    return count;
}

int main() {
    string s;
    cout << "Enter string: ";
    cin >> s;

    cout << "Total Palindromic Substrings: " 
         << countSubstrings(s) << endl;

    return 0;
}
