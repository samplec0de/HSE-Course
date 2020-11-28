#pragma once

#include "typelist.h"

template<typename TList, typename TargetType>
struct IndexOf;

template<typename T>
struct IndexOf<NullType, T> {
  enum {
    pos = -1
  };
};

template<typename T>
struct IndexOf<TypeList<T, NullType>, T> {
  enum {
    pos = 0
  };
};

template<typename X, typename T>
struct IndexOf<TypeList<X, NullType>, T> {
  enum {
    pos = -1
  };
};

template<typename X, typename Y, typename Z, typename T>
struct IndexOf<TypeList<X, TypeList<Y, Z>>, T> {
  enum {
    pos = IndexOf<TypeList<Y, Z>, T>::pos == -1 ? -1 : IndexOf<TypeList<Y, Z>, T>::pos + 1
  };
};
