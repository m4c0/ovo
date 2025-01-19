#pragma leco tool

import silog;
import yoyo;
import ovo;

void run(yoyo::reader * r) {
  ovo::decoder d{r};

  while (d.preload()) {
  }

  constexpr const auto buf_size = 1024;
  float buf[buf_size];
  while (d.fill(buf, buf_size) > 0) {
  }
}

int main() {
  yoyo::file_reader::open("silent.ogg")
    .map([](auto & r) { run(&r); })
    .take([](auto msg) { silog::die("failure"); });
}
