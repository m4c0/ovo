module;
#include "vorbis/vorbisfile.h"

export module ovo;
import yoyo;

namespace ovo {
export class decoder {
  static constexpr const auto buf_size = 102400;

  yoyo::reader *m_r;
  OggVorbis_File m_vf{};
  bool m_started{};
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

    return false;
  }
  unsigned fill(void *data, unsigned size) { return 0; }
};
} // namespace ovo
