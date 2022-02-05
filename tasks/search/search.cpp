#include "search.h"
#include <cmath>
#include <set>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

std::vector<std::string_view> StringViewSplit(std::string_view& str, const std::string_view& elem = " ") {
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

std::unordered_map<std::string_view, double> CountIDF(
    std::vector<std::string_view>& lines, std::unordered_map<std::string_view, std::set<size_t>>& query_count,
    const std::set<std::string_view>& queries) {
    for (size_t i = 0; i < lines.size(); ++i) {
        auto words = Split(lines[i]);
        for (const auto& word : words) {
            for (const auto& query : queries) {
                if (word == query) {
                    query_count[query].insert(i);
                    break;
                }
            }
        }
    }
    std::unordered_map<std::string_view, double> idf(query_count.size());
    for (const auto& [query, lines_set] : query_count) {
        double res = static_cast<double>(lines.size()) / static_cast<double>(lines_set.size());
        idf[query] = log(res);
    }
    return idf;
}

std::map<std::pair<std::string_view, size_t>, double> CountTF(
    std::vector<std::string_view>& lines, std::unordered_map<std::string_view, std::set<size_t>>& query_count,
    const std::set<std::string_view>& queries) {
    std::map<std::pair<std::string_view, size_t>, double> tf;
    for (const auto& query : queries) {
        for (const auto& line : query_count[query]) {
            auto words = Split(lines[line]);
            size_t cur_cnt = 0;
            for (const auto& word : words) {
                if (word == query) {
                    cur_cnt++;
                }
            }
            tf[{query, line}] = static_cast<double>(cur_cnt) / words.size();
        }
    }
    return tf;
}

bool ComparePair(const std::pair<double, size_t>& a, const std::pair<double, size_t>& b) {
    if (a.first != b.first) {
        return a.first > b.first;
    }
    return a.second < b.second;
}

std::vector<std::pair<double, size_t>> CountTFIDF(std::map<std::pair<std::string_view, size_t>, double>& tf,
                                                  std::unordered_map<std::string_view, double>& idf) {
    std::vector<std::pair<double, size_t>> tf_idf;
    std::unordered_map<size_t, double> tf_idf_map;
    for (const auto& [line, value] : tf) {
        double res = idf[line.first] * value;
        tf_idf_map[line.second] += res;
    }
    for (const auto& [line, res] : tf_idf_map) {
        tf_idf.push_back({res, line});
    }
    std::sort(tf_idf.begin(), tf_idf.end(), ComparePair);
    return tf_idf;
}

std::vector<std::string_view> CutVector(std::vector<std::pair<double, size_t>>& tf_idf, size_t len,
                                        std::vector<std::string_view>& lines) {
    std::vector<std::string_view> res;
    for (size_t i = 0; i < len; ++i) {
        if (tf_idf[i].second > 0) {
            res.push_back(lines[tf_idf[i].second]);
        }
    }
    return res;
}

std::vector<std::string_view> Search(std::string_view text, std::string_view query, size_t results_count) {
    auto queries = Split(query);
    std::set<std::string_view> set_queries(queries.begin(), queries.end());
    std::unordered_map<std::string_view, std::set<size_t>> query_count;

    auto lines = StringViewSplit(text, "\n");

    auto idf = CountIDF(lines, query_count, set_queries);

    auto tf = CountTF(lines, query_count, set_queries);

    auto tf_idf = CountTFIDF(tf, idf);

    return CutVector(tf_idf, results_count, lines);
}