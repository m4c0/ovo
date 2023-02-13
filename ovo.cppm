module;
#include "vorbis/vorbisfile.h"

export module ovo;
import yoyo;

namespace ovo {
export class decoder {
  static constexpr const auto buf_size = 102400;
  static constexpr const auto max_samples_at_once = 1024;

  yoyo::reader *m_r;
  OggVorbis_File m_vf{};
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
    return ov_open_callbacks(this, &m_vf, nullptr, 0, cbs) == 0;
  }

public:
  constexpr explicit decoder(yoyo::reader *r) : m_r{r} {}
  ~decoder() {
    if (m_started)
      ov_clear(&m_vf);
  }

  bool preload() {
    if (!m_started && start())
      m_started = true;
    if (!m_started)
      return false;

    auto diff = (m_rp + buf_size - m_wp) % buf_size;
    if (diff <= max_samples_at_once)
      return false;

    float **pcm{};
    auto smp = ov_read_float(&m_vf, &pcm, max_samples_at_once, &m_section);
    for (auto i = 0; i < smp; i++) {
      // TODO: Do something if audio isn't stereo-16bits-44100
      m_buffer[m_wp] = pcm[0][i];
      m_wp = (m_wp + 1) % buf_size;
    }

    return smp > 0;
  }
  unsigned fill(float *data, unsigned size) { return 0; }
};
} // namespace ovo
