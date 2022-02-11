#include "split.h"
#include <cctype>

std::vector<std::string_view> SplitText(std::string_view& str, const std::string_view& elem = "\n") {
    std::vector<std::string_view> result;
    size_t first = 0;
    while (first < str.size()) {
        const auto second = str.find(elem, first);
        if (first != second) {
            result.push_back(str.substr(first, second - first));
        }
        if (second == std::string_view::npos) {
            break;
        }
        first = second + 1;
    }
    return result;
}

std::vector<std::string_view> SplitLine(std::string_view text) {
    std::vector<std::string_view> words;

    while (!text.empty()) {
        if (!std::isalpha(text[0])) {
            text.remove_prefix(1);
            continue;
        }

        size_t word_len = 1;
        while (word_len < text.size() && std::isalpha(text[word_len])) {
            ++word_len;
        }

        words.push_back(text.substr(0, word_len));
        text.remove_prefix(word_len);
    }

    return words;
}