#include "simpletest_console_reporter.hpp"

#include <iostream>

#define SIMPLETEST_UNUSED(x) (void)x

namespace simpletest {
ConsoleReporter::ConsoleReporter() {
  stream.Reserve(1024);
}

void ConsoleReporter::OnTestSuiteStart(const TestSuite& test_suite) {
  const auto num_test_cases = test_suite.GetTestCases().size();
  stream << test_suite.GetName() << " (" << num_test_cases
         << (num_test_cases == 1 ? " test case" : " test cases") << ")\n";
}

void ConsoleReporter::OnTestCaseStart(const TestCase& test_case) {
  SIMPLETEST_UNUSED(test_case);
}

void ConsoleReporter::OnTestCaseEnd(const TestCase& test_case,
                                    const TestCase::Result& result) {
  const bool passed = result.IsPassed();
  const char* const status_text = passed ? "Passed" : "Failed";

  stream << "    " << status_text << " -- " << test_case.GetName() << " ("
         << result.GetTestTime() << " ms)\n";

  result.ForEachFailureLocation([&](const FailureLocation& location) {
    stream << "              |- " << location.file << ':' << location.line
           << '\n';
  });
}

void ConsoleReporter::OnTestSuiteEnd(const TestSuite& test_suite) {
  SIMPLETEST_UNUSED(test_suite);
  std::cout << stream << '\n';
  stream.Clear();
}

void ConsoleReporter::OnSummary(TestSummary summary) {
  const auto pass_rate =
      CalculatePassRate(summary.num_passed, summary.num_failed);
  stream << "------------------------------------------------------------------"
            "----------\n";
  stream << "Result: " << pass_rate << "% (" << summary.num_passed
         << " passed, " << summary.num_failed << " failed)\n";
  stream << "Time  : " << summary.total_test_time << " ms\n";
  stream << "------------------------------------------------------------------"
            "----------\n";
  std::cout << stream << '\n';
  stream.Clear();
}
}  // namespace simpletest
