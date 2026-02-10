#include "simpletest_test_runner.hpp"

#include "simpletest_reporter.hpp"

namespace simpletest {
TestRunner::TestRunner(const std::vector<TestSuite>& test_suites,
                       Reporter* reporter)
    : test_suites_(test_suites), reporter_(reporter) {}

void TestRunner::RunAllTests() {
  for (const auto& test_suite : test_suites_) {
    ProcessTestSuite(test_suite);
  }
  reporter_->OnSummary(summary_);
}

void TestRunner::ProcessTestSuite(const TestSuite& test_suite) {
  reporter_->OnTestSuiteStart(test_suite);
  const auto& test_cases = test_suite.GetTestCases();
  for (const auto& test_case : test_cases) {
    ProcessTestCase(test_case);
  }
  reporter_->OnTestSuiteEnd(test_suite);
}

void TestRunner::ProcessTestCase(const TestCase& test_case) {
  reporter_->OnTestCaseStart(test_case);
  auto result = test_case.Run();
  summary_.total_test_time += result.GetTestTime();
  if (result.IsPassed()) {
    ++summary_.num_passed;
  } else {
    ++summary_.num_failed;
  }
  reporter_->OnTestCaseEnd(test_case, result);
}
}  // namespace simpletest
