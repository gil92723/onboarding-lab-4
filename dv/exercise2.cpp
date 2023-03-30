#include <bit>
#include <cstdint>

#include <catch2/catch_test_macros.hpp>
#include <VExercise2.h>

using namespace std;

struct RainbowRead{
  uint16_t value;
  static constexpr uint16_t mask {0x50a};

  void step() {
    uint16_t bits = value & mask;
    value = (value << 1) | (popcount(bits) & 1);
  }
};

void step(VExercise2& model) {
  model.clk = 1;
  model.eval();
  model.clk = 0;
  model.eval();
}

void test_value_init(uint16_t init) {
  VExercise2 model;
  model.reset = 1;
  model.init = init;
  step(model);
  model.reset = 0;

  RainbowRead lsfr{(uint16_t) ~init};
  for(size_t i = 0; i < 100; i++){
    REQUIRE(model.out == lsfr.value);
    step(model);
    lsfr.step();
  }

  model.reset = 1;
  step(model);
  REQUIRE(model.out == (uint16_t) ~init);
}

TEST_CASE("Initial value 0x00") {
  test_value_init(0x00);
}

TEST_CASE("Initial value 0xFF") {
  test_value_init(0xFF);
}

TEST_CASE("Initial value 0x55") {
  test_value_init(0x55);
}

TEST_CASE("Initial value 0xAA") {
  test_value_init(0xAA);
}