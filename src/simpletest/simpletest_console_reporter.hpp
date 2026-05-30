#ifndef SIMPLETEST_SIMPLETEST_CONSOLE_REPORTER_HPP_
#define SIMPLETEST_SIMPLETEST_CONSOLE_REPORTER_HPP_

#include "simpletest_reporter.hpp"

#include <iostream>

namespace simpletest {
class ConsoleReporter : public Reporter {
 public:
  ConsoleReporter() { stream.Reserve(1024); }

  ~ConsoleReporter() = default;

  void OnTestSuiteStart(const TestSuite& test_suite) override {
    const auto num_test_cases = test_suite.GetTestCases().size();
    stream << test_suite.GetName() << " (" << num_test_cases
           << (num_test_cases == 1 ? " test case" : " test cases") << ")\n";
  }

  void OnTestCaseStart(const TestCase& test_case) override { (void)test_case; }

  void OnTestCaseEnd(const TestCase& test_case,
                     const TestCase::Result& result) override {
    const bool passed = result.IsPassed();
    const char* const status_text = passed ? "Passed" : "Failed";

    stream << "    " << status_text << " -- " << test_case.GetName() << " ("
           << result.GetTestTime() << " ms)\n";

    result.ForEachFailureLocation([&](const FailureLocation& location) {
      stream << "              |- " << location.file << ':' << location.line
             << '\n';
    });
  }

  void OnTestSuiteEnd(const TestSuite& test_suite) override {
    (void)test_suite;
    std::cout << stream << '\n';
    stream.Clear();
  }

  void OnSummary(TestSummary summary) override {
    const auto pass_rate =
        CalculatePassRate(summary.num_passed, summary.num_failed);
    stream
        << "------------------------------------------------------------------"
           "----------\n";
    stream << "Result: " << pass_rate << "% (" << summary.num_passed
           << " passed, " << summary.num_failed << " failed)\n";
    stream << "Time  : " << summary.total_test_time << " ms\n";
    stream
        << "------------------------------------------------------------------"
           "----------\n";
    std::cout << stream << '\n';
    stream.Clear();
  }

 private:
  TextStream stream;
};
}  // namespace simpletest

#endif