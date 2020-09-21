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
  BigInteger(int);
  BigInteger(long long);
  BigInteger(const std::string&);
  BigInteger(const char*);
  void fillFromString(const std::string&);
  std::string toString() const;
  friend std::ostream &operator<<(std::ostream&, const BigInteger&);
  friend std::istream &operator>>(std::istream&, BigInteger&);
  BigInteger operator+(const BigInteger&) const;
  BigInteger operator-(const BigInteger&) const;
  BigInteger& operator--();
  BigInteger operator-() const;
  BigInteger operator+=(const BigInteger&);
  BigInteger operator-=(const BigInteger&);
  bool operator==(const BigInteger&) const;
  bool operator!=(const BigInteger&) const;
  bool operator>(const BigInteger&) const;
  bool operator>=(const BigInteger&) const;
  bool operator<(const BigInteger&) const;
  bool operator<=(const BigInteger&) const;
  explicit operator bool() const;
};

std::ostream &operator<<(std::ostream&, const BigInteger&);
std::istream &operator>>(std::ostream&, BigInteger&);

#endif //BIGINTEGER_BIGINTEGER_H
