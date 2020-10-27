/*Copyright 2019 by Smouzh Tsimafei */

#define _USE_MATH_DEFINES
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;
int main() {
    double S1 = 50.0;
    double S2 = 60.0;
    double alpha = 100.0;
    double ma = 3.0;
    double a = 0.002;
    double b = 3.0;

    double mS1 = 0.002 + (3.0 * (50.0 / 1000.0)) / 1000.0;

      std::cout << std::setprecision(7);
      std::cout << "mS1 = " << mS1 << "\n";

    double mS2 = 0.002 + (3.0 * (60.0 / 1000.0)) / 1000.0;
      std::cout << "mS2 = " << mS2 << "\n";
    double alpha_rad = alpha * M_PI / 180;

    double denominator = sqrt(S1 * S1 + S2 * S2 - 2 * S1 * S2 * cos(alpha_rad));
    double first_derivative = (S1 - S2 * cos(alpha_rad)) / denominator;
    double second_derivative = (S2 - S1 * cos(alpha_rad)) / denominator;
    double third_derivative = -1 *S1* S2 * sin(alpha_rad) / denominator;

    double ma_rad = ma / 3600.0 * M_PI / 180;

    double mS3 = sqrt(pow(first_derivative * mS1, 2) +
      pow(second_derivative * mS2, 2) +
      pow(third_derivative * ma_rad, 2));
      std::cout << "mS3 = " << mS3 << "\n";

    return 0;
}
