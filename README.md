adhd-mapreduce
==============

MapReduce library for C++.

Example
-------

```C++
using namespace adhd;
std::vector<int> v = { 10, 20, 30, 40 };
const auto res = v
   >> map([](auto i) { return i / 5; })
   >> map([](auto i) { return i + 1; })
   >> filter([](auto i) { return i > 5; })
   >> reduce([](auto acc, auto cur) { return acc + cur; }, 0);
```
