#pragma once

#include "typelist.h"

template<typename TList, typename TargetType>
struct EraseAll;

// Тесты считают, что удаление из NullType легитимно
template<typename T>
struct EraseAll<NullType, T> {
  typedef NullType NewTypeList;
};

// Удаление из последнего
template<typename X>
struct EraseAll<TypeList<X, NullType>, X> {
  typedef NullType NewTypeList;
};

// Конец удаления
template<typename X, typename T>
struct EraseAll<TypeList<X, NullType>, T> {
  typedef TypeList<X, NullType> NewTypeList;
};

// Удаление из начала
template<typename X, typename Y, typename Z>
struct EraseAll<TypeList<X, TypeList<Y, Z>>, X> {
  typedef typename EraseAll<TypeList<Y, Z>, X>::NewTypeList NewTypeList;
};

// Проталкивание процесса удаления
template<typename X, typename Y, typename Z, typename T>
struct EraseAll<TypeList<X, TypeList<Y, Z>>, T> {
  typedef TypeList<X, typename EraseAll<TypeList<Y, Z>, X>::NewTypeList> NewTypeList;
};
