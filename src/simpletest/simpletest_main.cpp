#include "simpletest.hpp"

int main(int argc, char** argv) {
  (void)argc;
  (void)argv;
  return simpletest::UnitTest::Get().RunAllTests();
}