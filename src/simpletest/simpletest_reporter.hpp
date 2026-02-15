#ifndef SIMPLETEST_SIMPLETEST_REPORTER_HPP_
#define SIMPLETEST_SIMPLETEST_REPORTER_HPP_

#include "simpletest_test_suite.hpp"
#include "simpletest_utils.hpp"

namespace simpletest {
class SIMPLETEST_API Reporter {
 public:
  virtual ~Reporter() = default;

  virtual void OnTestSuiteStart(const TestSuite&) = 0;
  virtual void OnTestCaseStart(const TestCase&) = 0;
  virtual void OnTestCaseEnd(const TestCase&, const TestCase::Result&) = 0;
  virtual void OnTestSuiteEnd(const TestSuite&) = 0;
  virtual void OnSummary(TestSummary summary) = 0;
};
}  // namespace simpletest

#endif