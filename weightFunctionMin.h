#include "weightFunction.h"

weightFunction *min(weightFunction *f1, weightFunction *f2);

constantFunction *min(constantFunction *f1, constantFunction *f2);
piecewiseLinearFunction *min(constantFunction *f1, linearFunction *f2);
piecewiseLinearFunction *min(constantFunction *f1, piecewiseLinearFunction *f2);
repeatingFunction *min(constantFunction *f1, repeatingFunction *f2);

piecewiseLinearFunction *min(linearFunction *f1, constantFunction *f2);
weightFunction *min(linearFunction *f1, linearFunction *f2);
piecewiseLinearFunction *min(linearFunction *f1, piecewiseLinearFunction *f2);
piecewiseLinearFunction *min(linearFunction *f1, repeatingFunction *f2);

piecewiseLinearFunction *min(piecewiseLinearFunction *f1, constantFunction *f2);
piecewiseLinearFunction *min(piecewiseLinearFunction *f1, linearFunction *f2);
piecewiseLinearFunction *min(piecewiseLinearFunction *f1, piecewiseLinearFunction *f2);
piecewiseLinearFunction *min(piecewiseLinearFunction *f1, repeatingFunction *f2);

repeatingFunction *min(repeatingFunction *f1, constantFunction *f2);
piecewiseLinearFunction *min(repeatingFunction *f1, linearFunction *f2);
piecewiseLinearFunction *min(repeatingFunction *f1, piecewiseLinearFunction *f2);
repeatingFunction *min(repeatingFunction *f1, repeatingFunction *f2);
