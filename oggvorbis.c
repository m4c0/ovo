// Nothing we can do about warnings in Ogg/Vorbis code
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#pragma clang diagnostic ignored "-Wunused-but-set-variable"

#pragma leco add_include_dir "ogg/include"
#pragma leco add_include_dir "vorbis/include"

#include "oggvorbis.h"

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
