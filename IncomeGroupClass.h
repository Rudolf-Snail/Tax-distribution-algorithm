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
    inline void SetTaxOfIndividual(const long double taxOfIndividual);
    inline void SetTaxOfGroup(const long double taxOfGroup);

    static constexpr inline long double CheckIncomeOfIndividual(const long double incomeOfIndividual);

    static constexpr inline long double CheckIncomeOfGroup(const long double incomeOfGroup);

    static constexpr inline long long int CheckIndexOfStartOfGroup(const long long int indexOfStartOfGroup);

    static constexpr inline long long int CheckGroupSize(const long long int groupSize);

    static constexpr inline long double CheckIncomePercentile(const long double incomePercentile);

    static constexpr inline long double CalculateIncomeOfIndividual(const long double incomeOfGroup, const long long int groupSize);
    static constexpr inline long double CalculateIncomeOfGroup(const long double incomeOfIndividual, const long long int groupSize);

    static constexpr inline long double CalculateIncomePercentile(const long long int indexOfStartOfGroup, const long long int sizeOfSortedIncome);
    static constexpr inline long double CalculateIncomePercentile(const long long int indexOfStartOfGroup, const std::vector<long double> &sortedIncome);

public:
    // Constructors
    inline IncomeGroup(const long double incomeOfIndividual, const long long int indexOfStartOfGroup, const long long int groupSize, const long long int sizeOfSortedIncomes);
    // Destructors
    inline ~IncomeGroup();

    // Functions
    const constexpr inline long double IncomeOfIndividual() const;
    const constexpr inline long double IncomeOfGroup() const;
    const constexpr inline long long int IndexOfStartOfGroup() const;
    const constexpr inline long long int GroupSize() const;
    const constexpr inline long double IncomePercentile() const;

    const inline long double TaxOfIndividual() const;
    inline void SetTaxOfIndividualAndUpdateGroup(const long double taxOfIndividual);

    const inline long double TaxOfGroup() const;
    inline void SetTaxOfGroupAndUpdateIndividual(const long double taxOfGroup);

    inline void CalculateAndSetTaxOfIndividual();
    inline void CalculateAndSetTaxOfGroup();
};