#ifndef LimitedRatioAndLimitedPercentageClasses_cpp
#define LimitedRatioAndLimitedPercentageClasses_cpp

#include "LimitedRatioAndLimitedPercentageClasses.h"

// LimitedRatio class

// Protected
// Protected functions
constexpr long double LimitedRatio::CheckValue(const long double ratioOfValues) const
{
    if (ratioOfValues < 0 || ratioOfValues > 1)
        throw std::invalid_argument{"The ratioOfValues cannot be smaller than 0 or larger than 1."};

    return ratioOfValues;
}

void LimitedRatio::SetValue(const LimitedRatio &ratio)
{
    this->value = ratio();
}

void LimitedRatio::SetValue(const LimitedPercentage &percentage)
{
    this->value = (percentage.ConvertToRatio())();
}

// Public
// Constructors
LimitedRatio::LimitedRatio(const LimitedRatio &ratio)
{
    *this = ratio;
}

LimitedRatio::LimitedRatio(const long double ratioOfValues)
{
    *this = ratioOfValues;
}

LimitedRatio::LimitedRatio(const long double smallerOrEqualValue, const long double biggerOrEqualValue)
{
    (*this)(smallerOrEqualValue, biggerOrEqualValue);
}

LimitedRatio::LimitedRatio(const LimitedPercentage &percentage)
{
    (*this)(percentage);
}

// Destructor
LimitedRatio::~LimitedRatio()
{
}

// Public functions
LimitedPercentage LimitedRatio::ConvertToPercentage() const
{
    return LimitedPercentage((*this)() * 100);
}

// Operator overloading
long double LimitedRatio::operator()() const
{
    return value;
}

void LimitedRatio::operator()(const long double smallerOrEqualValue, const long double biggerOrEqualValue)
{
    Partial::operator()(smallerOrEqualValue, biggerOrEqualValue);
}

void LimitedRatio::operator()(const LimitedPercentage &percentage)
{
    SetValue(percentage);
}

LimitedRatio &LimitedRatio::operator=(const LimitedRatio &value)
{
    SetValue(value);

    return *this;
}

LimitedRatio &LimitedRatio::operator=(const long double value)
{
    Partial::operator=(value);

    return *this;
}

// LimitedPercentage class

// Protected
// Protected functions
constexpr long double LimitedPercentage::CheckValue(const long double percentageOfValues) const
{
    if (percentageOfValues < 0 || percentageOfValues > 100)
        throw std::invalid_argument{"The percentageOfValues cannot be smaller than 0 or bigger than 100."};

    return percentageOfValues;
}
void LimitedPercentage::SetValue(const LimitedPercentage &percentage)
{
    this->value = percentage();
}
void LimitedPercentage::SetValue(const LimitedRatio &ratio)
{
    this->value = (ratio.ConvertToPercentage())();
}

constexpr long double LimitedPercentage::CalculateValue(const long double smallerOrEqualValue, const long double biggerOrEqualValue) const
{
    return Partial::CalculateValue(smallerOrEqualValue, biggerOrEqualValue) * 100;
}

// Public
// Constructors
LimitedPercentage::LimitedPercentage(const LimitedPercentage &percentage)
{
    *this = percentage;
}

LimitedPercentage::LimitedPercentage(const long double percentageOfValues)
{
    *this = percentageOfValues;
}

LimitedPercentage::LimitedPercentage(const long double smallerOrEqualValue, const long double biggerOrEqualValue)
{
    (*this)(smallerOrEqualValue, biggerOrEqualValue);
}

LimitedPercentage::LimitedPercentage(const LimitedRatio &ratio)
{
    (*this)(ratio);
}
// Destructor
LimitedPercentage::~LimitedPercentage()
{
}

// Public functions
LimitedRatio LimitedPercentage::ConvertToRatio() const
{
    return LimitedRatio((*this)() / 100);
}

// Operator overloading
long double LimitedPercentage::operator()() const
{
    return value;
}

void LimitedPercentage::operator()(const long double smallerOrEqualValue, const long double biggerOrEqualValue)
{
    Partial::operator()(smallerOrEqualValue, biggerOrEqualValue);
}

void LimitedPercentage::operator()(const LimitedRatio &ratio)
{
    SetValue(ratio);
}

LimitedPercentage &LimitedPercentage::operator=(const LimitedPercentage &value)
{
    SetValue(value);

    return *this;
}

LimitedPercentage &LimitedPercentage::operator=(const long double value)
{
    Partial::operator=(value);

    return *this;
}

#endif