#ifndef POWER_H_
#define POWER_H_

#include <cassert>

template <typename T, typename Integral, typename Operation>
T power(T base, Integral exponent, T identity, Operation multiplies) {
  assert(exponent >= 0);

  if (exponent == 0) return identity;

  T result = power(base, exponent / 2, identity, multiplies);
  result   = multiplies(result, result);

  return (exponent % 2 == 0) ? result : multiplies(base, result);
}

#endif  // POWER_H_
