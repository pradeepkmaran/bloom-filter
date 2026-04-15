#include "bloom_filter.hpp"
#include <iostream>
#include <cassert>
#include <vector>
#include <string>

void test_basic_insertion() {
    std::cout << "Running test_basic_insertion..." << std::endl;
    bloom::BloomFilter bf(1000, 0.01);
    
    bf.add("hello");
    bf.add("world");
    
    assert(bf.contains("hello") == true);
    assert(bf.contains("world") == true);
    assert(bf.contains("not-in-filter") == false);
    std::cout << "test_basic_insertion passed!" << std::endl;
}

void test_false_positive_rate() {
    std::cout << "Running test_false_positive_rate..." << std::endl;
    uint64_t n = 10000;
    double p = 0.01;
    bloom::BloomFilter bf(n, p);
    
    // Insert n elements
    for (uint64_t i = 0; i < n; ++i) {
        bf.add("key-" + std::to_string(i));
    }
    
    // Check for false positives in another n elements
    uint64_t false_positives = 0;
    for (uint64_t i = n; i < 2 * n; ++i) {
        if (bf.contains("key-" + std::to_string(i))) {
            false_positives++;
        }
    }
    
    double actual_p = static_cast<double>(false_positives) / n;
    std::cout << "Actual false positive rate: " << actual_p << " (Target: " << p << ")" << std::endl;
    
    // Standard bloom filter check: actual p should be reasonably close to p
    // We'll allow a bit of margin
    assert(actual_p < p * 2); 
    std::cout << "test_false_positive_rate passed!" << std::endl;
}

int main() {
    test_basic_insertion();
    test_false_positive_rate();
    std::cout << "All C++ tests passed!" << std::endl;
    return 0;
}
