#ifndef IncomeGroupClass_h
#define IncomeGroupClass_h

#include <vector>

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

    const long double incomePercentile;

    // Functions
    void SetTaxOfIndividual(const long double taxOfIndividual);
    void SetTaxOfGroup(const long double taxOfGroup);

    static constexpr long double CheckIncomeOfIndividual(const long double incomeOfIndividual);

    static constexpr long double CheckIncomeOfGroup(const long double incomeOfGroup);

    static constexpr long long int CheckIndexOfStartOfGroup(const long long int indexOfStartOfGroup);

    static constexpr long long int CheckGroupSize(const long long int groupSize);

    static constexpr long double CheckIncomePercentile(const long double incomePercentile);

    static constexpr long double CalculateIncomeOfIndividual(const long double incomeOfGroup, const long long int groupSize);
    static constexpr long double CalculateIncomeOfGroup(const long double incomeOfIndividual, const long long int groupSize);

    static constexpr long double CalculateIncomePercentile(const long long int indexOfStartOfGroup, const long long int sizeOfSortedIncome);
    static constexpr long double CalculateIncomePercentile(const long long int indexOfStartOfGroup, const std::vector<long double> &sortedIncome);

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
    constexpr long double IncomePercentile() const;

    long double TaxOfIndividual() const;
    void SetTaxOfIndividualAndUpdateGroup(const long double taxOfIndividual);

    long double TaxOfGroup() const;
    void SetTaxOfGroupAndUpdateIndividual(const long double taxOfGroup);

    void CalculateAndSetTaxOfIndividual();
    void CalculateAndSetTaxOfGroup();
};
#endif
