#ifndef SIMPLETEST_SIMPLETEST_UTILS_HPP_
#define SIMPLETEST_SIMPLETEST_UTILS_HPP_

#include <cmath>
#include <ostream>
#include <string>

namespace simpletest {
namespace internal {
template <typename Float>
inline constexpr const char* kFloatFmtStr = "%.*f";

template <>
inline constexpr const char* kFloatFmtStr<long double> = "%.*Lf";
}  // namespace internal

struct TestSummary {
  double total_test_time = 0.0;
  int num_passed = 0;
  int num_failed = 0;
};

struct Precision {
  int precision;
};

inline Precision SetPrecision(int value) noexcept {
  return Precision{value};
}

class TextStream {
 public:
  TextStream() = default;
  ~TextStream() = default;

  void Clear() { text.clear(); }
  void Reserve(size_t n) { text.reserve(n); }
  const std::string& GetString() const { return text; }

  TextStream& operator<<(Precision value) {
    precision = value;
    return *this;
  }

  TextStream& operator<<(const char* value) {
    text.append(value);
    return *this;
  }

  TextStream& operator<<(char value) {
    text.append(1, value);
    return *this;
  }

  TextStream& operator<<(bool value) {
    if (value) {
      text.append("true", "4");
    } else {
      text.append("false", "5");
    }
    return *this;
  }

  template <typename Int>
  typename std::enable_if<std::is_integral<Int>::value, TextStream>::type&
  operator<<(Int value) {
    AppendInt<Int>(value);
    return *this;
  }

  template <typename Float>
  typename std::enable_if<std::is_floating_point<Float>::value,
                          TextStream>::type&
  operator<<(Float value) {
    AppendFloat<Float>(value);
    return *this;
  }

 private:
  std::string text;
  Precision precision{4};

  template <typename Int>
  void AppendInt(Int num) {
    static_assert(std::is_integral<Int>::value,
                  "AppendInt requires an integral type");

    if (num == 0) {
      text += '0';
      return;
    }

    if constexpr (std::is_signed<Int>::value) {
      if (num < 0) {
        text += '-';
        num = Int(-(num + 1)) + 1;
      }
    }

    char result[20];
    char* end = result + sizeof(result);
    char* p = end;
    do {
      *--p = char('0' + (num % 10));
      num /= 10;
    } while (num);

    text.append(p, static_cast<size_t>(end - p));
  }

  template <typename Float>
  void AppendFloat(Float num) {
    static_assert(std::is_floating_point<Float>::value,
                  "AppendFloat requires an floating-point type");

    if (std::isnan(num)) {
      text.append("NaN", 3);
      return;
    }

    if (std::isinf(num)) {
      if (num < 0) {
        text.append("-Inf", 4);
      } else {
        text.append("Inf", 3);
      }
      return;
    }

    static constexpr auto kBufferSize =
        std::numeric_limits<Float>::max_exponent10 + 20;

    char result[kBufferSize];
    auto written =
        snprintf(result, sizeof(result), internal::kFloatFmtStr<Float>,
                 precision.precision, num);
    if (written > 0) {
      text.append(result, written < static_cast<int>(sizeof(result))
                              ? static_cast<size_t>(written)
                              : sizeof(result) - 1);
    }
  }
};

inline double CalculatePassRate(int num_passed, int num_failed) noexcept {
  const auto total = num_passed + num_failed;
  if (total == 0) {
    return 100.0;
  }
  return (num_passed * 100.0) / total;
}
}  // namespace simpletest

inline std::ostream& operator<<(std::ostream& os,
                                const simpletest::TextStream& text) {
  os << text.GetString();
  return os;
}

#endif