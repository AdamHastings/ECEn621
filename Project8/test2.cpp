#include <iostream>
#include <map>
#include <math.h>
#include <stdio.h>
#include <iomanip>
using namespace std;

int main() {

     map<int, int> myMap;

     try{
          myMap.at(2);
     } catch(const std::out_of_range& ex) {
          cout << "doesn't exist from: \"" << ex.what() << "\" "<< endl;
     }


	for (auto it = myMap.begin(); it != myMap.end(); it++)
          cout << it->first << " -> " << it->second << endl;
}