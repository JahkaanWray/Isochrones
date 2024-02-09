#include <vector>

#ifndef WEIGHTFUNCTION
#define WEIGHTFUNCTION

enum class weightFunctionType
{
    constant,
    linear,
    piecewiseLinear,
    repeating
};

class weightFunction
{
public:
    virtual double operator()(double x) const = 0;
    weightFunctionType getType() const { return type; }
    double getMinimum() const { return minimum; }

protected:
    weightFunction(weightFunctionType t) : type(t) {}
    double minimum;

private:
    weightFunctionType type;
};

class constantFunction : public weightFunction
{
private:
    double c;

public:
    constantFunction(double c) : c(c), weightFunction(weightFunctionType::constant) { minimum = c; };
    double operator()(double x) const { return c; };
    double value() const { return c; }
};

class linearFunction : public weightFunction
{
private:
    double m;
    double c;

public:
    linearFunction(double m, double x1, double y1) : m(m), c(y1 - m * x1), weightFunction(weightFunctionType::linear){};
    double operator()(double x) const;
    double gradient() const { return m; }
    double intercept() const { return c; }
};

class piecewiseLinearFunction : public weightFunction
{
private:
    struct functionSegment
    {
        weightFunction *f;
        double lowerBound;
        double upperBound;
    };
    std::vector<functionSegment> functions;

public:
    piecewiseLinearFunction() : weightFunction(weightFunctionType::piecewiseLinear){};
    double operator()(double x) const;
    void addFunction(weightFunction *f, double lowerBound, double upperBound);
    void addUnboundedLeftFunction(weightFunction *f, double upperBound);
    void addUnboundedRightFunction(weightFunction *f, double lowerBound);
    std::vector<functionSegment> getFunctions() const { return functions; }
};

class repeatingFunction : public weightFunction
{
private:
    weightFunction *f;
    double lowerBound;
    double upperBound;

public:
    repeatingFunction(weightFunction *f, double lowerBound, double upperBound) : f(f), lowerBound(lowerBound), upperBound(upperBound), weightFunction(weightFunctionType::repeating){};
    double operator()(double x) const;
    weightFunction *getFunction() const { return f; }
    double getLowerBound() const { return lowerBound; }
    double getUpperBound() const { return upperBound; }
};

weightFunction *shiftFunction(weightFunction *f, double shift);
constantFunction *shiftFunction(constantFunction *f, double shift);
linearFunction *shiftFunction(linearFunction *f, double shift);
piecewiseLinearFunction *shiftFunction(piecewiseLinearFunction *f, double shift);
repeatingFunction *shiftFunction(repeatingFunction *f, double shift);

piecewiseLinearFunction *repeatingFunctionToPiecewiseLinearFunction(repeatingFunction *f, double lowerBound, double upperBound);

#endif