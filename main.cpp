// Артамонов Олег, М80-208Б
// Лабораторная работа №8
// Вариант 16, 8-угольник, треугольник, квадрат

#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <sstream>
#include <cmath>

#include "factory.h"
#include "handler.h"

void menu() {
    std::cout << "Select an action:\n";
    std::cout << "0. Exit.\n";
    std::cout << "1. Add figure.\n";
}

void menu_figures() {
    std::cout << "Select a figure from the list: \n";
    std::cout << "1. Octagon.\n";
    std::cout << "2. Triangle.\n";
    std::cout << "3. Square.\n";
}


int main(int argc, char** argv) {
    size_t buf_size = 2;

    if (argc == 2) {
        std::stringstream argc;
        argc << argv[1];
        argc >> buf_size;
    }

    Handler handler(buf_size);

    handler.Functions([](const std::list<std::shared_ptr<Figure>>& figures) {
        for (auto& figure : figures) {
            figure->Print();
        }
    });

    static int filename;

    handler.Functions([](const std::list<std::shared_ptr<Figure>>& figures) {
        filename = rand();
        std::string str = std::to_string(filename) + ".txt";
        std::ofstream file(str);
        for (auto items : figures) {
            items->Write(file);
        }
        file.close();
    });

    int choice_action;

    menu();
    while (true) {
        std::cout << ">> ";
        std::cin >> choice_action;
        switch (choice_action) {
        case 0:
            std::cout << "Goodbye.\n";
            return 0;
            break;
        case 1:
            int figure_num;
            menu_figures();
            std::cout << ">> ";
            std::cin >> figure_num;
            handler.Push(Factory<double>::CreateFigure(figure_num));
            std::cout << "Done.\n";
            break;
        default:
            std::cout << "Incorrect input!\n";
            break;
        }
    };

    std::cout << std::endl;
    return 0;
}