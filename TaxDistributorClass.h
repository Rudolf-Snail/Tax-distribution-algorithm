#ifndef TaxDistributorClass_h
#define TaxDistributorClass_h

#include "IncomeGroupClass.cpp"

#include <memory>
#include <algorithm>

class TaxDistributor
{
private:
    // Variables
    const std::shared_ptr<std::vector<long double>> sortedIncomes;
    std::shared_ptr<std::vector<IncomeGroup>> incomeGroups;

    long double totalIncome;

    const long double taxPercentage;
    long double totalTax;
    long double taxRemaining;

    long double lastPercentile;
    long double highestIndividualIncome;

    // Functions
    constexpr void CheckIncome(const std::vector<long double> &incomes) const;
    constexpr std::shared_ptr<std::vector<long double>> SortIncome(const std::vector<long double> &incomes) const;

    constexpr long double CheckTaxPercentage(const long double taxPercentage) const;

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
    TaxDistributor(const std::vector<long double> &incomes, const long double taxPercentage);
    // Destructor
    ~TaxDistributor();

    // Functions
    constexpr void DistributeTax();

    constexpr std::shared_ptr<std::vector<long double>> SortedIncomes() const;
    const std::shared_ptr<std::vector<IncomeGroup>> IncomeGroups() const;

    constexpr long double TotalIncome() const;
    constexpr long double TaxPercentage() const;
    constexpr long double TotalTax() const;
    constexpr long double TaxRemaining() const;
    constexpr long double LastPercentile() const;
    constexpr long double HighestIndividualIncome() const;
};
#endif
