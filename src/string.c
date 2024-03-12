#include <ctype.h>
#include <stdlib.h>
#include <string.h>


#include "string.h"


str str_create_from_zstr(c8* zstring) {
    return (str) {
        .len = strlen(zstring),
        .handle = zstring,
    };
}


str str_create_from_string_slice_copy(StringSlice slice) {
    c8* zstring = malloc(sizeof(c8) * (slice.len + 1));
    *(zstring + slice.len) = 0;
    memcpy(zstring, slice.handle, slice.len);
    return (str) {
        .handle = zstring,
        .len = slice.len,
    };
}


str str_create_from_zstr_copy(c8* zstring) {
    uaddr len = strlen(zstring);
    c8* handle = malloc(sizeof(c8) * len + 1);
    memcpy(handle, zstring, len);
    *(handle + len) = 0;
    return (str) {
        .len = len,
        .handle = handle,
    };
}


void str_destroy(str string) {
    free(string.handle);
    string.handle = NULL;
}


bool str_eq(str a, str b) {
    if (a.len == b.len) {
        if (memcmp(a.handle, b.handle, a.len)) {
            return true;
        }
    }
    return false;
}


str str_join(str a, str b) {
    uaddr len = a.len + b.len;
    c8* zstring = malloc(sizeof(c8) * (len + 1));
    *(zstring + len) = 0;
    memcpy(zstring, a.handle, a.len);
    memcpy(zstring + a.len, b.handle, b.len);
    return (str) {
        .handle = zstring,
        .len = len,
    };
}


str str_recase_upper(str a) {
    c8* handle = a.handle;
    for (uaddr i = 0; i < a.len; i += 1) {
        *handle = toupper(*handle);
        handle += 1;
    }
    return a;
}


StringSlice str_cut_pre(str a, uaddr size) {
    if (a.len < size) {
        return *((StringSlice*) &a);
    } else {
        return (StringSlice) {
            .len = a.len - size,
            .handle = a.handle + size,
        };
    }
}


StringSlice str_cut_post(str a, uaddr size) {
    if (a.len < size) {
        return *((StringSlice*) &a);
    } else {
        return (StringSlice) {
            .len = a.len - size,
            .handle = a.handle,
        };
    }
}

