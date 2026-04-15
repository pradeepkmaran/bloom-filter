#include "bloom_filter_c.h"
#include "bloom_filter.hpp"

extern "C" {

struct bloom_filter_t {
    bloom::BloomFilter* bf;
};

bloom_filter_t* bloom_filter_new(uint64_t projected_elements, double false_positive_rate) {
    bloom_filter_t* wrapper = new bloom_filter_t;
    wrapper->bf = new bloom::BloomFilter(projected_elements, false_positive_rate);
    return wrapper;
}

void bloom_filter_free(bloom_filter_t* bf) {
    if (bf) {
        delete bf->bf;
        delete bf;
    }
}

void bloom_filter_add(bloom_filter_t* bf, const void* data, size_t len) {
    if (bf && bf->bf) {
        bf->bf->add(data, len);
    }
}

bool bloom_filter_check(bloom_filter_t* bf, const void* data, size_t len) {
    if (bf && bf->bf) {
        return bf->bf->contains(data, len);
    }
    return false;
}

}
