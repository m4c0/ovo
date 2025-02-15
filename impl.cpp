#pragma leco add_include_dir "ogg/include"
#pragma leco add_include_dir "vorbis/include"

module;
#include "oggvorbis.h"
#include "vorbis/vorbisfile.h"

#include <stdio.h>

module ovo;

void ovo::deleter::operator()(OggVorbis_File * f) {
  ov_clear(f);
  delete f;
}

ovo::file ovo::open_callbacks(const char * data, unsigned sz) {
  constexpr const ov_callbacks cbs{
    .read_func = [](auto, auto, auto, auto) -> size_t { return 0; },
  };
  file f { new OggVorbis_File {} };
  if (0 != ov_open_callbacks(nullptr, *f, data, sz, cbs)) {
    silog::die("Could not start OggVorbis");
  }
  return f;
}

size_t file_read(void * ptr, size_t size, size_t nmemb, void * f) { return fread(ptr, size, nmemb, (FILE *)f); }
int file_seek(void * f, ogg_int64_t offset, int whence) { return fseek((FILE *)f, offset, whence); }
int file_close(void * f) { return fclose((FILE *)f); }
long file_tell(void * f) { return ftell((FILE *)f); }
ovo::file ovo::open_file(jute::view name) {
  constexpr const ov_callbacks cbs { file_read, file_seek, file_close, file_tell };

  auto file = fopen(name.cstr().begin(), "rb");
  if (!file) silog::die("Could not open OggVorbis file");

  ovo::file f { new OggVorbis_File {} };
  if (0 != ov_open_callbacks(file, *f, nullptr, 0, cbs)) {
    silog::die("Could not start OggVorbis");
  }
  return f;
}

long ovo::bitrate(ovo::file & f, int i) { return ov_bitrate(*f, i); }

long ovo::read_float(ovo::file & f, float *** pcm, int samples, int * current) {
  long res = ov_read_float(*f, pcm, samples, current);
  if (res >= 0) return res;
  silog::die("Could not read OggVorbis");
}
double ovo::time_tell(ovo::file & f) { return ov_time_tell(*f); }
double ovo::time_total(ovo::file & f, int i) { return ov_time_total(*f, i); }
