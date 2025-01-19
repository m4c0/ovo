#pragma leco add_include_dir "ogg/include"
#pragma leco add_include_dir "vorbis/include"
#pragma leco add_impl oggvorbis

module;
#include "oggvorbis.h"
#include "vorbis/vorbisfile.h"

export module ovo;
import hai;
import yoyo;

namespace ovo {
  struct deleter {
    void operator()(OggVorbis_File * f) { ov_clear(f); delete f; }
  };
  export using file = hai::value_holder<OggVorbis_File *, deleter>;

export class decoder {
  static constexpr const auto buf_size = 102400;
  static constexpr const auto max_samples_at_once = 1024;

  yoyo::reader *m_r;
  file m_vf {};
  bool m_started{};
  int m_section{};
  float m_buffer[buf_size];
  unsigned m_rp = 0;
  unsigned m_wp = 0;

  static size_t read_func(void *buf, size_t size, size_t n_memb, void *ptr) {
    auto *self = static_cast<decoder *>(ptr);
    auto sz = size * n_memb;
    return self->m_r->read(buf, sz).map([sz] { return sz; }).unwrap(0);
  }

  bool start() {
    constexpr const ov_callbacks cbs{
        .read_func = read_func,
        .seek_func = [](auto, auto, auto) { return -1; },
    };
    m_vf = file { new OggVorbis_File {} };
    return ov_open_callbacks(this, *m_vf, nullptr, 0, cbs) == 0;
  }

public:
  constexpr explicit decoder(yoyo::reader *r) : m_r{r} {}

  bool preload() {
    if (!m_started && start())
      m_started = true;
    if (!m_started)
      return false;

    auto diff = (m_rp + buf_size - m_wp) % buf_size;
    if (diff <= max_samples_at_once)
      return false;

    float **pcm{};
    auto smp = ov_read_float(*m_vf, &pcm, max_samples_at_once, &m_section);
    for (auto i = 0; i < smp; i++) {
      // TODO: Do something if audio isn't stereo-16bits-44100
      m_buffer[m_wp] = pcm[0][i];
      m_wp = (m_wp + 1) % buf_size;
    }

    return smp > 0;
  }
  unsigned fill(float *data, unsigned size) {
    unsigned av = (m_wp + buf_size - m_rp) % buf_size;
    if (av == 0)
      return 0;

    unsigned res = av > size ? size : av;
    for (auto i = 0; i < res; i++) {
      data[i] = m_buffer[m_rp];
      m_rp = (m_rp + 1) % buf_size;
    }
    return res;
  }
};
} // namespace ovo
