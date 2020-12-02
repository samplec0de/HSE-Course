#pragma once

#include "erase.h"
#include "typelist.h"

template<typename TList>
struct NoDuplicates;

template<>
struct NoDuplicates<NullType> {
  typedef NullType NewTypeList;
};

template<typename X, typename Y>
struct NoDuplicates<TypeList<X, Y>> {
  typedef TypeList<X, typename EraseAll<typename NoDuplicates<Y>::NewTypeList, X>::NewTypeList> NewTypeList;
};
