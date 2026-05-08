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
    constexpr inline void CheckIncome(const std::vector<long double> &incomes) const;
    const constexpr inline std::shared_ptr<std::vector<long double>> SortIncome(const std::vector<long double> &incomes) const;

    constexpr inline long double CheckTaxPercentage(const long double taxPercentage) const;

    inline void GroupIntoIncomeGroupsAndCalculateTotalIncome();

    inline void SetUpAllNeededVariables();

    inline void CalculateTotalTaxAndSetTaxRemaining();

    inline void SetLastPercentileAndHighestIndividualIncome();

    constexpr inline long double CalculateLowerTaxRange(const IncomeGroup &previousIncomeGroup) const;
    constexpr inline long double CalculateUpperTaxRange(IncomeGroup &previousIncomeGroup, IncomeGroup &currentIncomeGroup) const;

    const constexpr inline long double CalculateTaxForIncomeGroup(const long double lowerTaxRange, const long double upperTaxRange, IncomeGroup &previousIncomeGroup, IncomeGroup &currentIncomeGroup) const;
    const constexpr inline void CalculateTaxesForIncomeGroups();

    const constexpr inline void CalculateMoneyAfterTaxesForIncomeGroups();

public:
    // Constructors
    TaxDistributor(const std::vector<long double> &incomes, const long double taxPercentage);
    // Destructor
    ~TaxDistributor();

    // Functions
    const constexpr inline void DistributeTax();

    const constexpr inline std::shared_ptr<std::vector<long double>> SortedIncomes() const;
    const constexpr inline std::shared_ptr<std::vector<IncomeGroup>> IncomeGroups() const;

    const constexpr inline long double TotalIncome() const;
    const constexpr inline long double TaxPercentage() const;
    const constexpr inline long double TotalTax() const;
    const constexpr inline long double TaxRemaining() const;
    const constexpr inline long double LastPercentile() const;
    const constexpr inline long double HighestIndividualIncome() const;
};