# tagged_t

Header file for strongly typed `typedef`'s through tagged (phantom) types

# Example

```cpp
MAKE_TAGGED(Meters, double)
MAKE_TAGGED(Seconds, double)

int main() {
  Meters d1{3.5}, d2{2.1};
  Seconds t1{1.2}, t2{4.8};

  // arithmetic
  auto d3 = d1 + d2; // 5.6 meters
  auto t3 = t2 - t1; // 3.6 seconds

  std::cout << "d1 + d2 = " << d3 << " m\n"; // 5.6
  std::cout << "t2 - t1 = " << t3 << " s\n"; // 3.6
}
```
