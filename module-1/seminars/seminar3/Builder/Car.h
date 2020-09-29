//
// Created by Андрей Москалёв on 29.09.2020.
//

#ifndef BIGINTEGER_MODULE_1_SEMINARS_SEMINAR3_CAR_H_
#define BIGINTEGER_MODULE_1_SEMINARS_SEMINAR3_CAR_H_
#include <iostream>
#include <string>
#include <vector>

class Car {
  std::string manufacturer;
  std::string model;
  std::string wheelModel;
  int mainColor;
  int wheelSize;
  std::vector<int> doors;
  int enginePower;
  int engineLitters;
 public:
  Car();

  bool buildDoors(std::vector<int>& colors);
  bool buildEngine(int power, int litters);
  bool buildWheels(const std::string& model, int size);
  bool setMeta(const std::string& manufacturerName, const std::string& modelName);
  bool addDoor(int color);

};

#endif //BIGINTEGER_MODULE_1_SEMINARS_SEMINAR3_CAR_H_
