#ifndef SIMPLETEST_SIMPLETEST_CONSOLE_REPORTER_HPP_
#define SIMPLETEST_SIMPLETEST_CONSOLE_REPORTER_HPP_

#include "simpletest_reporter.hpp"

namespace simpletest {
class SIMPLETEST_API ConsoleReporter : public Reporter {
 public:
  ConsoleReporter();
  ~ConsoleReporter() = default;

  void OnTestSuiteStart(const TestSuite& test_suite) override;
  void OnTestCaseStart(const TestCase& test_case) override;
  void OnTestCaseEnd(const TestCase& test_case,
                     const TestCase::Result& result) override;
  void OnTestSuiteEnd(const TestSuite& test_suite) override;
  void OnSummary(TestSummary summary) override;

 private:
  TextStream stream;
};
}  // namespace simpletest

#endif