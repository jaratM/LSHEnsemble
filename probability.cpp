#include "probability.hpp"
#include <math.h>

double integral(func f, double a, double b, double precision){
    double area = 0;
	double x = a;
    while( x < b ){
        area += f(x + 0.5*precision) *precision;
		x += precision;
	}
    return area;
}

func falsePositive(int x, int q, int l, int k){
    return [x, q, l, k](double t) mutable{
        return 1.0 - pow(1.0-pow(t/(1.0+double(x)/double(q)-t), double(k)), double(l));
    };
}

func falseNegative(int x, int q, int l, int k){
    return [x, q, l, k](double t) mutable{
        return 1.0 - (1.0 - pow(1.0-pow(t/(1.0+double(x)/double(q)-t), double(k)), double(l)));
    };
}

double probFalseNegative(int x, int q, int l, int k, double t, double precision){
    func fn = falseNegative(x, q, l, k);
	double xq = double(x) / double(q);
	if (xq >= 1.0) {
		return integral(fn, t, 1.0, precision);
	}
	if( xq >= t ){
		return integral(fn, t, xq, precision);
	} else {
		return 0.0;
	}
}

double probFalsePositive(int x, int q, int l, int k, double t, double precision){
    func fp = falsePositive(x, q, l, k);
	double xq = double(x) / double(q);
	if (xq >= 1.0 ){
		return integral(fp, 0.0, t, precision);
	}
	if (xq >= t) {
		return integral(fp, 0.0, t, precision);
	} else {
		return integral(fp, 0.0, xq, precision);
	}
}