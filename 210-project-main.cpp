// COMSC210 | Lab 29, 30, 31 | Majd Bohsali
// IDE Used: Visual Studio Code
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <array>
#include <list>
#include <string>

using namespace  std; 

void simulateTimeStep(map<string, array<list<double>,3>>& trafficData);
void printAllData(map<string, array<list<double>,3>> trafficData);
const int NUM_SIMS = 48;
int main() {    
    map<string, array<list<double>,3>> trafficData; 
    ifstream inputFile("input.txt"); 
    string inputLine; 

    if(inputFile.is_open()) { 
        // collect data and push into map
        while (getline(inputFile, inputLine)) {
            string interName, carCount, carInflow, carOutflow; 
            stringstream ss(inputLine); 

            getline(ss, interName, ','); 
            getline(ss, carCount, ','); 
            getline(ss, carInflow, ','); 
            getline(ss, carOutflow, ','); 
            trafficData[interName][0].push_back(stod(carCount)); 
            trafficData[interName][1].push_back(stod(carInflow)); 
            trafficData[interName][2].push_back(stod(carOutflow)); 
        }
        inputFile.close();
    } else { 
        cout << "Unable to read data file";
    }

    // Output inital traffic state
    cout << "Inital Print: " << endl; 
    printAllData(trafficData); 

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
    for(auto& intersection: trafficData) {
        string name = intersection.first;  
        double numCars = intersection.second[0].back();
        double carInflow = intersection.second[1].back();
        double carOutflow = intersection.second[2].back();

        double 
    }
}

void printAllData(map<string, array<list<double>,3>> trafficData) { 
    for(auto& data: trafficData) { 
        cout << "Intersection: " << data.first << endl
             << "\tCars: " << data.second[0].back() << endl 
             << "\tInflow: " << data.second[1].back() << endl 
             << "\tOutflow: " << data.second[2].back() << endl << endl; 
    }
}