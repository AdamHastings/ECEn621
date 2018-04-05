#include <iostream>
#include <cstdlib>
#include <math.h>       /* pow */
#include <time.h>       /* time */
#include <stdlib.h>     /* srand, rand */
#include <iomanip>      /* set precision */

using namespace std;

#define RADIX 4
#define A 2
#define RHO ((A)/(RADIX * 1.0 - 1))
#define K 64
#define NUM_TESTS 100000

double getLowerBound(int d, double S, int k) {
	return 2 * S * (d - RHO) + pow((d - RHO), 2) * pow(RADIX, -(k));
}

double getUpperBound(int d, double S, int k) {
	return 2 * S * (d + RHO) + pow((d + RHO), 2) * pow(RADIX, -(k));
}

int getNextDigit(double z_k, double S_k, int k) {
	double L_2 = getLowerBound(2, S_k, k);
	double L_1 = getLowerBound(1, S_k, k);
	double L_0 = getLowerBound(0, S_k, k);
	double L_n1 = getLowerBound(-1, S_k, k);
	double L_n2 = getLowerBound(-2, S_k, k);

	double scaled_residual = RADIX * z_k;
	if (scaled_residual > L_2)
		return 2;
	else if (scaled_residual > L_1)
		return 1;
	else if (scaled_residual > L_0)
		return 0;
	else if (scaled_residual > L_n1)
		return -1;
	else
		return -2;
}

// return a random float in the specified range
double randf(double fMin, double fMax){
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}


double computesqrt(double input) {
	if (input < 0.25 || input >= 1) {
		cout << "Error: Input needs to be in the range [0.25, 1)" << endl;
		return 0;
	}
	// TODO: We need some kind of lookup table for s_0 and s_1
	int s_0;// = 1;
	int s_1;// = -1;
	double S;


	if (input > 0.8) {
		s_0 = 1;
		s_1 = 0;
		S = 1;
	}
	else if (input > 0.4) {
		s_0 = 1;
		s_1 = -1;
		S = 0.75;
	}
	else {
		s_0 = 0;
		s_1 = 2;
		S = 0.5;
	}

	double z = RADIX * ( input - pow(S, 2));
	double s;

	for (int i=2; i < K; i++) {
		s = getNextDigit(z, S, i);
		z = (RADIX * z) - (2 * S * s) - (pow(s, 2)* pow(RADIX, -(i)));
		S = S + (s * pow(RADIX, -(i)));
	}
	return S;
}

int main() {

	srand (time(NULL)); // seed rand()

	// set cout precision to 16 decimal places
	cout << fixed << setprecision(16);

	// max error found
	double max_error = 0.00000000000001;
	int passed = 0;

	// for i random tests
	for(int i=1; i<=NUM_TESTS; i++){

		double input = randf(.25,1);

		// compute results
		double expexted_result = sqrt(input);
		double computed_result = computesqrt(input);
		double error = fabs(expexted_result-computed_result);

		// record maximum error found
		if(error>max_error) {
			max_error = error;

			// report results
			cout << "Test " << i << ": sqrt(" << input << ")" << endl;
			cout << "\tExpected result: " << expexted_result << endl;
			cout << "\tComputed result: " << computed_result << endl;
			cout << "\tError:           " << error << endl << endl;
		} else {
			passed++;
		}
	}

	// report number of tests, and maximum error
	cout << "Tests run    :  " << NUM_TESTS << endl;
	cout << "Tests pased  :  " << passed << endl;

	return 0;
}