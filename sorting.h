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
    void sort(Image* image, SortingDirection direction) override {
        const int n = image->getElementCount();

        int* f = new int[n];

        for (int i = 0; i < n; i++) {
            f[i] = i; // pomocni niz
        }

        directMerge(f, n, image, direction);

        // inverzna mapa za permutaciju piksela
        int* inv = new int[n];
        for (int i = 0; i < n; i++) {
            inv[f[i]] = i;
        }

        // postavljanje piksela na tacna mesta
        for (int i = 0; i < n; i++) {
            while (inv[i] != i) {
                int t = inv[i];
                image->swapElements(i, t);
                std::swap(inv[i], inv[t]);
            }
        }

        delete[] f;
        delete[] inv;
    }

private:

    void directMerge(int* f, int n, Image* image, SortingDirection direction) {
        int l = 1;
        int* f1 = new int[n];
        int* f2 = new int[n];

        while (l < n) {
            int count1 = 0, count2 = 0;
            split(f, l, f1, f2, n, count1, count2);

            int i = 0, j = 0, k = 0;

            while (i < count1 && j < count2) {
                int u1 = std::min(i + l - 1, count1 - 1);
                int u2 = std::min(j + l - 1, count2 - 1);

                merge(f1, i, u1, f2, j, u2, f, k, image, direction);

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

    void merge(int* a, int l1, int u1, int* b, int l2, int u2, int* c, int& k, Image* image, SortingDirection direction) {
        int i = l1;
        int j = l2;

        while (i <= u1 && j <= u2) {
            int valA = image->getElement(a[i]);
            int valB = image->getElement(b[j]);

            bool condition;
            if (direction == ASCENDING) condition = (valA <= valB);
            else condition = (valA >= valB);

            if (condition) {
                c[k++] = a[i++];
            } else {
                c[k++] = b[j++];
            }
        }

        while (i <= u1) c[k++] = a[i++];
        while (j <= u2) c[k++] = b[j++];
    }

    void split(int* f, int l, int* f1, int* f2, int n, int& i1, int& i2) {
        i1 = 0;
        i2 = 0;
        int i = 0;

        // delimo niz na segmente duzine l
        while (i < n) {
            for (int j = 0; j < l && i < n; j++) {
                f1[i1++] = f[i++];
            }
            for (int j = 0; j < l && i < n; j++) {
                f2[i2++] = f[i++];
            }
        }
    }
};

#endif //ASP2_DZ3_SORTING_H