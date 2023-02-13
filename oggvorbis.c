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

#include "ogg/src/bitwise.c"
#include "ogg/src/framing.c"
#include "vorbis/lib/analysis.c"
#include "vorbis/lib/bitrate.c"
#include "vorbis/lib/block.c"
#include "vorbis/lib/codebook.c"
#include "vorbis/lib/envelope.c"
#include "vorbis/lib/floor0.c"
#include "vorbis/lib/floor1.c"
#include "vorbis/lib/info.c"
#include "vorbis/lib/lookup.c"
#include "vorbis/lib/lpc.c"
#include "vorbis/lib/lsp.c"
#include "vorbis/lib/mapping0.c"
#include "vorbis/lib/mdct.c"
#include "vorbis/lib/registry.c"
#include "vorbis/lib/res0.c"
#include "vorbis/lib/smallft.c"
#include "vorbis/lib/synthesis.c"
#include "vorbis/lib/vorbisfile.c"
#include "vorbis/lib/window.c"

#define FLOOR1_fromdB_LOOKUP FLOOR1_fromdB_LOOKUP2
#define bitreverse bitreverse2

#include "vorbis/lib/psy.c"
#include "vorbis/lib/sharedbook.c"
