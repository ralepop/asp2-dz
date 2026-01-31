#include <iostream>
#include <fstream>

#include "image_processor.h"
#include "sorting.h"

int main() {

    SortingAlgorithm* algorithm = new MergeInsertSort();
    SortingAlgorithm* algorithm2 = new ExampleSort();
    
    int choice;

    while (true) {
        std::cout << "\n--- MENI ---\n";
        std::cout << "1. Merge sort & Insertion sort\n";
        std::cout << "2. Quick sort & Bubble sort\n";
        std::cout << "0. Izlaz\n";

        std::cin >> choice;

        if (choice == 0) break;

        switch (choice) {
            case 1: {
                std::string inputPath, outputPath;
                std::cout << "Unesi putanju input fajla: ";            
                std::cin >> inputPath;
                std::cout << "Unesi putanju output fajla: ";
                std::cin >> outputPath;
                
                ImageProcessor::reconstructImage(inputPath.c_str(), outputPath.c_str(), algorithm);
                break;
            }
            case 2: {
                std::string inputPath, outputPath;
                std::cout << "Unesi putanju input fajla: ";            
                std::cin >> inputPath;
                std::cout << "Unesi putanju output fajla: ";
                std::cin >> outputPath;
                
                ImageProcessor::reconstructImage(inputPath.c_str(), outputPath.c_str(), algorithm2);
                break;
            }

            default: {
                std::cout << "Nepoznata opcija.\n";
            }
        }
    }

    delete algorithm;

    return 0;
}