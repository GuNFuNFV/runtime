
/*
<https://github.com/rafagafe/tiny-json>
     
  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
  Copyright (c) 2016-2018 Rafa Garcia <rafagarcia77@gmail.com>.
  Permission is hereby  granted, free of charge, to any  person obtaining a copy
  of this software and associated  documentation files (the "Software"), to deal
  in the Software  without restriction, including without  limitation the rights
  to  use, copy,  modify, merge,  publish, distribute,  sublicense, and/or  sell
  copies  of  the Software,  and  to  permit persons  to  whom  the Software  is
  furnished to do so, subject to the following conditions:
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
  THE SOFTWARE  IS PROVIDED "AS  IS", WITHOUT WARRANTY  OF ANY KIND,  EXPRESS OR
  IMPLIED,  INCLUDING BUT  NOT  LIMITED TO  THE  WARRANTIES OF  MERCHANTABILITY,
  FITNESS FOR  A PARTICULAR PURPOSE AND  NONINFRINGEMENT. IN NO EVENT  SHALL THE
  AUTHORS  OR COPYRIGHT  HOLDERS  BE  LIABLE FOR  ANY  CLAIM,  DAMAGES OR  OTHER
  LIABILITY, WHETHER IN AN ACTION OF  CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE  OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
    
*/

#ifndef _TINY_JSON_H_
#define	_TINY_JSON_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#define json_containerOf( ptr, type, member ) \
    ((type*)( (char*)ptr - offsetof( type, member ) ))

/** @defgroup tinyJson Tiny JSON parser.
  * @{ */

/** Enumeration of codes of supported JSON properties types. */
typedef enum {
    JSON_OBJ, JSON_ARRAY, JSON_TEXT, JSON_BOOLEAN,
    JSON_INTEGER, JSON_REAL, JSON_NULL
} jsonType_t;

/** Structure to handle JSON properties. */
typedef struct json_s {
    struct json_s* sibling;
    char const* name;
    union {
        char const* value;
        struct {
            struct json_s* child;
            struct json_s* last_child;
        } c;
    } u;
    jsonType_t type;
} json_t;

/** Parse a string to get a json.
  * @param str String pointer with a JSON object. It will be modified.
  * @param mem Array of json properties to allocate.
  * @param qty Number of elements of mem.
  * @retval Null pointer if any was wrong in the parse process.
  * @retval If the parser process was successfully a valid handler of a json.
  *         This property is always unnamed and its type is JSON_OBJ. */
json_t const* json_create( char* str, json_t mem[], unsigned int qty );

/** Get the name of a json property.
  * @param json A valid handler of a json property.
  * @retval Pointer to null-terminated if property has name.
  * @retval Null pointer if the property is unnamed. */
static inline char const* json_getName( json_t const* json ) {
    return json->name;
}

/** Get the value of a json property.
  * The type of property cannot be JSON_OBJ or JSON_ARRAY.
  * @param property A valid handler of a json property.
  * @return Pointer to null-terminated string with the value. */
static inline char const* json_getValue( json_t const* property ) {
    return property->u.value;
}

/** Get the type of a json property.
  * @param json A valid handler of a json property.
  * @return The code of type.*/
static inline jsonType_t json_getType( json_t const* json ) {
    return json->type;
}

/** Get the next sibling of a JSON property that is within a JSON object or array.
  * @param json A valid handler of a json property.
  * @retval The handler of the next sibling if found.
  * @retval Null pointer if the json property is the last one. */
static inline json_t const* json_getSibling( json_t const* json ) {
    return json->sibling;
}

/** Search a property by its name in a JSON object.
  * @param obj A valid handler of a json object. Its type must be JSON_OBJ.
  * @param property The name of property to get.
  * @retval The handler of the json property if found.
  * @retval Null pointer if not found. */
json_t const* json_getProperty( json_t const* obj, char const* property );


/** Search a property by its name in a JSON object and return its value.
  * @param obj A valid handler of a json object. Its type must be JSON_OBJ.
  * @param property The name of property to get.
  * @retval If found a pointer to null-terminated string with the value.
  * @retval Null pointer if not found or it is an array or an object. */
char const* json_getPropertyValue( json_t const* obj, char const* property );

