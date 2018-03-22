#include <iostream>
#include <map>
#include <math.h>
#include <stdio.h>
#include <iomanip>
using namespace std;

#define RADIX  	10
#define A  		5
#define K 		8
#define RHO 	(A / (1.0 * RADIX - 1))

map<double, double> reciprocal_table;

void populate_table(){
	// cout << "Reciprocal Table:" << endl;
	cout << fixed << setprecision(32);
	for(double i=0.5; i < 1; i = i + pow(2,-K)) {
		double unrounded = 1 / i;
		double rounded_up = ceil ( unrounded * pow(2,K)) / pow(2,K);
		reciprocal_table[i] = rounded_up;
		// cout << i << " : " << reciprocal_table[i] << endl;
	}
	// cout << endl;
}

int get_next_digit(double w) {
	return (int) round(RADIX * w);
}

double divide(double x, double d) {
	
	double x_prime = x * reciprocal_table[d];
	double d_prime = d * reciprocal_table[d];
	// cout << "m :" << reciprocal_table[d] << endl;
	// cout << "x_prime: " << x_prime << endl;
	// cout << "d_prime: " << d_prime << endl;
	// cout << "ideal: " << x_prime / d_prime << endl << endl;

	double q = 0;
	double w = x_prime;
	// cout << "w0: " << w << endl;
	int D;


	for (int i=1; i<=K; i++) {
		// cout << "D" << i-1 << ": " << D << endl;
		D = get_next_digit(w);
		q = q + D * pow(RADIX,-(i));
		w = RADIX * w - d_prime * D;
		// cout << "w" << i << ": " << w << endl;
	}
	return q;
}


int main() {

	if (RHO < 0.5 || RHO >= 1) {
		cout << "ERROR: Non-redundant digit set" << endl;
		return 0;
	}

	double x = 0.66666666;
	double d = 0.51171875;
	populate_table();
	cout << "Expected result: " << x / d << endl;
	cout << "Computed result: " << divide(x, d) << endl;
}