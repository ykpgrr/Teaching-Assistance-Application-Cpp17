/**
    CS 509 Advanced C++ Programming - Project, greedysolver.h
    Purpose: it's includes greedy algorithms to solve scheduing problem.

    @author Yakup Gorur @ykpgrr
    @version 0.1 June 7, 2019
*/


#ifndef GREEDYSOLVER_H
#define GREEDYSOLVER_H

#include <iostream>
#include "data.h"

class GreedySolver
{
protected:
    Data data;  // Keeps the "Assistant.csv" and "Courses.csv" as a vector
public:

    /**
        Default constructor.

        @param Data, which includes courses and assistants
    */
    GreedySolver(Data & _data) : data(_data){}

    /**
        A greedy solving algorithms

        @param Null
        @return void
    */
    void Solver();

    /**
        Checking possibility of solution corresponding to requsted assistance
        hours as min&max from courses from courses.csv

        @param Null
        @return char, solution type. Consider the requested max/min assistance
        hours. 'a' means: not possible solution. 'b' means: possible solution but
        with minumun requested assistance hour. 'c' means: possible solution.
    */
    char CheckPossibility();

    /**
        Print the finding solution.

        @param Null
        @return void
    */
    void PrintSolution();

    /**
        Write  the finding solution in csv file as "SOLUTION.csv"

        @param Null
        @return void
    */
    void WriteCsv(std::string folder_path);
};

char GreedySolver::CheckPossibility(){
    auto type = char();
    std::cout<<"***CheckPossibility***" << std::endl;

    if(Assistant::total_assistance_hour < Course::total_min_assist)
    {
        std::cout<<"It is not possible to find solution. Because There are not "
                   "enough assistances." << std::endl;
        std::cout<<"total available assistance hours: " << Assistant::total_assistance_hour << std::endl;
        std::cout<<"total minumum requested assistanship hours: " << Course::total_min_assist << std::endl;
        type = 'a';
    } else if (Assistant::total_assistance_hour < Course::total_max_assist)
    {
        std::cout<<"It is  possible to find solution. But It is not possible to "
                   "find solution with Maximum Requested AssistanceShip. "
                   "Because There are not enough assistances." << std::endl;
        std::cout<<"total available assistance hours: " << Assistant::total_assistance_hour << std::endl;
        std::cout<<"total minumum requested assistanship hours: " << Course::total_min_assist << std::endl;
        std::cout<<"total maximum requested assistanship hours: " << Course::total_max_assist << std::endl;
        type =  'b';
    } else {
        std::cout<<"It is  possible to find solution." << std::endl;
        std::cout<<"total available assistance hours: " << Assistant::total_assistance_hour << std::endl;
        std::cout<<"total maximum requested assistanship hours: " << Course::total_max_assist << std::endl;
        type =  'c';
    }
    std::cout<<"**********************" << std::endl;
    return type;
}

void GreedySolver::Solver(){

    auto solution_type = this->CheckPossibility(); // Check, Is there a solution

    // If solution type = a , There is not enough assistance hours
    if (solution_type == 'a') {
        return;
    }

    // Iterate over courses and assign assistant with greedily
    for ( auto& course : data.courses_vec) {

        // Iterate over assistances
        for ( auto& assistance : data.assistances_vec)
        {

            // If There is no Course remaining hours and
            // there is no reamaining TA number pass this course
            auto course_remaining_hour = int{};
            if(course.get_remaining_TA_number() <= 0 && course.get_TA_hours(solution_type) <= 0 )
                break;
            else if (course.get_remaining_TA_number() > 0 && course.get_TA_hours(solution_type) <= 0 ) {
                course_remaining_hour = 5;
            }
            else
                course_remaining_hour = course.get_TA_hours(solution_type);

            // Is there available number of serves for this assistance. If it's not, continue
            // Is there any remaining serve hours for this assistance. If it's not, continue.
            if(assistance.get_remain_course_num() <= 0 || assistance.left_hours < 5)
                continue;

            // Is Assistance hours bigger than Requested TA hours?
            if(course.get_TA_hours(solution_type) <= assistance.left_hours)
            {
                //assign the assistance on a new course
                course.assistance_hour_map.insert(std::pair<std::string, uint>(assistance.get_name(), course_remaining_hour ));
                assistance.left_hours -= course_remaining_hour;
                course.used_course_hours += course_remaining_hour;

                // increase the assigned course number for this assistance
                assistance.inc_assigned_course();

                // increase the assigned TA number for this assistance
                course.increase_TA_count();

                // this course has enough TA_hours. ! But it need to check that:
                // Is there enough TA number.

            } else // Is Requested TA hours bigger than assistance hours?
            {
                //assign the assistance on a new course
                course.assistance_hour_map.insert(std::pair<std::string, uint>(assistance.get_name(), assistance.left_hours ));

                course.used_course_hours += assistance.left_hours;
                assistance.left_hours = 0;

                // increase the assigned course number
                assistance.inc_assigned_course();

                // increase the assigned TA number for this assistance
                course.increase_TA_count();
                continue;
            }
        }   // End of the for. Iteration over assistances

    }   // End of the for. Iteration over courses
}

void GreedySolver::PrintSolution(){

    for( auto course : this->data.courses_vec){
        std::cout<< course.get_code();
        for ( auto assigned_ta : course.assistance_hour_map){
            std::cout<< ", "<< assigned_ta.first << ", " << assigned_ta.second;
        }
        std::cout<< std::endl;
    }

    for(auto assistant : this->data.assistances_vec){
        if (assistant.left_hours != 0) {
            std::cout<< assistant.get_name() << ", " << assistant.left_hours << std::endl;
            continue;
        }
    }
}

void GreedySolver::WriteCsv(std::string folder_path){

    std::ofstream csvfile;
    csvfile.open (folder_path + "SOLUTION.csv");

    for( auto course : this->data.courses_vec){
        csvfile<< course.get_code();
        for ( auto assigned_ta : course.assistance_hour_map){
            csvfile<< ", "<< assigned_ta.first << ", " << assigned_ta.second;
        }
        csvfile<< std::endl;
    }

    for( auto assistant : this->data.assistances_vec){
        if (assistant.left_hours != 0) {
            csvfile<< assistant.get_name() << ", " << assistant.left_hours << std::endl;
            continue;
        }
    }

}


#endif // GREEDYSOLVER_H
