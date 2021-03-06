//
// Created by Андрей Москалёв on 13.09.2020.
//

#include "biginteger.h"

void print_digit(std::string &out, unsigned short digit) {
  std::string s = std::to_string(digit);
  while (s.size() < RADIX_N_POW) {
    s.insert(s.begin(), '0');
  }
  out += s;
}

std::string BigInteger::toString() const {
  std::string representation;
  if (isNegative) {
    representation += '-';
  }
  bool was_digit = false;
  for (size_t i = SIZE - 1; i > 0; --i) {
    if (!digits[i]) {
      if (was_digit)
        print_digit(representation, digits[i]);
    } else {
      if (was_digit)
        print_digit(representation, digits[i]);
      else {
        was_digit = true;
        representation += std::to_string(digits[i]);
      }
    }
  }
  if (was_digit)
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
  for (size_t i = 0; i < SIZE; ++i)
    digits[i] = 0;
}

void BigInteger::fillFromString(const std::string &n) {
  zeroize();
  std::string s;
  size_t ind = 0;
  int to = 0;
  if (n[to] == '-') {
    ++to;
    isNegative = true;
  }
  for (int i = int(n.size() - 1); i >= to; --i) {
    s.insert(s.begin(), n[i]);
    if (s.size() == RADIX_N_POW) {
      digits[ind++] = std::stoi(s);
      s.clear();
    }
  }
  if (!s.empty())
    digits[ind] = std::stoi(s);
}


BigInteger::BigInteger(int n) {
  zeroize();
  if (n < 0) {
    isNegative = true;
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
    isNegative = true;
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
    isNegative = true;
  }
  for (int i = int(n.size()) - 1; i >= to; --i) {
    s.insert(s.begin(), n[i]);
    if (s.size() == RADIX_N_POW) {
      digits[ind++] = std::stoi(s);
      s.clear();
    }
  }
  if (!s.empty())
    digits[ind] = std::stoi(s);
}

BigInteger BigInteger::operator+(const BigInteger &other) const {
  BigInteger b = *this;
  return b += other;
}

BigInteger BigInteger::operator-(const BigInteger &other) const {
  BigInteger a = *this;
  return a -= other;
}

bool BigInteger::operator==(const BigInteger &other) const {
  for (size_t i = 0; i < SIZE; ++i)
    if (isNegative == other.isNegative && digits[i] != other.digits[i])
      return false;
  return true;
}

bool BigInteger::operator>(const BigInteger &other) const {
  if (isNegative && !other.isNegative)
    return false;
  if (!isNegative && other.isNegative)
    return true;
  if (*this == other)
    return false;
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
  if (!isNegative) {
    if (lastNonZeroLeft == lastNonZeroRight)
      return bigger;
    return lastNonZeroLeft > lastNonZeroRight;
  }
  if (lastNonZeroLeft == lastNonZeroRight)
    return !bigger;
  return lastNonZeroLeft < lastNonZeroRight;
}

