#include "word2vec.h"
#include <vector>

std::vector<std::string> FindClosestWords(const std::vector<std::string>& words,
                                          const std::vector<std::vector<int>>& vectors) {
    int cur_sum;
    int max_sum = -2000000000;
    std::vector<std::string> closest_words;
    for (size_t i = 1; i < vectors.size(); ++i) {
        cur_sum = 0;
        for (size_t j = 0; j < vectors[i].size(); ++j) {
            cur_sum += vectors[0][j] * vectors[i][j];
        }
        if (cur_sum > max_sum) {
            max_sum = cur_sum;
            closest_words = {words[i]};
        } else if (cur_sum == max_sum) {
            closest_words.push_back(words[i]);
        }
    }
    return closest_words;
}
