

#ifndef NF_PLATFORM_COMMON_H
#define NF_PLATFORM_COMMON_H

#include "stdio.h"
#include "stdbool.h"
#include "stdint.h"
#include "rte_ip.h"
#include "rte_gtp.h"
#include "rte_tcp.h"
#include "rte_udp.h"
#include "rte_ether.h"
#include "rte_sctp.h"
//#include "../../nf/ngap.h"
#include "rte_hash.h"
#include "stdio.h"
#include "worker/message.h"
#include "rte_jhash.h"
#include "rte_ethdev.h"
#include "rte_malloc.h"
#include "rte_table_hash_cuckoo.h"
#include "custom_hash.h"




void DumpHex(const void *data, size_t size);

static inline void hexDump(
        const char *desc,
        const void *addr,
        const int len,
        int perLine
) {
    // Silently ignore silly per-line values.

    if (perLine < 4 || perLine > 64) perLine = 16;

    int i;
    unsigned char buff[perLine + 1];
    const unsigned char *pc = (const unsigned char *) addr;

    // Output description if given.

    if (desc != NULL) printf("%s:\n", desc);

    // Length checks.

    if (len == 0) {
        printf("  ZERO LENGTH\n");
        return;
    }
    if (len < 0) {
        printf("  NEGATIVE LENGTH: %d\n", len);
        return;
    }

    // Process every byte in the data.

    for (i = 0; i < len; i++) {
        // Multiple of perLine means new or first line (with line local_offset).

        if ((i % perLine) == 0) {
            // Only print previous-line ASCII buffer for lines beyond first.

            if (i != 0) printf("  %s\n", buff);

            // Output the local_offset of current line.

            printf("  %04x ", i);
        }

        // Now the hex code for the specific character.

        printf(" %02x", pc[i]);

        // And buffer a printable ASCII character for later.

        if ((pc[i] < 0x20) || (pc[i] > 0x7e)) // isprint() may be better.
            buff[i % perLine] = '.';
        else
            buff[i % perLine] = pc[i];
        buff[(i % perLine) + 1] = '\0';
    }

    // Pad out last line if not exactly perLine characters.

    while ((i % perLine) != 0) {
        printf("   ");
        i++;
    }

    // And print the final ASCII buffer.

    printf("  %s\n", buff);
}
#define PORTAL_PORT 4997
#define GTP_PORT 2152

enum worker_call {
    TRANSMIT = 1,
    FREE_MESSAGE = 2,
    ALLOCATE_BUFFER = 3,
    FREE_MBUF = 4

};


static uint16_t checksum(uint16_t *addr, int count) {

    register long sum = 0;

    while (count > 1) {

        sum += *(unsigned short*)addr++;
        count -= 2;

    }

    if (count > 0) {
        sum += *(unsigned char *)addr;
    }

    while (sum >> 16) {
        sum = (sum & 0xffff) + (sum >> 16);
    }

    return ~sum;
}

#endif //NF_PLATFORM_COMMON_H
