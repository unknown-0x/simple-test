#include <simpletest/simpletest.hpp>

TEST_CASE(String, Comparision_Char) {
  const char* a = "abc";
  const char* b = "123";
  const char* c = "abc";
  CHECK_STR_EQ(a, c);
  CHECK_STR_NE(a, b);
}

TEST_CASE(String, Comparision_WChar) {
  const wchar_t* a = L"abc";
  const wchar_t* b = L"123";
  const wchar_t* c = L"abc";

  CHECK_STR_EQ(a, c);
  CHECK_STR_NE(a, b);
}

#ifdef __cpp_char8_t
TEST_CASE(String, Comparision_Char8) {
  const char8_t* a = u8"abc";
  const char8_t* b = u8"123";
  const char8_t* c = u8"abc";

  CHECK_STR_EQ(a, c);
  CHECK_STR_NE(a, b);
}
#endif

TEST_CASE(String, Comparision_Char16) {
  const char16_t* a = u"abc";
  const char16_t* b = u"123";
  const char16_t* c = u"abc";

  CHECK_STR_EQ(a, c);
  CHECK_STR_NE(a, b);
}

TEST_CASE(String, Comparision_Char32) {
  const char32_t* a = U"abc";
  const char32_t* b = U"123";
  const char32_t* c = U"abc";

  CHECK_STR_EQ(a, c);
  CHECK_STR_NE(a, b);
}