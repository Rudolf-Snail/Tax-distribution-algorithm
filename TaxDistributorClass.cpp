#ifndef TaxDistributorClass_cpp
#define TaxDistributorClass_cpp

#include "TaxDistributorClass.h"

#include <stdexcept>

// Private
// Private functions
constexpr void TaxDistributor::CheckIncome(const std::vector<long double> &incomes) const
{
    if (incomes.empty())
        throw std::invalid_argument{"The vector income cannot be empty."};
}

constexpr std::shared_ptr<std::vector<long double>> TaxDistributor::SortIncome(const std::vector<long double> &incomes) const
{
    CheckIncome(incomes);

    auto incomesCopy = std::make_shared<std::vector<long double>>(incomes);

    std::sort(incomesCopy->begin(), incomesCopy->end());

    return incomesCopy;
}

void TaxDistributor::GroupIntoIncomeGroupsAndCalculateTotalIncome()
{
    long double previousIncome = (*sortedIncomes)[0];

    if (previousIncome < 0)
        throw std::invalid_argument{"Value of any income cannot be negative."};

    long long int startIndexOfPreviousIncome = 0;

    long double currentIncome;

    auto sizeOfSortedIncomes = sortedIncomes->size();

    long long int index = 0;

    for (; index < sizeOfSortedIncomes; ++index)
    {
        currentIncome = (*sortedIncomes)[index];

        totalIncome += currentIncome;

        if (currentIncome != previousIncome)
        {
            incomeGroups->push_back(IncomeGroup(previousIncome, startIndexOfPreviousIncome, index - startIndexOfPreviousIncome, sizeOfSortedIncomes));

            previousIncome = currentIncome;
            startIndexOfPreviousIncome = index;
        }
    }

    incomeGroups->push_back(IncomeGroup(previousIncome, startIndexOfPreviousIncome, index - startIndexOfPreviousIncome, sizeOfSortedIncomes)); // Take care of the last IncomeGroup.
}

void TaxDistributor::SetUpAllNeededVariables()
{
    GroupIntoIncomeGroupsAndCalculateTotalIncome();

    CalculateTotalTaxAndSetTaxRemaining();

    SetLastPercentileAndHighestIndividualIncome();
}

void TaxDistributor::CalculateTotalTaxAndSetTaxRemaining()
{
    totalTax = totalIncome * taxPercentage() / 100;
    taxRemaining = totalTax;
}

void TaxDistributor::SetLastPercentileAndHighestIndividualIncome()
{
    auto lastIncomeGroup = (*incomeGroups)[incomeGroups->size() - 1];

    lastPercentile = lastIncomeGroup.IncomePercentile();
    highestIndividualIncome = lastIncomeGroup.IncomeOfIndividual();
}

constexpr long double TaxDistributor::CalculateLowerTaxRange(const IncomeGroup &previousIncomeGroup) const
{
    return previousIncomeGroup.TaxOfIndividual();
}

constexpr long double TaxDistributor::CalculateUpperTaxRange(const IncomeGroup &previousIncomeGroup, const IncomeGroup &currentIncomeGroup) const
{
    const auto taxOfIndividualInPreviousIncomeGroup = previousIncomeGroup.TaxOfIndividual();
    const auto incomeOfIndividualInPreviousIncomeGroup = previousIncomeGroup.IncomeOfIndividual();

    const auto currentIncomeOfIndividual = currentIncomeGroup.IncomeOfIndividual();

    const auto incomeOfIndividualDifference = currentIncomeOfIndividual - incomeOfIndividualInPreviousIncomeGroup;
    const auto maxTaxForTheCurrentNetIncomeToBeEqualToThePreviousNetIncome = taxOfIndividualInPreviousIncomeGroup + incomeOfIndividualDifference;

    const auto taxOfCurrentIncomeOfIndividual = currentIncomeOfIndividual * taxPercentage() / 100;

    return std::min({maxTaxForTheCurrentNetIncomeToBeEqualToThePreviousNetIncome, taxOfCurrentIncomeOfIndividual, currentIncomeOfIndividual, taxRemaining});
}

constexpr long double TaxDistributor::CalculateTaxForIncomeGroup(const long double lowerTaxRange, const long double upperTaxRange, IncomeGroup &previousIncomeGroup, IncomeGroup &currentIncomeGroup) const
{
    const auto currentIncomePercentile = currentIncomeGroup.IncomePercentile()();
    const auto previousIncomeOfIndividual = previousIncomeGroup.IncomeOfIndividual();

    const auto currentPercentileToTheLastPercentile = (lastPercentile() == 0) ? 1 : LimitedRatio(currentIncomePercentile, lastPercentile());
    const auto previousPercentileToCurrentPercentile = (currentIncomePercentile == 0) ? 0 : LimitedReverseRatio(previousIncomeGroup.IncomePercentile()(), currentIncomePercentile);
    const auto currentIndividualIncomeToHighestIndividualIncome = (highestIndividualIncome == 0) ? 0 : LimitedRatio(currentIncomeGroup.IncomeOfIndividual(), highestIndividualIncome);
    const auto previousIncomeToCurrentIncome = (currentIncomeGroup.IncomeOfIndividual() == 0) ? 0 : LimitedReverseRatio(previousIncomeOfIndividual, currentIncomeGroup.IncomeOfIndividual());

    const auto ratioBasedOnFactors = (currentPercentileToTheLastPercentile() + previousPercentileToCurrentPercentile() + currentIndividualIncomeToHighestIndividualIncome() + previousIncomeToCurrentIncome()) / 4;

    return lowerTaxRange + (ratioBasedOnFactors * (upperTaxRange - lowerTaxRange));
}

