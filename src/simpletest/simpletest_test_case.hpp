#ifndef SIMPLETEST_SIMPLETEST_TEST_CASE_HPP_
#define SIMPLETEST_SIMPLETEST_TEST_CASE_HPP_

#include <chrono>
#include <vector>

namespace simpletest {
struct FailureLocation {
  const char* file;
  int line;
};

SIMPLETEST_API std::vector<FailureLocation>& GetGlobalFailureLocations();

class SIMPLETEST_API TestCase {
 public:
  class Result {
   public:
    Result() = default;

    bool IsPassed() const { return failure_count_ == 0; }
    double GetTestTime() const { return test_time_; }
    int GetFailureCount() const { return failure_count_; }

    template <typename Fn>
    void ForEachFailureLocation(Fn&& fn) const {
      if (failure_count_ == 0) {
        return;
      }
      auto& failure_locations = GetGlobalFailureLocations();
      for (int i = 0; i < failure_count_; ++i) {
        fn(failure_locations[static_cast<size_t>(first_failure_index_ + i)]);
      }
    }

    SIMPLETEST_API static void AddFailureLocation(TestCase::Result& result,
                                                  FailureLocation loc);

   private:
    friend class TestCase;

    double test_time_ = 0.0;
    int first_failure_index_ = -1;
    int failure_count_ = 0;
  };

  using Function = void (*)(Result&);

  TestCase(const char* name, Function func);
  Result Run() const;
  const char* GetName() const { return name_; }

 private:
  const char* name_;
  Function func_;
};
}  // namespace simpletest
#endif