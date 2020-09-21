//
// Created by Андрей Москалёв on 13.09.2020.
//

#include "BigInteger.h"

void print_digit(std::string &out, unsigned short digit) {
  std::string s = std::to_string(digit);
  while (s.size() < RADIX_N_POW) {
    s = '0' + s;
  }
  out += s;
}

std::string BigInteger::toString() const {
  std::string representation;
  if (ltz) {
    representation += '-';
  }
  bool was = false;
  for (size_t i = SIZE - 1; i > 0; --i) {
    if (!digits[i]) {
      if (was)
        print_digit(representation, digits[i]);
    } else {
      if (was)
        print_digit(representation, digits[i]);
      else {
        was = true;
        representation += std::to_string(digits[i]);
      }
    }
  }
  if (was)
    print_digit(representation, digits[0]);
  else
    representation += std::to_string(digits[0]);
  return representation;
}

std::ostream &operator<<(std::ostream &out, const BigInteger &bint) {
  out << bint.toString();
  return out;
}

std::istream &operator>>(std::istream &in, BigInteger &bint) {
  std::string input;
  in >> input;
  bint.fillFromString(input);
  return in;
}

void BigInteger::zeroize() {
  for (size_t i = 0; i < SIZE; ++i) digits[i] = 0;
}

void BigInteger::fillFromString(const std::string &n) {
  zeroize();
  std::string s;
  size_t ind = 0;
  int to = 0;
  if (n[to] == '-') {
    ++to;
    ltz = true;
  }
  for (int i = n.size() - 1; i >= to; --i) {
    s = n[i] + s;
    if (s.size() == RADIX_N_POW) {
      digits[ind++] = std::stoi(s);
      s.clear();
    }
  }
  if (!s.empty()) digits[ind] = std::stoi(s);
}


BigInteger::BigInteger(int n) {
  zeroize();
  if (n < 0) {
    ltz = true;
    n = -n;
  }
  size_t ind = 0;
  while (n > 0) {
    digits[ind++] = n % RADIX;
    n /= RADIX;
  }
}

BigInteger::BigInteger(long long n) {
  zeroize();
  if (n < 0) {
    ltz = true;
    n = -n;
  }
  size_t ind = 0;
  while (n > 0) {
    digits[ind++] = n % RADIX;
    n /= RADIX;
  }
}

BigInteger::BigInteger(const std::string &n) {
  fillFromString(n);
}

BigInteger::BigInteger() {
  zeroize();
}

BigInteger::BigInteger(const char *cstr) {
  zeroize();
  std::string s, n = std::string(cstr);
  size_t ind = 0;
  int to = 0;
  if (n[to] == '-') {
    ++to;
    ltz = true;
  }
  for (int i = n.size() - 1; i >= to; --i) {
    s = n[i] + s;
    if (s.size() == RADIX_N_POW) {
      digits[ind++] = std::stoi(s);
      s.clear();
    }
  }
  if (!s.empty()) digits[ind] = std::stoi(s);
}

BigInteger BigInteger::operator+(const BigInteger &other) const {
  if (!ltz && !other.ltz) {
    BigInteger b = *this;
    for (size_t i = 0; i < SIZE; ++i) {
      b.digits[i] += other.digits[i];
      if (b.digits[i] >= RADIX) {
        b.digits[i + 1] += b.digits[i] / RADIX;
        b.digits[i] %= RADIX;
      }
    }
    return b;
  } else if (ltz && other.ltz) {
    BigInteger a = *this;
    BigInteger b = other;
    a.ltz = false;
    b.ltz = false;
    return -(a + b);
  } else if (ltz && !other.ltz) {
    BigInteger a = *this;
    return other - -a;
  } else {
    BigInteger a = other;
    return *this - -a;
  }
}

BigInteger BigInteger::operator-(const BigInteger &other) const {
  BigInteger a = *this;
  BigInteger b = other;
  if (!a.ltz && !b.ltz) {
    if (b <= a) {
      for (size_t i = 0; i < SIZE; ++i) {
        if (a.digits[i] < other.digits[i]) {
          size_t j;
          for (j = i + 1; j < SIZE; ++j) {
            if (a.digits[j] > 0) {
              --a.digits[j];
              break;
            }
          }
          for (j = j - 1; j > i; --j) {
            a.digits[j] += RADIX - 1;
          }
          a.digits[i] += RADIX;
        }
        a.digits[i] -= other.digits[i];
      }
      return a;
    } else {
      BigInteger res = b - a;
      res.ltz = true;
      return res;
    }
  } else if (a.ltz && !b.ltz) {
    a.ltz = false;
    return b - a;
  } else {
    a.ltz = false;
    b.ltz = false;
    BigInteger result = a + b;
    result.ltz = true;
    return result;
  }
}

