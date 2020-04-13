/* Yakup Görür S017327 Department of Computer Science */
/**
 CS 509 Advanced C++ Programming - Project, main.cpp
 Purpose: command usage of framework
 framework: create a “teaching assistant scheduling framework"
 
 @author Yakup Gorur @ykpgrr
 @version 0.1 June 7, 2019
 */

#include <iostream>
//#include <filesystem> // It's not supportted by Mac OS!
#include "data.h"
#include "greedysolver.h"
#include "optimalsolver.h"

using namespace std;

// It's not supportted by Mac OS!
//auto INPUT_CSV_FOLDER = string (std::filesystem::current_path());
auto INPUT_CSV_FOLDER = string ("/Users/yakupgorur/SoftwareDeveloper/myGithub/Teaching-Assistance-Application-Cpp17"); // Enter PATH
auto INPUT_ASSISTANT  = INPUT_CSV_FOLDER + "/ASSISTANTS.csv";
auto INPUT_COURSES  = INPUT_CSV_FOLDER + "/COURSES.csv";

// Static variable of classes. To calculate how many object was created.
uint Assistant::total_assistance_hour = 0;
uint Course::total_max_assist = 0;
uint Course::total_min_assist = 0;

// Controls operation of the program.
int main(){
    
    cout<< "Please enter correct 'folder' path of 'ASSISTANT.csv' and "
           "'COURSES.csv' on line 21 ('INPUT_CSV_FOLDER')" <<endl <<
           "'std::filesystem' is not working on Mac OS (CLANG)" << endl;

    auto test_data = Data{INPUT_ASSISTANT, INPUT_COURSES};
    test_data.Print();

    cout<<endl<<endl<<"******Starting GreedySolver***"<<endl<<endl;
    auto my_greedy = GreedySolver{test_data};
    my_greedy.Solver();
    my_greedy.PrintSolution();
    my_greedy.WriteCsv(INPUT_CSV_FOLDER + "/");
    cout<<endl<<endl<<"******End of the GreedySolver***"<<endl<<endl;

    cout<<endl<<endl<<"***** Starting OptimalSolver***"<<endl<<endl;
    auto my_optimal = OptimalSolver{test_data};
    my_optimal.Solver();
    my_optimal.PrintSolution();
    my_optimal.WriteCsv(INPUT_CSV_FOLDER + "/" + "OPTIMAL_");
    cout<< endl << "Calculated Cost of the optimal Solution: "<<my_optimal.CalculateCost();
    cout<<endl<<endl<<"*****End of the OptimalSolver***"<<endl<<endl;
}


