#include <stdio.h>

int main() {
  int N_array[3] = {20, 50, 100};

  for (int i=0; i < sizeof(N_array)/sizeof(N_array[0]); i++) {
	int N = N_array[i];
	int length = snprintf( NULL, 0, "%d", N ) + 4;
	char* str = malloc( length + 1 );
	snprintf( str, length + 1, "%d.txt", N );

	FILE *fp;
	fp = fopen(str, "w+");
	fprintf(fp, "%d\n", N);
	fclose(fp);
	free(str);
  }

  return 0;
}

