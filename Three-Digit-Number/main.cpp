#include <iostream>
#include <iomanip>
#include <chrono>
#include <vector>

using std::cout, std::cin, std::setprecision, std::chrono::duration_cast, std::chrono::microseconds,
        std::vector;

using hr_clock = std::chrono::high_resolution_clock;


void Build_BruteForce(int m) {
    cout << "Found numbers, using bruteforce(m=" << m << "):\n";
    if(m > 0 && m <= 27) {
        for(int i = 1; i < 10; i++)
            for(int j = 0; j < 10; j++)
                for(int k = 0; k < 10; k++) {
                    if(i + j + k == m)
                        cout << (i * 100 + j * 10 + k) << "\n";
                }
    }
    cout << "\n";
}

void Build_Optimized(int m){
    cout << "Found numbers, using optimized algorithm(m=" << m << "):\n";
    if(m > 0 && m <= 27) {
        int highi = m < 9 ? m + 1 : 10;
        for(int i = m < 20 ? 1: m - 18; i < highi; i++) {
            int sumTwoLastDigits = m - i,
                highj = sumTwoLastDigits < 9 ? sumTwoLastDigits + 1 : 10;
            for(int j = sumTwoLastDigits < 10 ? 0 : sumTwoLastDigits - 9; j < highj; j++) {
                cout << (i * 100 + j * 10 + sumTwoLastDigits - j) << "\n";
            }
        }
    }
    cout << "\n";
}

int main() {
    vector<vector<double>> durations(27, vector<double>(2));
    for (int m = 1; m < 28; m++) {
        hr_clock::time_point t1 = hr_clock::now();
        Build_BruteForce(m);
        hr_clock::time_point t2 = hr_clock::now();

        auto duration = duration_cast<microseconds>(t2 - t1).count();
        durations[m-1][0] = (double)duration/10000;

        t1 = hr_clock::now();
        Build_Optimized(m);
        t2 = hr_clock::now();

        duration = duration_cast<microseconds>(t2 - t1).count();
        durations[m-1][1] = (double)duration/10000;
    }

    cout << "Durations of bruteforce algorithm for all possible m's:\n";
    for (int i = 0; i < 27; i++) {
        cout << durations[i][0] << " ";
        cout << "\n";
    }
    cout << "\n";

    cout << "Durations of optimized algorithm for all possible m's:\n";
    for (int i = 0; i < 27; i++) {
        cout << durations[i][1] << " ";
        cout << "\n";
    }
    cout << "\n";

//    cout << "Found all numbers in " << setprecision(2) << (double)duration1/10000  << " seconds, using bruteforce algorithm.\n";
//    cout << "Found all numbers in " << setprecision(2) << (double)duration2/10000  << " seconds, using optimized algorithm.\n";

    return 0;
}