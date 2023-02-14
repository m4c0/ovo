#pragma once
#include "../yoyo/build.hpp"
#include "ecow.hpp"

auto ovo() {
  using namespace ecow;

  auto m = unit::create<seq>("ovo-all");
  m->add_wsdep("yoyo", yoyo());

  auto ov = m->add_unit<>("oggvorbis.c");
  ov->add_include_dir("ogg/include");
  ov->add_include_dir("vorbis/include");

  auto mm = m->add_unit<mod>("ovo");
  mm->add_include_dir("ogg/include");
  mm->add_include_dir("vorbis/include");

  return m;
}
