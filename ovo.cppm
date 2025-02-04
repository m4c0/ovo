#pragma leco add_impl impl
#pragma leco add_impl oggvorbis
module;
struct OggVorbis_File;

export module ovo;
import hai;
import jute;
import silog;
import yoyo;

namespace ovo {
  struct deleter { void operator()(OggVorbis_File * f); };
  export using file = hai::value_holder<OggVorbis_File *, deleter>;

  export file open_file(jute::view name);
  export file open_callbacks(const char * data, unsigned sz);
  export file open_callbacks(const auto & data) {
    return open_callbacks(data.begin(), data.size());
  }

  export long bitrate(file & f, int i);
  export long read_float(file & f, float *** pcm, int samples, int * i);
  export double time_tell(file & f);
  export double time_total(file & f, int i);
} // namespace ovo
