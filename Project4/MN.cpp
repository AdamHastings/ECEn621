// MN.cpp

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// turns on debugging, prints i, z[i], D[i] each iteration in mul_normalize
#define DEBUGX

// number of digits computed
#define N 40

int D[N]; // Digit array

double XMAX, XMIN;  // Limits on what can be normalized, computed at startup

// compute the sequence of digits D that normalize x --> 1.0L
// return 0 if residual diverges, 1 if it converges
int mul_normalize(double x, int D[N])
{
    // put your code here
}

// compute the range over which mul_normalize can converge
void minmax()
{
    double x;      // product
    int i;         // iteration counter
    double shift;  // 2^(-i)

    for (i=0, shift=1.0L, x=1.0L; i<N; i++)
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

int main(int argc, char* argv[])
{
    double x;
    int i;

    minmax();  // init XMIN and XMAX
    printf("XMIN = %f    XMAX = %f\n", XMIN, XMAX);

    x = 1.23456789L;
    mul_normalize(x, D);

    x = 1.987654321L;
    mul_normalize(x, D);

    // stop here until the above normalize works
    // test by uncommenting #define DEBUGX above and comparing results with Dr. Wilde
    // if it works, remove the next line, and comment out #define DEBUGX above
    return 0;

    // try to break the algorithm...
    // test random numbers until the cows come home
 
    srand(42554); // everyone choose their own seed to the random number generator, please

    for (;;)  // loop forever
    {
        x = (XMAX-XMIN)*((double)rand()/(double)RAND_MAX)+XMIN;
        if ( mul_normalize(x, D)==0 )
        {
            // should not ever happen, but if it does....
            printf("Diverge: x=%f *****************\n", x);
            return 1;
        }
        else printf("%f\n", x); // converges, just print number
    }

    return 0;
}