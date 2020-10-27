/*Copyright 2020 bu Tsimafei Smouzh*/
/*  Определить среднюю квадратическую погрешность (в мм) радиуса шара R = 10.0 м.
, если известно, что объем шара V, вычисленный по этому значению радиуса, ошибочен на mv = 1.57 м3.
*/

#include <iostream>
#include <cmath>

int main() {
double R = 10, m_R = 0, m_V = 1.6, V = 0;
V = 4.0 / 3.0*3.14*pow(R, 3);
std::cout << "V = " << V << "\n";
m_R = pow(1.0 / 36.0 / 3.14*pow(1.0 / V, 2), 1.0 / 3.0)*m_V;
std::cout << "mR = " << m_R << "\n";
std::cout << "mR = " << m_R * 1000 << "\n";
system("pause");
return 0;
}
