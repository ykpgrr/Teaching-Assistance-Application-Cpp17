/**
    CS 509 Advanced C++ Programming - Project, data.h
    Purpose: reads the assistants.csv and courses.csv. Keeps the corresponding
    type vector as assistances_vec, courses_vec.

    @author Yakup Gorur @ykpgrr
    @version 0.1 June 7, 2019
*/


#ifndef DATA_H
#define DATA_H

#include <iostream>
#include <vector>
// #include <filesystem>
#include "csvio.h"
#include "assistant.h"
#include "course.h"

class Data
{
private:
    std::string in_assistants_csv;  // Path "ASSISTANTS.csv"
    std::string in_courses_csv;     // Path "COURSES.csv"

    /**
        Read "ASSISTANTS.csv" and save in "assistances_vec"

        @param Null
        @return void
    */
    void ReadAssistances();

    /**
        Read "COURSES.csv" and save in "courses_vec"

        @param Null
        @return void
    */
    void ReadCourses();

public:

    std::vector<Assistant> assistances_vec; // Vector of assistances
    std::vector<Course> courses_vec;        // Vector of courses

    /**
        Default ctor.

        @param string;string, Path of the input files from assistances.csv and
        courses.csv
        @return void
    */
    Data(std::string _in_assistants_csv, std::string _in_courses_csv);

    /**
        Print the reading files data to check correctness.

        @param Null
        @return void
    */
    void Print();
};

Data::Data(std::string _in_assistants_csv, std::string _in_courses_csv):
    in_assistants_csv(_in_assistants_csv), in_courses_csv(_in_courses_csv){
    ReadCourses();
    ReadAssistances();
}

void Data::ReadAssistances(){
    auto file_assistances = std::ifstream{this->in_assistants_csv};
    auto row = CSVRow{};

    // Read row by row
    while(row.readNextRow(file_assistances))
    {
        auto name = std::string{};   //Assistance name
        auto hours2assist = uint{};   //Total Assistanceship service hours
        auto max_course = uint{};    //Maximum course number
        auto old_assisted_courses = std::list<std::string>{};

        // read columns
        for (auto i= std::size_t{0}; i<row.size(); ++i)
        {
            if (i==0)
                name = row[i];
            else if (i==1) {
                hours2assist = std::stoi(row[i]);
            }
            else if (i==2) {
                max_course = std::stoi(row[i]);
            }
            else {
                old_assisted_courses.push_back(row[i]);
            }
        }   // End of the for

        // Add assistance into vector
        this->assistances_vec.push_back(Assistant(name, hours2assist, max_course, old_assisted_courses));
    }   // End of the while
}

void Data::ReadCourses(){

    auto file_courses = std::ifstream{this->in_courses_csv};
    auto row = CSVRow{};

    // Read row by row //TODO: error check for missing data
    while(row.readNextRow(file_courses))
    {
        auto code = std::string{row[0]};   // Course Code
    auto instructor_name = std::string{row[1]}; // Instructor name
auto min_TA_hours = uint(std::stoi(row[2]));  // requested min Teaching assistance hours
auto max_TA_hours = uint(std::stoi(row[3]));  // requested max Teaching assistance hours
auto min_TA_count = uint(std::stoi(row[4]));  // requested min Teaching assistance count
//auto course_name = std::string{};     // In this project it's not necessary

// Add course into vector
this->courses_vec.push_back(Course(code, instructor_name,
                                   min_TA_hours, max_TA_hours,
                                   min_TA_count));
} // End of the While

}
void Data::Print(){
    std::cout<<"*****Printing Assistances*****"<< std::endl;
    for(auto& x : this->assistances_vec){
        x.Print();
    }
    std::cout<<std::endl;

    std::cout<<"*****Printing Courses*****"<< std::endl;
    for(auto x : this->courses_vec){
        x.Print();
    }


}



#endif // DATA_H
