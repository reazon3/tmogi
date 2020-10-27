/*Copyright 2020 by Tsimafei Smouzh*/
/*  Отметки двух точек  Н1 = 104.427 ± 0.005 м и Н2 = 108.283 ± 0.007 м а измеренная наклонная длина между ними D = 153.54 ± 0.06 м.
 Вычислить знаменатель относительной средней квадратической погрешности уклона по линии.
*/
#include <iostream>
#include <cmath>
int main() {
double H1 = 104.427;
double mh1 = 0.005;
double H2 = 108.283;
double mh2 = 0.007;
double D = 153.540;
double md = 0.06;
double i =(H2 - H1) / (D*sqrt(1 - (pow(H2 - H1, 2) / pow(D, 2))));
std::cout.precision(2);
std::cout << "i=" << i << "\n";
double  mdH2 = pow(D, 2) /
pow(sqrt(pow(D, 2) - pow(H2 - H1, 2)),3);
double  mdH1 = (-pow(D, 2)) /
pow(sqrt((pow(D, 2) - pow(H2-H1, 2))), 3);
double  mdD = (-D * (H2 - H1)) /
pow(sqrt(pow(D, 2) - pow(H2 - H1, 2)), 3);
std::cout << "mdH2=" << mdH2 << "\n";
std::cout << "mdH1=" << mdH1 << "\n";
std::cout << "mdD=" << mdD << "\n";
double mi = sqrt(pow(mdH2, 2)*pow(mh2, 2) +
pow(mdH1, 2) * pow(mh1, 2) + pow(mdD, 2) * pow(md, 2));
std::cout.precision(5);
std::cout << "mi=" << mi << "\n";
double T = (i / mi);
std::cout << "T=" << T << "\n";
system("pause");
return 0;
}
