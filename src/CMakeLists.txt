add_library(simpletest INTERFACE)
add_library(simpletest::simpletest ALIAS simpletest)
file(GLOB_RECURSE SIMPLETEST_HEADERS "simpletest/*.hpp")
target_sources(simpletest INTERFACE ${SIMPLETEST_HEADERS})

target_enable_clang_format(simpletest)
target_enable_clang_tidy(simpletest)

# simpletest_main 
add_library(
    simpletest_main
    simpletest/simpletest_main.cpp
)

add_library(simpletest::main ALIAS simpletest_main)
target_link_libraries(simpletest_main PUBLIC simpletest::simpletest)
target_include_directories(simpletest_main PUBLIC ${PROJECT_ROOT}/src)

target_compiler_warnings(simpletest_main)
target_enable_clang_format(simpletest_main)
target_enable_clang_tidy(simpletest_main)

if(BUILD_SHARED_LIBS AND MSVC)
  set_target_properties(simpletest_main
    PROPERTIES
      WINDOWS_EXPORT_ALL_SYMBOLS ON
  )
endif()