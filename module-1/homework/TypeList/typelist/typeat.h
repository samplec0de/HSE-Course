#pragma once

#include "typelist.h"

template<typename TList, unsigned int index>
struct TypeAt;

template<typename X, typename Y, unsigned int index>
struct TypeAt<TypeList<X, Y>, index> {
  typedef typename TypeAt<Y, index - 1>::TargetType TargetType;
};

template<typename T, typename U>
struct TypeAt<TypeList<T, U>, 0> {
  typedef T TargetType;
};

// Получаем не существующий (слишком большой индекс)
template<unsigned int index>
struct TypeAt<NullType, index> {
  typedef NullType TargetType;
};
