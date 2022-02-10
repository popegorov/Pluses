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

std::string PathToString(std::vector<std::string_view> path) {
    std::string result;
    for (size_t i = 1; i < path.size(); ++i) {
        result += "/";
        result += path[i];
    }
    return result;
}

void ChangeAbsolutePath(const std::vector<std::string_view>& path, std::vector<std::string_view>& result,
                        bool flag = false) {
    if (flag) {
        result.clear();
    }
    for (const auto& elem : path) {
        if (elem == ".." && !result.empty()) {
            result.pop_back();
        } else if (elem != ".." && elem != ".") {
            result.push_back(elem);
        }
    }
}

void ChangeRelativePath(const std::vector<std::string_view>& path, const std::vector<std::string_view>& cur_dir,
                        std::vector<std::string_view>& relative_path, bool flag) {
    if (flag) {
        size_t len = cur_dir.size();
        if (len > path.size()) {
            len = path.size();
        }
        size_t max_i = cur_dir.size();
        for (size_t i = 0; i < len; ++i) {
            if (path[i] != cur_dir[i]) {
                max_i = i;
                break;
            }
        }
        if (max_i == cur_dir.size()) {
            relative_path = {"."};
        } else {
            relative_path.clear();
            for (size_t i = 0; i < (cur_dir.size() - max_i); ++i) {
                relative_path.push_back("..");
            }
        }
        for (size_t i = max_i; i < path.size(); ++i) {
            relative_path.push_back(path[i]);
        }
    } else {
        for (const auto& elem : path) {
            if (elem == ".." && !relative_path.empty() && relative_path.size() != 1) {
                relative_path.pop_back();
                if (relative_path.empty()) {
                    relative_path = {"."};
                }
            } else if (elem == ".." && !relative_path.empty() && relative_path[0] == ".") {
                relative_path = {".."};
            } else if (elem == ".." && !relative_path.empty() && relative_path[0] == "..") {
                relative_path.push_back("..");
            } else if (elem != ".." && elem != ".") {
                relative_path.push_back(elem);
            }
        }
    }
}

UnixPath::UnixPath(std::string_view initial_dir) {
    std::vector<std::string_view> res;
    ChangeAbsolutePath(StringViewSplit(initial_dir), res);
    cur_dir_ = res;
    absolute_path_ = {cur_dir_.begin(), cur_dir_.end()};
    relative_path_ = {"."};
}

void UnixPath::ChangeDirectory(std::string_view initial_directory) {
    bool first_sym_is_slash = (!initial_directory.empty() && initial_directory[0] == '/');
    auto path = StringViewSplit(initial_directory);
    ChangeRelativePath(path, cur_dir_, relative_path_, first_sym_is_slash);
    ChangeAbsolutePath(path, absolute_path_, first_sym_is_slash);
}

std::string UnixPath::GetAbsolutePath() const {
    if (absolute_path_.empty()) {
        return "/";
    }
    return "/" + static_cast<std::string>(absolute_path_[0]) + PathToString(absolute_path_);
}

std::string UnixPath::GetRelativePath() const {
    return static_cast<std::string>(relative_path_[0]) + PathToString(relative_path_);
}
