// Tax distribution algorithm — a tax distributing program
// Copyright (C) 2026  Martin Herchel

// This file is part of Tax distribution algorithm.
// Tax distribution algorithm is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
// Tax distribution algorithm is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
// You should have received a copy of the GNU General Public License along with Tax distribution algorithm. If not, see <https://www.gnu.org/licenses/>. 

#ifndef PartialClass_h
#define PartialClass_h

class Partial
{
protected:
    // Variables
    long double value;

    // Functions
    virtual constexpr long double CheckValue(const long double value) const; // Not static because of a lack of inheritance for static functions.
    virtual constexpr void CheckValues(const long double part, const long double base) const; // Not static because of a lack of inheritance for static functions.

    virtual void SetValue(const Partial &partial);
    virtual void SetValue(const long double value);
    virtual void SetValue(const long double part, const long double base);

    virtual constexpr long double CalculateValue(const long double part, const long double base) const;

public:
    // Constructors
    Partial();
    Partial(const Partial &partial);
    Partial(const long double value);
    Partial(const long double part, const long double base);
    // Destructor
    ~Partial();

    // Operator overloading
    virtual long double operator()() const;

    virtual void operator()(const long double part, const long double base);

    virtual Partial &operator=(const Partial &value);
    virtual Partial &operator=(const long double value);
};

#endif