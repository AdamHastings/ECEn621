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



double getClosest(double pos);
double divide(double x, double d);
void populate_table();
int get_next_digit(double w);


void populate_table(){
	cout << "Reciprocal Table:" << endl;
	// cout << fixed << setprecision(32);
	for(double i=0.5; i < 1; i = i + pow(2,-K)) {
		double unrounded = 1 / i;
		double rounded_up = ceil ( unrounded * pow(2,K)) / pow(2,K);
		reciprocal_table[i] = rounded_up;
		cout << i << " : " << reciprocal_table[i] << endl;
	}
	cout << endl;
}

int get_next_digit(double w) {
	return (int) round(RADIX * w);
}

double divide(double x, double d) {

	// double x_prime = x * reciprocal_table[d];
	// double x_prime = reciprocal_table[d];
	reciprocal_table[d];


	// double d_prime = d * reciprocal_table[d];


	// cout << "m :" << reciprocal_table[d] << endl;
	// cout << "x_prime: " << x_prime << endl;
	// cout << "d_prime: " << d_prime << endl;
	// cout << "ideal: " << x_prime / d_prime << endl << endl;

     cout << "d: " << d << endl;
     cout << "rt[d]: " << getClosest(d) << endl;

	double q = 0;
	// double w = x_prime;
	// // cout << "w0: " << w << endl;
	// int D;


	// for (int i=1; i<=K; i++) {
	// 	// cout << "D" << i-1 << ": " << D << endl;
	// 	D = get_next_digit(w);
	// 	q = q + D * pow(RADIX,-(i));
	// 	w = RADIX * w - d_prime * D;
	// 	// cout << "w" << i << ": " << w << endl;
	// }
	return q;
}

double getClosest(double pos){

     // if(pos <= reciprocal_table.begin()->first) return reciprocal_table.begin()->first;   // if pos is less than all map elements, or equal to the first one, return the first one
     // if(reciprocal_table.size() < 2) return reciprocal_table.begin()->first;              // if only one element in map, return it


     // int i=0;

     for (auto it = reciprocal_table.begin(); it != reciprocal_table.end(); it++) {
          double next_val = next(it)->first;
          double curr_val = it->first;

          // cout << "iteration: " << i << endl;


          cout << "\tcurr_val: " << curr_val << " -> " << it->second << endl;
          cout << "\tnext_val: " << next_val <<  " -> " << next(it)->second << endl;


          // double test = .62;

          // if(test < next_val) { // if pos is less than next map element
          //      cout << "x: " << curr_val << endl;
          //      cout << "xx: " <<  next_val << endl;
          //      return curr_val;
          // }
          // i++;
     }



     cout << "ERROR" << endl;
     return -1;
}

int main() {

	if (RHO < 0.5 || RHO >= 1) {
		cout << "ERROR: Non-redundant digit set" << endl;
		return 0;
	}

	double x = 0.66666666;
	double dd = 0.61;
	populate_table();
	cout << "Expected result: " << x / dd << endl;
	cout << "Computed result: " << divide(x, dd) << endl;
}