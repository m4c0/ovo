#pragma leco tool

import print;
import ovo;

int main() try {
  ovo::file f = ovo::open_file("silent.ogg");
  putfn("Time total: %f", ovo::time_total(f, -1));

  float ** pcm {};
  int i {};
  while (ovo::read_float(f, &pcm, 1024, &i) > 0) {
    // Now use pcm[channel][sample]
  }
} catch (...) {
  return 1;
}
