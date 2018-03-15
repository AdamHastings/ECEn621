#include <iostream>
#include <map>
#include <math.h>
using namespace std;

#define RADIX  	10
#define A  		5
#define K 		8
#define RHO 	(A / (RADIX - 1))

int digit_array[K+1];
map<double, double> reciprocal_table;

void populate_table(){
	cout << "Reciprocal Table:" << endl;
	// TODO: We need to make sure m is always rounded up!
	for(double i=0.5; i < 1; i = i + pow(2,-K)) {
		reciprocal_table[i] = 1 / i;
		cout << i << " : " << reciprocal_table[i] << endl;
	}
	cout << endl;
}

int get_next_digit(double w) {
	return (int) round(w);
}

double divide(double x, double d) {
	
	double x_prime = x * reciprocal_table[d];
	double d_prime = d * reciprocal_table[d];

	double q = 0;
	double w = x_prime;
	int D;

	for (int i=0; i<K; i++) {
		D = get_next_digit(w);
		q = q + D * pow(RADIX,-(i+1));
		w = RADIX * w - d_prime * D;
	}
	return q;
}


int main() {
	double x = 0.564;
	double d = 0.789;
	populate_table();
	cout << "Expected result: " << x / d << endl;
	cout << "Computed result: " << divide(x, d) << endl;
}