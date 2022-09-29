#include <iostream>
#include <cmath>
#include <iomanip>
#include <chrono>
#include <vector>
#include <algorithm>
#include <random>

using std::cout, std::cin, std::sin, std::setprecision, std::chrono::duration_cast, std::chrono::milliseconds,
    std::vector, std::copy, std::random_device, std::mt19937, std::uniform_int_distribution, std::sort;

using hr_clock = std::chrono::high_resolution_clock;

vector<int> GenerateRandomArray(int n) {
    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> dist(1, n);

    vector<int> array(n);
    for (int i = 0; i < n; i++) array[i] = dist(mt);

    return array;
}

void BubbleSort(vector<int> &array) {
    bool swapped;
    do {
        swapped = false;
        for (int i = 0; i < array.size()-1; i++) {
            if (array[i] > array[i+1]) {
                std::swap(array[i], array[i+1]);
                swapped = true;
            }
        }
    } while (swapped);
}

void Merge(vector<int> &array, int p, int q, int r) {
    int n1 = q - p+1;
    int n2 = r - q;

    vector<int> left(n1);
    vector<int> right(n2);
    copy(array.begin()+p, array.begin()+q+1, left.begin());
    copy(array.begin()+q+1, array.begin()+r+1, right.begin());
    left.push_back(INT32_MAX);
    right.push_back(INT32_MAX);

    int i = 0, j = 0;
    for (int k = p; k < r+1; k++) {
        if (left[i] <= right[j]) {
            array[k] = left[i++];
        } else {
            array[k] = right[j++];
        }
    }
}

void MergeSort(vector<int> &array, int p, int r) {
    int q = (p+r)/2;
    if (p < r) {
        MergeSort(array, p, q);
        MergeSort(array, q + 1, r);
        Merge(array, p, q, r);
    }
}

void CountingSort(vector<int> &array, int k) {
    vector<int> count_array(k+1);
    vector<int> result(array.size());

    for (auto num: array) {count_array[num]++;}

    for (int i = 0; i < k+1; i++) {
        count_array[i] += count_array[i-1];
    }

    for (int number : array) {
        result[count_array[number] - 1] = number;
        count_array[number] -= 1;
    }

    array = result;
}

vector<double> TestSortingAlgorithms(vector<int> arr) {
    vector<int> arr_bubble_sort(arr);
    vector<int> arr_merge_sort(arr);
    vector<int> arr_count_sort(arr);
    vector<int> arr_std_sort(arr);
    vector<double> results;

    // Bubble Sort
    hr_clock::time_point t1 = hr_clock::now();
    BubbleSort(arr_bubble_sort);
    hr_clock::time_point t2 = hr_clock::now();
    auto duration = duration_cast<milliseconds>(t2 - t1).count();
    results.push_back((double)duration/1000);

    // Merge Sort
    t1 = hr_clock::now();
    MergeSort(arr_merge_sort, 0, arr_merge_sort.size()-1); // NOLINT(cppcoreguidelines-narrowing-conversions)
    t2 = hr_clock::now();
    duration = duration_cast<milliseconds>(t2 - t1).count();
    results.push_back((double)duration/1000);

    // Counting Sort
    t1 = hr_clock::now();
    CountingSort(arr_count_sort, arr_count_sort.size()); // NOLINT(cppcoreguidelines-narrowing-conversions)
    t2 = hr_clock::now();
    duration = duration_cast<milliseconds>(t2 - t1).count();
    results.push_back((double)duration/1000);

    // std::sort
    t1 = hr_clock::now();
    sort(arr_std_sort.begin(), arr_std_sort.end());
    t2 = hr_clock::now();

    duration = duration_cast<milliseconds>(t2 - t1).count();
    results.push_back((double)duration/1000);

    return results;
}

int main() {
    vector<int> random_arr;
    vector<vector<double>> test_results;

    cout << "Testing Sorting Algorithms...\n";
    for (int n = 10; n < 51; n+=5) {
        random_arr = GenerateRandomArray(n*1000);
        test_results.push_back(TestSortingAlgorithms(random_arr));
    }

    cout << "Bubble Sort:\n";
    for (auto & test_result : test_results) {
        cout << test_result[0] << "\n";
    }

    cout << "Merge Sort:\n";
    for (auto & test_result : test_results) {
        cout << test_result[1] << "\n";
    }

    cout << "Counting Sort:\n";
    for (auto & test_result : test_results) {
        cout << test_result[2] << "\n";
    }

    cout << "Standard C++ Sort(std::sort):\n";
    for (auto & test_result : test_results) {
        cout << test_result[3] << "\n";
    }

/*
    // Bubble Sort
    hr_clock::time_point t1 = hr_clock::now();
    BubbleSort(arr_bubble_sort);
    hr_clock::time_point t2 = hr_clock::now();

    auto duration = duration_cast<milliseconds>(t2 - t1).count();
    cout << "Bubble sort: Array of size " << n << " sorted in " << setprecision(2) << (double)duration/1000  << " seconds.\n";

    // Merge Sort
    t1 = hr_clock::now();
    MergeSort(arr_merge_sort, 0, arr_merge_sort.size()-1); // NOLINT(cppcoreguidelines-narrowing-conversions)
    t2 = hr_clock::now();

    duration = duration_cast<milliseconds>(t2 - t1).count();
    cout << "Merge sort: Array of size " << n << " sorted in " << setprecision(2) << (double)duration/1000  << " seconds.\n";

    // Counting Sort
    t1 = hr_clock::now();
    CountingSort(arr_count_sort, arr_count_sort.size()); // NOLINT(cppcoreguidelines-narrowing-conversions)
    t2 = hr_clock::now();

    duration = duration_cast<milliseconds>(t2 - t1).count();
    cout << "Counting sort: Array of size " << n << " sorted in " << setprecision(2) << (double)duration/1000  << " seconds.\n";

    // std::sort
    t1 = hr_clock::now();
    sort(arr_std_sort.begin(), arr_std_sort.end());
    t2 = hr_clock::now();

    duration = duration_cast<milliseconds>(t2 - t1).count();
    cout << "Standard C++ Sort(std::sort) : Array of size " << n << " sorted in " << setprecision(2) << (double)duration/1000  << " seconds.\n";
*/
    return 0;
}
