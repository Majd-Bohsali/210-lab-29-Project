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
#include <iomanip>

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
    cout << "Completed Running Simulations..." << endl;

    cout << endl << "Print real program data" << endl; 
    printData(trafficData); 

    return 0;
}

void simulateTimeStep(map<string, array<list<double>,3>>& trafficData, int hour) {
    hour %= 24;
    // Defines values needed for rush peaks and efficencey
    double rush1 = 5, rush2 = 17, out_min = 0.45, out_max = 1.8, in_min = 0.9, in_max = 1.1, PI = acos(-1); 
    
    for(auto& intersection: trafficData) {
        string name = intersection.first;  
        double numCars = intersection.second[0].back();
        double baseCarInflow = intersection.second[1].front();
        double baseCarOutflow = intersection.second[2].front();

        double inflowMult = ((in_max - in_min)/2) * (pow((cos((hour - rush1) * (2 * PI / (rush2 - rush1)))), 3 ) + 1.0) + in_min; 
        double outflowMult = ((out_max - out_min) / 2.0) * (pow((cos((hour - rush1) * (2 * PI / (rush2 - rush1)))), 3) + 1.0) + out_min;

        double carInflow = baseCarInflow * inflowMult; 
        double carOutflow = baseCarOutflow * outflowMult; 
        carOutflow = max(0.1, min(1.0, carOutflow)); 

        // checks if there is an accident 
        double chance = rand() % 100 + 1; 
        if(chance <= 2) { 
            carOutflow *= 0.5; 
        }
        carOutflow = max(0.1, min(1.0, carOutflow)); 

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
    cout << "What Intersection do you want to check (type end to quit): "; 
    cin >> selection; 

    while (selection != "end") {

        auto it = trafficData.find(selection); 

        if(it == trafficData.end()) { 
            cout << "Selection does not exist." << endl; 
        } else {
            cout << "Intersection Selected: " << selection << endl;
            cout << "  Number of Cars History: ";
                for (double val : trafficData[selection][0])
                    cout << val << ", ";
                cout << endl << endl;
            cout << "  Inflow History: ";
                for (double val : trafficData[selection][1])
                    cout << setprecision(3) << val << ", ";
                cout << endl << endl;
            cout << "  Outflow History: ";
                for (double val : trafficData[selection][2])
                    cout << setprecision(3) << val << ", ";
                cout << endl << endl;
        }   
        cout << "What Intersection do you want to check (type end to quit): "; 
        cin >> selection;  
    }
}