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
void printData(map<string, array<list<double>,3>> trafficData);
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

    // temporary dummy data
    trafficData["Intersection1"][0].push_back(35); 
    trafficData["Intersection1"][1].push_back(5); 
    trafficData["Intersection1"][2].push_back(1); 

    // Output inital traffic state
    cout << "Inital Print: " << endl; 
    printData(trafficData); 

    cout << "Running Simulations..." << endl;
    for(int i = 0; i < NUM_SIMS; i++) { // runs for NUM_SIMS times
        simulateTimeStep(trafficData); // runs a simulation
        // Output current traffic states
    }

    return 0;
}

void simulateTimeStep(map<string, array<list<double>,3>>& trafficData) {
    // For each intersection in the map
        // Get the most recent rates and values from the lists
        // Check for any possible accidents (will be low % rate)
        // Calculate new traffic from the inflow and outflow values
        // Modify inflow and outflow rates if necessary
        // Push new values to each list in the map
    printData(trafficData); 
}

void printData(map<string, array<list<double>,3>> trafficData) { 
    for(auto& data: trafficData) { 
        cout << "Intersection: " << data.first << endl
             << "\tCars: " << data.second[0].back() << endl 
             << "\tInflow: " << data.second[1].back() << endl 
             << "\tOutflow: " << data.second[2].back() << endl << endl; 
    }
}