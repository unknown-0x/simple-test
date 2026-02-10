#ifndef SIMPLETEST_SIMPLETEST_UNIT_TEST_HPP_
#define SIMPLETEST_SIMPLETEST_UNIT_TEST_HPP_

#include "simpletest_test_suite.hpp"

namespace simpletest {
class Reporter;
class SIMPLETEST_API UnitTest {
 public:
  UnitTest();
  UnitTest(const UnitTest&) = delete;
  UnitTest(UnitTest&&) = delete;
  UnitTest operator=(const UnitTest&) = delete;
  UnitTest operator=(UnitTest&&) = delete;
  ~UnitTest();

  int RunAllTests() const;

  void SetReporter(Reporter* new_reporter);

  TestSuite& GetOrAddTestSuite(const char* suite_name);

  static UnitTest& Get();

 private:
  std::vector<TestSuite> suites_;
  Reporter* reporter_;
};
}  // namespace simpletest

#endif