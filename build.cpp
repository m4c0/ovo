#include "ecow.hpp"

class cmake : public ecow::unit {
  void build_self() const override {
    const auto out = ecow::impl::current_target()->build_folder() + name();
    const auto build = out + "/build";
    const auto install = out + "/install";

    auto setup =
        std::string{"cmake -S "} + name() + " -B " + build +
        " -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=" + install;
    if (std::system(setup.c_str()) != 0)
      throw std::runtime_error("Failed to setup CMake");

    auto compile = std::string{"cmake --build "} + build + " --target install";
    if (std::system(compile.c_str()) != 0)
      throw std::runtime_error("Failed to build with CMake");
  }

  [[nodiscard]] pathset self_objects() const override { return {}; }

public:
  using unit::unit;
};

int main(int argc, char **argv) {
  using namespace ecow;

  auto m = unit::create<seq>("ovo");
  m->add_unit<cmake>("vorbis");
  m->add_unit<mod>("ovo");

  auto poc = unit::create<exe>("poc");
  poc->add_ref(m);
  poc->add_unit("poc");
  return ecow::run_main(poc, argc, argv);
}
