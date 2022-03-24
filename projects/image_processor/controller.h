#pragma once

#include "image.h"
#include <string>

class Controller {
public:
    Controller(int argc, std::vector<std::string>& argv);

    void Load(char*& arg);

    void ApplyFilters();

    void Save(char*& arg);

private:
    int argc_;
    std::vector<std::string> argv_;
    Image im_;
};
