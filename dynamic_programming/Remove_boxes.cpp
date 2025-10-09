//Problem Statement
//You are given an array of boxes, where boxes[i] represents the color of the i-th box.
//You can repeatedly remove consecutive boxes of the same color.
//If you remove k consecutive boxes of the same color, you gain k * k points.

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int dp[100][100][100]; // DP cache

    int solve(vector<int>& boxes, int l, int r, int k) {
        if (l > r) return 0;
        if (dp[l][r][k] != -1) return dp[l][r][k];

        // Merge same-color boxes at the end
        while (r > l && boxes[r] == boxes[r - 1]) {
            r--;
            k++;
        }

        // Option 1: remove the last group directly
        int res = solve(boxes, l, r - 1, 0) + (k + 1) * (k + 1);

        // Option 2: merge non-adjacent same-colored boxes
        for (int i = l; i < r; i++) {
            if (boxes[i] == boxes[r]) {
                res = max(res, solve(boxes, l, i, k + 1) + solve(boxes, i + 1, r - 1, 0));
            }
        }

        return dp[l][r][k] = res;
    }

    int removeBoxes(vector<int>& boxes) {
        memset(dp, -1, sizeof(dp));
        return solve(boxes, 0, boxes.size() - 1, 0);
    }
};

int main() {
    vector<int> boxes = {1, 3, 2, 2, 2, 3, 4, 3, 1};
    Solution sol;
    cout << "Maximum points: " << sol.removeBoxes(boxes) << endl;
    return 0;
}
