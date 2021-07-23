# C++ bench for zero cost abstructions

I've added a C++ benchmark to original work using Google Benchmark for measurements.

Current result on my MacBook

```
2021-07-23T13:55:18+03:00
Running bin/cpp-bench
Run on (4 X 2600 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x2)
  L1 Instruction 32 KiB (x2)
  L2 Unified 256 KiB (x2)
  L3 Unified 3072 KiB (x1)
Load Average: 3.78, 8.93, 7.38
--------------------------------------------------------------------
Benchmark                          Time             CPU   Iterations
--------------------------------------------------------------------
sample_pair                     64.1 ns         64.0 ns     10917882
calculate_direct_index         10561 ns        10524 ns        53988
calculate_for_range            27445 ns        27245 ns        27407
calculate_ranges               82566 ns        80947 ns         9140
calculate_tranform_reduce       8266 ns         8227 ns        85861
```
