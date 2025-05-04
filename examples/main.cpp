#include "tagged_t.h"
#include <algorithm>
#include <iostream>
#include <vector>

MAKE_TAGGED(Meters, double);
MAKE_TAGGED(Seconds, double);

int main() {
  Meters d1{3.5}, d2{2.1};
  Seconds t1{1.2}, t2{4.8};

  auto d3 = d1 + d2; // 5.6 meters
  auto t3 = t2 - t1; // 3.6 seconds

  std::cout << "d1 + d2 = " << d3 << " m\n";
  std::cout << "t2 - t1 = " << t3 << " s\n";

  // mixed comparators won’t compile:
  // if (d1 < t1) { … }

  // but same-tag comparisons work:
  if (d2 < d1) {
    std::cout << d2 << " is less than " << d1 << "\n";
  }

  // range algorithms
  std::vector<Meters> distances{d1, d2, d3};
  std::sort(distances.begin(), distances.end());
  std::cout << "sorted distances:";
  for (auto& d : distances)
    std::cout << ' ' << d;
  std::cout << '\n';

  // swap
  swap(d1, d2);
  std::cout << "after swap, d1=" << d1 << ", d2=" << d2 << "\n";

  return 0;
}
