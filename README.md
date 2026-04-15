# Bloom Filter Library

A high-performance, modular, and exportable Bloom Filter implementation in C++17 with a C-compatible API for cross-language FFI integration.

## Features
- **Efficient**: Uses MurmurHash3 and Double-Hashing (Kirsch-Mitzenmacher optimization).
- **Modular**: Build as both static (`.a`) and shared (`.so`) libraries.
- **Cross-Language**: Exposes a standard C API for use in Python, Go, Rust, Java, etc.
- **CMake Integrated**: Supports `find_package(BloomFilter)` for easy C++ integration.
- **Dockerized**: Build and test in an isolated environment.

## Directory Structure
- `include/`: Header files (`.hpp` for C++, `.h` for C).
- `src/`: Implementation files.
- `tests/`: C++ unit tests.
- `wrappers/`: Language-specific FFI wrappers (e.g., Python).
- `cmake/`: CMake configuration templates.

## Quick Start (Local)

### Build
```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j$(nproc)
```

### Run Tests
```bash
./test_bloom
```

## Usage

### C++ Example
```cpp
#include "bloom_filter.hpp"

bloom::BloomFilter bf(1000000, 0.01); // 1M elements, 1% FPR
bf.add("some-key");
if (bf.contains("some-key")) {
    // Possibly exists
}
```

### C / FFI Example
```c
#include "bloom_filter_c.h"

bloom_filter_t* bf = bloom_filter_new(1000000, 0.01);
bloom_filter_add(bf, "key", 3);
if (bloom_filter_check(bf, "key", 3)) {
    // Possibly exists
}
bloom_filter_free(bf);
```

### Python Example
See `wrappers/python/bloom_filter.py` for a full `ctypes` implementation.

## Docker
Build and run tests in Docker:
```bash
docker build -t bloom-filter .
docker run --rm bloom-filter
```

## Installation
To install the library on your system:
```bash
cd build
sudo make install
```
Then use it in other projects via CMake:
```cmake
find_package(BloomFilter REQUIRED)
target_link_libraries(your_app BloomFilter::bloom_filter_shared)
```
