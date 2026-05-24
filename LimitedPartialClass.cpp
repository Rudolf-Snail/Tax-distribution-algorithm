// Tax distribution algorithm — a tax distributing program
// Copyright (C) 2026  Martin Herchel

// This file is part of Tax distribution algorithm.
// Tax distribution algorithm is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
// Tax distribution algorithm is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
// You should have received a copy of the GNU General Public License along with Tax distribution algorithm. If not, see <https://www.gnu.org/licenses/>. 

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