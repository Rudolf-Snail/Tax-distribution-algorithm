#ifndef IncomeGroupClass_cpp
#define IncomeGroupClass_cpp

#include "IncomeGroupClass.h"

#include <stdexcept>

// Private
// Private functions
void IncomeGroup::SetTaxOfIndividual(const long double taxOfIndividual)
{
    if (taxOfIndividual < 0)
        throw std::invalid_argument{"Tax of an individual cannot be smaller than 0."};

    this->taxOfIndividual = taxOfIndividual;
}

void IncomeGroup::SetTaxOfGroup(const long double taxOfGroup)
{
    if (taxOfGroup < 0)
        throw std::invalid_argument{"Tax of a group cannot be smaller than 0."};

    this->taxOfGroup = taxOfGroup;
}

constexpr long double IncomeGroup::CheckIncomeOfIndividual(const long double incomeOfIndividual)
{
    if (incomeOfIndividual < 0)
        throw std::invalid_argument{"Income of an individual cannot be smaller than 0."};

    return incomeOfIndividual;
}

constexpr long double IncomeGroup::CheckIncomeOfGroup(const long double incomeOfGroup)
{
    if (incomeOfGroup < 0)
        throw std::invalid_argument{"Income of a group cannot be smaller than 0."};

    return incomeOfGroup;
}

constexpr long long int IncomeGroup::CheckIndexOfStartOfGroup(const long long int indexOfStartOfGroup)
{
    if (indexOfStartOfGroup < 0)
        throw std::invalid_argument{"IndexOfStartOfGroup cannot be smaller than 0."};

    return indexOfStartOfGroup;
}

constexpr long long int IncomeGroup::CheckGroupSize(const long long int groupSize)
{
    if (groupSize <= 0)
        throw std::invalid_argument{"GroupSize cannot be 0 or smaller."};

    return groupSize;
}

constexpr long double IncomeGroup::CalculateIncomeOfIndividual(const long double incomeOfGroup, const long long int groupSize)
{
    return CheckIncomeOfIndividual(incomeOfGroup / groupSize);
}

constexpr long double IncomeGroup::CalculateIncomeOfGroup(const long double incomeOfIndividual, const long long int groupSize)
{
    return CheckIncomeOfGroup(incomeOfIndividual * groupSize);
}

constexpr LimitedPercentage IncomeGroup::CalculateIncomePercentile(const long long int indexOfStartOfGroup, const long long int sizeOfSortedIncome)
{
    if (indexOfStartOfGroup >= sizeOfSortedIncome || indexOfStartOfGroup < 0)
        throw std::out_of_range{"Index is out of the range of sortedIncome."};

    return (sizeOfSortedIncome == 1) ? LimitedPercentage(1.0L * 100) : LimitedPercentage(1.0L * indexOfStartOfGroup / (sizeOfSortedIncome - 1) * 100);
}

constexpr LimitedPercentage IncomeGroup::CalculateIncomePercentile(const long long int indexOfStartOfGroup, const std::vector<long double> &sortedIncome)
{
    return CalculateIncomePercentile(indexOfStartOfGroup, sortedIncome.size());
}

// Public
// Constructors
IncomeGroup::IncomeGroup(const long double incomeOfIndividual, const long long int indexOfStartOfGroup, const long long int groupSize, const long long int sizeOfSortedIncomes)
    : incomeOfIndividual{CheckIncomeOfIndividual(incomeOfIndividual)},
      indexOfStartOfGroup{CheckIndexOfStartOfGroup(indexOfStartOfGroup)},
      groupSize{CheckGroupSize(groupSize)},
      incomePercentile{CalculateIncomePercentile(indexOfStartOfGroup, sizeOfSortedIncomes)},

      incomeOfGroup{CalculateIncomeOfGroup(incomeOfIndividual, groupSize)}

{
    this->taxOfIndividual = 0;
    CalculateAndSetTaxOfGroup();
}

// Destructor
IncomeGroup::~IncomeGroup()
{
}

// Public functions
constexpr long double IncomeGroup::IncomeOfIndividual() const
{
    return incomeOfIndividual;
}

constexpr long double IncomeGroup::IncomeOfGroup() const
{
    return incomeOfGroup;
}

constexpr long long int IncomeGroup::IndexOfStartOfGroup() const
{
    return indexOfStartOfGroup;
}

constexpr long long int IncomeGroup::GroupSize() const
{
    return groupSize;
}

constexpr LimitedPercentage IncomeGroup::IncomePercentile() const
{
    return incomePercentile;
}

long double IncomeGroup::TaxOfIndividual() const
{
    return taxOfIndividual;
}

void IncomeGroup::SetTaxOfIndividualAndUpdateGroup(const long double taxOfIndividual)
{
    SetTaxOfIndividual(taxOfIndividual);

    CalculateAndSetTaxOfGroup();
}

long double IncomeGroup::TaxOfGroup() const
{
    return taxOfGroup;
}

void IncomeGroup::SetTaxOfGroupAndUpdateIndividual(const long double taxOfGroup)
{
    SetTaxOfGroup(taxOfGroup);

    CalculateAndSetTaxOfIndividual();
}

void IncomeGroup::CalculateAndSetTaxOfIndividual()
{
    SetTaxOfIndividual(TaxOfGroup() / GroupSize());
}

void IncomeGroup::CalculateAndSetTaxOfGroup()
{
    SetTaxOfGroup(TaxOfIndividual() * GroupSize());
}

#endif