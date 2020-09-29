//
// Created by Андрей Москалёв on 29.09.2020.
//

#include "Car.h"

Car::Car() {
    mainColor = 0;
    enginePower = 0;
}

bool Car::buildDoors(std::vector<int>& colors) {
  for (int color : colors) {
    addDoor(color);
  }
  return true;
}

bool Car::buildEngine(int power, int litters) {
  enginePower = power;
  engineLitters = litters;
  return true;
}

bool Car::setMeta(const std::string& manufacturerName, const std::string& modelName) {
  manufacturer = manufacturerName;
  model = modelName;
  return true;
}

bool Car::addDoor(int color) {
  if (doors.size() < 5) {
    doors.push_back(color);
    return true;
  }
  return false;
}

bool Car::buildWheels(const std::string& model, int size) {
  wheelModel = model;
  wheelSize = size;
  return true;
}
