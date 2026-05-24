// Tax distribution algorithm — a tax distributing program
// Copyright (C) 2026  Martin Herchel

// This file is part of Tax distribution algorithm.
// Tax distribution algorithm is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
// Tax distribution algorithm is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
// You should have received a copy of the GNU General Public License along with Tax distribution algorithm. If not, see <https://www.gnu.org/licenses/>. 

#include "Input.cpp"

#include <format>

int main()
{
    std::cout << "Tax distribution algorithm Copyright (C) 2026  Martin Herchel.\n" <<
                "This program comes with ABSOLUTELY NO WARRANTY; details available in LICENSE.txt file.\n" <<
                "This is free software, and you are welcome to redistribute it under certain conditions; specified in the LICENSE.txt file.\n\n";

    auto incomes = std::make_unique<std::vector<long double>>();

    const std::string inputInstructions1 = "Enter number with the value of income to add and press Enter to add it to the list of incomes; press Enter with no number or value present to stop adding incomes: ";

    const std::string vectorEmptyMessage1 = "You must enter at least one valid income to continue.\n";

    const long double minimumLongDoubleValue = std::numeric_limits<long double>::lowest();
    const long double maximumLongDoubleValue = std::numeric_limits<long double>::max();
    const std::string valueOutOfRangeMessage1 = std::format("That value is out of range for a long double type; the minimum value you can use is: {}; the maximum value you can use is {}.\n", minimumLongDoubleValue, maximumLongDoubleValue);

    const std::string conversionUnsuccessfulMessage1 = "No conversion could be performed.\n";

    const long double minimumValueInclusive1 = 0;
    const long double maximumValueInclusive1 = std::numeric_limits<long double>::max();
    const std::string valueOutOfAcceptedRangeMessage1 = std::format("The value must be within the range from {} to {}.\n", minimumValueInclusive1, maximumValueInclusive1);

    CheckAndProcessInput(inputInstructions1, valueOutOfRangeMessage1, conversionUnsuccessfulMessage1, valueOutOfAcceptedRangeMessage1, minimumValueInclusive1, maximumValueInclusive1, "", true, &incomes, vectorEmptyMessage1);

    const std::string inputInstructions2 = "Enter percentage of the sum of all incomes to collect and press Enter to set it as the tax percentage; valid values are 0-100 inclusive: ";

    const long double minimumValueInclusive2 = 0;
    const long double maximumValueInclusive2 = 100;
    const std::string valueOutOfAcceptedRangeMessage2 = std::format("The value must be within the range from {} to {}.\n", minimumValueInclusive2, maximumValueInclusive2);

    const std::string emptyInputMessage = "You must enter a value to continue.\n";

    long double taxPercentage = CheckAndProcessInput(inputInstructions2, valueOutOfRangeMessage1, conversionUnsuccessfulMessage1, valueOutOfAcceptedRangeMessage2, minimumValueInclusive2, maximumValueInclusive2, emptyInputMessage);

    auto taxDistributor = TaxDistributor(*incomes, taxPercentage);
    taxDistributor.DistributeTax();

    const auto incomeGroups = taxDistributor.IncomeGroups();
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

        auto incomePercentile = currentIncomeGroup->IncomePercentile()();

        std::cout << "Income of individual: " << incomeOfIndividual << "; Income of group: " << incomeOfGroup << "; Tax of individual: " << taxOfIndividual << "; Tax of group: " << taxOfGroup << "; Net income of individual: " << netIncomeOfIndividual << "; Net income of group: " << netIncomeOfGroup << "; Income percentile: " << incomePercentile << "\n";
    }

    std::cout << "After tax distribution there is: " << std::fabs(taxDistributor.TaxRemaining()) << " " << ((taxDistributor.TaxRemaining() < 0) ? "owed to taxpayers" : "left to pay") << ".\n";

    std::cout << "Press the Enter key to end the program.\n";
    std::cin.get();

    return 0;
}