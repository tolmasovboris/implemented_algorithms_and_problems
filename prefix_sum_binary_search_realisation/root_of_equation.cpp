#include <iostream>
double a_koef;
double b_koef;
double c_koef;
double d_koef;
const double cDiffC = 0.000000001;
const int cPresision = 12;
double FuncBerecnen(double x) {
  return x * x * x * a_koef + x * x * b_koef + x * c_koef + d_koef;
}
int main() {
  std::cin >> a_koef >> b_koef >> c_koef >> d_koef;
  double right = 1;
  while (FuncBerecnen(-right) * FuncBerecnen(right) >= 0) {
    right *= 2;
  }
  double left = -right;
  while (right - left >= cDiffC) {
    double mid = (right + left) / 2;
    if (FuncBerecnen(mid) * FuncBerecnen(right) > 0) {
      right = mid;
    } else {
      left = mid;
    }
  }
  std::cout << std::fixed;
  std::cout.precision(cPresision);
  std::cout << left;
}
