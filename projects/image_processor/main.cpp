#include "image_processor.h"
#include <iostream>

int main() {
    ImageProcessor im;
    std::cout << "Введите адрес исходного изображения:" << std::endl;

    std::string in;
    std::cin >> in;
    std::ifstream input("example.bmp", std::ios::binary);
    //    while (!input) {
    //        std::cout << "Адрес не валиден. Попробуйте ещё раз:" << std::endl;
    //        std::cin >> in;
    //        std::ifstream input(in, std::ios::binary);
    //    } TODO

    im.Load(input);

    std::cout << "Выберете методы, которые хотите вызвать и напишите их названия:"
                 "\ncrop\nnegative\ngs\n\nЕсли хотите закончить, напишите save"
              << std::endl
              << std::endl;

    std::string cur_method;
    std::cin >> cur_method;

    while (cur_method != "save") {
        if (cur_method == "crop") {
            size_t width, height;
            std::cout << "Задайте новую ширину картинки:" << std::endl;
            std::cin >> width;
            std::cout << "Задайте новую высоту картинки:" << std::endl;
            std::cin >> height;
            im.FilterCrop(width, height);
            std::cout << std::endl;
        } else if (cur_method == "neg") {
            im.FilterNeg();
        } else if (cur_method == "gs") {
            im.FilterGs();
        } else {
            std::string _;
            std::getline(std::cin, _);
            std::cout << "Такого метода нет. Попробуйте ещё раз:" << std::endl;
        }
        std::cin >> cur_method;
    }

    std::cout << "Введите адрес, по которому хотите сохранить изображение" << std::endl;
    std::string out;
    std::cin >> out;
    std::ofstream output("output2.bmp", std::ios::binary);
    im.Save(output);
}
