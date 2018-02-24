// MN.cpp

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

// turns on debugging, prints i, z[i], D[i] each iteration in mul_normalize
#define DEBUGX
#ifdef DEBUGX
#  define DEBUG_PRINT(i, z, d, y) (printf("%i\t%8f\t%0d\t%0.17f\n", i, z, d, y))
#else
#  define DEBUG_PRINT(i, z, d, y) ((void)0)
#endif

// number of digits computed
#define N 40

int D[N], L[N], U[N]; // Digit array

double XMAX, XMIN;  // Limits on what can be normalized, computed at startup
double YMAX, YMIN;
// YMIN = -1.56202383321486216
// YMAX = 

double ZMAX = 2;
double ZMIN = -2;

// Select next digit in digit recurrence
int getNextDigit(double z, int i) {
    // double upper = U[i];
    // double lower = L[i];
    // double range = upper - lower;


    if (z > 0.5)
        return 1;
    else if (z > -0.5)
        return 0;
    else if (i == 0)
        return 0;
    else
        return -1;
}

// // Compute Bounds (I don't think this is necessary)
// void computeUandL() {
//     L[N-1] = ZMIN;
//     U[N-1] = ZMAX;

//     for (int i=N-2; i>=0; i--) {
//         L[i] = ((L[i+1]/2) - 1)/ (1 - pow(2, -i));
//         U[i] = ((U[i+1]/2) + 1)/ (1 + pow(2, -i));
//     }
// }



// compute the sequence of digits D that normalize x --> 1.0L
// return 0 if residual diverges, 1 if it converges
int mul_normalize(double x, int D[N])
{

    double x_k = x;
    // double old_x_k;
    double z_k = 2*(1.0 - x);
    double y_k = 0;
    D[0] = getNextDigit(z_k, 0);
    // D[0] = -1;
    DEBUG_PRINT(0, z_k, D[0], y_k);

    for (int i=1; i < N; i++) {

        // Find next x (not even sure this is necessary)
        // x_k = x_k * (1 + pow(2.0, -i) * D[i-1]);
        // old_x_k = x_k;
        x_k = x_k * (1 + D[i-1] * pow(2, -(i-1)));
        
        // Find next y_k
        y_k = y_k - log(1 + D[i-1] * pow(2, -(i-1)));

        // Find next z_k
        // z_k = 2 * (z_k * (1 + pow(2.0, -(i-1)) * D[i-1]) - D[i-1]);
        z_k = pow(2, i-1) * (1 - x_k);
        
        // Select next d
        D[i] = getNextDigit(z_k, i);
        // D[i] = -1;
        
        // Print if debugging
        DEBUG_PRINT(i, z_k, D[i], y_k);
    }
    if (z_k > ZMIN && z_k < ZMAX)
        return 1;
    else
        return 0;

}


// compute the range over which mul_normalize can converge
void minmax()
{
    double x;      // product
    int i;         // iteration counter
    double shift;  // 2^(-i)

    for (i=1, shift=0.5L, x=1.0L; i<N; i++)
    {
        x = x * (1.0L + shift); // x = 1.11111111... (by multiplicative rule of interpretation)
        shift = shift/2.0L;
    }
    XMIN = 1.0L/x;

    for (i=1, shift=0.5L, x=1.0L; i<N; i++)
    {
        x = x * (1.0L - shift); // x = 0.nnnnnnnn... where n=(-1) (this is a positive number!)
        shift = shift/2.0L;
    }
    XMAX = 1.0L/x;
}

// void minmax () {
    
//     double L_k = -2;
//     double U_k =  2;

//     for (int i=N; i>0; i--) {

//         if (i != 1)
//             L_k = ((L_k)/2 - 1)/(1 - pow(2, -(i-1)));
//         U_k = ((U_k)/2 + 1)/(1 + pow(2, -(i-1)));

//     }

//     XMAX = U_k;
//     XMIN = L_k;

// }

int main(int argc, char* argv[])
{
    // double x;
//     computeUandL();


    minmax();  // init XMIN and XMAX
    printf("XMIN = %f    XMAX = %f\n\n", XMIN, XMAX);

    double x = 1.23456789L;
    printf("Results for x = %0.10f\n\n", x);
    printf(" i        z[i]          D[i]    Y[i+1]\n");
    printf("---     ---------       ----    ------\n");
    mul_normalize(x, D);


    // x = 1.987654321L;
    // mul_normalize(x, D);

    // stop here until the above normalize works
    // test by uncommenting #define DEBUGX above and comparing results with Dr. Wilde
    // if it works, remove the next line, and comment out #define DEBUGX above
    // return 0;

    // try to break the algorithm...
    // test random numbers until the cows come home

//     srand(45893); // everyone choose their own seed to the random number generator, please

//     for (;;)  // loop forever
//     {
//         x = (XMAX-XMIN)*((double)rand()/(double)RAND_MAX)+XMIN;
//         if ( mul_normalize(x, D)==0 )
//         {
//             // should not ever happen, but if it does....
//             printf("Diverge: x=%f *****************\n", x);
//             return 1;
//         }
//         else printf("%f\n", x); // converges, just print number
//     }

    // return 0;
}