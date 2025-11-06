// COMSC210 | Lab 29, 30, 31 | Majd Bohsali
// IDE Used: Visual Studio Code
#include <iostream>
#include <fstream>
#include <map>
#include <array>
#include <list>
#include <string>

using namespace  std; 

void simulateTimeStep(map<string, array<list<double>,3>>& trafficData);
const int NUM_SIMS = 48;
int main() {    
    map<string, array<list<double>,3>> trafficData; 

    ifstream inputFile("input.txt"); 

    if(inputFile.is_open()) { 
        // collect data and push into map
        inputFile.close();
    } else { 
        cout << "Unable to read data file";
    }

    // Output inital traffic state

    for(int i = 0; i < NUM_SIMS; i++) { // runs for NUM_SIMS times
        // call simulateTimeStep(trafficData)
        // Output current traffic states
    }
    // Output results in a formated output

    return 0;
}

void simulateTimeStep(map<string, array<list<double>,3>>& trafficData) {
    // For each intersection in the map
        // Get the most recent rates and values from the lists
        // Check for any possible accidents (will be low % rate)
        // Calculate new traffic from the inflow and outflow values
        // Modify inflow and outflow rates if necessary
        // Push new values to each list in the map
}