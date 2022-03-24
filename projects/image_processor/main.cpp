#include "controller.h"

namespace {

std::vector<std::string> MakeVectorOfString(int argc, char**& argv) {
    std::vector<std::string> res;
    for (size_t i = 3; i < argc; ++i) {
        res.push_back(std::string(argv[i]));
    }
    return res;
}

} // namespace

int main(int argc, char** argv) {
    auto new_argv = MakeVectorOfString(argc, argv);
    Controller controller(argc - 3, new_argv);
    controller.Load(argv[1]);
    controller.ApplyFilters();
    controller.Save(argv[2]);
}
