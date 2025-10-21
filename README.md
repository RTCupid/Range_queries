<div align="center">
  
  # Solving the Range Query Problem in C++ Using a Red-Black Tree
  ![C++](https://img.shields.io/badge/C++-23-blue?style=for-the-badge&logo=cplusplus)
  ![CMake](https://img.shields.io/badge/CMake-3.20+-green?style=for-the-badge&logo=cmake)
  ![Testing](https://img.shields.io/badge/Google_Test-Framework-red?style=for-the-badge&logo=google)

</div>

## Check [Contribution Guidelines](contribution_guidelines.md)

## Other Languages

1. [Russian](/README-R.md)
2. [English](/README.md)

## Content
- [1. Installation and Build](#installation-and-build)
- [2. Task Range Queries](#task-range-queries)
- [3. Introduction](#introduction)
- [4. Implementation of Red-Black Tree](#implementation-of-red-black-tree)
- [5. Project structure](#project-structure)
- [6. Requirements](#requirements)
- [7. Project Creators](#project-creators)

## Installation and Build:

To install, compile, and run enter:
```bash
git clone git@github.com:RTCupid/Range_queries.git
cd Range_queries
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cd build
cmake --build .
./Range_queries
```
To run unit tests, enter:
```bash
ctest
```

If you want a debug build, enter:
```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cd build
cmake --build .
./Range_queries
```

The following cmake flags are implemented for selecting the data structure and measuring the operating time
| Flag          | Type / Values                   | Default | Purpose                                                     | Effect in Code                                                                        |
| ------------- | ------------------------------- | ------- | ----------------------------------------------------------- | ------------------------------------------------------------------------------------- |
| `RB_TREE_RUN` | bool: `ON`/`OFF` or macro `0/1` | `ON`    | Enables the implementation based on a custom Red-Black tree | Compiles and executes code sections under `#if RB_TREE_RUN`     |
| `STD_SET_RUN` | bool: `ON`/`OFF` or macro `0/1` | `OFF`   | Enables the implementation using `std::set`                 | Compiles and executes code sections under `#if STD_SET_RUN`     |
| `TIMING_RUN`  | bool: `ON`/`OFF` or macro `0/1` | `ON`    | Enables timing output (performance measurement)             | Activates timing-related output or logic under `#if TIMING_RUN` |


## Task Range Queries

- `Range queries` are convenient for using with data stored in a tree.
- Let the input be `keys` (each `key` is an integer, all `keys`
different) and `queries` (each `query` is a pair of two integers, the second
greater than the first).
- For each `query`, we need to count the number of `keys` in the tree such that all of them lie strictly between its left and right boundaries, inclusive.
- Input: k 10 k 20 q 8 31 q 6 9 k 30 k 40 q 15 40.
- Result: 2 0 3.

## Introduction
`Range queries` are essential operations in `modern computing`, widely used in `databases`, `financial systems`, and `data analytics`. They help find records within specific value ranges, like customers with purchases between $100 and $500 or transactions within certain amounts for fraud detection. These systems require efficient handling of constantly changing data.

A simple solution stores keys in an array and checks each element during queries. However, this approach becomes very slow with large datasets, as processing time grows exponentially. This makes it unsuitable for real-time applications.

A better solution uses `Red-Black Trees` - self-balancing binary search trees that maintain efficient operations through color rules and rotations. Each node can store subtree size, enabling range queries in logarithmic time instead of linear time. This provides significant performance improvements for large-scale systems.

## Implementation of Red-Black Tree

## Project structure

## Requirements
- C++23 or later
- CMake 3.20+
- Google Test (for testing)
- Graphviz (optional, for visualization)

## Project Creators

<div align="center">

  <a href="https://github.com/RTCupid">
    <img src="https://raw.githubusercontent.com/BulgakovDmitry/3D_triangles/main/img/A.jpeg" width="160" height="160" style="border-radius: 50%;">
  </a>
  <a href="https://github.com/BulgakovDmitry">
    <img src="https://raw.githubusercontent.com/BulgakovDmitry/3D_triangles/main/img/D.jpeg" width="160" height="160" style="border-radius: 50%;">
  </a>
  <br>
  <a href="https://github.com/RTCupid"><strong>@RTCupid, </strong></a>
  <a href="https://github.com/BulgakovDmitry"><strong>@BulgakovDmitry</strong></a>
  <br>
</div>
