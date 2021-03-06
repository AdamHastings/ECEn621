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

double recurrence_sin(double sin_theta, double cos_theta, double sine, double cosine) {
     return sine*cos_theta + cosine*sin_theta;
}

double recurrence_cos(double sin_theta, double cos_theta, double sine, double cosine) {
     return cosine*cos_theta - sine*sin_theta;
}

int main() {
     int N_array[3] = {20, 50, 100};
     for (int i=0; i < sizeof(N_array)/sizeof(N_array[0]); i++) {
          int N = N_array[i];
          int length = snprintf(NULL, 0, "%d", N );
          char* str = malloc( sizeof(char) * (length + 5));
          snprintf(str, length + 5, "%d.txt", N);

          FILE *fp;
          fp = fopen(str, "w+");
          free(str);

          double delta = M_PI / (2 * N);
          double sin_theta = computeDelta_sine(delta);
          double cos_theta = computeDelta_cosine(delta);
          double sine = 1;
          double cosine = 0;

          fprintf(fp, "value         ours       lib        diff\n");
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
     }
     return 0;
}

