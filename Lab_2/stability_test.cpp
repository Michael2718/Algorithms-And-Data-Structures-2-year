#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

using std::vector, std::string, std::random_device, std::mt19937, std::uniform_int_distribution,
    std::sort, std::stable_sort, std::cout;


vector<int> GenerateRandomArray(int n) {
    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> dist(1, n);

    vector<int> array(n);
    for (int i = 0; i < n; i++) array[i] = dist(mt);

    return array;
}


struct {
    bool operator()(vector<int> a, vector<int> b) const { return a[0] < b[0]; }
} SortByKey;

bool isSortingStable(vector<vector<int>> array, const vector<vector<int>>& sorted_array) {
    vector<vector<int>> stable_sorted_array(std::move(array));
    stable_sort(stable_sorted_array.begin(), stable_sorted_array.end(), SortByKey);

    return stable_sorted_array == sorted_array;
}

int main() {
    int n = 20;
    string abc = "abcdefghijklmnopqrstuvwxyz";

    vector<int> random_arr = GenerateRandomArray(n);
    vector<vector<int>> arr_with_keys(n, vector<int>(2));
    vector<vector<int>> arr_with_keys_unstable_sort(arr_with_keys);
    vector<vector<int>> arr_with_keys_stable_sort(arr_with_keys);

    cout << "Random array with keys:\n";
    for (int i = 0; i < n; i++) {
        arr_with_keys[i] = {random_arr[i], abc[i % 26]};
        arr_with_keys_unstable_sort[i] = {random_arr[i], abc[i % 26]};
        arr_with_keys_stable_sort[i] = {random_arr[i], abc[i % 26]};
        cout << "(" << arr_with_keys_unstable_sort[i][0] << ", " << (char)arr_with_keys_unstable_sort[i][1] << ")\n";
    }

    cout << "\n";
    cout << "Sorted array with keys(unstable sort):\n";
    sort(arr_with_keys_unstable_sort.begin(), arr_with_keys_unstable_sort.end(), SortByKey);
    for (auto arr: arr_with_keys_unstable_sort) {
        cout << "(" << arr[0] << ", " << (char)arr[1] << ")\n";
    }

    cout << "\n";
    cout << "Sorted array with keys(stable sort):\n";
    stable_sort(arr_with_keys_stable_sort.begin(), arr_with_keys_stable_sort.end(), SortByKey);
    for (auto arr: arr_with_keys_stable_sort) {
        cout << "(" << arr[0] << ", " << (char)arr[1] << ")\n";
    }

    cout << "\n";
    cout << "Testing Stability Of Sorting Methods...\n";
    cout << "std::sort(unstable sort): "
         << (isSortingStable(arr_with_keys, arr_with_keys_unstable_sort) ? "Stable\n" : "Unstable\n");
    cout << "std::stable_sort: "
         << (isSortingStable(arr_with_keys, arr_with_keys_stable_sort) ? "Stable\n" : "Unstable\n");

    return 0;
}
