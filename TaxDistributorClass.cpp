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

constexpr long double TaxDistributor::CheckTaxPercentage(const long double taxPercentage) const
{
    if (taxPercentage < 0 || taxPercentage > 100)
        throw std::invalid_argument{"The taxPercentage cannot be smaller than 0 or bigger than 100."};

    return taxPercentage;
}

void TaxDistributor::GroupIntoIncomeGroupsAndCalculateTotalIncome()
{
    long double previousIncome = (*sortedIncomes)[0];
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
    totalTax = totalIncome * taxPercentage / 100;
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
    const long double taxOfIndividualInPreviousIncomeGroup = previousIncomeGroup.TaxOfIndividual();
    const long double incomeOfIndividualInPreviousIncomeGroup = previousIncomeGroup.IncomeOfIndividual();

    const long double currentIncome = currentIncomeGroup.IncomeOfIndividual();

    const long double incomeDifference = currentIncome - incomeOfIndividualInPreviousIncomeGroup;
    const long double maxTaxForTheCurrentNetIncomeToBeEqualToThePreviousNetIncome = taxOfIndividualInPreviousIncomeGroup + incomeDifference;

    const long double taxPercentageOfCurrentIncome = currentIncome * taxPercentage / 100;

    return std::min({maxTaxForTheCurrentNetIncomeToBeEqualToThePreviousNetIncome, taxPercentageOfCurrentIncome, currentIncome, taxRemaining});
}

constexpr long double TaxDistributor::CalculateTaxForIncomeGroup(const long double lowerTaxRange, const long double upperTaxRange, IncomeGroup &previousIncomeGroup, IncomeGroup &currentIncomeGroup) const
{
    const long double ratioOfCurrentPercentileToTheLastPercentile = currentIncomeGroup.IncomePercentile() / lastPercentile;
    const long double reverseRatioOfPreviousPercentileToCurrentPercentile = (currentIncomeGroup.IncomePercentile() == 0) ? 0 : 1 - (previousIncomeGroup.IncomePercentile() / currentIncomeGroup.IncomePercentile());
    const long double ratioOfCurrentIndividualIncomeToHighestIndividualIncome = (highestIndividualIncome == 0) ? 0 : currentIncomeGroup.IncomeOfIndividual() / highestIndividualIncome;
    const long double reverseRatioOfPreviousIncomeToCurrentIncome = (previousIncomeGroup.IncomeOfIndividual() == 0 || currentIncomeGroup.IncomeOfIndividual() == 0) ? 0 : 1 - (previousIncomeGroup.IncomeOfIndividual() / currentIncomeGroup.IncomeOfIndividual());

    const long double ratioBasedOnFactors = (ratioOfCurrentPercentileToTheLastPercentile + reverseRatioOfPreviousPercentileToCurrentPercentile + ratioOfCurrentIndividualIncomeToHighestIndividualIncome + reverseRatioOfPreviousIncomeToCurrentIncome) / 4;

    return lowerTaxRange + (ratioBasedOnFactors * (upperTaxRange - lowerTaxRange));
}

constexpr void TaxDistributor::CalculateTaxesForIncomeGroups()
{
    const auto sizeOfIncomeGroups = incomeGroups->size();

    IncomeGroup *previousIncomeGroup = new IncomeGroup(0, 0, 1, sizeOfIncomeGroups);
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

constexpr void TaxDistributor::CalculateMoneyAfterTaxesForIncomeGroups()
{
    IncomeGroup *currentIncomeGroup;
    long double currentIncomeGroupTaxOfGroup;

    long double ratioOfCurrentIncomeGroupIncomeOfGroupToTaxPaidByIncomeGroups;

    long double taxOfCurrentIncomeGroup;

    const auto sizeOfIncomeGroups = incomeGroups->size();

    const long double taxPaidByIncomeGroups = totalTax - taxRemaining;

    taxRemaining = totalTax;

    for (long long int index = 0; index < sizeOfIncomeGroups; ++index)
    {
        currentIncomeGroup = &(*incomeGroups)[index];
        currentIncomeGroupTaxOfGroup = currentIncomeGroup->TaxOfGroup();

        ratioOfCurrentIncomeGroupIncomeOfGroupToTaxPaidByIncomeGroups = currentIncomeGroupTaxOfGroup / taxPaidByIncomeGroups;

        taxOfCurrentIncomeGroup = totalTax * ratioOfCurrentIncomeGroupIncomeOfGroupToTaxPaidByIncomeGroups;

        currentIncomeGroup->SetTaxOfGroupAndUpdateIndividual(taxOfCurrentIncomeGroup);
        taxRemaining -= taxOfCurrentIncomeGroup;
    }
}

// Public
// Constructors
TaxDistributor::TaxDistributor(const std::vector<long double> &incomes, const long double taxPercentage) : sortedIncomes{SortIncome(incomes)}, taxPercentage{CheckTaxPercentage(taxPercentage)}
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
    CalculateTaxesForIncomeGroups();

    CalculateMoneyAfterTaxesForIncomeGroups();
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

constexpr long double TaxDistributor::TaxPercentage() const
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

 constexpr long double TaxDistributor::LastPercentile() const
{
    return lastPercentile;
}

constexpr long double TaxDistributor::HighestIndividualIncome() const
{
    return highestIndividualIncome;
}