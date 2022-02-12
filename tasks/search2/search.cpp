#include "search.h"
#include "hashing.h"
#include "split.h"
#include <cmath>

std::vector<HashMap> FillHashMap(const std::vector<std::string_view>& lines, std::vector<size_t>& line_sizes) {
    std::vector<HashMap> res(lines.size());
    for (size_t i = 0; i < lines.size(); ++i) {
        auto words = SplitLine(lines[i]);
        line_sizes[i] = words.size();
        for (const auto& word : words) {
            res[i][word]++;
        }
    }
    return res;
}

std::vector<size_t> CountLineSizes(const std::vector<std::string_view>& lines) {
    std::vector<size_t> line_sizes;
    for (const auto& elem : lines) {
        line_sizes.push_back(SplitLine(elem).size());
    }
    return line_sizes;
}

std::unordered_map<std::string_view, double> CountIDF(const std::vector<HashMap>& query_count, const HashSet& queries,
                                                      const size_t text_size) {
    std::unordered_map<std::string_view, double> idf(queries.size());
    for (const auto& query : queries) {
        size_t cur_cnt = 0;
        for (auto& hash_map : query_count) {
            if (hash_map.contains(query) && hash_map.at(query)) {
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

std::vector<std::pair<double, size_t>> CountTFIDF(const std::vector<HashMap>& query_count, const HashSet& queries,
                                                  const std::unordered_map<std::string_view, double>& idf,
                                                  const std::vector<std::string_view>& lines,
                                                  const std::vector<size_t>& line_sizes) {
    std::vector<std::pair<double, size_t>> tf_idf;
    std::unordered_map<size_t, double> tf_idf_map;
    for (size_t i = 0; i < query_count.size(); ++i) {
        for (const auto& query : queries) {
            if (query_count[i].contains(query) && query_count[i].at(query)) {
                tf_idf_map[i] += static_cast<double>(query_count[i].at(query)) / line_sizes[i];
            }
        }
    }
    for (const auto& [line, res] : tf_idf_map) {
        tf_idf.push_back({res, line});
    }
    std::sort(tf_idf.begin(), tf_idf.end(), ComparePair);
    return tf_idf;
}

std::vector<std::string_view> CutVector(const std::vector<std::pair<double, size_t>>& tf_idf, const size_t len,
                                        const std::vector<std::string_view>& lines) {
    size_t min_len = len;
    if (len > tf_idf.size()) {
        min_len = tf_idf.size();
    }
    std::vector<std::string_view> res;
    for (size_t i = 0; i < min_len; ++i) {
        if (tf_idf[i].first > 0) {
            res.push_back(lines[tf_idf[i].second]);
        } else {
            break;
        }
    }
    return res;
}

void SearchEngine::BuildIndex(std::string_view text) {
    lines_ = SplitText(text, "\n");
    line_sizes_ = CountLineSizes(lines_);

    query_count_ = FillHashMap(lines_, line_sizes_);
}

std::vector<std::string_view> SearchEngine::Search(std::string_view query, size_t results_count) const {
    auto queries = SplitLine(query);
    HashSet query_set = {queries.begin(), queries.end()};

    auto idf = CountIDF(query_count_, query_set, lines_.size());

    auto tf_idf = CountTFIDF(query_count_, query_set, idf, lines_, line_sizes_);

    return CutVector(tf_idf, results_count, lines_);
}