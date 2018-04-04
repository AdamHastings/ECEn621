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
#define K 4
#define NUM_TESTS   1 // 10000

double getLowerBound(int d, double S) {
	return 2 * S * (d - RHO) + pow((d - RHO), 2) * pow(RADIX, -(K + 1));
}

int getNextDigit(double z_k, double S_k) {
	double L_2 = getLowerBound(2, S_k);
	double L_1 = getLowerBound(1, S_k);
	double L_0 = getLowerBound(0, S_k);
	double L_n1 = getLowerBound(-1, S_k);
	double L_n2 = getLowerBound(-2, S_k);
	cout << "L_2: " << L_2 << endl;
	cout << "L_1: " << L_1 << endl;
	cout << "L_0: " << L_0 << endl;
	cout << "L_n1: " << L_n1 << endl;
	cout << "L_n2: " << L_n2 << endl;

	double scaled_residual = RADIX * z_k;
	cout << "scaled_residual: " << scaled_residual << endl;
	if (scaled_residual >= L_2)
		return 2;
	else if (scaled_residual >= L_1)
		return 1;
	else if (scaled_residual >= L_0)
		return 0;
	else if (scaled_residual >= L_n1)
		return -1;
	else
		return -2;
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
	// cout << "Input: " << input << endl;
	// TODO: We need some kind of lookup table for s_0 and s_1
	int s_0 = 1;
	int s_1 = -1;

	// double S_0 = s_0;
	// if (invariant())
	// 	s_1 = -2;
	// else if (invariant())
	// 	s_l = -1;
	// else if (invariant())
	// 	s_1 = 0;
	// else {
	// 	cout << "Error: Invariant is not satisfied with input " << input << endl;
	// 	return 0;
	// }


	// if (input > 0.8) {
	// 	s_1 = 0;
	// 	// cout << "Picked 0" << endl;
	// }
	// else if (input > .4) {
	// 	s_1 = -1;
	// 	// cout << "Picked -1" << endl;
	// }
	// else {
	// 	s_1 = -2;
	// 	// cout << "Picked -2" << endl;
	// }

	double S_1 = s_0 * pow(RADIX, 0) + s_1 * pow(RADIX, -1);
	// cout << "S_1: " << S_1 << endl;

	double z_1 = RADIX * ( input - pow(S_1, 2));

	double z = z_1;
	double S = S_1;
	int s = s_1;
	cout << "z1: " << z_1 << endl << endl;

	for (int i=2; i < K; i++) {
		s = getNextDigit(z, S);
		z = RADIX * z - 2 * S * s - pow(s, 2)* pow(RADIX, -i);
		S = S + s * pow(RADIX, -i);
		cout << "z: " << z << ", S: " << S << ", s: " << s << endl;  // << endl;

	}
	return S;
}

int main() {

	// srand (time(NULL)); // seed rand()
	srand(100);

	// set cout precision to 16 decimal places
	cout << fixed << setprecision(16);

	// max error found
	double max_error;

	// for i random tests
	for(int i=1; i<=NUM_TESTS; i++){

		// double input = randf(.25,1);
		double input = 0.6899135700380027;

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
		}
	}

	// report number of tests, and maximum error
	cout << "Tests run: " << NUM_TESTS << endl;
	cout << "Maximum error: " << max_error << endl;

	return 0;
}