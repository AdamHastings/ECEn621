#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define M_PI 3.14159265358979323846


double computeDelta_sine(double delta) {
	return delta - (delta*delta*delta)/6 +(delta*delta*delta*delta*delta) / 120;
}

double computeDelta_cosine(double delta) {
	return 1 - (delta*delta)/2 + (delta*delta*delta*delta)/24 - (delta*delta*delta*delta*delta*delta)/720;
}

double recurrence_sin(double sin) {
	return 
}

double recurrence_cos(double cos) {

}

double sine, cosine;

int main() {
  int N_array[1] = {20};

  for (int i=0; i < sizeof(N_array)/sizeof(N_array[0]); i++) {

	int N = N_array[i];
	printf("------ %d ------\n", N);
	int length = snprintf( NULL, 0, "%d", N );
	char* str = malloc( sizeof(char) * (length + 5) );
	snprintf( str, length + 1, "%d.txt", N );

	FILE *fp;
	fp = fopen(str, "w+");
	free(str);

	double delta = M_PI / (2 * N);
	double sin_theta = computeDelta_sine(delta);
	double cos_theta = computeDelta_cosine(delta);



	// TODO: N*4
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
			sine = recurrence_sin(sin_theta, 
		}
		printf("%f\n", sine);
		fprintf(fp, "%f\n", sine);
	}

	fclose(fp);
  }

  return 0;
}

