// Tax distribution algorithm — a tax distributing program
// Copyright (C) 2026  Martin Herchel

// This file is part of Tax distribution algorithm.
// Tax distribution algorithm is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
// Tax distribution algorithm is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
// You should have received a copy of the GNU General Public License along with Tax distribution algorithm. If not, see <https://www.gnu.org/licenses/>. 

#ifndef LimitedRatioAndLimitedPercentageClasses_h
#define LimitedRatioAndLimitedPercentageClasses_h

#include "LimitedPartialClass.cpp"

class LimitedPercentage;

class LimitedRatio : public LimitedPartial
{
protected:
    // Functions
    virtual constexpr long double CheckValue(const long double value) const override;

    virtual void SetValue(const LimitedRatio &ratio);
    virtual void SetValue(const LimitedPercentage &percentage);

public:
    // Constructors
    LimitedRatio() = default;
    LimitedRatio(const LimitedRatio &ratio);
    LimitedRatio(const long double ratioOfValues);
    LimitedRatio(const long double smallerOrEqualValue, const long double biggerOrEqualValue);
    LimitedRatio(const LimitedPercentage &percentage);
    // Destructor
    ~LimitedRatio();

    // Functions
    LimitedPercentage ConvertToPercentage() const;

    // Operator overloading
    virtual long double operator()() const override;

    virtual void operator()(const long double smallerOrEqualValue, const long double biggerOrEqualValue) override;
    virtual void operator()(const LimitedPercentage &percentage);

    virtual LimitedRatio &operator=(const LimitedRatio &value);
    virtual LimitedRatio &operator=(const long double value) override;
};

class LimitedPercentage : public LimitedPartial
{
protected:
    // Functions
    virtual constexpr long double CheckValue(const long double value) const override;

    virtual void SetValue(const LimitedPercentage &percentage);
    virtual void SetValue(const LimitedRatio &ratio);

    virtual constexpr long double CalculateValue(const long double smallerOrEqualValue, const long double biggerOrEqualValue) const override;

public:
    // Constructors
    LimitedPercentage() = default;
    LimitedPercentage(const LimitedPercentage &percentage);
    LimitedPercentage(const long double percentageOfValues);
    LimitedPercentage(const long double smallerOrEqualValue, const long double biggerOrEqualValue);
    LimitedPercentage(const LimitedRatio &ratio);
    // Destructor
    ~LimitedPercentage();

    // Functions
    LimitedRatio ConvertToRatio() const;

    // Operator overloading
    virtual long double operator()() const override;

    virtual void operator()(const long double smallerOrEqualValue, const long double biggerOrEqualValue) override;
    virtual void operator()(const LimitedRatio &ratio);

    virtual LimitedPercentage &operator=(const LimitedPercentage &value);
    virtual LimitedPercentage &operator=(const long double value) override;
};

#endif