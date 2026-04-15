#ifndef BLOOM_FILTER_HPP
#define BLOOM_FILTER_HPP

#include <vector>
#include <string>
#include <cmath>
#include <cstdint>
#include <memory>
#include "MurmurHash3.h"

namespace bloom {

class BloomFilter {
public:
    /**
     * @brief Construct a new Bloom Filter object
     * 
     * @param projected_elements Expected number of elements to be stored
     * @param false_positive_rate Desired probability of false positives (0.0 to 1.0)
     */
    BloomFilter(uint64_t projected_elements, double false_positive_rate) {
        // m = -(n * ln(p)) / (ln(2)^2)
        uint64_t num_bits = static_cast<uint64_t>(-static_cast<double>(projected_elements) * std::log(false_positive_rate) / std::pow(std::log(2), 2));
        
        // k = (m / n) * ln(2)
        num_hashes_ = static_cast<uint32_t>(std::round(static_cast<double>(num_bits) / projected_elements * std::log(2)));
        if (num_hashes_ == 0) num_hashes_ = 1;

        // Round up bits to nearest 64 to use uint64_t vector
        size_t num_words = (num_bits + 63) / 64;
        bits_.resize(num_words, 0);
        bit_count_ = num_words * 64;
    }

    /**
     * @brief Add a key to the bloom filter
     */
    void add(const std::string& key) {
        add(key.data(), key.size());
    }

    void add(const void* data, size_t len) {
        uint64_t hashes[2];
        MurmurHash3_x64_128(data, static_cast<int>(len), 0, hashes);

        uint64_t h1 = hashes[0];
        uint64_t h2 = hashes[1];

        for (uint32_t i = 0; i < num_hashes_; ++i) {
            uint64_t combined_hash = h1 + static_cast<uint64_t>(i) * h2;
            uint64_t pos = combined_hash % bit_count_;
            bits_[pos / 64] |= (1ULL << (pos % 64));
        }
    }

    /**
     * @brief Check if a key might be in the bloom filter
     */
    bool contains(const std::string& key) const {
        return contains(key.data(), key.size());
    }

    bool contains(const void* data, size_t len) const {
        uint64_t hashes[2];
        MurmurHash3_x64_128(data, static_cast<int>(len), 0, hashes);

        uint64_t h1 = hashes[0];
        uint64_t h2 = hashes[1];

        for (uint32_t i = 0; i < num_hashes_; ++i) {
            uint64_t combined_hash = h1 + static_cast<uint64_t>(i) * h2;
            uint64_t pos = combined_hash % bit_count_;
            if (!(bits_[pos / 64] & (1ULL << (pos % 64)))) {
                return false;
            }
        }
        return true;
    }

    // Accessors for serialization
    const std::vector<uint64_t>& data() const { return bits_; }
    uint32_t num_hashes() const { return num_hashes_; }
    uint64_t bit_count() const { return bit_count_; }

private:
    std::vector<uint64_t> bits_;
    uint32_t num_hashes_;
    uint64_t bit_count_;
};

} // namespace bloom

#endif // BLOOM_FILTER_HPP
