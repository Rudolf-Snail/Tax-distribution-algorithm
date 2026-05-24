// Tax distribution algorithm — a tax distributing program
// Copyright (C) 2026  Martin Herchel

// This file is part of Tax distribution algorithm.
// Tax distribution algorithm is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
// Tax distribution algorithm is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
// You should have received a copy of the GNU General Public License along with Tax distribution algorithm. If not, see <https://www.gnu.org/licenses/>. 

#ifndef LimitedReverseRatioClass_h
#define LimitedReverseRatioClass_h

#include "LimitedRatioAndLimitedPercentageClasses.cpp"

class LimitedReverseRatio : public LimitedRatio
{
protected:
    // Functions
    virtual void SetValue(const LimitedReverseRatio &ratio);
    virtual void SetValue(const LimitedRatio &ratio) override;

    virtual constexpr long double CalculateValue(const long double smallerOrEqualValue, const long double biggerOrEqualValue) const;
    virtual constexpr long double CalculateValue(const LimitedRatio &ratio) const;

public:
    // Constructors
    LimitedReverseRatio() = default;
    LimitedReverseRatio(const LimitedReverseRatio &reverseRatioOfValues);
    LimitedReverseRatio(const LimitedRatio &ratio);
    LimitedReverseRatio(const long double reverseRatioOfValues);
    LimitedReverseRatio(const long double smallerOrEqualValue, const long double biggerOrEqualValue);
    // Destructor
    ~LimitedReverseRatio();

    // Functions
    LimitedRatio ConvertToRatio();

    // Operator overloading
    virtual long double operator()() const override;

    virtual void operator()(const long double smallerOrEqualValue, const long double biggerOrEqualValue) override;
    virtual void operator()(const LimitedRatio &value);

    virtual LimitedReverseRatio &operator=(const LimitedReverseRatio &value);
    virtual LimitedReverseRatio &operator=(const long double value) override;
};

#endif