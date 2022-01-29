#include "word2vec.h"
#include <vector>
#include <limits>

int ScalarMultiplication(const std::vector<int>& first, const std::vector<int>& second) {
    int sum = 0;
    for (size_t i = 0; i < first.size(); ++i) {
        sum += first[i] * second[i];
    }
    return sum;
}

std::vector<std::string> FindClosestWords(const std::vector<std::string>& words,
                                          const std::vector<std::vector<int>>& vectors) {
    int max_sum = std::numeric_limits<int>::min();
    std::vector<std::string> closest_words;
    for (size_t i = 1; i < vectors.size(); ++i) {
        int cur_sum = ScalarMultiplication(vectors[0], vectors[i]);
        if (cur_sum > max_sum) {
            max_sum = cur_sum;
            closest_words = {words[i]};
        } else if (cur_sum == max_sum) {
            closest_words.push_back(words[i]);
        }
    }
    return closest_words;
}