//
// Created by Андрей Москалёв on 22.09.2020.
//
#include <stdio.h>
#include <stdint.h>
#include <iostream>
#include <string>

class Particle {
 public:
  Particle() = delete;

  Particle(unsigned short int R, unsigned short int G, unsigned short int B): m_R(R), m_G(G), m_B(B)
    {};

  std::string toString() {
    std::string s = "{";
    s += std::to_string(m_R);
    s += ", ";
    s += std::to_string(m_G);
    s += ", ";
    s += std::to_string(m_B);
    s += "}";
    return s;
  }

 private:
  unsigned short int m_R;
  unsigned short int m_G;
  unsigned short int m_B;
};

class Bullet {
 public:
  Bullet() = delete;

  Bullet(int32_t x, int32_t y, int32_t z, Particle* p)
    : m_x(x), m_y(y), m_z(z), m_particle(p)
  { };

  Bullet(const Bullet& other)
      : m_x(other.m_x), m_y(other.m_y), m_z(other.m_z), m_particle(other.m_particle)
  { };

  ~Bullet() = default;

  std::string particleString() {
    return m_particle->toString();
  }

 private:
  int32_t m_x;

  int32_t m_y;

  int32_t m_z;

  Particle * m_particle;

};

int main() {

  int32_t x = 0, y = 0, z = 0;
  Particle particle1(255, 255, 255);
  Bullet bullet(x, y, z, &particle1);
  Bullet bullet1 = bullet;
  std::cout << bullet1.particleString();
  return 0;
}
