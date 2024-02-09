#include "weightFunctionAdd.h"

weightFunction *add(weightFunction *f1, weightFunction *f2)
{
    switch (f1->getType())
    {
    case weightFunctionType::constant:
        switch (f2->getType())
        {
        case weightFunctionType::constant:
            return add((constantFunction *)f1, (constantFunction *)f2);
        case weightFunctionType::linear:
            return add((constantFunction *)f1, (linearFunction *)f2);
        case weightFunctionType::piecewiseLinear:
            return add((constantFunction *)f1, (piecewiseLinearFunction *)f2);
        case weightFunctionType::repeating:
            return add((constantFunction *)f1, (repeatingFunction *)f2);
        default:
            break;
        }
    case weightFunctionType::linear:
        switch (f2->getType())
        {
        case weightFunctionType::constant:
            return add((linearFunction *)f1, (constantFunction *)f2);
        case weightFunctionType::linear:
            return add((linearFunction *)f1, (linearFunction *)f2);
        case weightFunctionType::piecewiseLinear:
            return add((linearFunction *)f1, (piecewiseLinearFunction *)f2);
        case weightFunctionType::repeating:
            return add((linearFunction *)f1, (repeatingFunction *)f2);
        default:
            break;
        }
    case weightFunctionType::piecewiseLinear:
        switch (f2->getType())
        {
        case weightFunctionType::constant:
            return add((piecewiseLinearFunction *)f1, (constantFunction *)f2);
        case weightFunctionType::linear:
            return add((piecewiseLinearFunction *)f1, (linearFunction *)f2);
        case weightFunctionType::piecewiseLinear:
            return add((piecewiseLinearFunction *)f1, (piecewiseLinearFunction *)f2);
        case weightFunctionType::repeating:
            return add((piecewiseLinearFunction *)f1, (repeatingFunction *)f2);
        default:
            break;
        }
    case weightFunctionType::repeating:
        switch (f2->getType())
        {
        case weightFunctionType::constant:
            return add((repeatingFunction *)f1, (constantFunction *)f2);
        case weightFunctionType::linear:
            return add((repeatingFunction *)f1, (linearFunction *)f2);
        case weightFunctionType::piecewiseLinear:
            return add((repeatingFunction *)f1, (piecewiseLinearFunction *)f2);
        case weightFunctionType::repeating:
            return add((repeatingFunction *)f1, (repeatingFunction *)f2);
        default:
            break;
        }
    }
    return nullptr;
}

constantFunction *add(constantFunction *f1, constantFunction *f2)
{
    return new constantFunction(f1->value() + f2->value());
}

linearFunction *add(constantFunction *f1, linearFunction *f2)
{
    return new linearFunction(f2->gradient(), 0, f2->intercept() + f1->value());
}

piecewiseLinearFunction *add(constantFunction *f1, piecewiseLinearFunction *f2)
{
    piecewiseLinearFunction *f3 = new piecewiseLinearFunction();
    for (auto it = f2->getFunctions().begin(); it != f2->getFunctions().end(); it++)
    {
        f3->addFunction(add(f1, it->f), it->lowerBound, it->upperBound);
    }
    return f3;
}

repeatingFunction *add(constantFunction *f1, repeatingFunction *f2)
{
    return new repeatingFunction(add(f1, f2->getFunction()), f2->getLowerBound(), f2->getUpperBound());
}

linearFunction *add(linearFunction *f1, linearFunction *f2)
{
    return new linearFunction(f1->gradient() + f2->gradient(), 0, f1->intercept() + f2->intercept());
}

linearFunction *add(linearFunction *f1, constantFunction *f2)
{
    return add(f2, f1);
}

piecewiseLinearFunction *add(linearFunction *f1, piecewiseLinearFunction *f2)
{
    piecewiseLinearFunction *f3 = new piecewiseLinearFunction();
    for (auto it = f2->getFunctions().begin(); it != f2->getFunctions().end(); it++)
    {
        f3->addFunction(add(f1, it->f), it->lowerBound, it->upperBound);
    }
    return f3;
}

weightFunction *add(linearFunction *f1, repeatingFunction *f2)
{
    throw "Not implemented";
    return nullptr;
}

piecewiseLinearFunction *add(piecewiseLinearFunction *f1, linearFunction *f2)
{
    return add(f2, f1);
}

piecewiseLinearFunction *add(piecewiseLinearFunction *f1, constantFunction *f2)
{
    return add(f2, f1);
}

piecewiseLinearFunction *add(piecewiseLinearFunction *f1, piecewiseLinearFunction *f2)
{
    piecewiseLinearFunction *f3 = new piecewiseLinearFunction();
    for (auto it = f1->getFunctions().begin(); it != f1->getFunctions().end(); it++)
    {
        f3->addFunction(add(it->f, f2), it->lowerBound, it->upperBound);
    }
    return f3;
}

piecewiseLinearFunction *add(piecewiseLinearFunction *f1, repeatingFunction *f2)
{
    throw "Not implemented";
    return nullptr;
}

repeatingFunction *add(repeatingFunction *f1, constantFunction *f2)
{
    return add(f2, f1);
}

weightFunction *add(repeatingFunction *f1, linearFunction *f2)
{
    throw "Not implemented";
}

piecewiseLinearFunction *add(repeatingFunction *f1, piecewiseLinearFunction *f2)
{
    throw "Not implemented";
}

repeatingFunction *add(repeatingFunction *f1, repeatingFunction *f2)
{
    throw "Not implemented";
}