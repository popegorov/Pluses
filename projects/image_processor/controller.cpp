#include "controller.h"
#include "image_exception.h"
#include "filters/blur.h"
#include "filters/crop.h"
#include "filters/edge_detection.h"
#include "filters/grayscale.h"
#include "filters/negative.h"
#include "filters/sharpening.h"
#include <memory>

namespace {

int NextArgToInt(int argc, std::vector<std::string>& argv, size_t i) {
    if (i + 1 >= argc) {
        throw IncorrectFilterInformation();
    }
    try {
        return std::stoi(argv[++i]);
    } catch (std::invalid_argument e) {
        throw IncorrectFilterInformation();
    }
}

double NextArgToDouble(int argc, std::vector<std::string>& argv, size_t i) {
    if (i + 1 >= argc) {
        throw IncorrectFilterInformation();
    }
    try {
        return std::stof(argv[++i]);
    } catch (std::invalid_argument e) {
        throw IncorrectFilterInformation();
    }
}

void Modify(const std::vector<std::unique_ptr<Filter>>& to_do, Image& im) {
    for (const auto& filter: to_do) {
        filter->Modify(im);
    }
}

} // namespace

Controller::Controller(int argc, std::vector<std::string>& argv) {
    argc_ = argc;
    argv_ = argv;
    im_ = Image();
}

void Controller::Load(char*& arg) {
    if (argc_ < 0) {
        throw IncorrectInputOrOutputData();
    }

    std::ifstream input(arg, std::ios::binary);
    if (!input) {
        throw IncorrectInputOrOutputData();
    }

    im_.Load(input);
}

void Controller::ApplyFilters() {
    std::vector<std::unique_ptr<Filter>> filters_to_do;
    for (int i = 0; i < argc_; ++i) {
        auto cur_arg = argv_[i];
        if (cur_arg == "-blur") {

            auto sigma = NextArgToDouble(argc_, argv_, i);
            ++i;

            if (!sigma) {
                throw IncorrectFilterInformation();
            }

            filters_to_do.push_back(std::make_unique<Blur>(sigma));

        } else if (cur_arg == "-crop") {

            auto width = NextArgToInt(argc_, argv_, i);
            ++i;
            auto height = NextArgToInt(argc_, argv_, i);
            ++i;

            if (width < 0 || height < 0) {
                throw IncorrectFilterInformation();
            }

            filters_to_do.push_back(std::make_unique<Crop>(width, height));

        } else if (cur_arg == "-edge") {

            auto threshold = NextArgToDouble(argc_, argv_, i);
            ++i;

            filters_to_do.push_back(std::make_unique<EdgeDetection>(threshold));

        } else if (cur_arg == "-gs") {

            filters_to_do.push_back(std::make_unique<GrayScale>());

        } else if (cur_arg == "-neg") {

            filters_to_do.push_back(std::make_unique<Negative>());

        } else if (cur_arg == "-sharp") {

            filters_to_do.push_back(std::make_unique<Sharpening>());

        } else {

            throw IncorrectFilterInformation();

        }
    }

    Modify(filters_to_do, im_);
}

void Controller::Save(char*& arg) {
    std::ofstream output(arg, std::ios::binary);
    if (!output) {
        throw IncorrectInputOrOutputData();
    }
    im_.Save(output);
}

