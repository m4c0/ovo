import yoyo_libc;
import ovo;

int main() {
  yoyo::file_reader r{"silent.ogg"};
  ovo::decoder d{&r};

  while (d.preload()) {
  }

  char buf[1024];
  while (d.fill(buf, sizeof(buf)) > 0) {
  }
}
