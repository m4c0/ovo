#pragma leco tool

import yoyo;
import ovo;

int main() {
  yoyo::file_reader r{"silent.ogg"};
  ovo::decoder d{&r};

  while (d.preload()) {
  }

  constexpr const auto buf_size = 1024;
  float buf[buf_size];
  while (d.fill(buf, buf_size) > 0) {
  }
}
