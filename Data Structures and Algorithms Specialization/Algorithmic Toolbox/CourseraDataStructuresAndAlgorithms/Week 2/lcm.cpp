#include <iostream>

long long gcd_fast(long long a, long long b) {

    if (b != 0)
        return gcd_fast(b, a % b);
    return a;

}

long long lcm_fast(long long a, long long b) {

    if (!a || !b)
        return 0;
    return (a * b) / gcd_fast(a, b);
}


int main() {

  long long a, b;
  std::cin >> a >> b;
  std::cout << lcm_fast(a, b) << std::endl;
  return 0;
}
