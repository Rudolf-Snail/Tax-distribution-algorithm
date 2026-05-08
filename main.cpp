#include "TaxDistributorClass.cpp"

#include <iostream>
#include <iomanip>

int main()
{
    auto incomes = std::unique_ptr<std::vector<long double>>(new std::vector<long double> {10'000, 20'000, 20'000, 20'000, 5'000, 50'000, 100'000, 15'000, 25'000, 45'000, 45'000, 45'000, 45'000, 60'000, 61'000, 20'001, 99'999, 10'001, 50'001, 5'001, 45'001});

    const long double taxPercentage = 50;

    auto taxDistributor = TaxDistributor(*incomes, taxPercentage);
    taxDistributor.DistributeTax();

    auto incomeGroups = taxDistributor.IncomeGroups();
    const auto sizeOfIncomeGroups = incomeGroups->size();

    std::cout << std::fixed; // Increase floating number precision.
    std::cout << std::setprecision(3); // Limit the decimal part of floating number to 3 places.

    for (long long int index = 0; index < sizeOfIncomeGroups; ++index)
    {
        auto currentIncomeGroup = &(*incomeGroups)[index];

        auto incomeOfIndividual = currentIncomeGroup->IncomeOfIndividual();
        auto incomeOfGroup = currentIncomeGroup->IncomeOfGroup();

        auto taxOfIndividual = currentIncomeGroup->TaxOfIndividual();
        auto taxOfGroup = currentIncomeGroup->TaxOfGroup();

        auto netIncomeOfIndividual = incomeOfIndividual - taxOfIndividual;
        auto netIncomeOfGroup = incomeOfGroup - taxOfGroup;

        auto incomePercentile = currentIncomeGroup->IncomePercentile();

        std::cout << "Income of individual: " << incomeOfIndividual << "; Income of group: " << incomeOfGroup << "; Tax of individual: " << taxOfIndividual << "; Tax of group: " << taxOfGroup << "; Net income of individual: " << netIncomeOfIndividual << "; Net income of group: " << netIncomeOfGroup << "; Income percentile: " << incomePercentile << "\n";
    }

    return 0;
}