#include "controller.h"
#include "image_exception.h"
#include "filters/blur.h"
#include "filters/crop.h"
#include "filters/edge_detection.h"
#include "filters/grayscale.h"
#include "filters/negative.h"
#include "filters/sharpening.h"
#include <cctype>
#include <string>

namespace {

bool IsInteger(const char* arg) {
    std::string str = arg;
    return std::all_of(str.begin(), str.end(), [](char c){return isdigit(c);});
}

bool IsDouble(const char* arg) {
    std::string str = arg;
    return std::all_of(str.begin(), str.end(), [](char c){return (isdigit(c) || c == '-' || c == '.');});
}

int NextArgToInt(int argc, char**& argv, size_t i) {
    if (i + 1 >= argc) {
        throw IncorrectFilterInformation();
    }
    auto next_arg = argv[++i];
    if (!IsInteger(next_arg)) {
        throw IncorrectFilterInformation();
    }
    return std::atoi(next_arg);
}

double NextArgToDouble(int argc, char**& argv, size_t i) {
    if (i + 1 >= argc) {
        throw IncorrectFilterInformation();
    }
    auto next_arg = argv[++i];
    if (!IsDouble(next_arg)) {
        throw IncorrectFilterInformation();
    }
    return std::atof(next_arg);
}

} // namespace

Controller::Controller(int argc, char** &argv) {
    argc_ = argc;
    argv_ = argv;
    im_ = Image();
}

void Controller::Load() {
    if (argc_ < 3) {
        throw IncorrectInputOrOutputData();
    }

    std::ifstream input(argv_[1], std::ios::binary);
    if (!input) {
        throw IncorrectInputOrOutputData();
    }

    im_.Load(input);
}

void Controller::ApplyFilters() {
    std::vector<Filter *> filters_to_do;
    for (int i = 3; i < argc_; ++i) {
        auto cur_arg = static_cast<std::string>(argv_[i]);
        if (cur_arg == "-blur") {

            auto sigma = NextArgToInt(argc_, argv_, i);
            ++i;

            if (!sigma) {
                throw IncorrectFilterInformation();
            }

            auto blur = new Blur(sigma);
            filters_to_do.push_back(blur);

        } else if (cur_arg == "-crop") {

            auto width = NextArgToInt(argc_, argv_, i);
            ++i;
            auto height = NextArgToInt(argc_, argv_, i);
            ++i;

            if (width < 0 || height < 0) {
                throw IncorrectFilterInformation();
            }

            auto crop = new Crop(width, height);
            filters_to_do.push_back(crop);

        } else if (cur_arg == "-edge") {

            auto threshold = NextArgToDouble(argc_, argv_, i);
            ++i;

            auto edge_detection = new EdgeDetection(threshold);
            filters_to_do.push_back(edge_detection);

        } else if (cur_arg == "-gs") {

            auto grayscale = new GrayScale();
            filters_to_do.push_back(grayscale);

        } else if (cur_arg == "-neg") {

            auto negative = new Negative();
            filters_to_do.push_back(negative);

        } else if (cur_arg == "-sharp") {

            auto sharpening = new Sharpening();
            filters_to_do.push_back(sharpening);

        } else {

            throw IncorrectFilterInformation();

        }
    }

    for (auto filter: filters_to_do) {
        filter->Modify(im_);
        delete filter;
    }
}

void Controller::Save() {
    std::ofstream output(argv_[2], std::ios::binary);
    if (!output) {
        throw IncorrectInputOrOutputData();
    }
    im_.Save(output);
}
