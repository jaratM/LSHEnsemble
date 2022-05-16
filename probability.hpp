#ifndef probability
#define probability
#include "utils.hpp"


double integral_fn(int x, int q, int l, int k, double a, double b, double precision);

double integral_fp(int x, int q, int l, int k, double a, double b, double precision);

double falsePositive(int x, int q, int l, int k);

double falseNegative(int x, int q, int l, int k);

double probFalseNegative(int x, int q, int l, int k, double t, double precision);

double probFalsePositive(int x, int q, int l, int k, double t, double precision);
#endif