// COMSC210 | LAb 29, 30, 31 | Majd Bohsali
// IDE Used: Visual Studio Code
#include <iostream>
#include <fstream>
#include <map>
#include <array>
#include <list>
#include <string>

using namespace  std; 

const int NUM_SIMS = 48;
int main() {    
    map<string, array<list<double>,3>> trafficData; 

    ifstream inputFile("input.txt"); 

    if(inputFile.is_open()) { 
        // collect data
        inputFile.close();
    } else { 
        cout << "Unable to read data file";
    }

    for(int i = 0; i < NUM_SIMS; i++) { // runs for NUM_SIMS times

    }

    return 0;
}