#ifndef BLOOM_FILTER_C_H
#define BLOOM_FILTER_C_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct bloom_filter_t bloom_filter_t;

/**
 * @brief Create a new bloom filter
 */
bloom_filter_t* bloom_filter_new(uint64_t projected_elements, double false_positive_rate);

/**
 * @brief Free the bloom filter
 */
void bloom_filter_free(bloom_filter_t* bf);

/**
 * @brief Add data to the bloom filter
 */
void bloom_filter_add(bloom_filter_t* bf, const void* data, size_t len);

/**
 * @brief Check if data is in the bloom filter
 */
bool bloom_filter_check(bloom_filter_t* bf, const void* data, size_t len);

#ifdef __cplusplus
}
#endif

#endif // BLOOM_FILTER_C_H
