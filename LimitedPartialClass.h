#ifndef LimitedPartialClass_h
#define LimitedPartialClass_h

#include "PartialClass.cpp"

class LimitedPartial : public Partial
{
protected:
    // Functions
    virtual constexpr void CheckValues(const long double smallerOrEqualValue, const long double biggerOrEqualValue) const override;

public:
    // Constructor
    LimitedPartial() = default;
    // Destructor
    ~LimitedPartial();
};

#endif