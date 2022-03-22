#include "image.h"
#include "filters/blur.h"
#include "filters/crop.h"
#include "filters/edge_detection.h"
#include "filters/grayscale.h"
#include "filters/negative.h"
#include "filters/sharpening.h"

int main(int argc, char **argv) {
    Image im;
    std::ifstream input(argv[1], std::ios::binary);
    im.Load(input);
    std::ofstream output(argv[2], std::ios::binary);
    std::vector<Filter *> filters_to_do;

    for (int i = 3; i < argc; ++i) {
        if (static_cast<std::string>(argv[i]) == "-blur") {

            auto sigma = std::atoi(argv[++i]);
            auto blur = new Blur(sigma);
            filters_to_do.push_back(blur);

        } else if (static_cast<std::string>(argv[i]) == "-crop") {

            auto width = std::atoi(argv[++i]);
            auto height = std::atoi(argv[++i]);
            auto crop = new Crop(width, height);
            filters_to_do.push_back(crop);

        } else if (static_cast<std::string>(argv[i]) == "edge") {

            auto threshold = std::atoi(argv[++i]);
            auto edge_detection = new EdgeDetection(threshold);
            filters_to_do.push_back(edge_detection);

        } else if (static_cast<std::string>(argv[i]) == "-gs") {

            auto grayscale = new GrayScale();
            filters_to_do.push_back(grayscale);

        } else if (static_cast<std::string>(argv[i]) == "-neg") {

            auto negative = new Negative();
            filters_to_do.push_back(negative);

        } else if (static_cast<std::string>(argv[i]) == "-sharp") {

            auto sharpening = new Sharpening();
            filters_to_do.push_back(sharpening);

        }
    }
    for (const auto &filter: filters_to_do) {
        filter->Modify(im);
        delete filter;
    }

    im.Save(output);
}
