#include <iostream>

#include "image_processor.h"
#include "sorting.h"
#include "utils.h"

int main() {

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
                int k;
                std::cout << "Unesi prag k za Matijinu heuristiku: ";
                std::cin >> k;

                std::string inputPath, outputPath;
                std::cout << "Unesi putanju input fajla: ";            
                std::cin >> inputPath;
                std::cout << "Unesi putanju output fajla: ";
                std::cin >> outputPath;
                
                SortingAlgorithm* algorithm = new MergeInsertSort(k);

                Stopwatch sw;
                sw.start();
                
                ImageProcessor::reconstructImage(inputPath.c_str(), outputPath.c_str(), algorithm);

                long long time = sw.stop();
                std::cout << "Vreme: " << time << " ms\n";
                
                delete algorithm;
                break;
            }
            case 2: {
                double c;
                std::cout << "Unesi konstantu c za Markovu heuristiku: ";
                std::cin >> c;

                std::string inputPath, outputPath;
                std::cout << "Unesi putanju input fajla: ";            
                std::cin >> inputPath;
                std::cout << "Unesi putanju output fajla: ";
                std::cin >> outputPath;
                
                SortingAlgorithm* algorithm = new ExampleSort;

                ImageProcessor::reconstructImage(inputPath.c_str(), outputPath.c_str(), algorithm);

                delete algorithm;
                break;
            }

            default: {
                std::cout << "Nepoznata opcija.\n";
            }
        }
    }

    return 0;
}