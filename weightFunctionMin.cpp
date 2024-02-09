#include <iostream>
#include "weightFunctionMin.h"

constantFunction *min(constantFunction *f1, constantFunction *f2)
{
    if (f1->value() < f2->value())
    {
        return f1;
    }
    else
    {
        return f2;
    }
}

piecewiseLinearFunction *min(constantFunction *f1, linearFunction *f2)
{
    piecewiseLinearFunction *f3 = new piecewiseLinearFunction();
    double x = (f1->value() - f2->intercept()) / f2->gradient();
    if (f2->gradient() > 0)
    {
        f3->addFunction(f2, 0, x);
        f3->addFunction(f1, x, 1000);
    }
    else
    {
        f3->addFunction(f1, 0, x);
        f3->addFunction(f2, x, 1000);
    }
    return f3;
}

piecewiseLinearFunction *min(constantFunction *f1, piecewiseLinearFunction *f2)
{
    return min(f2, f1);
}

repeatingFunction *min(constantFunction *f1, repeatingFunction *f2)
{
    return min(f2, f1);
}

piecewiseLinearFunction *min(linearFunction *f1, constantFunction *f2)
{
    return min(f2, f1);
}

weightFunction *min(linearFunction *f1, linearFunction *f2)
{
    if (f1->gradient() == f2->gradient())
    {
        return f1->intercept() < f2->intercept() ? f1 : f2;
    }
    piecewiseLinearFunction *f3 = new piecewiseLinearFunction();
    double x = (f1->intercept() - f2->intercept()) / (f2->gradient() - f1->gradient());
    if (f1->gradient() > f2->gradient())
    {
        f3->addFunction(f1, 0, x);
        f3->addFunction(f2, x, 1000);
    }
    else
    {
        f3->addFunction(f2, 0, x);
        f3->addFunction(f1, x, 1000);
    }
    return f3;
}

piecewiseLinearFunction *min(linearFunction *f1, piecewiseLinearFunction *f2)
{
    piecewiseLinearFunction *f3 = new piecewiseLinearFunction();

    for (int i = 0; i < f2->getFunctions().size(); i++)
    {
        weightFunction *f = f2->getFunctions()[i].f;
        double l = f2->getFunctions()[i].lowerBound;
        double u = f2->getFunctions()[i].upperBound;
        f3->addFunction(min(f1, f), l, u);
    }
    return f3;
}

piecewiseLinearFunction *min(linearFunction *f1, repeatingFunction *f2)
{
    throw "Not implemented";
}

piecewiseLinearFunction *min(piecewiseLinearFunction *f1, constantFunction *f2)
{
    std::cout << "Calling function with piecewiseLinearFunction *f1, constantFunction *f2\n";
    piecewiseLinearFunction *f3 = new piecewiseLinearFunction();
    for (int i = 0; i < f1->getFunctions().size(); i++)
    {
        weightFunction *f = f1->getFunctions()[i].f;
        double l = f1->getFunctions()[i].lowerBound;
        double u = f1->getFunctions()[i].upperBound;
        f3->addFunction(min(f, f2), l, u);
    }
    return f3;
}

piecewiseLinearFunction *min(piecewiseLinearFunction *f1, linearFunction *f2)
{
    return min(f2, f1);
}

piecewiseLinearFunction *min(piecewiseLinearFunction *f1, piecewiseLinearFunction *f2)
{
    piecewiseLinearFunction *f3 = new piecewiseLinearFunction();
    if (f1->getFunctions()[0].lowerBound < f2->getFunctions()[0].lowerBound)
    {
        for (int i = 0; i < f1->getFunctions().size(); i++)
        {
            weightFunction *f = f1->getFunctions()[i].f;
            double l = f1->getFunctions()[i].lowerBound;
            double u = f1->getFunctions()[i].upperBound;
            f3->addFunction(min(f, f2), l, u);
        }
    }
    else
    {
        for (int i = 0; i < f2->getFunctions().size(); i++)
        {
            weightFunction *f = f2->getFunctions()[i].f;
            double l = f2->getFunctions()[i].lowerBound;
            double u = f2->getFunctions()[i].upperBound;
            f3->addFunction(min(f, f1), l, u);
        }
    }
    return f3;
}

piecewiseLinearFunction *min(piecewiseLinearFunction *f1, repeatingFunction *f2)
{
    throw "Not implemented";
}

repeatingFunction *min(repeatingFunction *f1, constantFunction *f2)
{
    weightFunction *f = min(f1->getFunction(), f2);
    return new repeatingFunction(f, f1->getLowerBound(), f1->getUpperBound());
}

