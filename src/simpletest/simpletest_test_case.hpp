#ifndef SIMPLETEST_SIMPLETEST_TEST_CASE_HPP_
#define SIMPLETEST_SIMPLETEST_TEST_CASE_HPP_

#include <chrono>
#include <vector>

namespace simpletest {
struct FailureLocation {
  const char* file;
  int line;
};

inline std::vector<FailureLocation>& GetGlobalFailureLocations() {
  static std::vector<FailureLocation> failure_locations{};
  return failure_locations;
}

class TestCase {
 public:
  class Result {
   public:
    Result() = default;

    bool IsPassed() const noexcept { return failure_count_ == 0; }
    double GetTestTime() const noexcept { return test_time_; }
    int GetFailureCount() const noexcept { return failure_count_; }

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

    static void AddFailureLocation(TestCase::Result& result,
                                   FailureLocation loc) {
      auto& failure_locations = GetGlobalFailureLocations();
      failure_locations.push_back(loc);
      if (result.first_failure_index_ == -1) {
        result.first_failure_index_ =
            static_cast<int>(failure_locations.size()) - 1;
      }
      ++result.failure_count_;
    }

   private:
    friend class TestCase;

    double test_time_ = 0.0;
    int first_failure_index_ = -1;
    int failure_count_ = 0;
  };

  using Function = void (*)();

  TestCase(const char* name, Function func) : name_(name), func_(func) {}

  void Run() {
    using Clock = std::chrono::steady_clock;

    auto start = Clock::now();
    func_();
    auto end = Clock::now();
    result_.test_time_ =
        std::chrono::duration<double, std::milli>(end - start).count();
  }

  const Result& GetResult() const noexcept { return result_; }
  Result& GetResult() noexcept { return result_; }
  const char* GetName() const noexcept { return name_; }

 private:
  Result result_;
  const char* name_;
  Function func_;
};
}  // namespace simpletest
#endif