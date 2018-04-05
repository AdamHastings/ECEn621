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
#define NUM_TESTS 10000

double getLowerBound(int d, double S, int k) {
	return 2 * S * (d - RHO) + pow((d - RHO), 2) * pow(RADIX, -(k));
}

double getUpperBound(int d, double S, int k) {
	return 2 * S * (d + RHO) + pow((d + RHO), 2) * pow(RADIX, -(k));
}


// PROBLEM: We're calling this on z_1 --- It only works on k>=2
int getNextDigit(double z_k, double S_k, int k) {
	double L_2 = getLowerBound(2, S_k, k);
	double L_1 = getLowerBound(1, S_k, k);
	double L_0 = getLowerBound(0, S_k, k);
	double L_n1 = getLowerBound(-1, S_k, k);
	double L_n2 = getLowerBound(-2, S_k, k);
	// cout << "L_2: " << L_2 << endl;
	// cout << "L_1: " << L_1 << endl;
	// cout << "L_0: " << L_0 << endl;
	// cout << "L_n1: " << L_n1 << endl;
	// cout << "L_n2: " << L_n2 << endl;

	double scaled_residual = RADIX * z_k;
	// cout << "S_k: " << S_k << ", scaled_residual: " << scaled_residual << endl;
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
	// for (int i=A; i>=-A; i--) {
	// 	double next_S = S_k + (i * pow(RADIX, -(k)));
	// 	cout << "s = " << i << ", next_S = " << next_S << endl;
	// 	double upperBound = getUpperBound(i, next_S, k);
	// 	double lowerBound = getLowerBound(i, next_S, k);
	// 	double scaled_residual = RADIX * z_k;
	// 	cout << "\t" << lowerBound << " < " << scaled_residual << " < " << upperBound << endl;
	// 	if (scaled_residual < upperBound && scaled_residual > lowerBound) {
	// 		cout << "returning " << i << endl;
	// 		cout << "================\n\n";
	// 		return i;
	// 	}
	// }
	// cout << "broken?\n";
	// exit(0);
}

// return a random float in the specified range
double randf(double fMin, double fMax){
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

bool invariant(int k, double x, double S_k) {
	double z_k = pow(RADIX, k) * (x - pow(S_k, 2));
	return (z_k == pow(RADIX, k) * (x - pow(S_k, 2)));
}

double residual(int k, double x, double S_k) {
	double z_k = pow(RADIX, k) * (x - pow(S_k, 2));
	return z_k;
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

	// double S_1 = s_0 * pow(RADIX, 0) + s_1 * pow(RADIX, -1);
	// cout << "S_1: " << S_1 << endl;
	// cout << "S: " << S << endl;

	double z = RADIX * ( input - pow(S, 2));
	double s;
	
	// cout << "z_1: " << z_1 << endl << endl;
	// double s = s_1;
	// double z = z_1;
	// double S = S_1;


	// int s_2 = 1;
	// if (z_1 > 0.8) {
	// 	s_2 = 0;
	// 	cout << "Picked 0" << endl;
	// }
	// else if (z_1 > .4) {
	// 	s_2 = -1;
	// 	cout << "Picked -1" << endl;
	// }
	// else {
	// 	s_2 = -2;
	// 	cout << "Picked -2" << endl;
	// }


	// double S_2 = s_0 * pow(RADIX, 0) + s_1 * pow(RADIX, -1)+ s_2 * pow(RADIX, -2);
	// double z_2 = RADIX * z_1 - 2 * S_1 * s_2 - pow(s_2, 2)* pow(RADIX, -(2+1));
	// double z = z_2;
	// double S = S_2;
	// int s = s_2;

	// k+1 = i
	for (int i=2; i < K; i++) {
		s = getNextDigit(z, S, i);
		z = (RADIX * z) - (2 * S * s) - (pow(s, 2)* pow(RADIX, -(i)));
		S = S + (s * pow(RADIX, -(i)));
		// cout << "z: " << z << ", S: " << S << ", s: " << s << endl;  // << endl;
		// cout << "-\n-\n-\n";
	}
	return S;
}

int main() {

	srand (time(NULL)); // seed rand()
	// srand(100);

	// set cout precision to 16 decimal places
	cout << fixed << setprecision(16);

	// max error found
	double max_error = 0.00000000000001;
	int passed = 0;

	// for i random tests
	for(int i=1; i<=NUM_TESTS; i++){

		double input = randf(.25,1);
		// double input = 0.6899135700380027;
		// double input = 0.2902770085680657;
		// double input = 0.9180547640044497;

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
	cout << "Tests run: " << NUM_TESTS << endl;

	return 0;
}