piecewiseLinearFunction *min(repeatingFunction *f1, linearFunction *f2)
{
    throw "Not implemented";
}

piecewiseLinearFunction *min(repeatingFunction *f1, piecewiseLinearFunction *f2)
{
    throw "Not implemented";
}

repeatingFunction *min(repeatingFunction *f1, repeatingFunction *f2)
{
    // find the smallest common period
    // create piecewise function equivalent to both functions for this period
    // find min of these piecewise functions
    // convert back into repeating function
    double period1 = f1->getUpperBound() - f1->getLowerBound();
    double period2 = f2->getUpperBound() - f2->getLowerBound();
    // Currently only handles the case where the periods are equal
    if (period1 != period2)
    {
        std::cout << "Periods are not equal\n";
        return nullptr;
    }
    piecewiseLinearFunction *f3 = repeatingFunctionToPiecewiseLinearFunction(f1, f1->getLowerBound(), f1->getUpperBound());
    piecewiseLinearFunction *f4 = repeatingFunctionToPiecewiseLinearFunction(f2, f1->getLowerBound(), f1->getUpperBound());

    return new repeatingFunction(min(f3, f4), f1->getLowerBound(), f1->getUpperBound());
}

weightFunction *min(weightFunction *f1, weightFunction *f2)
{
    std::cout << "Calling function with weightFunction *f1, weightFunction *f2\n";
    if (f1->getType() == weightFunctionType::constant)
    {
        std::cout << "f1 is constant\n";
        if (f2->getType() == weightFunctionType::constant)
        {
            std::cout << "f2 is constant\n";
            return min((constantFunction *)f1, (constantFunction *)f2);
        }
        else if (f2->getType() == weightFunctionType::linear)
        {
            std::cout << "f2 is linear\n";
            return min((constantFunction *)f1, (linearFunction *)f2);
        }
        else if (f2->getType() == weightFunctionType::piecewiseLinear)
        {
            std::cout << "f2 is piecewiseLinear\n";
            return min((piecewiseLinearFunction *)f2, (constantFunction *)f1);
        }
        else if (f2->getType() == weightFunctionType::repeating)
        {
            std::cout << "f2 is repeating\n";
            return min((repeatingFunction *)f2, (constantFunction *)f1);
        }
    }
    else if (f1->getType() == weightFunctionType::linear)
    {
        std::cout << "f1 is linear\n";
        if (f2->getType() == weightFunctionType::constant)
        {
            std::cout << "f2 is constant\n";
            return min((constantFunction *)f2, (linearFunction *)f1);
        }
        else if (f2->getType() == weightFunctionType::linear)
        {
            std::cout << "f2 is linear\n";
            return min((linearFunction *)f1, (linearFunction *)f2);
        }
        else if (f2->getType() == weightFunctionType::piecewiseLinear)
        {
            std::cout << "f2 is piecewiseLinear\n";
            return min((piecewiseLinearFunction *)f2, (linearFunction *)f1);
        }
        else if (f2->getType() == weightFunctionType::repeating)
        {
        }
    }
    else if (f1->getType() == weightFunctionType::piecewiseLinear)
    {
        std::cout << "f1 is piecewiseLinear\n";
        if (f2->getType() == weightFunctionType::constant)
        {
            std::cout << "f2 is constant\n";
            return min((piecewiseLinearFunction *)f1, (constantFunction *)f2);
        }
        else if (f2->getType() == weightFunctionType::linear)
        {
            std::cout << "f2 is linear\n";
            return min((piecewiseLinearFunction *)f1, (linearFunction *)f2);
        }
        else if (f2->getType() == weightFunctionType::piecewiseLinear)
        {
            std::cout << "f2 is piecewiseLinear\n";
            return min((piecewiseLinearFunction *)f1, (piecewiseLinearFunction *)f2);
        }
        else if (f2->getType() == weightFunctionType::repeating)
        {
        }
    }
    else if (f1->getType() == weightFunctionType::repeating)
    {
        std::cout << "f1 is repeating\n";
        if (f2->getType() == weightFunctionType::constant)
        {
            std::cout << "f2 is constant\n";
            return min((repeatingFunction *)f1, (constantFunction *)f2);
        }
        else if (f2->getType() == weightFunctionType::linear)
        {
        }
        else if (f2->getType() == weightFunctionType::piecewiseLinear)
        {
        }
        else if (f2->getType() == weightFunctionType::repeating)
        {
        }
    }
    return nullptr;
}
