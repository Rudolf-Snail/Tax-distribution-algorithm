#ifndef Input_h
#define Input_h

#include "TaxDistributorClass.cpp"

#include <iostream>
#include <iomanip>
#include <cmath>
#include <limits>

enum class NextAction
{
    goToNextIteration,
    endAndReturn,
    goOn
};

inline long double CheckAndProcessInput(const std::string &inputInstructions, const std::string &valueOutOfRangeMessage, const std::string &conversionUnsuccesfulMessage, const std::string &valueOutOfAcceptedRangeMessage = "", const long double minimumValueInclusive = std::numeric_limits<long double>::lowest(), const long double maximumValueInclusive = std::numeric_limits<long double>::max(), const std::string &emptyInputMessage = "", const bool canGetMultipleValues = false, std::unique_ptr<std::vector<long double>> *vectorOfMultipleValues = nullptr, const std::string &vectorEmptyMessage = "");

inline void CreateVectorIfEmptyAndMultipleValuesIsTrue(const bool canGetMultipleValues, std::unique_ptr<std::vector<long double>> &vectorOfMultipleValues);

inline NextAction ProcessCorrectValue(const bool canGetMultipleValues, std::unique_ptr<std::vector<long double>> &vectorOfMultipleValues, const long double value);

constexpr NextAction ConversionSuccessful(const long double value, const std::string &valueOutOfRangeMessage, const char *afterLastInterpretedCharacter, const std::string &input, const std::string &conversionUnsuccesfulMessage, const std::string &valueOutOfAcceptedRangeMessage, const long double minimumValueInclusive, const long double maximumValueInclusive);

constexpr NextAction EmptyInput(const bool canGetMultipleValues, const std::string &input, const std::unique_ptr<std::vector<long double>> &vectorOfMultipleValues, const std::string &vectorEmptyMessage, const long double value, const std::string &emptyInputMessage);

#endif