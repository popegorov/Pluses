#include "search.h"
#include <cmath>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

std::vector<std::string_view> StringViewSplit(std::string_view& str, const std::string_view& elem = "\n") {
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

std::vector<std::string_view> Split(std::string_view text) {
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

struct Hash {
    size_t operator()(const std::string_view& s) const {
        size_t h = 1;
        if (!s.empty()){
            h = static_cast<size_t>(tolower(s[0]) - 'a' + 1);
        }
        size_t h_prev = 0;
        for (size_t i = 0; i < s.size(); ++i) {
            size_t h_new = h;
            h = ((h_prev * 1009 + static_cast<size_t>(tolower(s[i]) - 'a' + 1)) % static_cast<size_t>(1e9 + 7));
            h_prev = h_new;
        }
        return h;
    }
};

struct Equal {
    bool operator()(const std::string_view& a, const std::string_view& b) const {
        if (a.size() != b.size()) {
            return false;
        }
        for (size_t i = 0; i < a.size(); ++i) {
            if (tolower(a[i]) != tolower(b[i])) {
                return false;
            }
        }
        return true;
    }
};

using HashSet = std::unordered_set<std::string_view, Hash, Equal>;

HashSet FillQuerySet(const std::vector<std::string_view>& queries) {
    HashSet res;
    for (const auto& query : queries) {
        res.insert(query);
    }
    return res;
}

using HashMap = std::unordered_map<std::string_view, size_t, Hash, Equal>;

std::vector<HashMap> FillHashMap(const std::vector<std::string_view>& lines, const HashSet& queries,
                                 std::vector<size_t>& line_sizes) {
    std::vector<HashMap> res(lines.size());
    for (size_t i = 0; i < lines.size(); ++i) {
        auto words = Split(lines[i]);
        line_sizes[i] = words.size();
        for (const auto& word : words) {
            if (queries.contains(word)) {
                res[i][word] += 1;
            }
        }
    }
    return res;
}

std::unordered_map<std::string_view, double> CountIDF(std::vector<HashMap>& query_count, const HashSet& queries,
                                                      const size_t text_size) {
    std::unordered_map<std::string_view, double> idf(queries.size());
    for (const auto& query : queries) {
        size_t cur_cnt = 0;
        for (auto& hash_map : query_count) {
            if (hash_map[query]) {
                cur_cnt++;
            }
        }
        idf[query] = std::log(static_cast<double>(text_size) / cur_cnt);
    }
    return idf;
}

bool ComparePair(const std::pair<double, size_t>& a, const std::pair<double, size_t>& b) {
    if (a.first != b.first) {
        return a.first > b.first;
    }
    return a.second < b.second;
}

std::vector<std::pair<double, size_t>> CountTFIDF(std::vector<HashMap>& query_count, HashSet& queries,
                                                  std::unordered_map<std::string_view, double>& idf,
                                                  std::vector<std::string_view>& lines,
                                                  std::vector<size_t>& line_sizes) {
    std::vector<std::pair<double, size_t>> tf_idf;
    std::unordered_map<size_t, double> tf_idf_map;
    for (size_t i = 0; i < query_count.size(); ++i) {
        for (const auto& query : queries) {
            if (query_count[i][query]) {
                tf_idf_map[i] += static_cast<double>(query_count[i][query]) / line_sizes[i];
            }
        }
    }
    for (const auto& [line, res] : tf_idf_map) {
        tf_idf.push_back({res, line});
    }
    std::sort(tf_idf.begin(), tf_idf.end(), ComparePair);
    return tf_idf;
}

std::vector<std::string_view> CutVector(std::vector<std::pair<double, size_t>>& tf_idf, size_t len,
                                        std::vector<std::string_view>& lines) {
    if (len > tf_idf.size()) {
        len = tf_idf.size();
    }
    std::vector<std::string_view> res;
    for (size_t i = 0; i < len; ++i) {
        if (tf_idf[i].second > 0) {
            res.push_back(lines[tf_idf[i].second]);
        } else {
            break;
        }
    }
    return res;
}

std::vector<std::string_view> Search(std::string_view text, std::string_view query, size_t results_count) {
    auto queries = Split(query);
    auto query_set = FillQuerySet(queries);

    auto lines = StringViewSplit(text, "\n");
    size_t text_size = lines.size();
    std::vector<size_t> line_sizes(text_size);

    auto query_count = FillHashMap(lines, query_set, line_sizes);

    auto idf = CountIDF(query_count, query_set, text_size);

    auto tf_idf = CountTFIDF(query_count, query_set, idf, lines, line_sizes);

    return CutVector(tf_idf, results_count, lines);
}