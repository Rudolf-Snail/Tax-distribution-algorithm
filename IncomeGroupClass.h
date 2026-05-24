// Tax distribution algorithm — a tax distributing program
// Copyright (C) 2026  Martin Herchel

// This file is part of Tax distribution algorithm.
// Tax distribution algorithm is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
// Tax distribution algorithm is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
// You should have received a copy of the GNU General Public License along with Tax distribution algorithm. If not, see <https://www.gnu.org/licenses/>. 

#ifndef IncomeGroupClass_h
#define IncomeGroupClass_h

#include <vector>

#include "LimitedRatioAndLimitedPercentageClasses.h"

class IncomeGroup
{
private:
    // Variables
    const long double incomeOfIndividual;
    const long double incomeOfGroup;

    long double taxOfIndividual;
    long double taxOfGroup;

    const long long int indexOfStartOfGroup;
    const long long int groupSize;

    const LimitedPercentage incomePercentile;

    // Functions
    void SetTaxOfIndividual(const long double taxOfIndividual);
    void SetTaxOfGroup(const long double taxOfGroup);

    static constexpr long double CheckIncomeOfIndividual(const long double incomeOfIndividual);

    static constexpr long double CheckIncomeOfGroup(const long double incomeOfGroup);

    static constexpr long long int CheckIndexOfStartOfGroup(const long long int indexOfStartOfGroup);

    static constexpr long long int CheckGroupSize(const long long int groupSize);

    static constexpr long double CalculateIncomeOfIndividual(const long double incomeOfGroup, const long long int groupSize);
    static constexpr long double CalculateIncomeOfGroup(const long double incomeOfIndividual, const long long int groupSize);

    static constexpr LimitedPercentage CalculateIncomePercentile(const long long int indexOfStartOfGroup, const long long int sizeOfSortedIncome);
    static constexpr LimitedPercentage CalculateIncomePercentile(const long long int indexOfStartOfGroup, const std::vector<long double> &sortedIncome);

public:
    // Constructors
    IncomeGroup(const long double incomeOfIndividual, const long long int indexOfStartOfGroup, const long long int groupSize, const long long int sizeOfSortedIncomes);
    // Destructors
    ~IncomeGroup();

    // Functions
    constexpr long double IncomeOfIndividual() const;
    constexpr long double IncomeOfGroup() const;
    constexpr long long int IndexOfStartOfGroup() const;
    constexpr long long int GroupSize() const;
    constexpr LimitedPercentage IncomePercentile() const;

    long double TaxOfIndividual() const;
    void SetTaxOfIndividualAndUpdateGroup(const long double taxOfIndividual);

    long double TaxOfGroup() const;
    void SetTaxOfGroupAndUpdateIndividual(const long double taxOfGroup);

    void CalculateAndSetTaxOfIndividual();
    void CalculateAndSetTaxOfGroup();
};

#endif