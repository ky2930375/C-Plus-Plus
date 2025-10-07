/**
 * @file
 * @brief contains the definition of the function ::is_wildcard_match
 * @details
 * The function ::is_wildcard_match determines whether a given text matches
 * a pattern that may include wildcard characters:
 *  - '?' matches any single character
 *  - '*' matches any sequence of characters (including empty)
 *
 * The algorithm uses dynamic programming with O(n*m) time and space complexity,
 * where n = text length, m = pattern length.
 *
 * Example:
 *  - is_wildcard_match("aa", "a") -> false
 *  - is_wildcard_match("aa", "*") -> true
 *  - is_wildcard_match("cb", "?a") -> false
 *
 * This implementation includes test cases that verify correctness,
 * symmetry, and edge cases.
 *
 * @author
 *  [Khushi Yadav](https://github.com/khushiyadav29)
 */

#include <cassert>   /// for assert
#include <iostream>  /// for std::cout
#include <string>    /// for std::string
#include <vector>    /// for std::vector
#include <utility>   /// for std::move

/**
 * @brief Checks if the given text matches the wildcard pattern.
 * @details
 * The function supports:
 *  - '?' matching exactly one arbitrary character.
 *  - '*' matching zero or more arbitrary characters.
 *
 * Dynamic programming table `dp[i][j]` means whether the first i characters
 * of the text match the first j characters of the pattern.
 *
 * @param text input string
 * @param pattern pattern string (with '?' or '*')
 * @return true if text matches pattern, false otherwise
 */
bool is_wildcard_match(const std::string& text, const std::string& pattern) {
    const size_t n = text.size();
    const size_t m = pattern.size();

    std::vector<std::vector<bool>> dp(n + 1, std::vector<bool>(m + 1, false));
    dp[0][0] = true;  // empty text matches empty pattern

    // Handle patterns starting with '*' which can match empty string
    for (size_t j = 1; j <= m; ++j) {
        if (pattern[j - 1] == '*')
            dp[0][j] = dp[0][j - 1];
    }

    for (size_t i = 1; i <= n; ++i) {
        for (size_t j = 1; j <= m; ++j) {
            if (pattern[j - 1] == '?' || pattern[j - 1] == text[i - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else if (pattern[j - 1] == '*') {
                // '*' matches zero characters (dp[i][j-1])
                // or one/more characters (dp[i-1][j])
                dp[i][j] = dp[i][j - 1] || dp[i - 1][j];
            }
        }
    }

    return dp[n][m];
}

/**
 * @brief Represents a single test case for ::is_wildcard_match
 */
struct TestCase {
    const std::string text;
    const std::string pattern;
    const bool expected;

    TestCase(std::string t, std::string p, bool e)
        : text(std::move(t)), pattern(std::move(p)), expected(e) {}
};

/**
 * @return Example test cases for ::is_wildcard_match
 */
std::vector<TestCase> get_test_cases() {
    return {
        TestCase("", "", true),
        TestCase("a", "a", true),
        TestCase("aa", "a", false),
        TestCase("aa", "*", true),
        TestCase("cb", "?a", false),
        TestCase("adceb", "*a*b", true),
        TestCase("acdcb", "a*c?b", false),
        TestCase("", "*", true),
        TestCase("abc", "???", true),
        TestCase("abc", "??", false),
        TestCase("abc", "a*", true),
        TestCase("abcde", "a*c?e", true),
        TestCase("abc", "a*d", false)
    };
}

/**
 * @brief Tests ::is_wildcard_match using the provided test cases
 * @param test_cases list of test cases
 * @tparam TestCases container type holding test cases
 */
template <typename TestCases>
static void test_is_wildcard_match(const TestCases& test_cases) {
    for (const auto& tc : test_cases) {
        assert(is_wildcard_match(tc.text, tc.pattern) == tc.expected);
    }
}

/**
 * @brief Runs all tests for ::is_wildcard_match
 */
static void tests() {
    const auto cases = get_test_cases();
    assert(!cases.empty());
    test_is_wildcard_match(cases);
    std::cout << "All tests have successfully passed!\n";
}

/**
 * @brief Main function
 * @returns 0 on successful execution
 */
int main() {
    tests();
    return 0;
}
