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
    const constexpr std::shared_ptr<std::vector<long double>> SortIncome(const std::vector<long double> &incomes) const;

    constexpr long double CheckTaxPercentage(const long double taxPercentage) const;

    void GroupIntoIncomeGroupsAndCalculateTotalIncome();

    void SetUpAllNeededVariables();

    void CalculateTotalTaxAndSetTaxRemaining();

    void SetLastPercentileAndHighestIndividualIncome();

    constexpr long double CalculateLowerTaxRange(const IncomeGroup &previousIncomeGroup) const;
    constexpr long double CalculateUpperTaxRange(IncomeGroup &previousIncomeGroup, IncomeGroup &currentIncomeGroup) const;

    const constexpr long double CalculateTaxForIncomeGroup(const long double lowerTaxRange, const long double upperTaxRange, IncomeGroup &previousIncomeGroup, IncomeGroup &currentIncomeGroup) const;
    const constexpr void CalculateTaxesForIncomeGroups();

    const constexpr void CalculateMoneyAfterTaxesForIncomeGroups();

public:
    // Constructors
    TaxDistributor(const std::vector<long double> &incomes, const long double taxPercentage);
    // Destructor
    ~TaxDistributor();

    // Functions
    const constexpr void DistributeTax();

    const constexpr std::shared_ptr<std::vector<long double>> SortedIncomes() const;
    const constexpr std::shared_ptr<std::vector<IncomeGroup>> IncomeGroups() const;

    const constexpr long double TotalIncome() const;
    const constexpr long double TaxPercentage() const;
    const constexpr long double TotalTax() const;
    const constexpr long double TaxRemaining() const;
    const constexpr long double LastPercentile() const;
    const constexpr long double HighestIndividualIncome() const;
};