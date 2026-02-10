add_executable(
    example
    math.cpp
    string.cpp
    fixture.cpp
    floating_point.cpp
)

target_link_libraries(example simpletest::main)
target_enable_clang_format(example)
target_enable_clang_tidy(example)

add_test(NAME example COMMAND example)