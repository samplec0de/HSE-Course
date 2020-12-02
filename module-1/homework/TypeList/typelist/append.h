#pragma once

#include "typelist.h"

template<typename TList, typename NewType>
struct Append;
// Добавление NullType к NullType
template<>
struct Append<NullType, NullType> {
  typedef NullType NewTypeList;
};

// Добавление T к NullType
template<typename T>
struct Append<NullType, T> {
  typedef TypeList<T, NullType> NewTypeList;
};

// Добавление NullType к TypeList<X, Y>
template<typename X, typename Y>
struct Append<TypeList<X, Y>, NullType> {
  typedef TypeList<X, Y> NewTypeList;
};

// Добавление T к TypeList<X, Y>
template<typename X, typename Y, typename T>
struct Append<TypeList<X, Y>, T> {
  typedef TypeList<X, typename Append<Y, T>::NewTypeList> NewTypeList;
};

// Добавление T к TypeList<X, NullType>
template<typename X, typename T>
struct Append<TypeList<X, NullType>, T> {
  typedef TypeList<X, TypeList<T, NullType>> NewTypeList;
};
