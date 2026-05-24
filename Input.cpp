// Tax distribution algorithm — a tax distributing program
// Copyright (C) 2026  Martin Herchel

// This file is part of Tax distribution algorithm.
// Tax distribution algorithm is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
// Tax distribution algorithm is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
// You should have received a copy of the GNU General Public License along with Tax distribution algorithm. If not, see <https://www.gnu.org/licenses/>. 

#ifndef Input_cpp
#define Input_cpp

#include "Input.h"

inline long double CheckAndProcessInput(const std::string &inputInstructions, const std::string &valueOutOfRangeMessage, const std::string &conversionUnsuccesfulMessage, const std::string &valueOutOfAcceptedRangeMessage, const long double minimumValueInclusive, const long double maximumValueInclusive, const std::string &emptyInputMessage, const bool canGetMultipleValues, std::unique_ptr<std::vector<long double>> *vectorOfMultipleValues, const std::string &vectorEmptyMessage)
{
    CreateVectorIfEmptyAndMultipleValuesIsTrue(canGetMultipleValues, *vectorOfMultipleValues);

    std::string input = "";
    long double value = 0;

    char *afterLastInterpretedCharacter;

    while (true)
    {
        std::cout << inputInstructions;

        std::getline(std::cin, input);

        switch (EmptyInput(canGetMultipleValues, input, *vectorOfMultipleValues, vectorEmptyMessage, value, emptyInputMessage))
        {
        case NextAction::endAndReturn:
            return value;
        case NextAction::goToNextIteration:
            continue;
        case NextAction::goOn:
            break;
        }

        afterLastInterpretedCharacter = 0;

        value = std::strtold(input.c_str(), &afterLastInterpretedCharacter);

        switch (ConversionSuccessful(value, valueOutOfRangeMessage, afterLastInterpretedCharacter, input, conversionUnsuccesfulMessage, valueOutOfAcceptedRangeMessage, minimumValueInclusive, maximumValueInclusive))
        {
        case NextAction::goToNextIteration:
            continue;
        case NextAction::goOn:
            break;
        }

        switch (ProcessCorrectValue(canGetMultipleValues, *vectorOfMultipleValues, value))
        {
        case NextAction::goToNextIteration:
            continue;
        case NextAction::endAndReturn:
            return value;
        }
    }
}

inline void CreateVectorIfEmptyAndMultipleValuesIsTrue(const bool canGetMultipleValues, std::unique_ptr<std::vector<long double>> &vectorOfMultipleValues)
{
    if (canGetMultipleValues && vectorOfMultipleValues == nullptr)
    {
        vectorOfMultipleValues = std::make_unique<std::vector<long double>>();
    }
}

inline NextAction ProcessCorrectValue(const bool canGetMultipleValues, std::unique_ptr<std::vector<long double>> &vectorOfMultipleValues, const long double value)
{
    if (canGetMultipleValues)
    {
        (*vectorOfMultipleValues).push_back(value);

        return NextAction::goToNextIteration;
    }
    else
    {
        return NextAction::endAndReturn;
    }
}

constexpr NextAction ConversionSuccessful(const long double value, const std::string &valueOutOfRangeMessage, const char *afterLastInterpretedCharacter, const std::string &input, const std::string &conversionUnsuccesfulMessage, const std::string &valueOutOfAcceptedRangeMessage, const long double minimumValueInclusive, const long double maximumValueInclusive)
{
    if (value == HUGE_VALL)
    {
        std::cout << valueOutOfRangeMessage;

        return NextAction::goToNextIteration;
    }
    else if (value == 0 && afterLastInterpretedCharacter == input)
    {
        std::cout << conversionUnsuccesfulMessage;

        return NextAction::goToNextIteration;
    }
    else if (value < minimumValueInclusive || value > maximumValueInclusive)
    {
        std::cout << valueOutOfAcceptedRangeMessage;

        return NextAction::goToNextIteration;
    }
    else
    {
        return NextAction::goOn;
    }
}

constexpr NextAction EmptyInput(const bool canGetMultipleValues, const std::string &input, const std::unique_ptr<std::vector<long double>> &vectorOfMultipleValues, const std::string &vectorEmptyMessage, const long double value, const std::string &emptyInputMessage)
{
    if (canGetMultipleValues && input == "")
    {
        if ((*vectorOfMultipleValues).empty())
        {
            std::cout << vectorEmptyMessage;

            return NextAction::goToNextIteration;
        }

        return NextAction::endAndReturn;
    }
    else if (input == "")
    {
        std::cout << emptyInputMessage;

        return NextAction::goToNextIteration;
    }

    return NextAction::goOn;
}

#endif