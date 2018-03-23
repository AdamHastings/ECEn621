#include <iostream>
#include <map>
#include <math.h>
#include <stdio.h>
#include <iomanip>
#include <time.h>       /* time */
#include <stdlib.h>     /* srand, rand */

using namespace std;

#define RADIX  	10
#define A  		5
#define K 		8
#define RHO 	     (A / (1.0 * RADIX - 1))
#define NUM_TESTS   1000000

map<double, double> reciprocal_table;

// return a random float in the specified range
double randf(double fMin, double fMax){
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

// return the key to the nearest map element that exists
double getClosest(double pos){
     if(reciprocal_table.size() < 1) return 0;                                            // if map is empty
     if(reciprocal_table.size() < 2) return reciprocal_table.begin()->first;              // if only one element in map, return it
     if(pos <= reciprocal_table.begin()->first) return reciprocal_table.begin()->first;   // if pos is less than all map elements, or equal to the first one, return the first one

     for (auto it = reciprocal_table.begin(); it != reciprocal_table.end(); it++) {
          auto it_next = next(it);                     // get iterator to next map element
          if(it_next == reciprocal_table.end()){       // if it is the last element in the map
               return it->first;
          } else {
               if(pos < it_next->first) {                             // if pos is less than next map element
                    // it is lower bound, it_next is upper bound
                    if(pos - it->first <= it_next->first - pos)      // if pos is closer to current element (it)
                         return it->first;
                    else                                             // pos is closer to next element (it_next)
                         return it_next->first;
               }
          }
     }
     return 0; // shouldn't ever get here, error condition
}

// fill the reciprocal table (this is precomputed in real hardware)
void populate_table(){
	for(double i=0.5; i < 1; i = i + pow(2,-K)) {
		double unrounded = 1 / i;
		double rounded_up = ceil ( unrounded * pow(2,K)) / pow(2,K);
		reciprocal_table[i] = rounded_up;
	}
}

// round the residual to select the next digit
int get_next_digit(double w) {
	return (int) round(RADIX * w);
}

// core division algorithm
double divide(double x, double d) {

     // prescale
	double x_prime = x * reciprocal_table[getClosest(d)];
	double d_prime = d * reciprocal_table[getClosest(d)];

     // initialize recurrence variables
	double q = 0;
	double w = x_prime;

     // this will hold the next digit selected
     int D;

     // run the recurrences
	for (int i=1; i<=K; i++) {
		// cout << "D" << i-1 << ": " << D << endl;
		D = get_next_digit(w);
		q = q + D * pow(RADIX,-(i));
		w = RADIX * w - d_prime * D;
		// cout << "w" << i << ": " << w << endl;
	}

     // return the quotient
	return q;
}


int main() {
	if (RHO < 0.5 || RHO >= 1) {
		cout << "ERROR: Non-redundant digit set" << endl;
		return 0;
	}

     srand (time(NULL)); // seed rand()

     // set cout precision to 16 decimal places
	cout << fixed << setprecision(16);

     // before any division, make sure to populate the reciprocal table
	populate_table();

     // max error found
     double max_error;

     // for i random tests
     for(int i=1; i<=NUM_TESTS; i++){

          // provide dividend (x) and divisor (d)
          // assumed to have previously been normalized to [1/2 ... 1)
          double x = randf(.5,1);
          double d = randf(.5,1);

          // compute results
          double expexted_result = x / d;
          double computed_result = divide(x, d);
          double error = fabs(expexted_result-computed_result);

          // record maximum error found
          if(error>max_error) max_error = error;

          // report results
          cout << "Test " << i << ": " << x << " / " << d << endl;
          cout << "\tExpected result: " << expexted_result << endl;
          cout << "\tComputed result: " << computed_result << endl;
          cout << "\tError:           " << error << endl << endl;
     }

     // report number of tests, and maximum error
     cout << "Tests run: " << NUM_TESTS << endl;
     cout << "Maximum error: " << max_error << endl;
}