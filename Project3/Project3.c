#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>

int sign(double x) {
	if (x == 0)
		return 0;
	else if (x > 0)
		return 1;
	else
		return -1;
}

void rotationMode() {
	double angles[5] = {0, 12, 25.5, 90, 277.2};
	int length = sizeof(angles)/sizeof(angles[0]);
	for (int i=0; i < length; i++) {
		double z = angles[i];
		double x = 0.607252935;
		double y = 0;
		for (int iteration = 0; iteration < 24; iteration++) {
			double old_x = x;
			double old_y = y;
			double old_z = z;
			int sigma = sign(z);
			x = old_x - (sigma * pow(2, -1*iteration) * old_y);
			y = old_y + (sigma * pow(2, -1*iteration) * old_x);
			z = old_z - (sigma * atan(pow(2, -1*iteration)));
		}
		printf("sine(%f) = %f\n", angles[i], y);
		printf("cosine(%f) = %f\n", angles[i], x);
		printf("tangent(%f) = %f\n\n", angles[i], y/x);
 	}
}


int main() {
	
	rotationMode();
	// vectorMode();

     /*
     int N_array[3] = {20, 50, 100};

	// pi in 8.24 fixed-point notation
	uint32_t pi = 0b00000011001001000011111101110000;

	for (int i=0; i < 1; i++) {
		int N = N_array[i];
		int length = snprintf(NULL, 0, "%d", N );
		char* str = malloc( sizeof(char) * (length + 5));
		snprintf(str, length + 5, "%d.txt", N);

		FILE *fp;
		fp = fopen(str, "w+");
		free(str);

		// Commented out for project 2
		//double delta_new = fixedpt_to_float(computeDivision(pi, int_to_fixedpt(2*N)));
		int32_t delta_fxp = computeDivision(pi, int_to_fixedpt(2*N));
		double delta = M_PI / (2 * N);
		printf("delta: %f, delta_fxp: %f\n", delta, fixedpt_to_float(delta_fxp));
		double sin_theta = computeDelta_sine(delta);
		double cos_theta = computeDelta_cosine(delta);
		double sine = 1;
		double cosine = 0;

		fprintf(fp, "value		 ours	 lib		diff\n");
		fprintf(fp, "---------------------------------------------------------\n");

		for (int j=0; j < N*4; j++) {
			if (j == 0) {
				sine = 0;
				cosine = 1;
			} else if (j == N) {
				sine = 1;
				cosine = 0;
			} else if (j == 2*N) {
				sine = 0;
				cosine = -1;
			} else if (j == 3*N) {
				sine = -1;
				cosine = 0;
			} else {
				double old_sine = sine;
				sine = recurrence_sin(sin_theta, cos_theta, sine, cosine);
				cosine = recurrence_cos(sin_theta, cos_theta, old_sine, cosine);
			}
			double theta = j*delta;
			double theta_deg = theta*180/M_PI;
			fprintf(fp, "sin(%6.2f) %10.6f %10.6f %10.6f\n",theta_deg, sine, sin(theta), sine-sin(theta));
			fprintf(fp, "cos(%6.2f) %10.6f %10.6f %10.6f\n",theta_deg, cosine, cos(theta), cosine-cos(theta));
		}
		fclose(fp);
	}*/

	
	return 0;
}
