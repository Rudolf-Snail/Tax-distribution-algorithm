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