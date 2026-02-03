#include <iomanip>
#include <ios>
#include <iostream>
#include <string>

#include "image_processor.h"
#include "sorting.h"
#include "utils.h"

int main() {

    int choice;

    while (true) {
        std::cout << "\n--- MENI ---\n";
        std::cout << "1. Merge sort & Insertion sort\n";
        std::cout << "2. Quick sort & Bubble sort\n";
        std::cout << "3. std::sort\n";
        std::cout << "4. Merenje\n";
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
                std::cout << "Unesi konstantu c za Sanjinu heuristiku: ";
                std::cin >> c;
                
                std::string inputPath, outputPath;
                std::cout << "Unesi putanju input fajla: ";            
                std::cin >> inputPath;
                std::cout << "Unesi putanju output fajla: ";
                std::cin >> outputPath;
                
                SortingAlgorithm* algorithm = new QuickBubbleSort(c);
                
                Stopwatch sw;
                sw.start();
                
                ImageProcessor::reconstructImage(inputPath.c_str(), outputPath.c_str(), algorithm);
                
                long long time = sw.stop();
                std::cout << "Vreme: " << time << " ms\n";
                
                delete algorithm;
                break;
            }
            case 3: {
                std::string inputPath, outputPath;
                std::cout << "Unesi putanju input fajla: ";            
                std::cin >> inputPath;
                std::cout << "Unesi putanju output fajla: ";
                std::cin >> outputPath;
                
                SortingAlgorithm* algorithm = new StdSort();
                
                Stopwatch sw;
                sw.start();
                
                ImageProcessor::reconstructImage(inputPath.c_str(), outputPath.c_str(), algorithm);
                
                long long time = sw.stop();
                std::cout << "Vreme: " << time << " ms\n";
                
                delete algorithm;
                break;

                break;
            }

            case 4:{
                int k;
                double c;
                std::cout << "Unesi prag k za Matijinu heuristiku: ";
                std::cin >> k;
                std::cout << "Unesi konstantu c za Sanjinu heuristiku: ";
                std::cin >> c;

                SortingAlgorithm* algs[] = {
                    new MergeInsertSort(k),
                    new QuickBubbleSort(c),
                    new StdSort()
                };

                std::string algNames[] = {"MergeInsert", "QuickBubble", "std::sort"};
                std::string files[] = {
                    "image_1_asc.txt", "image_1_desc.txt", "image_1_rand.txt",
                    "image_2_asc.txt", "image_2_desc.txt", "image_2_rand.txt",
                    "image_3_asc.txt", "image_3_desc.txt", "image_3_rand.txt",
                    "image_4_asc.txt", "image_4_desc.txt", "image_4_rand.txt"
                };

                const int numFiles = 12;
                const int numAlgs = 3;
                long long results[numFiles][numAlgs];

                Stopwatch sw;

                for (int i = 0; i < numFiles; i++) {
                    std::string path = "datoteke/" + files[i];
                    for (int j = 0; j < numAlgs; j++) {
                        sw.start();
                        ImageProcessor::reconstructImage(path.c_str(), "result.txt", algs[j]);
                        results[i][j] = sw.stop();
                    }
                }
                
                std::cout << "\n" << std::left << std::setw(20) << "Datoteka";
                for (const auto& alg : algNames) {
                    std::cout << std::right << std::setw(20) << alg;
                }
                std::cout << "\n" << std::string(75, '-') << std::endl;

                for (int i = 0; i < numFiles; i++) {
                    std::cout << std::left << std::setw(20) << files[i];
                    for (int j = 0; j < numAlgs; j++) {
                        std::string time = std::to_string(results[i][j]) + " ms";
                        std::cout << std::right << std::setw(18) << time;
                    }
                    std::cout << std::endl;
                }

                for (auto* a : algs) delete a;
                break;
            }
            default: {
                std::cout << "Nepoznata opcija.\n";
            }
        }
    }

    return 0;
}