bool BigInteger::operator<(const BigInteger &other) const {
  if (*this == other)
    return false;
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

BigInteger& BigInteger::operator+=(const BigInteger &other) {
  if ((!isNegative && !other.isNegative) || (isNegative && other.isNegative)) { // Оба операнда одного знака
    for (size_t i = 0; i < SIZE; ++i) {
      digits[i] += other.digits[i];
      if (digits[i] >= RADIX) {
        digits[i + 1] += digits[i] / RADIX;
        digits[i] %= RADIX;
      }
    }
    if (isNegative && other.isNegative) // Оба операнда отрицательные
      isNegative = true;
    return *this;
  } else if (isNegative && !other.isNegative) { // Левый операнд отрицательный, правый положительный
    if (greaterByAbsoluteValue(other, *this)) {
      // тут надо из other вычесть this, без доп памяти никак
      BigInteger result = other;
      for (size_t i = 0; i < SIZE; ++i) {
        if (result.digits[i] < digits[i]) {
          size_t j;
          for (j = i + 1; j < SIZE; ++j) {
            if (result.digits[j] > 0) {
              --result.digits[j];
              break;
            }
          }
          for (j = j - 1; j > i; --j) {
            result.digits[j] += RADIX - 1;
          }
          result.digits[i] += RADIX;
        }
        result.digits[i] -= digits[i];
      }
      return *this = result;
    } else {
      for (size_t i = 0; i < SIZE; ++i) {
        if (digits[i] < other.digits[i]) {
          size_t j;
          for (j = i + 1; j < SIZE; ++j) {
            if (digits[j] > 0) {
              --digits[j];
              break;
            }
          }
          for (j = j - 1; j > i; --j) {
            digits[j] += RADIX - 1;
          }
          digits[i] += RADIX;
        }
        digits[i] -= other.digits[i];
      }
      return *this;
    }
  } else { // Левый операнд положительный, правый отрицательный
    if (greaterByAbsoluteValue(*this, other)) {
      for (size_t i = 0; i < SIZE; ++i) {
        if (digits[i] < other.digits[i]) {
          size_t j;
          for (j = i + 1; j < SIZE; ++j) {
            if (digits[j] > 0) {
              --digits[j];
              break;
            }
          }
          for (j = j - 1; j > i; --j) {
            digits[j] += RADIX - 1;
          }
          digits[i] += RADIX;
        }
        digits[i] -= other.digits[i];
      }
      return *this;
    } else {
      // тут надо из other вычесть this, без доп памяти никак
      BigInteger result = other;
      for (size_t i = 0; i < SIZE; ++i) {
        if (result.digits[i] < digits[i]) {
          size_t j;
          for (j = i + 1; j < SIZE; ++j) {
            if (result.digits[j] > 0) {
              --result.digits[j];
              break;
            }
          }
          for (j = j - 1; j > i; --j) {
            result.digits[j] += RADIX - 1;
          }
          result.digits[i] += RADIX;
        }
        result.digits[i] -= digits[i];
      }
      return *this = result;
    }
  }
}

BigInteger& BigInteger::operator-=(const BigInteger &other) {
  if (!isNegative && !other.isNegative) {
    if (other <= *this) {
      for (size_t i = 0; i < SIZE; ++i) {
        if (digits[i] < other.digits[i]) {
          size_t j;
          for (j = i + 1; j < SIZE; ++j) {
            if (digits[j] > 0) {
              --digits[j];
              break;
            }
          }
          for (j = j - 1; j > i; --j) {
            digits[j] += RADIX - 1;
          }
          digits[i] += RADIX;
        }
        digits[i] -= other.digits[i];
      }
      return *this;
    } else {
      // нужно из other вычесть *this, без доп памяти никак
      BigInteger result = other;
      for (size_t i = 0; i < SIZE; ++i) {
        if (result.digits[i] < digits[i]) {
          size_t j;
          for (j = i + 1; j < SIZE; ++j) {
            if (result.digits[j] > 0) {
              --result.digits[j];
              break;
            }
          }
          for (j = j - 1; j > i; --j) {
            result.digits[j] += RADIX - 1;
          }
          result.digits[i] += RADIX;
        }
        result.digits[i] -= digits[i];
      }
      result.isNegative = true;
      return *this = result;
    }
  } else if (isNegative && other.isNegative) { // Оба отрицательные, к *this надо прибавить |other|
    if (greaterByAbsoluteValue(other, *this)) { // Надо из |other| вычесть *this
      // Надо вычесть из other *this, никак без доп памяти
      BigInteger result = other;
      result.isNegative = false;
      for (size_t i = 0; i < SIZE; ++i) {
        if (result.digits[i] < digits[i]) {
          size_t j;
          for (j = i + 1; j < SIZE; ++j) {
            if (result.digits[j] > 0) {
              --result.digits[j];
              break;
            }
          }
          for (j = j - 1; j > i; --j) {
            result.digits[j] += RADIX - 1;
          }
          result.digits[i] += RADIX;
        }
        result.digits[i] -= digits[i];
      }
      return *this = result;
    } else {
      // Надо из this вычесть other
      for (size_t i = 0; i < SIZE; ++i) {
        if (digits[i] < other.digits[i]) {
          size_t j;
          for (j = i + 1; j < SIZE; ++j) {
            if (digits[j] > 0) {
              --digits[j];
              break;
            }
          }
          for (j = j - 1; j > i; --j) {
            digits[j] += RADIX - 1;
          }
          digits[i] += RADIX;
        }
        digits[i] -= other.digits[i];
      }
      return *this;
    }
  } else if (isNegative && !other.isNegative) { // Левый отрицательный, правый положительный
    isNegative = false;
    *this += other;
    isNegative = true;
    return *this;
  } else { // Левый положительный, правый отрицательный
    // Нужно сложить абсолютные значения
    for (size_t i = 0; i < SIZE; ++i) {
      digits[i] += other.digits[i];
      if (digits[i] >= RADIX) {
        digits[i + 1] += digits[i] / RADIX;
        digits[i] %= RADIX;
      }
    }
    return *this;
  }
}

BigInteger BigInteger::operator-() const {
  BigInteger result = *this;
  result.isNegative = !result.isNegative;
  return result;
}

BigInteger &BigInteger::operator--() {
  return *this -= 1;
}

const BigInteger BigInteger::operator--(int) {
  BigInteger b = *this;
  --*this;
  return b;
}

BigInteger &BigInteger::operator++() {
  return *this += 1;
}

const BigInteger BigInteger::operator++(int) {
  BigInteger b = *this;
  ++*this;
  return b;
}

BigInteger BigInteger::operator*(const BigInteger &other) const {
  size_t digitsCountLeft = 0, digitsCountRight = 0;
  bool newLtz = ((short int)(isNegative) + other.isNegative) % 2;
  for (size_t i = 0; i < SIZE; ++i) {
    if (digits[i] != 0) {
      digitsCountLeft = i;
    }
    if (other.digits[i] != 0) {
      digitsCountRight = i;
    }
  }
  ++digitsCountLeft;
  ++digitsCountRight;
  BigInteger results[digitsCountRight];
  for (size_t i = 0; i < digitsCountRight; ++i) {
    for (size_t j = 0; j < digitsCountLeft; ++j) {
      int cur = int(digits[j]) * other.digits[i] + results[i].digits[j + i];
      results[i].digits[j + i] = cur % RADIX;
      results[i].digits[j + i + 1] += cur / RADIX;
    }
  }
  for (size_t i = 1; i < digitsCountRight; ++i) {
    results[0] += results[i];
  }
  results[0].isNegative = newLtz;
  return results[0];
}

BigInteger& BigInteger::operator*=(const BigInteger &other) {
  BigInteger result = *this;
  result = result * other;
  return *this = result;
}

BigInteger BigInteger::operator/(const BigInteger &other) const {
  short int lastDigitIndex = 0;
  for (short int  i = 0; i < SIZE; ++i) {
    if (digits[i] != 0) {
      lastDigitIndex = i;
    }
  }

  int buffer[SIZE];
  short int bufferIndex = 0;
  for (int & i : buffer) i = 0;
  BigInteger currentInteger = 0;
  BigInteger left = 0, right = RADIX + 1, middle;
  while (lastDigitIndex >= 0) {
    currentInteger = currentInteger * RADIX + digits[lastDigitIndex--];
    if (currentInteger < other && currentInteger != 0)
      continue;

    left = 0;
    right = RADIX + 1;
    while (right - left > 1) {
      middle = left + (right - left).divide2();
      if (other * middle > currentInteger) {
        right = middle;
      } else {
        left = middle;
      }
    }
    buffer[bufferIndex++] = stoi(left.toString());
    currentInteger = currentInteger - other * left;
  }
  BigInteger result(buffer, --bufferIndex);
  result.isNegative = ((short int)(isNegative) + other.isNegative) % 2;
  return result;
}

BigInteger BigInteger::divide2() const {
  short int lastDigitIndex = 0;
  for (short int  i = 0; i < SIZE; ++i) {
    if (digits[i] != 0) {
      lastDigitIndex = i;
    }
  }

  int buffer[SIZE];
  short int bufferIndex = 0;
  for (int & i : buffer) i = 0;
  int currentInteger = 0;
  while (lastDigitIndex >= 0) {
    currentInteger = currentInteger * RADIX + digits[lastDigitIndex--];
    if (currentInteger < 2) {
      if (lastDigitIndex >= 0) {
        currentInteger = currentInteger * RADIX + digits[lastDigitIndex--];
      }
    }
    buffer[bufferIndex++] = currentInteger / 2;
    currentInteger = currentInteger % 2;
  }
  return BigInteger(buffer, --bufferIndex);
}

BigInteger::BigInteger(const int *reversedDigits, short int indexOther) {
  zeroize();
  short int index = 0;
  for (; indexOther >= 0; --indexOther) {
    digits[index++] = reversedDigits[indexOther];
  }
}

BigInteger& BigInteger::operator/=(const BigInteger &other) {
  return *this = *this / other;
}

BigInteger BigInteger::operator%(const BigInteger &other) const {
  return *this - (*this / other) * other;
}

BigInteger& BigInteger::operator%=(const BigInteger &other) {
  return *this = *this % other;
}

BigInteger::~BigInteger() {
  delete[] digits;
}

BigInteger::BigInteger(const BigInteger &bint) {
  isNegative = bint.isNegative;
  for (size_t i = 0; i < SIZE; ++i)
    digits[i] = bint.digits[i];
}

BigInteger& BigInteger::operator=(const BigInteger &bint) {
  if (this == &bint) return *this;
  isNegative = bint.isNegative;
  for (size_t i = 0; i < SIZE; ++i)
    digits[i] = bint.digits[i];
  return *this;
}

bool greaterByAbsoluteValue(const BigInteger& a, const BigInteger& b) {
  bool bigger = false;
  size_t lastNonZeroLeft = 0;
  size_t lastNonZeroRight = 0;
  for (size_t i = 0; i < SIZE; ++i) {
    if (a.digits[i]) lastNonZeroLeft = i;
    if (b.digits[i]) lastNonZeroRight = i;
  }
  if (lastNonZeroLeft == lastNonZeroRight) {
    for (short int i = lastNonZeroLeft; i >= 0; --i) {
      if (a.digits[i] > b.digits[i]) {
        bigger = true;
      } else if (a.digits[i] < b.digits[i]) {
        break;
      }
    }
  }
  if (lastNonZeroLeft == lastNonZeroRight)
    return bigger;
  return lastNonZeroLeft > lastNonZeroRight;
}
