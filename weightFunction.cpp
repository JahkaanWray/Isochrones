#include <iostream>
#include <cmath>
#include "weightFunction.h"

double linearFunction::operator()(double x) const
{
    return m * x + c;
}

double piecewiseLinearFunction::operator()(double x) const
{
    for (auto it = functions.begin(); it != functions.end(); it++)
    {
        if (x >= it->lowerBound && x <= it->upperBound)
        {
            return (*it->f)(x);
        }
    }
    return 0;
}

void piecewiseLinearFunction::addFunction(weightFunction *f, double lowerBound, double upperBound)
{
    functionSegment newSegment;
    newSegment.f = f;
    newSegment.lowerBound = lowerBound;
    newSegment.upperBound = upperBound;
    functions.push_back(newSegment);
}

double repeatingFunction::operator()(double x) const
{
    double period = upperBound - lowerBound;
    double x2 = x - lowerBound;
    double x3 = x2 - period * std::floor(x2 / period);
    return (*f)(x3);
}

piecewiseLinearFunction *repeatingFunctionToPiecewiseLinearFunction(repeatingFunction *f, double lowerBound, double upperBound)
{
    double functionStart = f->getLowerBound();
    double functionEnd = f->getUpperBound();
    double period = functionEnd - functionStart;

    double shift = period * std::floor((lowerBound - functionStart) / period);

    piecewiseLinearFunction *f2 = new piecewiseLinearFunction();
    while (f->getLowerBound() + shift < upperBound)
    {
        weightFunction *shifted = shiftFunction(f->getFunction(), shift);
        f2->addFunction(shifted, f->getLowerBound() + shift, f->getUpperBound() + shift);
        shift += period;
    }

    return f2;
}

weightFunction *shiftFunction(weightFunction *f, double shift)
{
    if (f->getType() == weightFunctionType::constant)
    {
        return shiftFunction((constantFunction *)f, shift);
    }
    else if (f->getType() == weightFunctionType::linear)
    {
        return shiftFunction((linearFunction *)f, shift);
    }
    else if (f->getType() == weightFunctionType::piecewiseLinear)
    {
        return shiftFunction((piecewiseLinearFunction *)f, shift);
    }
    else if (f->getType() == weightFunctionType::repeating)
    {
        return shiftFunction((repeatingFunction *)f, shift);
    }
    return nullptr;
}

constantFunction *shiftFunction(constantFunction *f, double shift)
{
    return f;
}

linearFunction *shiftFunction(linearFunction *f, double shift)
{
    return new linearFunction(f->gradient(), 0, f->intercept() - shift * f->gradient());
}

piecewiseLinearFunction *shiftFunction(piecewiseLinearFunction *f, double shift)
{
    piecewiseLinearFunction *f2 = new piecewiseLinearFunction();
    for (int i = 0; i < f->getFunctions().size(); i++)
    {
        weightFunction *f3 = shiftFunction(f->getFunctions()[i].f, shift);
        double l = f->getFunctions()[i].lowerBound;
        double u = f->getFunctions()[i].upperBound;
        f2->addFunction(f3, l + shift, u + shift);
    }
    return f2;
}

repeatingFunction *shiftFunction(repeatingFunction *f, double shift)
{
    return new repeatingFunction(shiftFunction(f->getFunction(), shift), f->getLowerBound() + shift, f->getUpperBound() + shift);
}
