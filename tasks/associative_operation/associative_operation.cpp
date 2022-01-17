#include <libcodedirectory.h>
#include "associative_operation.h"

bool IsAssociative(const std::vector<std::vector<size_t>>& table) {
    int n = table.size();
    for (int x = 0; x < n; ++x) {
        for (int y = 0; y < n; ++y) {
            for (int z = 0; z < n; ++z) {
                if (table[table[x][y]][z] != table[x][table[y][z]]) {
                    return false;
                }
            }
        }
    }
    return true;
}
