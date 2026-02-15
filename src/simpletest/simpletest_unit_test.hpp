#ifndef SIMPLETEST_SIMPLETEST_UNIT_TEST_HPP_
#define SIMPLETEST_SIMPLETEST_UNIT_TEST_HPP_

#include "simpletest_test_suite.hpp"

namespace simpletest {
class Reporter;
class UnitTest {
 public:
  SIMPLETEST_API UnitTest();
  UnitTest(const UnitTest&) = delete;
  UnitTest(UnitTest&&) = delete;
  UnitTest operator=(const UnitTest&) = delete;
  UnitTest operator=(UnitTest&&) = delete;
  SIMPLETEST_API ~UnitTest();

  SIMPLETEST_API int RunAllTests() const;

  SIMPLETEST_API void SetReporter(Reporter* new_reporter);

  SIMPLETEST_API TestSuite& GetOrAddTestSuite(const char* suite_name);

  SIMPLETEST_API static UnitTest& Get();

 private:
  std::vector<TestSuite> suites_;
  Reporter* reporter_;
};
}  // namespace simpletest

#endif