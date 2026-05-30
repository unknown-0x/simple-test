#ifndef SIMPLETEST_SIMPLETEST_UNIT_TEST_HPP_
#define SIMPLETEST_SIMPLETEST_UNIT_TEST_HPP_

#include "simpletest_console_reporter.hpp"
#include "simpletest_test_suite.hpp"

#include <cstring>

#ifdef _WIN32
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <stdlib.h>
#endif

namespace simpletest {
class UnitTest {
 public:
  UnitTest() : reporter_{new ConsoleReporter()}, current_test_case_{nullptr} {
#ifdef _WIN32
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
    (void)_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
    (void)_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDERR);
#endif
  }

  UnitTest(const UnitTest&) = delete;
  UnitTest(UnitTest&&) = delete;
  UnitTest operator=(const UnitTest&) = delete;
  UnitTest operator=(UnitTest&&) = delete;

  ~UnitTest() { SetReporter(nullptr); }

  TestCase& GetCurrentTestCase() { return *current_test_case_; }

  int RunAllTests() {
    TestSummary summary{};
    for (auto& test_suite : suites_) {
      ProcessTestSuite(summary, test_suite);
    }
    reporter_->OnSummary(summary);
    return GetGlobalFailureLocations().size() == 0 ? 0 : -1;
  }

  void SetReporter(Reporter* new_reporter) {
    delete reporter_;
    reporter_ = new_reporter;
  }

  TestSuite& GetOrAddTestSuite(const char* suite_name) {
    for (auto& suite : suites_) {
      if (strcmp(suite.GetName(), suite_name) == 0) {
        return suite;
      }
    }
    suites_.emplace_back(suite_name);
    return suites_.back();
  }

  static UnitTest& Get() {
    static UnitTest global_unit_test{};
    return global_unit_test;
  }

 private:
  void ProcessTestSuite(TestSummary& summary, TestSuite& test_suite) {
    reporter_->OnTestSuiteStart(test_suite);
    auto& test_cases = test_suite.GetTestCases();
    for (auto& test_case : test_cases) {
      ProcessTestCase(summary, test_case);
    }
    reporter_->OnTestSuiteEnd(test_suite);
  }

  void ProcessTestCase(TestSummary& summary, TestCase& test_case) {
    reporter_->OnTestCaseStart(test_case);
    current_test_case_ = &test_case;
    test_case.Run();
    const auto& result = test_case.GetResult();
    summary.total_test_time += result.GetTestTime();
    if (result.IsPassed()) {
      ++summary.num_passed;
    } else {
      ++summary.num_failed;
    }
    reporter_->OnTestCaseEnd(test_case, result);
  }

  std::vector<TestSuite> suites_;
  Reporter* reporter_;
  TestCase* current_test_case_;
};
}  // namespace simpletest

#endif