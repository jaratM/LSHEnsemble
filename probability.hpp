#ifndef probability
#define probability
#include "utils.hpp"

using func = std::function<double(double)> ;

double integral(func f, double a, double b, double precision);

func falsePositive(int x, int q, int l, int k);

func falseNegative(int x, int q, int l, int k);

double probFalseNegative(int x, int q, int l, int k, double t, double precision);

double probFalsePositive(int x, int q, int l, int k, double t, double precision);
#endif