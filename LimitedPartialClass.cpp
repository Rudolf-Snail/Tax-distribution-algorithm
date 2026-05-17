#ifndef LimitedPartialClass_cpp
#define LimitedPartialClass_cpp

#include "LimitedPartialClass.h"

// Protected
// Protected functions
constexpr void LimitedPartial::CheckValues(const long double smallerOrEqualValue, const long double biggerOrEqualValue) const
{
    Partial::CheckValues(smallerOrEqualValue, biggerOrEqualValue);

    if (smallerOrEqualValue > biggerOrEqualValue)
        throw std::invalid_argument{"The smallerOrEqualValue cannot be bigger than the biggerOrEqualValue."};
}

// Public
// Destructor
LimitedPartial::~LimitedPartial()
{
}

#endif