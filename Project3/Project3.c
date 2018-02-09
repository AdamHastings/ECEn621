#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#define M_PI 3.14159265358979323846

// Get the sign of a double
int sign(double x) {
	if (x >= 0)
		return 1;
	else
		return -1;
}

// Run the rotation mode CORDIC algorithm
void rotationMode() {

	// Create file pointers and open files
	FILE *sinFP, *cosFP, *tanFP;
	sinFP = fopen("sin.txt", "w+");
	cosFP = fopen("cos.txt", "w+");
	tanFP = fopen("tan.txt", "w+");

	// Write headers
	fprintf(sinFP, "Value	 	 CORDIC	 	math.h		Difference\n");
	fprintf(sinFP, "----------------------------------------------------------\n");
	fprintf(cosFP, "Value	 	 CORDIC		math.h		Difference\n");
	fprintf(cosFP, "----------------------------------------------------------\n");
	fprintf(tanFP, "Value		 CORDIC		math.h		Difference\n");
	fprintf(tanFP, "----------------------------------------------------------\n");

	// Test angles in the range [-98, 98]
	for (double i=-98; i <= 98; i++) {

		double z = i * ((2 * M_PI)/360); // Convert to radians
		double x = 0.607252935; // 1/K
		double y = 0;

		// Hard code values that don't need to be approximated
		if (i == -90) {
			x = 0;
			y = -1;
		} else if (i == 0) {
			x = 1;
			y = 0;
		} else if (i == 90) {
			x = 0;
			y = 1;
		} else {
			// Run CORDIC algorithms
			for (int iteration = 0; iteration < 100; iteration++) {
				// Save old values
				double old_x = x;
				double old_y = y;
				double old_z = z;

				// Get next iteration
				int sigma = sign(z);
				x = old_x - (sigma * pow(2, -1*iteration) * old_y);
				y = old_y + (sigma * pow(2, -1*iteration) * old_x);
				z = old_z - (sigma * atan(pow(2, -1*iteration)));
			}
		}

		// Write to file
		fprintf(sinFP, "sin(%6.2f)    %10.6f     %10.6f      %11.8f\n",i, y, sin(i * (M_PI/180.0)), y-sin(i * (M_PI/180.0)));
		fprintf(cosFP, "cos(%6.2f)    %10.6f     %10.6f      %11.8f\n",i, x, cos(i * (M_PI/180.0)), x-cos(i * (M_PI/180.0)));
		if (i != 90 && i != -90) // Tan(+/-90) is undefined
			fprintf(tanFP, "tan(%6.2f)    %10.6f     %10.6f      %11.8f\n",i, y/x, tan(i * (M_PI/180.0)), y/x-tan(i * (M_PI/180.0)));

 	}

 	// Close the files
	fclose(sinFP);
	fclose(cosFP);
	fclose(tanFP);
}

// Run the vector mode CORDIC algorithm
void vectorMode() {

	// Create file pointer and open file
	FILE *arctanFP;
	arctanFP = fopen("arctan.txt", "w+");

	// Write header
	fprintf(arctanFP, "Value	 	 CORDIC	 	math.h		Difference\n");
	fprintf(arctanFP, "----------------------------------------------------------\n");

	// Test angles in the range [-98, 98]
	for (double i=-98; i <= 98; i++) {

		double z = 0;
		double x = 1;
		double y = i * ((2 * M_PI)/360); // Convert to radians

		// Hard code values that don't need to be approximated
		if (i == -90) {
			x = 0;
			y = -1;
		} else if (i == 0) {
			x = 1;
			y = 0;
		} else if (i == 90) {
			x = 0;
			y = 1;
		} else {
			// Run CORDIC algorithms
			for (int iteration = 0; iteration < 100; iteration++) {
				// Save old values
				double old_x = x;
				double old_y = y;
				double old_z = z;

				// Get next iteration
				int sigma = -1*sign(y);
				x = old_x - (sigma * pow(2, -1*iteration) * old_y);
				y = old_y + (sigma * pow(2, -1*iteration) * old_x);
				z = old_z - (sigma * atan(pow(2, -1*iteration)));
			}
		}

		// Write to file
		double arctan_mathlib = atan(i * (M_PI/180.0));
          fprintf(arctanFP, "arctan(%6.2f)    %10.6f     %10.6f      %11.8f\n",i, z, arctan_mathlib, z-arctan_mathlib);

          // do something about 90 and -90
 	}

 	// Close the file
	fclose(arctanFP);
}


int main() {

	rotationMode();
	vectorMode();

	return 0;
}

