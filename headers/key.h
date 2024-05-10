
#ifndef NFLAMBDA_RUNTIME_KEY_H
#define NFLAMBDA_RUNTIME_KEY_H
#include "stdint.h"
struct five_tuple {
    uint32_t src_ip;
    uint32_t dst_ip;
    uint16_t src_port;
    uint16_t dst_port;
//    uint8_t proto;
} __attribute__((packed));


#endif //NFLAMBDA_RUNTIME_KEY_H
