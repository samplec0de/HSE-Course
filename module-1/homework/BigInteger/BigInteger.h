//
// Created by Андрей Москалёв on 13.09.2020.
//

#ifndef BIGINTEGER_BIGINTEGER_H
#define BIGINTEGER_BIGINTEGER_H
#include <ostream>
#include <istream>
#include <string>
#include <cmath>

#include <iostream>

const unsigned short RADIX = 1e4;
const unsigned short RADIX_N_POW = log10(RADIX);
const int DIGITS_COUNT = 1000;
const int SIZE = DIGITS_COUNT / 4;

class BigInteger {
 private:
  unsigned short digits[SIZE];
  void zeroize();
  bool ltz = false;
 public:
  BigInteger();
  BigInteger(int n);
  BigInteger(long long n);
  BigInteger(const std::string &n);
  BigInteger(const char *n);
  void fillFromString(const std::string &n);
  std::string toString() const;
  friend std::ostream &operator<<(std::ostream &out, const BigInteger &bint);
  friend std::istream &operator>>(std::istream &out, BigInteger &bint);
  BigInteger operator+(const BigInteger &other) const;
  BigInteger operator-(const BigInteger &other) const;
  BigInteger operator-() const;
  BigInteger operator+=(const BigInteger &other);
  BigInteger operator-=(const BigInteger &other);
  bool operator==(const BigInteger &other) const;
  bool operator!=(const BigInteger &other) const;
  bool operator>(const BigInteger &other) const;
  bool operator>=(const BigInteger &other) const;
  bool operator<(const BigInteger &other) const;
  bool operator<=(const BigInteger &other) const;
  explicit operator bool() const;
};

std::ostream &operator<<(std::ostream &out, const BigInteger &bint);
std::istream &operator>>(std::ostream &in, BigInteger &bint);

#endif //BIGINTEGER_BIGINTEGER_H
