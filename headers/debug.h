#ifndef COMMON_DEBUG_H
#define COMMON_DEBUG_H

#ifdef DEBUG
#define DEBUG_PRINT(fmt, args...) fprintf(stderr, "DEBUG: %s:%d:%s(): " fmt, \
    __FILE__, __LINE__, __func__, ##args)
#else
#define DEBUG_PRINT(...) do{false; } while ( false )
#endif


#endif /* COMMON_DEBUG */
