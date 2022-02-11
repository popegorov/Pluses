#pragma once

#include <string>
#include <string_view>
#include <vector>

class UnixPath {

public:
    UnixPath(std::string_view initial_dir);

    void ChangeDirectory(std::string_view path);

    std::string GetAbsolutePath() const;
    std::string GetRelativePath() const;

private:
    std::vector<std::string_view> cur_dir_;
    std::vector<std::string_view> relative_path_;
    std::vector<std::string_view> absolute_path_;
};
