#ifndef STRING_H
#define STRING_H


#include <stdbool.h>


#include "primitives.h"


/* `str` is a NULL-delimitered char array with an attached length. */
typedef struct {
    uaddr len;
    c8* handle;
} str;


#include "string_slice.h"


#define str(STRING) (str) {   \
    .len = lengthof(STRING),  \
    .handle = STRING,         \
}


str str_create_from_zstr(c8* zstring);


str str_create_from_string_slice_copy(StringSlice slice);


str str_create_from_zstr_copy(c8* zstring);


void str_destroy(str string);


bool str_eq(str a, str b);


str str_join(str a, str b);


str str_recase_upper(str a);


StringSlice str_cut_pre(str a, uaddr size);


StringSlice str_cut_post(str a, uaddr size);


#endif

