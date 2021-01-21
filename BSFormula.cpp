#include "BSFormula.h"
#include "NormDistrib.h"
#include "OptionData.h"
#include <cmath>
#include <vector>

double BSFormulaCalc(OptionData inputdata)
{
		double d1 = (log(inputdata.s / inputdata.k) + (inputdata.r + pow(inputdata.sigma, 2) / 2) * inputdata.t) / (inputdata.sigma * sqrt(inputdata.t));
		double d2 = d1 - inputdata.sigma * sqrt(inputdata.t);
		double n1 = phi(d1);
		double n2 = phi(d2);
		double pv = inputdata.k * exp(-inputdata.r * inputdata.t);
		return n1 * inputdata.s - n2 * pv;
}

OptionData StructOptionData(double s, double k, double r, double t, double sigma, double premium)
{
	OptionData res;
	res.s = s;
	res.k = k;
	res.r = r;
	res.t = t;
	res.sigma = sigma;
	res.premium = premium;
	return res;
}

double DoApproximate(double s, double k, double r, double t, double premium, int depth)
{
	double potential_sigma = 1;
	double eval_prem;
	OptionData potential_input;

	for (int i = 1; i < depth; ++i)
	{
		double substractor = 1 / pow(10, i);
		for (int j = 1; j < 10; ++j)
		{
			potential_sigma -= substractor;
			potential_input = StructOptionData(s, k, r, t, potential_sigma, 0);
			eval_prem = BSFormulaCalc(potential_input);
			if (eval_prem < premium)
			{
				potential_sigma += substractor;
				break;
			}
		}

	}
	return potential_sigma;
}

double BSFormulaFindVolat(OptionData inputdata)
{
	return DoApproximate(inputdata.s, inputdata.k, inputdata.r, inputdata.t, inputdata.premium, 10);
}