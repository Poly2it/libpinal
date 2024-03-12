#ifndef STRING_SLICE_H
#define STRING_SLICE_H


#include <stdbool.h>


#include "primitives.h"


/* `StringSlice` is a char array created from `str` structs. */
typedef struct {
    uaddr len;
    c8* handle;
} StringSlice;


#include "string.h"


#define str_slice(STRING) (StringSlice) {  \
    .len = lengthof(STRING),               \
    .handle = STRING,                      \
}


StringSlice string_slice_create_from_str(str a);


StringSlice string_slice_recase_upper(StringSlice a);


bool string_slice_eq(StringSlice a, StringSlice b);


StringSlice string_slice_cut_pre(StringSlice a, uaddr size);


StringSlice string_slice_cut_post(StringSlice a, uaddr size);


#endif

