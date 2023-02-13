#include "../yoyo/build.hpp"
#include "ecow.hpp"

int main(int argc, char **argv) {
  using namespace ecow;

  auto m = unit::create<seq>("ovo-all");
  m->add_wsdep("yoyo", yoyo());

  auto ov = m->add_unit<>("oggvorbis.c");
  ov->add_include_dir("ogg/include");
  ov->add_include_dir("vorbis/include");

  auto mm = m->add_unit<mod>("ovo");
  mm->add_include_dir("ogg/include");
  mm->add_include_dir("vorbis/include");

  auto poc = unit::create<exe>("poc");
  poc->add_wsdep("yoyo", yoyo_libc());
  poc->add_ref(m);
  poc->add_unit("poc");

  auto all = unit::create<per_feat<seq>>("all");
  all->for_feature(windows_api).add_ref(poc);
  all->for_feature(cocoa).add_ref(poc);
  all->for_feature(android_ndk).add_ref(m);
  all->for_feature(webassembly).add_ref(m);

  return ecow::run_main(all, argc, argv);
}
