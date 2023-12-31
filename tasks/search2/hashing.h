#pragma once

#include <string_view>
#include <unordered_map>
#include <unordered_set>

struct Hash {
    size_t operator()(const std::string_view& s) const;
};

struct Equal {
    bool operator()(const std::string_view& a, const std::string_view& b) const;
};

using HashSet = std::unordered_set<std::string_view, Hash, Equal>;

using HashMap = std::unordered_map<std::string_view, size_t, Hash, Equal>;
