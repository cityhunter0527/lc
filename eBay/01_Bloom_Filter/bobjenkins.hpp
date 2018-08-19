#ifndef  _BOB_JENKINS_HASH_H_
#define  _BOB_JENKINS_HASH_H_

#include <stdio.h>      /* defines printf for tests */
#include <stdint.h>     /* defines uint32_t etc */

uint32_t hashlittle(const uint8_t *key, size_t length, uint32_t initval);
#endif
