# Solving the Range Query Problem in C++ Using a Red-Black Tree

<div align="center">

![C++](https://img.shields.io/badge/C++-23-blue?style=for-the-badge&logo=cplusplus)
![CMake](https://img.shields.io/badge/CMake-3.20+-green?style=for-the-badge&logo=cmake)
![Testing](https://img.shields.io/badge/Google_Test-Framework-red?style=for-the-badge&logo=google)

</div>

## Check the [Contribution Guidelines](contribution_guidelines.md)

## Other Languages

1. [Russian](/README-R.md)
2. [English](/README.md)

## Contents
- [1. Installation and Build](#installation-and-build)
- [2. Range Query Task](#range-query-task)
- [3. Introduction](#introduction)
- [4. Red-Black Tree Implementation](#red-black-tree-implementation)
- [5. Project Structure](#project-structure)
- [6. Requirements](#requirements)
- [7. Project Authors](#project-authors)

## Installation and Build

To install, compile, and run:
```bash
git clone git@github.com:RTCupid/Range_queries.git
cd Range_queries
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cd build
cmake --build .
./Range_queries
```

To run unit tests:
```bash
ctest
```

The tests include 2 categories (unit and end_to_end).
To run them separately:
```bash
ctest -L unit
ctest -L end_to_end
```

A generator is provided for creating end-to-end tests (path: ./build/tests/end_to_end/generator).
Generated tests will be executed in end_to_end testing.
Run the generator with:
```bash
./generator [tests per file] [number of files]
```

For debug build:
```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cd build
cmake --build .
./Range_queries
```

## Range Query Task

- Range queries are efficient when data is stored in a tree.
- The input contains `keys` (all integers, unique) and `queries` (two integers per query, the second greater than the first).
- For each query, count how many keys lie strictly between its boundaries, inclusive.
- Example input: `k 10 k 20 q 8 31 q 6 9 k 30 k 40 q 15 40`
- Output: `2 0 3`

## Introduction

Range queries are an essential operation in modern computing, widely used in databases, financial systems, and data analytics. They allow identifying records within specific value ranges — such as customers with purchases between $100 and $500 or transactions within thresholds for fraud detection. These systems require efficient processing of constantly changing data.

A naive solution uses an array and scans it for every query. However, that becomes slow with large datasets, because processing time grows linearly. This makes such approaches unsuitable for real-time systems.

A more efficient approach uses **Red-Black Trees** — self-balancing binary search trees that maintain performance through rotations and recoloring. Each node can store the size of its subtree, enabling range queries in logarithmic time.

## Red-Black Tree Implementation

This project implements a custom Red-Black Tree supporting efficient insertion, lookup, and range queries. Logarithmic performance is ensured through strict balancing rules.

### Key Features

- Full control over data structure (no std::set).
- Subtree sizes stored in each node for O(log n) range queries.
- Full implementation of classic Red-Black Tree balancing rules.

### Main Implementation Files

#### node.hpp
Defines the node structure:
- key  
- color (red/black)  
- parent/child pointers  
- subtree size (`size_`)  

#### tree.hpp
Defines the main `RB_tree` class:
- insertion with fix-up  
- search  
- subtree size updates  
- public container-like interface  

#### iterator.hpp
Bidirectional C++-style iterator:
- next/previous  
- comparison  
- dereference  

#### range_query.hpp
Implements logic for handling:
```bash
q L R
```

### CMake Flags

| Flag              | Values | Default | Purpose | Effect |
|-------------------|--------|---------|---------|--------|
| RB_TREE_RUN       | ON/OFF | ON      | Enables custom Red-Black Tree | `#ifdef RB_TREE_RUN` |
| STD_SET_RUN       | ON/OFF | OFF     | Enables std::set backend | `#ifdef STD_SET_RUN` |
| RB_TREE_LOG_RUN   | ON/OFF | OFF     | Enables log_distance optimization | `#ifdef RB_TREE_LOG_RUN` |
| TIMING_RUN        | ON/OFF | OFF     | Enables execution time measurement | `#ifdef TIMING_RUN` |

### Targets

| Target | Description | Flags |
|--------|-------------|--------|
| Range_queries_rb_tree | Main RB-tree implementation | RB_TREE_RUN |
| Range_queries_rb_tree_time | RB-tree with timing | RB_TREE_RUN, TIMING_RUN |
| Range_queries_std_set | std::set version | STD_SET_RUN |
| Range_queries_std_set_time | std::set with timing | STD_SET_RUN, TIMING_RUN |
| Range_queries_rb_tree_log | RB-tree with log_distance | RB_TREE_LOG_RUN |
| Range_queries_rb_tree_log_time | log_distance + timing | RB_TREE_LOG_RUN, TIMING_RUN |

## Project Structure
```txt
Range_queries/
├── CMakeLists.txt
├── include
│   ├── iterator.hpp
│   ├── node.hpp
│   ├── range_query.hpp
│   └── tree.hpp
├── README.md
├── README-R.md
├── contribution_guidelines.md
├── src
│   └── main.cpp
└── tests
    ├── CMakeLists.txt
    ├── end_to_end
    └── unit
```

## Requirements
- C++23 or newer  
- CMake 3.20+  
- Google Test  
- Graphviz (optional)

## Project Authors

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
