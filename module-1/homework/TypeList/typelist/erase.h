#pragma once

#include "typelist.h"

template<typename TList, typename TargetType>
struct Erase;

// Тесты считают, что из NullType можно удалять
template<typename T>
struct Erase<NullType, T> {
  typedef NullType NewTypeList;
};

// Если ничего не нашлось
template<typename X, typename T>
struct Erase<TypeList<X, NullType>, T> {
  typedef TypeList<X, NullType> NewTypeList;
};

// Удаление из начала
template<typename X, typename Y, typename Z>
struct Erase<TypeList<X, TypeList<Y, Z>>, X> {
  typedef TypeList<Y, Z> NewTypeList;
};

// Удаление из конца
template<typename X, typename Y, typename Z, typename T>
struct Erase<TypeList<X, TypeList<Y, Z>>, T> {
  typedef TypeList<X, Erase<TypeList<Y, Z>, T>> name;
};