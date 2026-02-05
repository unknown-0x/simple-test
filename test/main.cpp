#include <math/math.hpp>

#include <cstdio>

int main(int argc, char** argv) {
  (void)argc;
  (void)argv;

#if defined(_WIN64)
  printf("OS: Windows (64)\n");
#elif defined(_WIN32)
  printf("OS: Windows (32)\n");
#elif defined(__APPLE__) || defined(__MACH__)
  printf("OS: MacOS\n");
#elif defined(__linux__)
  printf("OS: Linux\n");
#else
  printf("OS: Unknown\n");
#endif

#if defined(NDEBUG)
  printf("Build type: RELEASE/OPTIMIZED\n");
#else
  printf("Build type: DEBUG\n");
#endif

#if defined(_MSC_VER) && !defined(__clang__)
  printf("Compiler: MSVC (cl)\n");
#elif defined(__clang__)
#if defined(_MSC_VER)
  printf("Compiler: MSVC (clang-cl)\n");
#else
  printf("Compiler: Clang\n");
#endif
#elif defined(__GNUC__)
  printf("Compiler: GCC\n");
#else
  printf("Compiler: Unknown\n");
#endif

#if defined(_M_X64) || defined(__x86_64__)
  printf("Arch: x64 (64-bit)\n");
#elif defined(_M_IX86) || defined(__i386__)
  printf("Arch: x86 (32-bit)\n");
#elif defined(_M_ARM64) || defined(__aarch64__)
  printf("Arch: ARM64\n");
#elif defined(_M_ARM) || defined(__arm__)
  printf("Arch: ARM (32-bit)\n");
#else
  printf("Arch: Unknown\n");
#endif

  if (math::Add(1, 2) != 3) {
    return -1;
  }

  if (math::Subtract(4, 2) != 2) {
    return -1;
  }

  if (math::Max(5, 1) != 5) {
    return -1;
  }

  printf("All tests passed!\n");

  return 0;
}