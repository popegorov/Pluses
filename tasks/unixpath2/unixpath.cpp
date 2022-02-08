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

std::string UnixPath::AbsolutePathToString() const {
    std::string result;
    for (const auto& elem : absolute_path_) {
        result += "/";
        result += elem;
    }
    if (result.empty()) {
        return "/";
    }
    return result;
}

std::string UnixPath::RelativePathToString() const {
    std::string result;
    result += relative_path_[0];
    for (size_t i = 1; i < relative_path_.size(); ++i) {
        result += "/";
        result += relative_path_[1];
    }
    return result;
}

std::vector<std::string_view>& NormalizeCurrentDirectory(std::vector<std::string_view>& cur_dir) {
    std::vector<std::string_view> result;
    for (const auto& elem : cur_dir) {
        if (elem == ".." && !result.empty()) {
            result.pop_back();
        } else if (elem != ".." && elem != ".") {
            result.push_back(elem);
        }
    }
    return cur_dir;
}

void UnixPath::ChangeRelativePath(const std::vector<std::string_view>& path, bool flag) {
    if (flag) {
        size_t len = cur_dir_.size();
        if (len > path.size()) {
            len = path.size();
        }
        size_t max_i = cur_dir_.size();
        for (size_t i = 0; i < len; ++i) {
            if (path[i] != cur_dir_[i]) {
                max_i = i;
                break;
            }
        }
        if (max_i == cur_dir_.size()) {
            relative_path_ = {"."};
        } else {
            relative_path_.clear();
            for (size_t i = 0; i < (cur_dir_.size() - max_i); ++i) {
                relative_path_.push_back("..");
            }
        }
        for (size_t i = max_i; i < path.size(); ++i) {
            relative_path_.push_back(path[i]);
        }
    } else {
        for (const auto& elem : path) {
            if (elem == ".." && !relative_path_.empty() && relative_path_.size() != 1) {
                relative_path_.pop_back();
                if (relative_path_.empty()) {
                    relative_path_ = {"."};
                }
            } else if (elem == ".." && !relative_path_.empty() && relative_path_[0] == ".") {
                relative_path_ = {".."};
            } else if (elem == ".." && !relative_path_.empty() && relative_path_[0] == "..") {
                relative_path_.push_back("..");
            } else if (elem != ".." && elem != ".") {
                relative_path_.push_back(elem);
            }
        }
    }
}

void UnixPath::ChangeAbsolutePath(const std::vector<std::string_view>& path, bool flag) {
    if (flag) {
        absolute_path_.clear();
    }
    for (const auto& elem : path) {
        if (elem == ".." && !absolute_path_.empty()) {
            absolute_path_.pop_back();
        } else if (elem != ".." && elem != ".") {
            absolute_path_.push_back(elem);
        }
    }
}

UnixPath::UnixPath(std::string_view initial_dir) {
    UnixPath::cur_dir_ = StringViewSplit(initial_dir);
    UnixPath::cur_dir_ = NormalizeCurrentDirectory(cur_dir_);
    UnixPath::absolute_path_ = {cur_dir_.begin(), cur_dir_.end()};
    UnixPath::relative_path_ = {"."};
}

void UnixPath::ChangeDirectory(std::string_view initial_directory) {
    bool first_sym_is_slash = (!initial_directory.empty() && initial_directory[0] == '/');
    auto path = StringViewSplit(initial_directory);
    UnixPath::ChangeRelativePath(path, first_sym_is_slash);
    UnixPath::ChangeAbsolutePath(path, first_sym_is_slash);
}

std::string UnixPath::GetAbsolutePath() const {
    return AbsolutePathToString();
}

std::string UnixPath::GetRelativePath() const {
    return RelativePathToString();
}