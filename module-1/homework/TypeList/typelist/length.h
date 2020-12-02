#pragma once

#include "typelist.h"

template<typename TList> 
struct Length;

template<>
struct Length<NullType> {
  enum {
    length = 0
  };
};

template<typename X, typename Y>
struct Length<TypeList<X, Y>> {
  enum {
    length = Length<Y>::length + 1
  };
};
