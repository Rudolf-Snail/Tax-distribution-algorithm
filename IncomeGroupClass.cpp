#include "IncomeGroupClass.h"

#include <stdexcept>

// Private
// Private functions
inline void IncomeGroup::SetTaxOfIndividual(const long double taxOfIndividual)
{
    if (taxOfIndividual < 0)
        throw std::invalid_argument{"Tax of an individual cannot be smaller than 0."};

    this->taxOfIndividual = taxOfIndividual;
}

inline void IncomeGroup::SetTaxOfGroup(const long double taxOfGroup)
{
    if (taxOfGroup < 0)
        throw std::invalid_argument{"Tax of a group cannot be smaller than 0."};

    this->taxOfGroup = taxOfGroup;
}

constexpr inline long double IncomeGroup::CheckIncomeOfIndividual(const long double incomeOfIndividual)
{
    if (incomeOfIndividual < 0)
        throw std::invalid_argument{"Income of an individual cannot be smaller than 0."};

    return incomeOfIndividual;
}

constexpr inline long double IncomeGroup::CheckIncomeOfGroup(const long double incomeOfGroup)
{
    if (incomeOfGroup < 0)
        throw std::invalid_argument{"Income of a group cannot be smaller than 0."};

    return incomeOfGroup;
}

constexpr inline long long int IncomeGroup::CheckIndexOfStartOfGroup(const long long int indexOfStartOfGroup)
{
    if (indexOfStartOfGroup < 0)
        throw std::invalid_argument{"IndexOfStartOfGroup cannot be smaller than 0."};

    return indexOfStartOfGroup;
}

constexpr inline long long int IncomeGroup::CheckGroupSize(const long long int groupSize)
{
    if (groupSize < 0)
        throw std::invalid_argument{"GroupSize cannot be smaller than 0;"};

    return groupSize;
}

constexpr inline long double IncomeGroup::CheckIncomePercentile(const long double incomePercentile)
{
    if (incomePercentile < 0 || incomePercentile > 100)
        throw std::invalid_argument{"IncomePercentile cannot be smaller than 0 or bigger than 100."};

    return incomePercentile;
}

constexpr inline long double IncomeGroup::CalculateIncomeOfIndividual(const long double incomeOfGroup, const long long int groupSize)
{
    return CheckIncomeOfIndividual(incomeOfGroup / groupSize);
}

constexpr inline long double IncomeGroup::CalculateIncomeOfGroup(const long double incomeOfIndividual, const long long int groupSize)
{
    return CheckIncomeOfGroup(incomeOfIndividual * groupSize);
}

constexpr inline long double IncomeGroup::CalculateIncomePercentile(const long long int indexOfStartOfGroup, const long long int sizeOfSortedIncome)
{
    if (indexOfStartOfGroup >= sizeOfSortedIncome || indexOfStartOfGroup < 0)
        throw std::out_of_range{"Index is out of the range of sortedIncome."};

    return CheckIncomePercentile(1.0L * indexOfStartOfGroup / (sizeOfSortedIncome - 1) * 100);
}

constexpr inline long double IncomeGroup::CalculateIncomePercentile(const long long int indexOfStartOfGroup, const std::vector<long double> &sortedIncome)
{
    return CalculateIncomePercentile(indexOfStartOfGroup, sortedIncome.size());
}

// Public
// Constructors
inline IncomeGroup::IncomeGroup(const long double incomeOfIndividual, const long long int indexOfStartOfGroup, const long long int groupSize, const long long int sizeOfSortedIncomes)
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
inline IncomeGroup::~IncomeGroup()
{
}

// Public functions
const constexpr inline long double IncomeGroup::IncomeOfIndividual() const
{
    return incomeOfIndividual;
}

const constexpr inline long double IncomeGroup::IncomeOfGroup() const
{
    return incomeOfGroup;
}

const constexpr inline long long int IncomeGroup::IndexOfStartOfGroup() const
{
    return indexOfStartOfGroup;
}

const constexpr inline long long int IncomeGroup::GroupSize() const
{
    return groupSize;
}

const constexpr inline long double IncomeGroup::IncomePercentile() const
{
    return incomePercentile;
}

const inline long double IncomeGroup::TaxOfIndividual() const
{
    return taxOfIndividual;
}

inline void IncomeGroup::SetTaxOfIndividualAndUpdateGroup(const long double taxOfIndividual)
{
    SetTaxOfIndividual(taxOfIndividual);

    CalculateAndSetTaxOfGroup();
}

const inline long double IncomeGroup::TaxOfGroup() const
{
    return taxOfGroup;
}

inline void IncomeGroup::SetTaxOfGroupAndUpdateIndividual(const long double taxOfGroup)
{
    SetTaxOfGroup(taxOfGroup);

    CalculateAndSetTaxOfIndividual();
}

inline void IncomeGroup::CalculateAndSetTaxOfIndividual()
{
    SetTaxOfIndividual(TaxOfGroup() / GroupSize());
}

inline void IncomeGroup::CalculateAndSetTaxOfGroup()
{
    SetTaxOfGroup(TaxOfIndividual() * GroupSize());
}