#include "palindrome.h"
#include <string>

bool IsPalindrome(const std::string& str) {
    std::string good_str;
    int str_size = str.size();
    for (int i = 0; i < str_size; ++i) {
        if (str[i] != ' ') {
            good_str.push_back(str[i]);
        }
    }
    int good_size = good_str.size();
    bool flag = true;
    for (int i = 0; i < (good_size / 2); ++i) {
        if (good_str[i] != good_str[good_size - i - 1]) {
            flag = false;
        }
    }
    return flag;
}
