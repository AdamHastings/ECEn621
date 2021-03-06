#include <iostream>
#include <map>
#include <math.h>
#include <stdio.h>
#include <iomanip>
#include <time.h>       /* time */
#include <stdlib.h>     /* srand, rand */
using namespace std;

map<double, double> reciprocal_table;

double mapGet(double i){
     try{
          reciprocal_table.at(i);
     } catch(const std::out_of_range& ex) {
          cout << i << " doesn't exist in: \"" << ex.what() << "\" "<< endl;
     }
}

// return a random float in the specified range
double randf(double fMin, double fMax){
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

// return the key to the nearest map element that exists
double getClosest(double pos){
     if(reciprocal_table.size() < 1) return 0;                                            // if map is empty
     if(reciprocal_table.size() < 2) return reciprocal_table.begin()->first;              // if only one element in map, return it
     if(pos <= reciprocal_table.begin()->first) return reciprocal_table.begin()->first;   // if pos is less than all map elements, or equal to the first one, return the first one

     for (auto it = reciprocal_table.begin(); it != reciprocal_table.end(); it++) {
          auto it_next = next(it);                     // get iterator to next map element
          if(it_next == reciprocal_table.end()){       // if it is the last element in the map
               return it->first;
          } else {
               if(pos < it_next->first) {                             // if pos is less than next map element
                    // it is lower bound, it_next is upper bound
                    if(pos - it->first <= it_next->first - pos)      // if pos is closer to current element (it)
                         return it->first;
                    else                                             // pos is closer to next element (it_next)
                         return it_next->first;
               }
          }
     }
     return 0; // shouldn't ever get here, error condition
}


int main() {
     srand (time(NULL));
     for(double i=20; i<=50; i+=.5)
           reciprocal_table[i]=i;
     for(int i=0; i<20; i++){
          double my_rand = randf(0,70);
          cout << "getClosest(" << my_rand << "): " << getClosest(my_rand) << endl;
     }
}


