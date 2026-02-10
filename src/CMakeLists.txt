add_library(
    simpletest
    simpletest/simpletest_console_reporter.hpp
    simpletest/simpletest_console_reporter.cpp
    simpletest/simpletest_reporter.hpp
    simpletest/simpletest_test_case.hpp
    simpletest/simpletest_test_case.cpp
    simpletest/simpletest_test_macros.hpp
    simpletest/simpletest_test_macros.cpp
    simpletest/simpletest_test_runner.hpp
    simpletest/simpletest_test_runner.cpp
    simpletest/simpletest_test_suite.hpp
    simpletest/simpletest_test_suite.cpp
    simpletest/simpletest_utils.hpp
    simpletest/simpletest_unit_test.hpp
    simpletest/simpletest_unit_test.cpp
)

add_library(simpletest::simpletest ALIAS simpletest)

target_enable_clang_format(simpletest)
target_enable_clang_tidy(simpletest)
target_compiler_warnings(simpletest)
target_export_api(simpletest SIMPLETEST_API)

# simpletest_main 
add_library(
    simpletest_main
    simpletest/simpletest_main.cpp
)

target_link_libraries(simpletest_main PUBLIC simpletest::simpletest)
target_enable_clang_format(simpletest_main)
target_enable_clang_tidy(simpletest_main)
target_compiler_warnings(simpletest_main)
target_import_api(simpletest_main simpletest::simpletest)
target_include_directories(simpletest_main PUBLIC ${PROJECT_ROOT}/src)

add_library(simpletest::main ALIAS simpletest_main)