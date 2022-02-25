#include <random>
#include <ctime>
#include <chrono>
#include "SmoothSort.h"

int main()
{
    srand(time(nullptr));

    for (size_t size = 1000; size < 5000; size += 1000) {
        vector<int> v1(size);
        vector<int> v2(size);

        for (size_t i = 0; i < size; i++) {
            v1[i] = i;
            v2[i] = rand() % 99999999;
        }

        chrono::time_point<chrono::system_clock>  start1 = chrono::system_clock::now();
        SmoothSort(v1);
        chrono::time_point<chrono::system_clock>  end1 = chrono::system_clock::now();

        chrono::time_point<chrono::system_clock>  start2 = chrono::system_clock::now();
        SmoothSort(v2);
        chrono::time_point<chrono::system_clock>  end2 = chrono::system_clock::now();
        cout << size << " " << chrono::duration<double>(end1 - start1).count() << " " << chrono::duration<double>(end2 - start2).count() << "\n";
    }

}