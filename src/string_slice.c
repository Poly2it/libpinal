#include <ctype.h>
#include <string.h>


#include "string_slice.h"


StringSlice string_slice_create_from_str(str a) {
    return *((StringSlice*) &a);
}


StringSlice string_slice_recase_upper(StringSlice a) {
    c8* handle = a.handle;
    for (uaddr i = 0; i < a.len; i += 1) {
        *handle = toupper(*handle);
        handle += 1;
    }
    return a;
}


bool string_slice_eq(StringSlice a, StringSlice b) {
    if (a.len == b.len) {
        if (memcmp(a.handle, b.handle, a.len)) {
            return true;
        }
    }
    return false;
}


StringSlice string_slice_cut_pre(StringSlice a, uaddr size) {
    if (a.len < size) {
        return *((StringSlice*) &a);
    } else {
        return (StringSlice) {
            .len = a.len - size,
            .handle = a.handle + size,
        };
    }
}


StringSlice string_slice_cut_post(StringSlice a, uaddr size) {
    if (a.len < size) {
        return *((StringSlice*) &a);
    } else {
        return (StringSlice) {
            .len = a.len - size,
            .handle = a.handle,
        };
    }
}

