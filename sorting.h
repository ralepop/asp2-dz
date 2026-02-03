#ifndef ASP2_DZ3_SORTING_H
#define ASP2_DZ3_SORTING_H

#include "image.h"
#include <algorithm>
#include <cmath>
#include <stack>
#include <utility>
#include <vector>

enum SortingDirection {
    ASCENDING,
    DESCENDING
};

inline void permutation(Image* image, int* f, int n) {
    int* inv = new int[n];
    for (int i = 0; i < n; i++) {
        inv[f[i]] = i;
    }

    for (int i = 0; i < n; i++) {
        while (inv[i] != i) {
            int t = inv[i];
            image->swapElements(i, t);
            std::swap(inv[i], inv[t]);
        }
    }
    delete[] inv;
}

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
        permutation(image, f, n);

        delete[] f;
        delete[] v;
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
};

class QuickBubbleSort final : public SortingAlgorithm {
public:

    QuickBubbleSort(double c) : c_constant(c) {}

    void sort(Image* image, SortingDirection direction) override {
        const int n = image->getElementCount();
        if (n <= 1) return; // sprecava log(0) u partition funkciji
        
        long long counter = 0;
        int* f = new int[n];  // pomocni niz
        int* v = new int[n]; // kesiranje

        for (int i = 0; i < n; i++) {
            f[i] = i;
            v[i] = image->getElement(i);
        }

        quick(f, v, 0, n - 1, n, counter, direction);

        permutation(image, f, n);

        delete[] f;
        delete[] v;
    }

private:

    double c_constant;

    void quick(int* f, int* a, int low, int high, int n, long long& counter, SortingDirection dir) {
        if (low >= high) return;

        const long long limit = c_constant * n * std::log2(n);

        std::stack<std::pair<int, int>> s;
        s.push({low, high});

        while (!s.empty()) {
            std::pair<int, int> range = s.top();
            s.pop();

            int currLow = range.first, currHigh = range.second;
            
            // sanjina heuristika
            bool check = checkHeuristic(limit, counter);
            if (check) {
                bubble(f, a, currLow, currHigh, dir);
                continue;
            }
            // kraj sanjine heuristike
            
            int j = partition(f, a, currLow, currHigh, limit, counter, dir);

            // ako ima mesta
            if (j - 1 > currLow) s.push({currLow, j - 1});
            if (j + 1 < currHigh) s.push({j + 1, currHigh});
        }
    }

    int partition(int* f, int* a, int down, int up, const long long& limit, long long& counter, SortingDirection dir) {
        int i = down + 1, j = up, pivot = a[f[down]];

        while (true) {
            // pomeramo i desno dok ne nadjemo element koji je na pogresnoj strani
            while (i <= j) {
                bool cond = (dir == ASCENDING) ? (a[f[i]] <= pivot) : (a[f[i]] >= pivot);
                counter++;
                if (cond) i++;
                else break;
            }
            
            // pomeramo j levo dok ne nadjemo element koji je na pogresnoj strani
            while (j >= i) {
                bool cond = (dir == ASCENDING) ? (a[f[j]] >= pivot) : (a[f[j]] <= pivot);
                counter++;
                if (cond) j--;
                else break;
            }

            if (i < j) {
                std::swap(f[i], f[j]);
                i++;
                j--;
            } else break;
        }

        std::swap(f[down], f[j]);
        return j;
    }

    void bubble(int* f, int* a, int start, int end, SortingDirection dir) {
        int pos = end;
        while (pos > start) {
            int bound = std::min(pos, end);
            pos = start;

            for (int i = start; i < bound; i++) {
                bool cond = (dir == ASCENDING) ? (a[f[i]] > a[f[i + 1]]) : (a[f[i]] < a[f[i + 1]]);
                if (cond) {
                    std::swap(f[i], f[i + 1]);
                    pos = i;
                }
            }
        }
    }

    bool checkHeuristic(const long long& limit, long long& counter) {
        if (counter >= limit) return true;
        return false;
    }
};

class StdSort final : public SortingAlgorithm {
public:
    void sort(Image* image, SortingDirection direction) override {
        int n = image->getElementCount();

        std::vector<int> arr(n), inv(n);
        for (int i = 0; i < n; i++) arr[i] = i;

        std::sort(arr.begin(), arr.end(), [&](int a, int b) {
            if (direction == ASCENDING) {
                return image->getElement(a) < image->getElement(b);
            }
            return image->getElement(a) > image->getElement(b);
        });

        for (int i = 0; i < n; i++) inv[arr[i]] = i;
        for (int i = 0; i < n; i++) {
            while (inv[i] != i) {
                int t = inv[i];
                image->swapElements(i, t);
                std::swap(inv[i], inv[t]);
            }
        }
    }
};

#endif //ASP2_DZ3_SORTING_H