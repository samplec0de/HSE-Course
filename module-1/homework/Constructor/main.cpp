//
// Created by Андрей Москалёв on 22.09.2020.
//
#include <stdio.h>
#include <stdint.h>

class Bullet {
 public:
  Bullet() = delete;

  Bullet(int32_t x, int32_t y, int32_t z)
    : m_x(x), m_y(y), m_z(z)
  { };

  Bullet(const Bullet& other)
      : m_x(other.m_x), m_y(other.m_y), m_z(other.m_z)
  { };

  ~Bullet() = default;

 private:
  int32_t m_x;

  int32_t m_y;

  int32_t m_z;

};

int main() {

  int32_t x = 0, y = 0, z = 0;
  Bullet bullet(x, y, z);
  Bullet bullet1 = bullet;
  return 0;
}