bool BigInteger::operator==(const BigInteger &other) const {
  for (size_t i = 0; i < SIZE; ++i)
    if (digits[i] != other.digits[i])
      return false;
  return true;
}

bool BigInteger::operator>(const BigInteger &other) const {
  if (ltz && !other.ltz) return false;
  if (!ltz && other.ltz) return true;
  if (*this == other) return false;
  bool bigger = false;
  size_t lastNonZeroLeft = 0;
  size_t lastNonZeroRight = 0;
  for (size_t i = 0; i < SIZE; ++i) {
    if (digits[i]) lastNonZeroLeft = i;
    if (other.digits[i]) lastNonZeroRight = i;
  }
  if (lastNonZeroLeft == lastNonZeroRight) {
    for (short int i = lastNonZeroLeft; i >= 0; --i) {
      if (digits[i] > other.digits[i]) {
        bigger = true;
      } else if (digits[i] < other.digits[i]) {
        break;
      }
    }
  }
  if (!ltz) {
      if (lastNonZeroLeft == lastNonZeroRight)
        return bigger;
    return lastNonZeroLeft > lastNonZeroRight;
  }
  if (lastNonZeroLeft == lastNonZeroRight)
    return !bigger;
  return lastNonZeroLeft < lastNonZeroRight;
}

bool BigInteger::operator<(const BigInteger &other) const {
  if (*this == other) return false;
  return !(*this > other);
}

bool BigInteger::operator>=(const BigInteger &other) const {
  return !(*this < other);
}

bool BigInteger::operator<=(const BigInteger &other) const {
  return !(*this > other);
}

bool BigInteger::operator!=(const BigInteger &other) const {
  return !(*this == other);
}

BigInteger::operator bool() const {
  if (*this == 0)
    return false;
  return true;
}

BigInteger BigInteger::operator+=(const BigInteger &other) {
  BigInteger result = *this;
  result = result + other;
  return result;
}

BigInteger BigInteger::operator-=(const BigInteger &other) {
  BigInteger result = *this;
  result = result - other;
  return result;
}

BigInteger BigInteger::operator-() const {
  BigInteger result = *this;
  result.ltz = !result.ltz;
  return result;
}

BigInteger &BigInteger::operator--() {
  if (!ltz) {
    if (digits[0] == 0) {
      size_t i;
      for (i = 1; i < SIZE; ++i) {
        if (digits[i] > 0) {
          break;
        }
      }
      if (i == SIZE) {
        digits[0] = 1;
        ltz = true;
      } else {
        --digits[i];
        for (i = i - 1; i > 0; --i) {
          digits[i] += RADIX - 1;
        }
        digits[0] = RADIX - 1;
      }
    } else {
      --digits[0];
    }
  } else {
    ++digits[0];
    size_t i;
    for (i = 0; i < SIZE; ++i) {
      if (digits[i] >= RADIX) {
        digits[i + 1] += digits[i] / RADIX;
        digits[i] %= RADIX;
      } else {
        break;
      }
    }
  }
  return *this;
}

BigInteger BigInteger::operator--(int) {
  BigInteger b = *this;
  --*this;
  return b;
}

BigInteger &BigInteger::operator++() {
  if (!ltz) {
    ++digits[0];
    size_t i;
    for (i = 0; i < SIZE; ++i) {
      if (digits[i] >= RADIX) {
        digits[i + 1] += digits[i] / RADIX;
        digits[i] %= RADIX;
      } else {
        break;
      }
    }
  } else {
    if (digits[0] == 0) {
      size_t i;
      for (i = 1; i < SIZE; ++i) {
        if (digits[i] > 0) {
          break;
        }
      }
      if (i == SIZE) {
        digits[0] = 1;
        ltz = true;
      } else {
        --digits[i];
        for (i = i - 1; i > 0; --i) {
          digits[i] += RADIX - 1;
        }
        digits[0] = RADIX - 1;
      }
    } else {
      --digits[0];
    }
  }
  return *this;
}

BigInteger BigInteger::operator++(int) {
  BigInteger b = *this;
  ++*this;
  return b;
}
//
//void BigInteger::routine() {
//  for (size_t i = 0; i < SIZE; ++i) {
//    if ()
//  }
//}
