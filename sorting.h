#ifndef ASP2_DZ3_SORTING_H
#define ASP2_DZ3_SORTING_H

#include "image.h"
#include <algorithm>
#include <utility>

enum SortingDirection {
    ASCENDING,
    DESCENDING
};

class SortingAlgorithm {
public:
    virtual ~SortingAlgorithm() = default;
    virtual void sort(Image* image, SortingDirection direction) = 0;
};

class ExampleSort final : public SortingAlgorithm {
public:
    void sort(Image* image, SortingDirection direction) override {
        const int count = image->getElementCount();

        for (int i = 0; i < count; i++) {
            for (int j = i + 1; j < count; j++) {
                const int el1 = image->getElement(i);
                const int el2 = image->getElement(j);

                if (direction == ASCENDING && el1 > el2 || direction == DESCENDING && el1 < el2)
                    image->swapElements(i, j);
            }
        }
    }
};

class MergeInsertSort final : public SortingAlgorithm {
public:

    MergeInsertSort(int k) : k_constant(k) {}

    void sort(Image* image, SortingDirection direction) override {
        const int n = image->getElementCount();
        
        int* f = new int[n];  // pomocni niz
        int* v = new int[n]; // kesiranje

        for (int i = 0; i < n; i++) {
            f[i] = i;
            v[i] = image->getElement(i);
        }

        directMerge(f, v, n, direction);

        // inverzna mapa za permutaciju piksela
        int* inv = new int[n];
        for (int i = 0; i < n; i++) {
            inv[f[i]] = i;
        }

        // postavljanje piksela na tacna mesta
        for (int i = 0; i < n; i++) {
            while (inv[i] != i) { // ako nije na dobroj poziciji
                int t = inv[i];
                image->swapElements(i, t);
                std::swap(inv[i], inv[t]);
            }
        }

        delete[] f;
        delete[] v;
        delete[] inv;
    }

private:

    int k_constant;

    void directMerge(int* f, int* v, int n, SortingDirection direction) {
        int l = 1;
        int* f1 = new int[n];
        int* f2 = new int[n];

        while (l < n) {

            // matijina heuristika
            if (2 * l <= k_constant) {
                for (int start = 0; start < n; start += 2 * l) {
                    int end = std::min(start + 2 * l - 1, n - 1);
                    insertionSort(f, v, start, end, direction);
                }
            }
            // kraj matijine heuristike

            int count1 = 0;
            int count2 = 0;
            
            split(f, l, f1, f2, n, count1, count2);

            int i = 0;
            int j = 0;
            int k = 0;

            while (i < count1 && j < count2) {
                int u1 = std::min(i + l - 1, count1 - 1);
                int u2 = std::min(j + l - 1, count2 - 1);

                merge(f1, i, u1, f2, j, u2, f, k, v, direction);

                i += l;
                j += l;
            }

            while (i < count1) f[k++] = f1[i++];
            while (j < count2) f[k++] = f2[j++];

            l *= 2;
        }

        delete[] f1;
        delete[] f2;
    }

    void merge(int* a, int l1, int u1, int* b, int l2, int u2, int* c, int& k, int* v, SortingDirection dir) {
        int i = l1, j = l2;

        while (i <= u1 && j <= u2) {
            bool cond = (dir == ASCENDING) ? (v[a[i]] <= v[b[j]]) : (v[a[i]] >= v[b[j]]);
            c[k++] = cond ? a[i++] : b[j++];
        }

        while (i <= u1) c[k++] = a[i++];
        while (j <= u2) c[k++] = b[j++];
    }

    void split(int* f, int l, int* f1, int* f2, int n, int& i1, int& i2) {
        i1 = 0, i2 = 0;
        int i = 0;

        // delimo niz na segmente duzine l
        while (i < n) {
            for (int j = 0; j < l && i < n; j++) f1[i1++] = f[i++];
            for (int j = 0; j < l && i < n; j++) f2[i2++] = f[i++];
        }
    }

    void insertionSort(int* a, int*v, int start, int end, SortingDirection direction) {
        for (int i = start + 1; i <= end; i++) {
            int k = a[i];
            int valK = v[k];
            int j = i - 1;

            while (j >= start) {
                bool cond = (direction == ASCENDING) ? (v[a[j]] > valK) : (v[a[j]] < valK);

                if (cond) {
                    a[j + 1] = a[j];
                    j--;
                } else break;
            }
            a[j + 1] = k;
        }
    }

    bool heuristicCheck(int* f, int* v, int start, int end, SortingDirection direction, double c) {
        if (start >= end) return true;
        int inv = 0;

        for (int i = start; i < end; i++) {
            if (direction == ASCENDING && v[f[i]] > v[f[i + 1]]) inv++;
            else if (direction == DESCENDING && v[f[i]] < v[f[i + 1]]) inv++;
        }

        return inv <= c * (end - start + 1);
    }
};

#endif //ASP2_DZ3_SORTING_H