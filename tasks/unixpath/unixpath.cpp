#include "unixpath.h"
#include <string_view>
#include <vector>

std::vector<std::string_view> StringViewSplit(std::string_view& str, const std::string_view& elem = "/") {
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

std::vector<std::string_view> PathModification(std::vector<std::string_view>& cur_dir,
                                               const std::vector<std::string_view>& path) {
    for (const auto& elem : path) {
        if (elem == ".." && !cur_dir.empty()) {
            cur_dir.pop_back();
        } else if (elem != ".." && elem != "."){
            cur_dir.push_back(elem);
        }
    }
    return cur_dir;
}

std::string NormalPath (const std::vector<std::string_view>& cur_dir) {
    std::string normal_path;
    for (const auto& elem : cur_dir) {
        normal_path += "/";
        normal_path += elem;
    }
    if (normal_path.empty()) {
        return "/";
    }
    return normal_path;
}

std::string NormalizePath(std::string_view current_working_dir, std::string_view path) {
    auto cur_dir = StringViewSplit(current_working_dir);
    auto cur_path = StringViewSplit(path);
    if (path[0] == '/') {
        cur_dir.clear();
    }
    cur_dir = PathModification(cur_dir, cur_path);
    return NormalPath(cur_dir);
}
