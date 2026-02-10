#include "simpletest_unit_test.hpp"

#include "simpletest_console_reporter.hpp"
#include "simpletest_reporter.hpp"
#include "simpletest_test_runner.hpp"

#include <cstring>

#ifdef _WIN32
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <stdlib.h>
#endif

namespace simpletest {
UnitTest::UnitTest() : reporter_{new ConsoleReporter()} {
#ifdef _WIN32
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
}

UnitTest::~UnitTest() {
  SetReporter(nullptr);
}

int UnitTest::RunAllTests() const {
  TestRunner runner{suites_, reporter_};
  runner.RunAllTests();
  return GetGlobalFailureLocations().size() == 0 ? 0 : -1;
}

void UnitTest::SetReporter(Reporter* new_reporter) {
  delete reporter_;
  reporter_ = new_reporter;
}

TestSuite& UnitTest::GetOrAddTestSuite(const char* suite_name) {
  for (auto& suite : suites_) {
    if (strcmp(suite.GetName(), suite_name) == 0) {
      return suite;
    }
  }
  suites_.emplace_back(suite_name);
  return suites_.back();
}

UnitTest& UnitTest::Get() {
  static UnitTest global_unit_test{};
  return global_unit_test;
}
}  // namespace simpletest