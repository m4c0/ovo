module;
#include "vorbis/vorbisfile.h"

export module ovo;
import yoyo;

namespace ovo {
export class decoder {
  yoyo::reader *m_r;
  OggVorbis_File m_vf{};
  bool m_started{};

  static size_t ov_read_func(void *buf, size_t size, size_t n_memb, void *ptr) {
    return 0;
  }

  bool start() {
    constexpr const ov_callbacks cbs{
        .read_func = ov_read_func,
        .seek_func = [](auto, auto, auto) { return -1; },
    };
    return ov_open_callbacks(this, &m_vf, nullptr, 0, cbs) == 0;
  }

public:
  constexpr explicit decoder(yoyo::reader *r) : m_r{r} {}
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
