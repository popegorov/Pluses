#pragma once

#include "image.h"

class Controller {
public:
    Controller(int argc, char**& argv);

    void Load();

    void ApplyFilters();

    void Save();

private:
    int argc_;
    char** argv_;
    Image im_;
};
