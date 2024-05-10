#ifndef NFLR_JSON_HELPER_H
#define NFLR_JSON_HELPER_H
// it depends on jansson
#include <jansson.h>


int get_Integer(const char *json_str, const char *field_name);

#define GET_INTEGER(json_string, target_struct, property_name) \
    do { \
        (target_struct)->property_name = get_Integer(json_string, #property_name); \
    } while (0)
#endif //NFLR_JSON_HELPER_H
