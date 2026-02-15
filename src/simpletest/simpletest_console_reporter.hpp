#ifndef SIMPLETEST_SIMPLETEST_CONSOLE_REPORTER_HPP_
#define SIMPLETEST_SIMPLETEST_CONSOLE_REPORTER_HPP_

#include "simpletest_reporter.hpp"

namespace simpletest {
class ConsoleReporter : public Reporter {
 public:
  SIMPLETEST_API ConsoleReporter();
  ~ConsoleReporter() = default;

  SIMPLETEST_API void OnTestSuiteStart(const TestSuite& test_suite) override;
  SIMPLETEST_API void OnTestCaseStart(const TestCase& test_case) override;
  SIMPLETEST_API void OnTestCaseEnd(const TestCase& test_case,
                                    const TestCase::Result& result) override;
  SIMPLETEST_API void OnTestSuiteEnd(const TestSuite& test_suite) override;
  SIMPLETEST_API void OnSummary(TestSummary summary) override;

 private:
  TextStream stream;
};
}  // namespace simpletest

#endif