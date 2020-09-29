//
// Created by Андрей Москалёв on 29.09.2020.
//
#include "Car.h"
#include <vector>

int main() {
  Car car;
  std::vector<int> doorsColor = {1, 1, 2, 2};
  bool doors = car.buildDoors(doorsColor);
  bool engine = car.buildEngine(1000, 10);
  bool wheels = car.buildWheels("Tire-A", 12);
  bool meta = car.setMeta("1C", "1C-1");
  if (doors && engine && wheels && meta) {
    std::cout << "Car built";
  } else {
    std::cout << "Check errors";
  }
  return 0;
}