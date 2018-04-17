#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#define M_PI 3.14159265358979323846
#define PI_TIMES_10exp10 31415926535
// Pi in fixed point: 11.00100100001111110111
// Pi in 8.24 fixed-point: 00000011 00100100 00111111 01110000


uint32_t int_to_fixedpt(uint32_t x) {
      return x << 24;
}

// 8.24 fixed-point representation
double fixedpt_to_float(uint32_t x) {
      uint32_t whole_bits = (x >> 24);
      double fractional_bits = ((double) (((unsigned) x << 8) >> 8)) / (2 << (24 - 1));
      double representation = (double) whole_bits + fractional_bits;
      return representation;
}

double fix_to_float(uint32_t x){  // convert 1.15 fixed point to float
     return (float)x / 0x8000;
}

// for(uint32_t try=0; try<50000000; try++){
//      if(fix_to_float(try) != (float)try/(2*2*2*2*2*2*2*2*2*2*2*2*2*2*2))
//        printf("error: 0x%x: %d, %f %f\n", try, try, (float)try/(2*2*2*2*2*2*2*2*2*2*2*2*2*2*2), fix_to_float(try));
// }

int getBit(int num, int index){
     return (num & ( 1 << index )) >> index;
}



// Get the index of the most significant bit
uint32_t get_MSB (uint32_t x) {
     if(x==0) return 0;
     uint32_t i;
     for(i=0; x!=0; i++) x = x >> 1;
     return i-1;
}

uint32_t computeDivision(uint32_t numerator, uint32_t denominator) {

     for(uint32_t i=0; i<100; i++){
          printf("b: %d\n",getBit(i,1));
          printf("i=%d, msb=%d\n",i,get_MSB(i));
     }


     // printf("numerator: %x\n", numerator);
     // printf("denominator: %x\n",  denominator);

     // printf("numerator: %f\n", fixedpt_to_float(numerator));
     // printf("denominator: %f\n",  fixedpt_to_float(denominator));

     // First normalize denominator to between 0.5 and 1
     uint32_t msb = get_MSB(denominator);
     uint32_t shift = (msb - 24);

     // uint32_t d_norm = denominator;
     uint32_t d_norm = denominator >> shift;

     printf("Denominator: %f, MSB: %d, shift: %d, Result: %f\n", fixedpt_to_float(denominator), msb, shift, fixedpt_to_float(d_norm));
     // int d_norm = denominator;

     uint32_t iterations = 5;
     for (uint32_t i=0; i<iterations; i++) {
          // First normalize denominator to between 0.5 and 1
          // int msb = get_MSB(d_norm);
          // int shift = (msb - 24);

          // uint32_t d_norm = d_norm >> shift;
          // printf("Denominator: %f, MSB: %d, shift: %d, Result: %f\n", fixedpt_to_float(denominator), msb, shift, fixedpt_to_float(d_norm));
          printf("numerator: %f\n", fixedpt_to_float(numerator));
          printf("denominator: %f\n",  fixedpt_to_float(d_norm));

          uint32_t subtraction = int_to_fixedpt(2) - d_norm;
          printf("subtraction: %f\n\n", fixedpt_to_float(subtraction));

          numerator = numerator * subtraction;
          d_norm = d_norm * subtraction;


          //numerator = numerator >> shift;
     }
     printf("numerator: %f\n", fixedpt_to_float(numerator));
     printf("denominator: %f\n",  fixedpt_to_float(denominator));

     uint32_t Q = numerator >> shift; // shift;
     return Q;
}


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




// Let's pick an arbitrary 8.24 fixed-point numbering system.
// Also, we can convert to float for printing!
int main() {

     uint32_t quotient = computeDivision(int_to_fixedpt(2), int_to_fixedpt(4));
     printf("Quotient: %f\n", fixedpt_to_float(quotient));

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

          fprintf(fp, "value        ours      lib      diff\n");
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
