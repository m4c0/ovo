#pragma once

#include <stdint.h>

#define _OS_TYPES_H
#define _ogg_malloc malloc
#define _ogg_calloc calloc
#define _ogg_realloc realloc
#define _ogg_free free
typedef int16_t ogg_int16_t;
typedef uint16_t ogg_uint16_t;
typedef int32_t ogg_int32_t;
typedef uint32_t ogg_uint32_t;
typedef int64_t ogg_int64_t;
typedef uint64_t ogg_uint64_t;
