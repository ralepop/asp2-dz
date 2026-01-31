# Algoritmi i strukture podataka 2 - DZ3 (srp)

Ovaj repozitorijum sadrži rešenje trećeg domaćeg zadatka na predmetu 13S112ASP2 (školska godina 2025/2026).

## Opis zadatka
Fokus zadatka je rekonstrukcija "tajne" ASCII slike čiji su elementi (pikseli) pomešani. Svaki piksel ima svoj indeks, a originalna slika se dobija sortiranjem ovih indeksa u rastućem redosledu.

## Implementirani algoritmi
Projekat realizuje hibridne algoritme sortiranja bez upotrebe rekurzije:

1.  **Merge Sort + Insertion Sort**:
    * Prelazak na Insertion Sort se vrši na osnovu izabrane heuristike (broj inverzija ili veličina particije).
2.  **Quick Sort + Bubble Sort**:
    * Prelazak na Bubble Sort se vrši na osnovu dubine particionisanja, broja poređenja sa pivotom ili broja uzastopnih loših podela.

## Funkcionalnosti
* Učitavanje kodirane slike iz tekstualne datoteke.
* Interaktivni meni za izbor algoritma i unos parametara (konstante za heuristike).
* Merenje vremena izvršavanja pomoću klase `Stopwatch`.
* Poređenje efikasnosti implementiranih algoritama sa `std::sort` funkcijom.
* Prikaz rezultata u tabelarnom formatu.

<br><br><br>

# Algorithms and Data Structures 2 - DZ3 (eng)

This repository contains the solution for the third assignment in the course 13S112ASP2 (academic year 2025/2026).

## Project Overview
The primary goal is the reconstruction of a "secret" ASCII image with shuffled pixels. Each pixel is associated with a unique index; the original image is restored by sorting these pixels in ascending order based on their indices.

## Implemented Algorithms
The project features hybrid sorting algorithms implemented iteratively (non-recursive):

1.  **Merge Sort + Insertion Sort**:
    * Transitions to Insertion Sort based on specific heuristics (number of inversions or partition size).
2.  **Quick Sort + Bubble Sort**:
    * Transitions to Bubble Sort based on partitioning depth, number of comparisons with the pivot, or consecutive "bad" splits.

## Features
* Loading encoded images from text files.
* Interactive CLI menu for selecting algorithms and defining heuristic constants.
* Execution time tracking using a custom `Stopwatch` class.
* Performance benchmarking against the standard `std::sort` library function.
* Tabular display of execution times for different initial pixel orders.