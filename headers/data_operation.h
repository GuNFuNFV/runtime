

#ifndef NFLAMBDA_RUNTIME_DATA_OPERATION_H
#define NFLAMBDA_RUNTIME_DATA_OPERATION_H
#include "stdint.h"
#include "stddef.h"
#include "string.h"

static inline void increment_n_byte_data(void* data, size_t n){
    // data is a pointer to the data
    // n is the size of the data
    // we need to increment the data by 1
    // if the data is 0xff, we need to set it to 0x00
    // and increment the next byte
    // if the data is 0x00, we need to set it to 0x01

    // get the last byte
    uint8_t* last_byte = (uint8_t*)data + n - 1;
    int current_byte = n - 1;
    // use while loop to increment the data
    while(*last_byte == 0xff){
        *last_byte = 0x00;
        last_byte--;
        current_byte--;
        if (current_byte < 0){
            // end of the data
            return;
        }
    }
    *last_byte = *last_byte + 1;
}

static inline void set_zero_n_byte_data(void *data, size_t n){
    // set the data to 0x00
    // data is a pointer to the data
    // n is the size of the data
    memset(data, 0x00, n);
}


#endif //NFLAMBDA_RUNTIME_DATA_OPERATION_H
