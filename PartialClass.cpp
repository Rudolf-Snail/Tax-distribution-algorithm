#ifndef PartialClass_cpp
#define PartialClass_cpp

#include "PartialClass.h"

#include <stdexcept>

// Protected
// Protected functions
constexpr long double Partial::CheckValue(const long double value) const
{
    return value;
}

constexpr void Partial::CheckValues(const long double part, const long double base) const
{
    if (base == 0)
        throw std::invalid_argument{"The value of base cannot be 0."};
}

void Partial::SetValue(const Partial &partial)
{
    this->value = partial();
}

void Partial::SetValue(const long double value)
{
    this->value = CheckValue(value);
}

void Partial::SetValue(const long double part, const long double base)
{
    CheckValues(part, base);

    this->value = CalculateValue(part, base);
}

constexpr long double Partial::CalculateValue(const long double part, const long double base) const
{
    return part / base;
}

// Public
// Public constructors
Partial::Partial()
{
    *this = 0;
}

Partial::Partial(const Partial &partial)
{
    *this = partial;
}

Partial::Partial(const long double value)
{
    *this = value;
}

Partial::Partial(const long double part, const long double base)
{
    (*this)(part, base);
}
// Destructor
Partial::~Partial()
{
}

// Operator overloading
long double Partial::operator()() const
{
    return value;
}

void Partial::operator()(const long double part, const long double base)
{
    SetValue(part, base);
}

Partial &Partial::operator=(const Partial &value)
{
    SetValue(value);

    return *this;
}

Partial &Partial::operator=(const long double value)
{
    SetValue(value);

    return *this;
}

#endif