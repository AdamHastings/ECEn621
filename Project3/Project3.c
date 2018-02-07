#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#define M_PI 3.14159265358979323846

int sign(double x) {
	if (x >= 0)
		return 1;
	else
		return -1;
}

void rotationMode() {

	FILE *sinFP, *cosFP, *tanFP;
	sinFP = fopen("sin.txt", "w+");
	cosFP = fopen("cos.txt", "w+");
	tanFP = fopen("tan.txt", "w+");

	fprintf(sinFP, "Value	 	 CORDIC	 	math.h		Difference\n");
	fprintf(sinFP, "----------------------------------------------------------\n");


	fprintf(cosFP, "Value	 	 CORDIC		math.h		Difference\n");
	fprintf(cosFP, "----------------------------------------------------------\n");


	fprintf(tanFP, "Value		 CORDIC		math.h		Difference\n");
	fprintf(tanFP, "----------------------------------------------------------\n");


	// double angles[5] = {0, 12.5, 67, 90, 92};
	// int length = sizeof(angles)/sizeof(angles[0]);
	for (double i=-98; i <= 98; i++) {

		double z = i * ((2 * M_PI)/360); // Convert to radians
		double x = 0.607252935;
		double y = 0;
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
			for (int iteration = 0; iteration < 100; iteration++) {
				double old_x = x;
				double old_y = y;
				double old_z = z;
				int sigma = sign(z);
				x = old_x - (sigma * pow(2, -1*iteration) * old_y);
				y = old_y + (sigma * pow(2, -1*iteration) * old_x);
				z = old_z - (sigma * atan(pow(2, -1*iteration)));
			}
		}
		fprintf(sinFP, "sin(%6.2f)    %10.6f     %10.6f      %11.8f\n",i, y, sin(i * (M_PI/180.0)), y-sin(i * (M_PI/180.0)));
		fprintf(cosFP, "cos(%6.2f)    %10.6f     %10.6f      %11.8f\n",i, x, cos(i * (M_PI/180.0)), x-cos(i * (M_PI/180.0)));
		if (i != 90 && i != -90)
			fprintf(tanFP, "tan(%6.2f)    %10.6f     %10.6f      %11.8f\n",i, y/x, tan(i * (M_PI/180.0)), y/x-tan(i * (M_PI/180.0)));
		
 	}

	fclose(sinFP);
	fclose(cosFP);
	fclose(tanFP);
}

void vectorMode() {
	// TODO
}


int main() {
	
	rotationMode();
	vectorMode();

	return 0;
}

