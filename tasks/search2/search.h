#pragma once

#include "hashing.h"

class SearchEngine {
public:
    void BuildIndex(std::string_view text);
    std::vector<std::string_view> Search(std::string_view query, size_t results_count) const;

private:
    std::vector<std::string_view> lines_;
    std::vector<size_t> line_sizes_;
    std::vector<HashMap> query_count_;

    std::unordered_map<std::string_view, double> CountIDF(const std::vector<HashMap>& query_count,
                                                          const HashSet& queries, const size_t text_size) const;

    std::vector<std::pair<double, size_t>> CountTFIDF(const std::vector<HashMap>& query_count, const HashSet& queries,
                                                      const std::unordered_map<std::string_view, double>& idf,
                                                      const std::vector<std::string_view>& lines,
                                                      const std::vector<size_t>& line_sizes) const;

    std::vector<std::string_view> CutVector(const std::vector<std::pair<double, size_t>>& tf_idf, const size_t len,
                                            const std::vector<std::string_view>& lines) const;
};
