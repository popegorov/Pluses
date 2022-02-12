#include "hashing.h"
#include <cctype>

size_t Hash::operator()(const std::string_view& s) const {
    size_t h = 1;
    if (!s.empty()) {
        h = static_cast<size_t>(std::tolower(s[0]) - 'a' + 1);
    }
    size_t h_prev = 0;
    for (size_t i = 0; i < s.size(); ++i) {
        size_t h_new = h;
        h = ((h_prev * 1009 + static_cast<size_t>(std::tolower(s[i]) - 'a' + 1)) % static_cast<size_t>(1e9 + 7));
        h_prev = h_new;
    }
    return h;
}

bool Equal::operator()(const std::string_view& a, const std::string_view& b) const {
    if (a.size() != b.size()) {
        return false;
    }
    for (size_t i = 0; i < a.size(); ++i) {
        if (std::tolower(a[i]) != std::tolower(b[i])) {
            return false;
        }
    }
    return true;
}
