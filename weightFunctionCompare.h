#include "weightFunction.h"
#include <limits>

class weightFunctionCompare
{
public:
    bool operator()(std::pair<weightFunction *, long> p1, std::pair<weightFunction *, long> p2)
    {
        if (p1.first->getType() == weightFunctionType::constant && p2.first->getType() == weightFunctionType::constant)
        {
            return operator()(std::make_pair((constantFunction *)p1.first, p1.second), std::make_pair((constantFunction *)p2.first, p2.second));
        }
        return false;
    }

    bool operator()(std::pair<constantFunction *, long> p1, std::pair<constantFunction *, long> p2)
    {
        return (*(p1.first))(0) > (*(p2.first))(0);
    }

    bool operator()(std::pair<constantFunction *, long> p1, std::pair<linearFunction *, long> p2)
    {
        return false;
    }

    bool operator()(std::pair<constantFunction *, long> p1, std::pair<piecewiseLinearFunction *, long> p2)
    {
        double min = std::numeric_limits<double>::infinity();
        for (auto it = p2.first->getFunctions().begin(); it != p2.first->getFunctions().end(); it++)
        {
            min = std::min(min, (*(it->f))(it->lowerBound));
            min = std::min(min, (*(it->f))(it->upperBound));
        }

        return (*(p1.first))(0) > min;
    }

    bool operator()(std::pair<constantFunction *, long> p1, std::pair<repeatingFunction *, long> p2)
    {
        double min = std::numeric_limits<double>::infinity();
        weightFunction *f = p2.first->getFunction();
        if (f->getType() == weightFunctionType::constant)
        {
            return (*(p1.first))(0) > (*(constantFunction *)f)(0);
        }
        else if (f->getType() == weightFunctionType::linear)
        {
            min = std::min(min, (*(linearFunction *)f)(p2.first->getLowerBound()));
            min = std::min(min, (*(linearFunction *)f)(p2.first->getUpperBound()));
            return (*(p1.first))(0) > min;
        }
        else if (f->getType() == weightFunctionType::piecewiseLinear)
        {
            piecewiseLinearFunction *p = (piecewiseLinearFunction *)f;
            for (auto it = p->getFunctions().begin(); it != p->getFunctions().end(); it++)
            {
                min = std::min(min, (*(it->f))(it->lowerBound));
                min = std::min(min, (*(it->f))(it->upperBound));
            }
        }
    }
};