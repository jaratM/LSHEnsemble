#include "probability.hpp"
#include <math.h>

double falsePositive(int x, int q, int l, int k, double t){
    return 1.0 - pow(1.0-pow(t/(1.0+double(x)/double(q)-t), double(k)), double(l));
}

double falseNegative(int x, int q, int l, int k, double t){
    return 1.0 - (1.0 - pow(1.0-pow(t/(1.0+double(x)/double(q)-t), double(k)), double(l)));
}

double integral_fp(int x, int q, int l, int k, double a, double b, double precision){
    double area = 0;
	double p = a;
    while( p < b ){
        area += falsePositive(x, q, l, k, p + 0.5*precision) *precision;
		p += precision;
	}
    return area;
}

double integral_fn(int x, int q, int l, int k, double a, double b, double precision){
    double area = 0;
	double p = a;
    while( p < b ){
        area += falseNegative(x, q, l, k, p + 0.5*precision) *precision;
		p += precision;
	}
    return area;
}
double probFalseNegative(int x, int q, int l, int k, double t, double precision){
	double xq = double(x) / double(q);
	if (xq >= 1.0) {
		return integral_fn(x, q, l, k, t, 1.0, precision);
	}
	if( xq >= t ){
		return integral_fn(x, q, l, k , t, xq, precision);
	} else {
		return 0.0;
	}
}

double probFalsePositive(int x, int q, int l, int k, double t, double precision){
	double xq = double(x) / double(q);
	if (xq >= 1.0 ){
		return integral_fp(x, q, l, k, 0.0, t, precision);
	}
	if (xq >= t) {
		return integral_fp(x, q, l, k, 0.0, t, precision);
	} else {
		return integral_fp(x, q, l, k, 0.0, xq, precision);
	}
}