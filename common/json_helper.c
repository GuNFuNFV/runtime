
#include "json_helper.h"


int get_Integer(const char *json_str, const char *field_name) {
    json_error_t error;
    json_t *root;
    json_t *field;

    root = json_loads(json_str, 0, &error);

    if (!root) {
        fprintf(stderr, "Error: on line %d: %s\n", error.line, error.text);
        return -1;
    }

    if (!json_is_object(root)) {
        fprintf(stderr, "Error: root is not a JSON object\n");
        json_decref(root);
        return -1;
    }

    field = json_object_get(root, field_name);

    if (!json_is_integer(field)) {
        fprintf(stderr, "Error: %s is not an integer field\n", field_name);
        json_decref(root);
        return -1;
    }

    long long result = json_integer_value(field);

    json_decref(root);

    return (int)result;
}