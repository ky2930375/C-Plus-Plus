/**
 * @file
 * @brief contains the definition of the function ::is_regex_match
 * @details
 * The function ::is_regex_match checks if a given input string matches a pattern
 * that can contain:
 *  - '.' which matches any single character
 *  - '*' which matches zero or more of the preceding character
 *
 * This is implemented using dynamic programming with O(n*m) time and memory complexity,
 * where n and m are the lengths of the input string and pattern respectively.
 *
 * Example:
 *  - is_regex_match("aa", "a*") -> true
 *  - is_regex_match("mississippi", "mis*is*p*.") -> false
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
 * @brief Checks if the input string matches the given pattern
 * @details
 * Uses dynamic programming to determine if a pattern (that may include '.' and '*')
 * matches an entire string.
 *
 * @param text input string
 * @param pattern regex pattern string
 * @return true if the text matches the pattern, false otherwise
 */
bool is_regex_match(const std::string& text, const std::string& pattern) {
    const size_t n = text.size();
    const size_t m = pattern.size();

    std::vector<std::vector<bool>> dp(n + 1, std::vector<bool>(m + 1, false));
    dp[0][0] = true;

    // Handle patterns like a*, a*b*, etc. that can match empty string
    for (size_t j = 2; j <= m; ++j) {
        if (pattern[j - 1] == '*') {
            dp[0][j] = dp[0][j - 2];
        }
    }

    for (size_t i = 1; i <= n; ++i) {
        for (size_t j = 1; j <= m; ++j) {
            if (pattern[j - 1] == '.' || pattern[j - 1] == text[i - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else if (pattern[j - 1] == '*') {
                dp[i][j] = dp[i][j - 2]; // zero occurrences of prev char
                if (pattern[j - 2] == '.' || pattern[j - 2] == text[i - 1]) {
                    dp[i][j] = dp[i][j] || dp[i - 1][j]; // one or more occurrences
                }
            }
        }
    }

    return dp[n][m];
}

/**
 * @brief Represents a single test case for ::is_regex_match
 */
struct TestCase {
    const std::string text;
    const std::string pattern;
    const bool expected;

    TestCase(std::string t, std::string p, bool e)
        : text(std::move(t)), pattern(std::move(p)), expected(e) {}
};

/**
 * @return Example test cases for ::is_regex_match
 */
std::vector<TestCase> get_test_cases() {
    return {
        TestCase("", "", true),
        TestCase("a", "a", true),
        TestCase("aa", "a", false),
        TestCase("aa", "a*", true),
        TestCase("ab", ".*", true),
        TestCase("mississippi", "mis*is*p*.", false),
        TestCase("mississippi", "mis*is*ip*.", true),
        TestCase("ab", ".*c", false),
        TestCase("aaa", "a*a", true),
        TestCase("aaa", "ab*a*c*a", true),
        TestCase("abcd", "d*", false),
        TestCase("aaa", "aaaa", false),
        TestCase("", "c*", true)
    };
}

/**
 * @brief Tests ::is_regex_match on all test cases
 * @param test_cases List of test cases
 * @tparam TestCases container type holding test cases
 */
template <typename TestCases>
static void test_is_regex_match(const TestCases& test_cases) {
    for (const auto& tc : test_cases) {
        assert(is_regex_match(tc.text, tc.pattern) == tc.expected);
    }
}

/**
 * @brief Runs all tests for ::is_regex_match
 */
static void tests() {
    const auto cases = get_test_cases();
    assert(!cases.empty());
    test_is_regex_match(cases);
    std::cout << "All tests have successfully passed!\n";
}

/**
 * @brief Main function
 * @returns 0 on success
 */
int main() {
    tests();
    return 0;
}
