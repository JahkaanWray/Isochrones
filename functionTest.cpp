#include <iostream>
#include "weightFunctionMin.h"

int main()
{
    constantFunction *c1 = new constantFunction(26);
    constantFunction *c2 = new constantFunction(25);
    linearFunction *l1 = new linearFunction(1, 0, 0);
    linearFunction *l2 = new linearFunction(1, 20, 0);
    linearFunction *l3 = new linearFunction(1, 100, 0);
    linearFunction *l4 = new linearFunction(1, 20, 0);
    linearFunction *l5 = new linearFunction(1, 70, 0);
    linearFunction *l6 = new linearFunction(1, 120, 0);

    piecewiseLinearFunction *p1 = new piecewiseLinearFunction();
    p1->addFunction(l1, 0, 50);
    p1->addFunction(l2, 50, 100);
    p1->addFunction(l3, 100, 150);

    piecewiseLinearFunction *p2 = new piecewiseLinearFunction();
    p2->addFunction(c2, 0, 20);
    p2->addFunction(l4, 20, 70);
    p2->addFunction(l5, 70, 120);
    p2->addFunction(l6, 120, 170);

    repeatingFunction *r1 = new repeatingFunction(l1, 0, 50);
    repeatingFunction *r2 = new repeatingFunction(l2, 20, 70);

    weightFunction *f1 = min(r1, r2);
    weightFunction *f2 = min(f1, c1);

    piecewiseLinearFunction *p3 = repeatingFunctionToPiecewiseLinearFunction(r1, 0, 50);
    piecewiseLinearFunction *p4 = repeatingFunctionToPiecewiseLinearFunction(r2, 0, 50);

    for (int i = 0; i < 300; i++)
    {
        std::cout << i << " " << (*f2)(i) << " \n";
    }
    std::cout << "\n";
}