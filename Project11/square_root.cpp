#include <iostream>
#include <cstdlib>
#include <math.h>       /* pow */
#include <time.h>       /* time */
#include <stdlib.h>     /* srand, rand */
#include <iomanip>      /* set precision */

using namespace std;

#define RADIX 2
#define A 1
#define RHO ((A)/(RADIX * 1.0 - 1))
#define K_MAX (64 + DELTA)
#define NUM_TESTS 1
#define DELTA 1


// Interpret digitArray as a number with radix = 2
double interpretArray(int x[K_MAX]) {
	double val = 0;
	for (int i=0; i < K_MAX; i++) {
		val += x[i] * pow(2, -i);
	}
}

int getNextDigit(double S, int k, double x, double z) {
	double B_1_0 = (2*S) + pow(2, -k) - x;
	double B_0_n1 = (-2*S) + pow(2, -k) - x;
	double scaled_residual = 2 * z;

	if (scaled_residual >= B_1_0)
		return 1;
	else if (scaled_residual >= B_0_n1)
		return 0;
	else
		return -1;
}

double computesqrt(int (&x)[K_MAX]) {

	double X, S, old_S, s, z;
	
	// k = 0
	X = x[0]; 

	// k = 1
	X += x[1] * pow(2, -1);
	s = 0;
	S = 0;
	z = pow(2, 1) * (X - pow(S, 2));
	old_S = S;

	// k = 2
	X += x[2] * pow(2, -2);
	s = 1;
	S = 0.5;
	z = pow(2, 2) * (X - pow(S, 2));


	// k >= 3
	for (int i=3; i < K_MAX-1; i++) {
		X += x[i] * pow(2, -i);
		s = getNextDigit(old_S, (i-1), x[i], z);
		old_S = S;
		S += s * pow(2, -(i-1));
		z = (2*z) + x[i] - (2*s*(old_S + S));
		cout << "z: " << z << ", S: " << S << ", s: " << s << endl;
	}

	return S;
}

// Fills an array of size K_MAX with random digits in the digit set {-1,0,1}
// Meant to be interpreted with radix = 2
void createRandInput(int x[K_MAX])
 {
	for (int i=0; i < K_MAX; i++) {
		x[i] = rand()%3 - 1;
	}
	double val = interpretArray(x);
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
		
		int input[K_MAX];
		double input_val;

		while(interpretArray(input) < 0.25 || interpretArray(input) >= 1) {
			createRandInput(input);
			input_val = interpretArray(input);
		}
		cout << "Input: " << input_val << endl << endl;

		// compute results
		double expexted_result = sqrt(input_val);
		double computed_result = computesqrt(input);
		double error = fabs(expexted_result-computed_result);

		// record maximum error found
		if(error>max_error) {
			max_error = error;

			// report results
			cout << "Test " << i << ": sqrt(" << input_val << ")" << endl;
			cout << "\tExpected result: " << expexted_result << endl;
			cout << "\tComputed result: " << computed_result << endl;
			cout << "\tError:           " << error << endl << endl;
		} else {
			passed++;
		}

		cout << endl;
		cout << "\tExpected result: " << expexted_result << endl;
		cout << "\tComputed result: " << computed_result << endl;
		cout << "\tError:           " << error << endl << endl;
	}



	// report number of tests, and maximum error
	cout << "Tests run    :  " << NUM_TESTS << endl;
	cout << "Tests pased  :  " << passed << endl;

	return 0;
}