#include <cstdint>

#include <catch2/catch_test_macros.hpp>
#include <VExercise1.h>

void test_op(uint8_t code, uint8_t(op)(uint8_t, uint8_t)) {
  VExercise1 model;
  model.op = code;
  model.a = 0;
  model.b = 0;

  do {
    do {
      model.eval();
      uint8_t result {op(model.a, model.b)};
      REQUIRE(result == model.out);
    } while(++model.b);
    model.b = 0;
  } while(++model.a);
}

TEST_CASE("Opcode 0, XOR") {
  test_op(0, [](uint8_t a, uint8_t b) -> uint8_t { return a ^ b; });
}

TEST_CASE("Opcode 1, Left Shift") {
  test_op(1, [](uint8_t a, uint8_t b) -> uint8_t { return ((b >= 8) ? 0 : a << b); }); // Needs to account for the fact that there are 8 bits; 0 or shift
}

TEST_CASE("Opcode 2, Mod") {
  test_op(2, [](uint8_t a, uint8_t b) -> uint8_t { return (b) ? a % b : 0; });
}

TEST_CASE("Opcode 3, NAND") {
  test_op(3, [](uint8_t a, uint8_t b) -> uint8_t { return ~(a & b); });
}
