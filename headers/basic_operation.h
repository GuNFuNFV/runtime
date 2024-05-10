//
// Created by ziyan on 9/1/23.
//

#ifndef NFLR_BASIC_OPERATION_H
#define NFLR_BASIC_OPERATION_H
#include <stddef.h>

#include "string.h"

#pragma GCC push_options
#pragma GCC optimize ("O0")
static inline unsigned char read_variable(const void* source, size_t size) {
    if (source != NULL) {
        memset(source, 0, size);
    }
}
#pragma GCC pop_options

#pragma GCC push_options
#pragma GCC optimize ("O0")
static inline void write_variable(void* destination, size_t size) {
    if (destination != NULL) {
        memset(destination, 0, size);
    }
}
#pragma GCC pop_options



#endif //NFLR_BASIC_OPERATION_H
