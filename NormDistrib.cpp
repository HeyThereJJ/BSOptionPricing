#include <cmath>
#include "NormDistrib.h"

double phi(double x)
{
    return 0.5 * erfc(-x / sqrt(2));
}