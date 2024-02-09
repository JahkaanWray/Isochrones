#include "weightFunction.h"

weightFunction *add(weightFunction *f1, weightFunction *f2);

constantFunction *add(constantFunction *f1, constantFunction *f2);
linearFunction *add(constantFunction *f1, linearFunction *f2);
piecewiseLinearFunction *add(constantFunction *f1, piecewiseLinearFunction *f2);
repeatingFunction *add(constantFunction *f1, repeatingFunction *f2);

linearFunction *add(linearFunction *f1, linearFunction *f2);
linearFunction *add(linearFunction *f1, constantFunction *f2);
piecewiseLinearFunction *add(linearFunction *f1, piecewiseLinearFunction *f2);
weightFunction *add(linearFunction *f1, repeatingFunction *f2);

piecewiseLinearFunction *add(piecewiseLinearFunction *f1, piecewiseLinearFunction *f2);
piecewiseLinearFunction *add(piecewiseLinearFunction *f1, constantFunction *f2);
piecewiseLinearFunction *add(piecewiseLinearFunction *f1, linearFunction *f2);
piecewiseLinearFunction *add(piecewiseLinearFunction *f1, repeatingFunction *f2);

repeatingFunction *add(repeatingFunction *f1, repeatingFunction *f2);
repeatingFunction *add(repeatingFunction *f1, constantFunction *f2);
weightFunction *add(repeatingFunction *f1, linearFunction *f2);
piecewiseLinearFunction *add(repeatingFunction *f1, piecewiseLinearFunction *f2);
