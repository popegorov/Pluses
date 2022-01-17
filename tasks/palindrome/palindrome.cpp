#include "palindrome.h"
#include <string>

bool IsPalindrome(const std::string& str) {
    std::string str_without_spaces;
    for (size_t i = 0; i < str.size(); ++i) {
        if (str[i] != ' ') {
            str_without_spaces.push_back(str[i]);
        }
    }
    int good_size = str_without_spaces.size();
    for (size_t i = 0; i < str_without_spaces.size() / 2; ++i) {
        if (str_without_spaces[i] != str_without_spaces[str_without_spaces.size() - i - 1]) {
            return false;
        }
    }
    return true;
}
