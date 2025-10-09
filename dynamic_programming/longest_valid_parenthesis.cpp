#include <bits/stdc++.h>
using namespace std;

int longestValidParentheses(string s) {
    int n = s.size();
    vector<int> dp(n, 0);
    int maxLen = 0;

    for (int i = 1; i < n; i++) {
        if (s[i] == ')') {
            // Case 1: "..."
            if (s[i - 1] == '(') {
                dp[i] = (i >= 2 ? dp[i - 2] : 0) + 2;
            }
            // Case 2: "....))"
            else if (i - dp[i - 1] - 1 >= 0 && s[i - dp[i - 1] - 1] == '(') {
                dp[i] = dp[i - 1] + 2;
                if (i - dp[i - 1] - 2 >= 0)
                    dp[i] += dp[i - dp[i - 1] - 2];
            }
            maxLen = max(maxLen, dp[i]);
        }
    }

    return maxLen;
}

int main() {
    string s;
    cout << "Enter parentheses string: ";
    cin >> s;

    cout << "Longest Valid Parentheses Length: "
         << longestValidParentheses(s) << endl;

    return 0;
}
