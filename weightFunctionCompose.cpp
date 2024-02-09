#include "weightFunctionCompose.h"

weightFunction *calculateNext(weightFunction *nodeWeight, weightFunction *edgeWeight)
{
    if (nodeWeight->getType() == weightFunctionType::constant)
    {
        if (edgeWeight->getType() == weightFunctionType::constant)
        {
            return calculateNext((constantFunction *)nodeWeight, (constantFunction *)edgeWeight);
        }
    }
    return nullptr;
}

constantFunction *calculateNext(constantFunction *nodeWeight, constantFunction *edgeWeight)
{
    return new constantFunction(nodeWeight->value() + edgeWeight->value());
}