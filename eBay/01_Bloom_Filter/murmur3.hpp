#ifndef _MURMURHASH3_H_
#define _MURMURHASH3_H_

#include <stdint.h>
#include <stdio.h>

uint32_t murmur3_32(const uint8_t* key, size_t len, uint32_t seed);


#endif
