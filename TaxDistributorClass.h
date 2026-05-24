// Tax distribution algorithm — a tax distributing program
// Copyright (C) 2026  Martin Herchel

// This file is part of Tax distribution algorithm.
// Tax distribution algorithm is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
// Tax distribution algorithm is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
// You should have received a copy of the GNU General Public License along with Tax distribution algorithm. If not, see <https://www.gnu.org/licenses/>. 

#ifndef TaxDistributorClass_h
#define TaxDistributorClass_h

#include "IncomeGroupClass.cpp"
#include "LimitedReverseRatioClass.cpp"

#include <memory>
#include <algorithm>

class TaxDistributor
{
private:
    // Variables
    const std::shared_ptr<std::vector<long double>> sortedIncomes;
    std::shared_ptr<std::vector<IncomeGroup>> incomeGroups;

    long double totalIncome;

    const LimitedPercentage taxPercentage;
    long double totalTax;
    long double taxRemaining;

    LimitedPercentage lastPercentile;
    long double highestIndividualIncome;

    // Functions
    constexpr void CheckIncome(const std::vector<long double> &incomes) const;
    constexpr std::shared_ptr<std::vector<long double>> SortIncome(const std::vector<long double> &incomes) const;

    void GroupIntoIncomeGroupsAndCalculateTotalIncome();

    void SetUpAllNeededVariables();

    void CalculateTotalTaxAndSetTaxRemaining();

    void SetLastPercentileAndHighestIndividualIncome();

    constexpr long double CalculateLowerTaxRange(const IncomeGroup &previousIncomeGroup) const;
    constexpr long double CalculateUpperTaxRange(const IncomeGroup &previousIncomeGroup, const IncomeGroup &currentIncomeGroup) const;

    constexpr long double CalculateTaxForIncomeGroup(const long double lowerTaxRange, const long double upperTaxRange, IncomeGroup &previousIncomeGroup, IncomeGroup &currentIncomeGroup) const;
    constexpr void CalculateRatioOutOfTotalTaxForIncomeGroups();

    constexpr void CalculateTaxesForIncomeGroups();

public:
    // Constructors
    TaxDistributor(const std::vector<long double> &incomes, const LimitedPercentage taxPercentage);
    // Destructor
    ~TaxDistributor();

    // Functions
    constexpr void DistributeTax();

    constexpr std::shared_ptr<std::vector<long double>> SortedIncomes() const;
    const std::shared_ptr<std::vector<IncomeGroup>> IncomeGroups() const;

    constexpr long double TotalIncome() const;
    constexpr LimitedPercentage TaxPercentage() const;
    constexpr long double TotalTax() const;
    constexpr long double TaxRemaining() const;
    constexpr LimitedPercentage LastPercentile() const;
    constexpr long double HighestIndividualIncome() const;
};

#endif