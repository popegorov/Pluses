#include "controller.h"

int main(int argc, char **argv) {
//    Image im;
//    std::ifstream input(argv[1], std::ios::binary);
//    if (!input) {
//        throw IncorrectInputOrOutputData();
//    }
//    im.Load(input);
//
//    std::ofstream output(argv[2], std::ios::binary);
//    if (!output) {
//        throw IncorrectInputOrOutputData();
//    }
//
//    std::vector<Filter *> filters_to_do;
//    for (int i = 3; i < argc; ++i) {
//        auto cur_arg = static_cast<std::string>(argv[i]);
//        if (cur_arg == "-blur") {
//
//            auto sigma = std::atoi(argv[++i]);
//            if (!sigma) {
//                throw IncorrectInputOrOutputData();
//            }
//
//            auto blur = new Blur(sigma);
//            filters_to_do.push_back(blur);
//
//        } else if (cur_arg == "-crop") {
//
//            auto width = std::atoi(argv[++i]);
//            auto height = std::atoi(argv[++i]);
//            if (width < 0 || height < 0) {
//                throw IncorrectInputOrOutputData();
//            }
//
//            auto crop = new Crop(width, height);
//            filters_to_do.push_back(crop);
//
//        } else if (cur_arg == "edge") {
//
//            auto threshold = std::atoi(argv[++i]);
//            auto edge_detection = new EdgeDetection(threshold);
//            filters_to_do.push_back(edge_detection);
//
//        } else if (cur_arg == "-gs") {
//
//            auto grayscale = new GrayScale();
//            filters_to_do.push_back(grayscale);
//
//        } else if (cur_arg == "-neg") {
//
//            auto negative = new Negative();
//            filters_to_do.push_back(negative);
//
//        } else if (cur_arg == "-sharp") {
//
//            auto sharpening = new Sharpening();
//            filters_to_do.push_back(sharpening);
//
//        }
//    }
//    for (auto filter: filters_to_do) {
//        filter->Modify(im);
//        delete filter;
//    }
//
//    im.Save(output);
    Controller controller(argc, argv);
    controller.Load();
    controller.ApplyFilters();
    controller.Save();
}
