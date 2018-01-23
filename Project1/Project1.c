#include <stdio.h>
#include <math.h>
#define M_PI 3.14159265358979323846


double computeSine(double delta) {
	return delta - (delta*delta*delta)/6 +(delta*delta*delta*delta*delta) / 120;
}


int main() {
  int N_array[1] = {20};

  for (int i=0; i < sizeof(N_array)/sizeof(N_array[0]); i++) {
	int N = N_array[i];
	// int length = snprintf( NULL, 0, "%d", N ) + 4;
	// char* str = malloc( length + 1 );
	snprintf( str, length + 1, "%d.txt", N );

	FILE *fp;
	fp = fopen(str, "w+");
	free(str);

	double delta = M_PI / (2 * N);

	double sine, cosine;

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
			sine += computeSine(delta*j);
		}
		printf("%0d\n", sine);
		fprintf(fp, "%d\n", sine);
	}

	fclose(fp);
  }

  return 0;
}

