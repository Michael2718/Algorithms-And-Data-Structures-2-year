#include <iostream>
#include <cmath>
#include <iomanip>
#include <chrono>
#include <vector>

using std::cout, std::cin, std::sin, std::setprecision, std::chrono::duration_cast, std::chrono::milliseconds,
    std::vector;

using hr_clock = std::chrono::high_resolution_clock;

double** create_matrix(int n, double phi, double mu) {
    auto** matrix = new double *[n];

    for(int i = 0; i < n; i++) {
        matrix[i] = new double [n];
        for (int j = 0; j < n; j++) {
            matrix[i][j] = pow(2.0, i * 1.0) / pow(i - 2.5, pow(i, 2)) *
                    (2 - pow(j -5, 2)) * sin(phi/(pow(mu, 2*i)));
        }
    }

    return matrix;
}

double** create_matrix_cleaned(int n, double phi, double mu) {
    auto** matrix = new double *[n];
    double first_part, second_part, third_part, raised_two = 0.5;
    for(int i = 0; i < n; i++) {
        matrix[i] = new double [n];
        first_part = (raised_two * 2) / pow(i - 2.5, pow(i, 2));
        raised_two *= 2;
        third_part = sin(phi/(pow(mu*mu, i)));
        for (int j = 0; j < n; j++) {
            second_part = 2 - (j-5)*(j-5); // (2 - pow(j -5, 2)) | (-j*j + 10*j - 23) | 2 - (j-5)*(j-5)
            matrix[i][j] = first_part * second_part * third_part;
        }
    }

    return matrix;
}

int main() {
    cout << "Enter size of matrix: ";
    int n;
    cin >> n;
    double phi = 42, mu = -1.5;

    hr_clock::time_point t1 = hr_clock::now();
    double** matrix1 = create_matrix(n, phi, mu);
    hr_clock::time_point t2 = hr_clock::now();

    auto duration = duration_cast<milliseconds>(t2 - t1).count();

    cout << "Square Matrix of size " << n << " created in " << setprecision(2) << (double)duration/1000  << " seconds.\n";


    t1 = hr_clock::now();
    double** matrix2 = create_matrix_cleaned(n, phi, mu);
    t2 = hr_clock::now();

    duration = duration_cast<milliseconds>(t2 - t1).count();

    cout << "Square Matrix of size " << n << " created in " << setprecision(2) << (double)duration/1000 << " seconds"
         << " with cleaned function.";


    for (int i = 0; i < n; i++) delete [] matrix1[i];
    for (int i = 0; i < n; i++) delete [] matrix2[i];
    delete [] matrix1;
    delete [] matrix2;
    return 0;
}