#ifndef MURMURHASH3_H
#define MURMURHASH3_H

#include <cstdint>
#include <cstddef>

#ifdef __cplusplus
extern "C" {
#endif

void MurmurHash3_x64_128(const void* key, int len, uint32_t seed, void* out);

#ifdef __cplusplus
}
#endif

#endif // MURMURHASH3_H