/** Get the first property of a JSON object or array.
  * @param json A valid handler of a json property.
  *             Its type must be JSON_OBJ or JSON_ARRAY.
  * @retval The handler of the first property if there is.
  * @retval Null pointer if the json object has not properties. */
static inline json_t const* json_getChild( json_t const* json ) {
    return json->u.c.child;
}

/** Get the value of a json boolean property.
  * @param property A valid handler of a json object. Its type must be JSON_BOOLEAN.
  * @return The value stdbool. */
static inline bool json_getBoolean( json_t const* property ) {
    return *property->u.value == 't';
}

/** Get the value of a json integer property.
  * @param property A valid handler of a json object. Its type must be JSON_INTEGER.
  * @return The value stdint. */
static inline int64_t json_getInteger( json_t const* property ) {
    return strtoll( property->u.value,(char**)NULL, 10);
}

/** Get the value of a json real property.
  * @param property A valid handler of a json object. Its type must be JSON_REAL.
  * @return The value. */
static inline double json_getReal( json_t const* property ) {
    return strtod( property->u.value,(char**)NULL );
}



/** Structure to handle a heap of JSON properties. */
typedef struct jsonPool_s jsonPool_t;
struct jsonPool_s {
    json_t* (*init)( jsonPool_t* pool );
    json_t* (*alloc)( jsonPool_t* pool );
};

/** Parse a string to get a json.
  * @param str String pointer with a JSON object. It will be modified.
  * @param pool Custom json pool pointer.
  * @retval Null pointer if any was wrong in the parse process.
  * @retval If the parser process was successfully a valid handler of a json.
  *         This property is always unnamed and its type is JSON_OBJ. */
json_t const* json_createWithPool( char* str, jsonPool_t* pool );

static void dump( json_t const* json ) {

    jsonType_t const type = json_getType( json );
    if ( type != JSON_OBJ && type != JSON_ARRAY ) {
        puts("error");
        return;
    }

    printf( "%s", type == JSON_OBJ? " {": " [" );

    json_t const* child;
    for( child = json_getChild( json ); child != 0; child = json_getSibling( child ) ) {

        jsonType_t propertyType = json_getType( child );
        char const* name = json_getName( child );
        if ( name ) printf(" \"%s\": ", name );

        if ( propertyType == JSON_OBJ || propertyType == JSON_ARRAY )
            dump( child );

        else {
            char const* value = json_getValue( child );
            if ( value ) {
                bool const text = JSON_TEXT == json_getType( child );
                char const* fmt = text? " \"%s\"": " %s";
                printf( fmt, value );
                bool const last = !json_getSibling( child );
                if ( !last ) putchar(',');
            }
        }
    }

    printf( "%s", type == JSON_OBJ? " }": " ]" );

}
//
typedef struct {
    json_t mem[1000];
    unsigned int nextFree;
    jsonPool_t pool;
} _jsonStaticPool_t;

static json_t *poolInit(jsonPool_t *pool) {
    _jsonStaticPool_t *spool = json_containerOf(pool, _jsonStaticPool_t, pool);
    spool->nextFree = 1;
    return &spool->mem[0];
}

static json_t *poolAlloc(jsonPool_t *pool) {
    _jsonStaticPool_t *spool = json_containerOf(pool, _jsonStaticPool_t, pool);
    if (spool->nextFree >= sizeof spool->mem / sizeof spool->mem[0]) return 0;
    return &spool->mem[spool->nextFree++];
}
/** @ } */
#define EXTRACT_JSON_INT_PROPERTY(json_obj, target_struct, property_name) \
    do { \
        json_t const *temp_property = json_getProperty((json_obj), #property_name); \
        if (temp_property) {                                              \
            (target_struct)->property_name = json_getInteger(temp_property); \
        } \
    } while (0)


// replace repetetive code
#define CREATE_JSON                                             \
    do {                                                        \
        _jsonStaticPool_t spool = {.pool = {.init = poolInit,   \
                                             .alloc = poolAlloc}}; \
        json_t const *json = json_createWithPool(config, &spool.pool); \
        if (!json) {                                            \
            DEBUG_PRINT("json_createWithPool failed\n");        \
            return NULL;                                        \
        }                                                       \
    } while (0)


json_t const *create_json(char* config);
#ifdef __cplusplus
}
#endif

#endif	/* _TINY_JSON_H_ */