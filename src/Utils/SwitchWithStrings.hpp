 #ifndef SWITCH_CASE_WITH_STRINGS_HPP
 #define SWITCH_CASE_WITH_STRINGS_HPP

 #include <inttypes.h>

uint64_t constexpr mix(char m, uint64_t s)
 {
  return ((s<<7) + ~(s>>3)) + ~m;
 }

uint64_t constexpr hash(const char * m)
 {
  return (*m) ? mix(*m,hash(m+1)) : 0;
 }

 #endif /* !SWITCH_CASE_WITH_STRINGS_HPP */