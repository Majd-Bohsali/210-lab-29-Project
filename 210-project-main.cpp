// COMSC210 | Lab 29, 30, 31 | Majd Bohsali
// IDE Used: Visual Studio Code
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <array>
#include <list>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace  std; 

void simulateTimeStep(map<string, array<list<double>,3>>& trafficData, int hour);
void printAllData(map<string, array<list<double>,3>> trafficData);
void printData(map<string, array<list<double>,3>> trafficData);
const int NUM_SIMS = 48, CARS_PER_GREEN_SEC = 10; // CARS_PER_GREEN_SEC = number of cars that leave per second of light being green
int main() {  
    srand(time(0));  
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

    cout << "Running Simulations..." << endl;
    for(int i = 0; i < NUM_SIMS; i++) { // runs for NUM_SIMS times
        simulateTimeStep(trafficData, i); // runs a simulation
    }

    printData(trafficData); 

    return 0;
}

void simulateTimeStep(map<string, array<list<double>,3>>& trafficData, int hour) {
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

        // checks if there is an accident 
        double chance = rand() % 100 + 1; 
        if(chance <= 2) { 
            carOutflow *= 0.5; 
        } else {
            carOutflow = intersection.second[2].front(); // takes original value after accident clears
        }

        double carLeave = carOutflow * CARS_PER_GREEN_SEC; 
        double newCars = (int)(max(numCars + carInflow - carLeave, 0.0)); // count cant become negative

        // updates values 
        intersection.second[0].push_back(newCars);
        intersection.second[1].push_back(carInflow);
        intersection.second[2].push_back(carOutflow);
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

void printData(map<string, array<list<double>,3>> trafficData) { 
    string selection;
    do {
    cout << "What Intersection do you want to check (type end to quit): "; 
    cin >> selection; 
    cout << "Intersection Selected: " << selection << endl
         << "\tCurrent Number of cars: " << trafficData[selection][0].back() << endl 
         << "\tCar Inflow: " << trafficData[selection][1].back() << endl 
         << "\tCar Outflow: " << trafficData[selection][2].back() << endl; 
    } while (selection != "end"); 
}