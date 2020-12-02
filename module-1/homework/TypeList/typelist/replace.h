#pragma once

#include "typelist.h"

template<typename TList, typename OldType, typename NewType> 
struct Replace;

template<typename O, typename N>
struct Replace<NullType, O, N> {
  typedef NullType NewTypeList;
};

// Замена
template<typename Y, typename O, typename N>
struct Replace<TypeList<O, Y>, O, N> {
  typedef TypeList<N, typename Replace<Y, O, N>::NewTypeList> NewTypeList;
};


// Проталкивание
template<typename X, typename Y, typename O, typename N>
struct Replace<TypeList<X, Y>, O, N> {
  typedef TypeList<X, typename Replace<Y, O, N>::NewTypeList> NewTypeList;
};
