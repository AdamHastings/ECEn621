#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#define M_PI 3.14159265358979323846
#define M_PI_2_32bits 11001001000011111101101010100010

// Pi in fixed point: 11. 0010 0100 0011 1111 0111
// pi/2             :  1. 1001 0010 0001 1111 1011 0101 0100 0100

uint32_t WHOLE_BITS = 1;
uint32_t FRAC_BITS = 31;
uint32_t E = 0;

// prints bits, assumes little endian, works for all types
void printBits(size_t const size, void const * const ptr){
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;

    for (i=size-1;i>=0;i--){
        for (j=7;j>=0;j--){
            byte = (b[i] >> j) & 1;
            printf("%u", byte);
        }
    }
    puts("");
}

// int to fixed
uint32_t int_to_fixedpt(uint32_t x) {
      return x << FRAC_BITS;
}

// uint32_t float_to_fixed(double x){
//      double res = x*pow(2,31);
//      printf("scaled res: %f\n", res);

//      printBits(sizeof(res),&res);

//      res = floor(res);
//      // uint32_t res2 = (int) floor(res);
//      uint32_t res2 = (int) res;
//      printBits(sizeof(res2),&res2);

//      return (int) (res+.5);

//      // printf("pow: %f\n",pow(2,31));
//      // return 0;
// }

// fixed to float
double fixed_to_float(uint32_t x) {
     uint32_t whole_bits = (x >> FRAC_BITS);
     double fractional_bits = ((double) (((unsigned) x << WHOLE_BITS) >> WHOLE_BITS)) / (2 << (FRAC_BITS - 1));
     if(fractional_bits<=0) fractional_bits *= -1; // take care of case when shift too far
     double representation = (double) whole_bits + fractional_bits;
     return representation;
}

// alternate fixed to float
double fix_to_float(uint32_t x){
     double y = (float) x / (1<<FRAC_BITS);
     return y>0? y:y*-1; // get rid of negative if shift went to sign bit
}

// return the bit at this index
int getBit(int num, int index){
     return (num & ( 1 << index )) >> index;
}

// get the index of the most significant bit (LSB is index 0)
uint32_t get_MSB (uint32_t x) {
     if(x==0) return 0;
     uint32_t i;
     for(i=0; x!=0; i++) x = x >> 1;
     return i-1;
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

// normalize by shifting MS-1 to MSB [.5, 1]
uint32_t normalize(uint32_t x){
     E = 30 - get_MSB(x);      // shift value to normalize by
     printf("normalize shifted denominator by %d\n",E);
     return x << E;     // normalized value
}

// uint32_t renormalize(uint64_t x){


// }

void myPrint(uint32_t x){
     printf("%f ", fixed_to_float(x));
     printBits(sizeof(x), &x);
}

uint32_t computeDivision(uint32_t numerator, uint32_t denominator) {

     // numerator comes in in fixed point
     // denominator is an int [1,255]

     printf("\n");
     printf("divide: %f / %d\n", fixed_to_float(numerator), denominator);

     // denominator must be pre normalized
     denominator = normalize(denominator);
     printf("denominator: %f\n", fixed_to_float(denominator));
     printf("denominator: ");
     printBits(sizeof(denominator), &denominator);
     printf("\n");


     for (uint32_t k=0; k<5; k++) {
          printf("\niteration %d \n",k);

          uint32_t subtraction = 0 - denominator;
          printf("subtraction: ");
          myPrint(subtraction);

          // denominator = denominator * subtraction;

          uint64_t denominator_long = (uint64_t) denominator * subtraction;

          printf("denominator_long: ");
          printBits(sizeof(denominator_long), &denominator_long);
          denominator = (denominator_long+0x40000000) >> FRAC_BITS;

          // numerator = numerator * subtraction;

          uint64_t numerator_long = (uint64_t) numerator * subtraction;
          printf("numerator_long: ");
          printBits(sizeof(numerator_long), &numerator_long);
          printf("\n");


          numerator = (numerator_long+0x40000000) >> FRAC_BITS;

          printf("denominator: ");
          myPrint(denominator);

          printf("numerator:   ");
          myPrint(numerator);

     }

     // denominator -> 1
     // numerator -> Q  (N/D)

     printf("FINAL\n");

     printf("denominator: ");
     myPrint(denominator);

     printf("numerator:   ");
     myPrint(numerator);


     printf("e: %d\n",E);
     numerator = numerator >> -1*(E+1);   // denormalize



     printf("post normal num:   ");
     myPrint(numerator);



     return numerator;
}

int main() {
     WHOLE_BITS = 1;
     FRAC_BITS = 32-WHOLE_BITS;

     uint32_t d = 37;

     // printf("d:      %f\n", fixed_to_float(d));
     // printf("d:      ");
     // printBits(sizeof(d), &d);

     // uint32_t d_norm = normalize(d); // normalize d to [.5,1]
     // printf("e:      %d\n", E);
     // printf("d_norm: %f\n", fixed_to_float(d_norm));
     // printf("d_norm: ");
     // printBits(sizeof(d_norm), &d_norm);


     // if(fixed_to_float(d) != fix_to_float(d))
     //      printf("THEY DIDNT AGREE!\n");

     uint32_t n = 0b11001001000011111101101010100010;

     printf("n :");
     myPrint(n);


     uint32_t quotient = computeDivision(n, d);
     printf("\nQuotient: \n");
     myPrint(quotient);


     return 0;
}
