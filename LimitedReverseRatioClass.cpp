// Tax distribution algorithm — a tax distributing program
// Copyright (C) 2026  Martin Herchel

// This file is part of Tax distribution algorithm.
// Tax distribution algorithm is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
// Tax distribution algorithm is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
// You should have received a copy of the GNU General Public License along with Tax distribution algorithm. If not, see <https://www.gnu.org/licenses/>. 

#ifndef LimitedReverseRatioClass_cpp
#define LimitedReverseRatioClass_cpp

#include "LimitedReverseRatioClass.h"

// Protected
// Protected functions
void LimitedReverseRatio::SetValue(const LimitedReverseRatio &ratio)
{
    this->value = ratio();
}

void LimitedReverseRatio::SetValue(const LimitedRatio &ratio)
{
    this->value = CalculateValue(ratio);
}

constexpr long double LimitedReverseRatio::CalculateValue(const long double smallerOrEqualValue, const long double biggerOrEqualValue) const
{
    return CalculateValue(LimitedRatio::CalculateValue(smallerOrEqualValue, biggerOrEqualValue));
}

constexpr long double LimitedReverseRatio::CalculateValue(const LimitedRatio &ratio) const
{
    return 1 - ratio();
}

// Public
// Constructors
LimitedReverseRatio::LimitedReverseRatio(const LimitedReverseRatio &reverseRatioOfValues)
{
    *this = reverseRatioOfValues;
}

LimitedReverseRatio::LimitedReverseRatio(const LimitedRatio &ratio)
{
    *this = ratio;
}

LimitedReverseRatio::LimitedReverseRatio(const long double reverseRatioOfValues)
{
    *this = reverseRatioOfValues;
}

LimitedReverseRatio::LimitedReverseRatio(const long double smallerOrEqualValue, const long double biggerOrEqualValue)
{
    (*this)(smallerOrEqualValue, biggerOrEqualValue);
}

// Destructor
LimitedReverseRatio::~LimitedReverseRatio()
{
}

// Public functions
LimitedRatio LimitedReverseRatio::ConvertToRatio()
{
    return LimitedRatio(CalculateValue((*this)()));
}

// Operator overloading
long double LimitedReverseRatio::operator()() const
{
    return value;
}

void LimitedReverseRatio::operator()(const long double smallerOrEqualValue, const long double biggerOrEqualValue)
{
    Partial::operator()(smallerOrEqualValue, biggerOrEqualValue);
}

void LimitedReverseRatio::operator()(const LimitedRatio &value)
{
    SetValue(value);
}

LimitedReverseRatio &LimitedReverseRatio::operator=(const LimitedReverseRatio &value)
{
    SetValue(value);

    return (*this);
}
LimitedReverseRatio &LimitedReverseRatio::operator=(const long double value)
{
    Partial::operator=(value);

    return (*this);
}

#endif