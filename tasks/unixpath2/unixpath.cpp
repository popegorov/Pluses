#include "unixpath.h"
#include <string_view>
#include <vector>

std::vector<std::string_view> Split(std::string_view& str, const std::string_view& elem = "/") {
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

std::vector<std::string_view> Normalize(const std::vector<std::string_view>& path) {
    std::vector<std::string_view> res;
    if (path[0] == ".") {
        res.push_back(".");
    }
    for (const auto& elem : path) {
        if (elem == ".." && res.size() == 1 && res.back() == ".") {
            res.pop_back();
            res.push_back(elem);
        } else if (elem == ".." && !res.empty() && res.back() != "..") {
            res.pop_back();
        } else if (elem != ".") {
            res.push_back(elem);
        }
    }
    return res;
}

std::string PathToString(std::vector<std::string_view> path) {
    if (path.empty()) {
        return "";
    }
    std::string result = static_cast<std::string>(path[0]);
    for (size_t i = 1; i < path.size(); ++i) {
        result += "/";
        result += path[i];
    }
    return result;
}

std::vector<std::string_view> ChangeAbsolutePath(const std::vector<std::string_view>& path,
                                                 std::vector<std::string_view>& result, bool flag = false) {
    if (flag) {
        result.clear();
    }
    for (const auto& elem : path) {
        result.push_back(elem);
    }
    result = Normalize(result);
    return result;
}

size_t LastSameSymbol(const std::vector<std::string_view>& cur_dir,
                      const std::vector<std::string_view>& absolute_path) {
    size_t len = cur_dir.size();
    if (len > absolute_path.size()) {
        len = absolute_path.size();
    }
    size_t max_i = cur_dir.size();
    for (size_t i = 0; i < len; ++i) {
        if (absolute_path[i] != cur_dir[i]) {
            max_i = i;
            break;
        }
    }
    return max_i;
}

void ChangeRelativePath(const std::vector<std::string_view>& absolute_path,
                        const std::vector<std::string_view>& cur_dir, std::vector<std::string_view>& relative_path) {
    auto max_i = LastSameSymbol(cur_dir, absolute_path);
    if (max_i == cur_dir.size()) {
        relative_path = {"."};
    } else {
        relative_path.clear();
        for (size_t i = 0; i < (cur_dir.size() - max_i); ++i) {
            relative_path.push_back("..");
        }
    }
    for (size_t i = max_i; i < absolute_path.size(); ++i) {
        relative_path.push_back(absolute_path[i]);
    }
}

UnixPath::UnixPath(std::string_view initial_dir) {
    cur_dir_ = absolute_path_ = Normalize(Split(initial_dir));
    relative_path_ = {"."};
}

void UnixPath::ChangeDirectory(std::string_view initial_directory) {
    bool first_sym_is_slash = (!initial_directory.empty() && initial_directory[0] == '/');
    auto path = Split(initial_directory);
    ChangeAbsolutePath(path, absolute_path_, first_sym_is_slash);
    ChangeRelativePath(absolute_path_, cur_dir_, relative_path_);
}

std::string UnixPath::GetAbsolutePath() const {
    return "/" + PathToString(absolute_path_);
}

std::string UnixPath::GetRelativePath() const {
    return PathToString(relative_path_);
}
