#include "../yoyo/build.hpp"
#include "ecow.hpp"

class cmake : public ecow::unit {
  pathset m_objs{};

  void build_self() const override {
    namespace fs = std::filesystem;

    const auto out = fs::path{ecow::impl::current_target()->build_folder()};
    const auto build = fs::absolute(out / name() / "build").string();
    const auto install = fs::absolute(out / "install").string();

    auto setup = std::string{"cmake -S "} + name() + " -B " + build +
                 " -DCMAKE_BUILD_TYPE=Release " +
                 " -DCMAKE_FIND_ROOT_PATH=" + install +
                 " -DCMAKE_INSTALL_PREFIX=" + install;
    if (std::system(setup.c_str()) != 0)
      throw std::runtime_error("Failed to setup CMake");

    auto compile = std::string{"cmake --build "} + build + " --target install";
    if (std::system(compile.c_str()) != 0)
      throw std::runtime_error("Failed to build with CMake");
  }

  [[nodiscard]] pathset self_objects() const override {
    namespace fs = std::filesystem;
    const auto out = fs::path{ecow::impl::current_target()->build_folder()};
    const auto install = fs::absolute(out / "install");

    pathset res{};
    for (const auto &o : m_objs) {
      res.insert(install / o);
    }
    return res;
  }

public:
  using unit::unit;

  void add_object(const std::string &o) { m_objs.insert(o); }
};

int main(int argc, char **argv) {
  using namespace ecow;

  auto m = unit::create<seq>("ovo-all");
  m->add_wsdep("yoyo", yoyo());
  m->add_unit<cmake>("ogg")->add_object("lib/libogg.a");

  auto v = m->add_unit<cmake>("vorbis");
  v->add_object("lib/libvorbis.a");
  v->add_object("lib/libvorbisfile.a");

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
