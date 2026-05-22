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