#ifndef LimitedReverseRatioClass_h
#define LimitedReverseRatioClass_h

#include "LimitedRatioAndLimitedPercentageClasses.cpp"

class LimitedReverseRatio : public LimitedRatio
{
protected:
    // Functions
    virtual void SetValue(const LimitedReverseRatio &ratio);
    virtual void SetValue(const LimitedRatio &ratio) override;

    virtual constexpr long double CalculateValue(const long double smallerOrEqualValue, const long double biggerOrEqualValue) const;
    virtual constexpr long double CalculateValue(const LimitedRatio &ratio) const;

public:
    // Constructors
    LimitedReverseRatio() = default;
    LimitedReverseRatio(const LimitedReverseRatio &reverseRatioOfValues);
    LimitedReverseRatio(const LimitedRatio &ratio);
    LimitedReverseRatio(const long double reverseRatioOfValues);
    LimitedReverseRatio(const long double smallerOrEqualValue, const long double biggerOrEqualValue);
    // Destructor
    ~LimitedReverseRatio();

    // Functions
    LimitedRatio ConvertToRatio();

    // Operator overloading
    virtual long double operator()() const override;

    virtual void operator()(const long double smallerOrEqualValue, const long double biggerOrEqualValue) override;
    virtual void operator()(const LimitedRatio &value);

    virtual LimitedReverseRatio &operator=(const LimitedReverseRatio &value);
    virtual LimitedReverseRatio &operator=(const long double value) override;
};

#endif