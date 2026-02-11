#include "simpletest_test_case.hpp"

#include <chrono>

namespace simpletest {
std::vector<FailureLocation>& GetGlobalFailureLocations() {
  static std::vector<FailureLocation> failure_locations{};
  return failure_locations;
}

TestCase::TestCase(const char* name, Function func)
    : name_(name), func_(func) {}

TestCase::Result TestCase::Run() const {
  using Clock = std::chrono::steady_clock;

  TestCase::Result result{};
  auto start = Clock::now();
  func_(result);
  auto end = Clock::now();
  result.test_time_ =
      std::chrono::duration<double, std::milli>(end - start).count();

  return result;
}

void TestCase::Result::AddFailureLocation(TestCase::Result& result,
                                          FailureLocation loc) {
  auto& failure_locations = GetGlobalFailureLocations();
  failure_locations.push_back(loc);
  if (result.first_failure_index_ == -1) {
    result.first_failure_index_ =
        static_cast<int>(failure_locations.size()) - 1;
  }
  ++result.failure_count_;
}
}  // namespace simpletest