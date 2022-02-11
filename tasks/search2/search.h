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
};