constexpr void TaxDistributor::CalculateRatioOutOfTotalTaxForIncomeGroups()
{
    const auto sizeOfIncomeGroups = incomeGroups->size();

    auto firstPreviousIncomeGroup = IncomeGroup(0, 0, 1, sizeOfIncomeGroups);
    auto *previousIncomeGroup = &firstPreviousIncomeGroup;
    IncomeGroup *currentIncomeGroup;

    long double taxOfAnIndividualInCurrentIncomeGroup;

    for (long long int index = 0; index < sizeOfIncomeGroups; ++index)
    {
        currentIncomeGroup = &(*incomeGroups)[index];

        taxOfAnIndividualInCurrentIncomeGroup = CalculateTaxForIncomeGroup(CalculateLowerTaxRange(*previousIncomeGroup), CalculateUpperTaxRange(*previousIncomeGroup, *currentIncomeGroup), *previousIncomeGroup, *currentIncomeGroup);

        currentIncomeGroup->SetTaxOfIndividualAndUpdateGroup(taxOfAnIndividualInCurrentIncomeGroup);

        taxRemaining -= currentIncomeGroup->TaxOfGroup();

        previousIncomeGroup = currentIncomeGroup;
    }
}

constexpr void TaxDistributor::CalculateTaxesForIncomeGroups()
{
    IncomeGroup *currentIncomeGroup;
    long double currentIncomeGroupTaxOfGroup;

    LimitedRatio currentIncomeGroupTaxOfGroupToTaxPaidByIncomeGroups;

    long double taxOfCurrentIncomeGroup;

    const auto sizeOfIncomeGroups = incomeGroups->size();

    const auto taxPaidByIncomeGroups = totalTax - taxRemaining;

    taxRemaining = totalTax;

    for (long long int index = 0; index < sizeOfIncomeGroups; ++index)
    {
        currentIncomeGroup = &(*incomeGroups)[index];
        currentIncomeGroupTaxOfGroup = currentIncomeGroup->TaxOfGroup();

        currentIncomeGroupTaxOfGroupToTaxPaidByIncomeGroups = currentIncomeGroupTaxOfGroup / taxPaidByIncomeGroups;

        taxOfCurrentIncomeGroup = totalTax * currentIncomeGroupTaxOfGroupToTaxPaidByIncomeGroups();

        currentIncomeGroup->SetTaxOfGroupAndUpdateIndividual(taxOfCurrentIncomeGroup);
        taxRemaining -= taxOfCurrentIncomeGroup;
    }
}

// Public
// Constructors
TaxDistributor::TaxDistributor(const std::vector<long double> &incomes, const LimitedPercentage taxPercentage) : sortedIncomes{SortIncome(incomes)}, taxPercentage{taxPercentage}
{
    incomeGroups = std::unique_ptr<std::vector<IncomeGroup>>(new std::vector<IncomeGroup>());

    totalIncome = 0;

    SetUpAllNeededVariables();
}

// Destructor
TaxDistributor::~TaxDistributor()
{
}

// Public functions
constexpr void TaxDistributor::DistributeTax()
{
    CalculateRatioOutOfTotalTaxForIncomeGroups();

    CalculateTaxesForIncomeGroups();
}

constexpr std::shared_ptr<std::vector<long double>> TaxDistributor::SortedIncomes() const
{
    return sortedIncomes;
}

const std::shared_ptr<std::vector<IncomeGroup>> TaxDistributor::IncomeGroups() const
{
    return incomeGroups;
}

constexpr long double TaxDistributor::TotalIncome() const
{
    return totalIncome;
}

constexpr LimitedPercentage TaxDistributor::TaxPercentage() const
{
    return taxPercentage;
}

constexpr long double TaxDistributor::TotalTax() const
{
    return totalTax;
}

constexpr long double TaxDistributor::TaxRemaining() const
{
    return taxRemaining;
}

constexpr LimitedPercentage TaxDistributor::LastPercentile() const
{
    return lastPercentile;
}

constexpr long double TaxDistributor::HighestIndividualIncome() const
{
    return highestIndividualIncome;
}

#endif