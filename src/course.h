/**
    CS 509 Advanced C++ Programming - Project, courses.h
    Purpose: keeping a course information from courses.csv

    @author Yakup Gorur @ykpgrr
    @version 0.1 June 7, 2019
*/

#ifndef COURSE_H
#define COURSE_H

#include <iostream>
#include <list>
#include <map>
#include "lecturer.h"
#include "assistant.h"


class Course
{

private:
    std::string code;   // Course Code
    //std::string name;     // In this project it's not necessary
    std::list<Lecturer> instructor_list;
    int min_TA_hours;
    int max_TA_hours;
    int min_TA_number;

    int TA_count;

public:

    int used_course_hours; // hours of given assistanceship duty
    std::map<std::string, uint> assistance_hour_map;

    static uint total_min_assist;   // to keep total hours of min assistanceship
    static uint total_max_assist;   // to keep total hours of max assistanceship


    /**
        Default ctor.

        @param string;string;uint;uint;uint, "Course Code", "Instruction name",
        "Minumum required TA hours", "Maximum required TA hours", "minumum TA
        count"
    */
    Course(std::string _code, std::string _instructor_name,
           int _min_TA_hours, int _max_TA_hours, int _min_TA_count);

    /**
        Print information about course

        @param
        @return void
    */
    void Print();

    // Getter for code
    auto get_code() { return code; }

    // Getter for min_TA_count
    auto get_min_TA_count() { return min_TA_number; }

    // Getter for min_TA_hours - used_course_hours
    auto get_left_min_requested_TA_hours() { return min_TA_hours - used_course_hours; }

    // Getter for max_TA_hours - used_course_hours
    auto get_left_max_requested_TA_hours() { return max_TA_hours - used_course_hours; }

    /**
        Get left requested TA hours corresponding to solution type which is
        selecting as with maximum TA Hours or with minumum TA Hours

        @param char, solution type can be 'a', 'b', 'c'.
        a' means: not possible solution. 'b' means: possible solution but
        with minumun requested assistance hour. 'c' means: possible solution.
        @return void
    */
    auto inline get_TA_hours(char solution_type){
        if (solution_type=='c')
            return get_left_max_requested_TA_hours();
        else
            return get_left_min_requested_TA_hours();
    }

    // Getter for remainin TA number to reach min TA number
    auto inline get_remaining_TA_number(){return ( this->min_TA_number) -  (this->TA_count);}

    // Increase assigned TA
    void inline increase_TA_count(){ ++(this->TA_count); }

};

Course::Course(std::string _code, std::string _instructor_name= "unknown",
               int _min_TA_hours= 0, int _max_TA_hours=0, int _min_TA_number=0):
    code(_code), min_TA_hours(_min_TA_hours),
    max_TA_hours(_max_TA_hours), min_TA_number(_min_TA_number)
{
    TA_count = 0; // / initialize the "TA_count" as zero
    used_course_hours = 0; // initialize the "used_course_hours" as zero

    // add instructor name into instructor list corresponding to Course Code
    instructor_list.push_back( Lecturer{_instructor_name, _code} );
    // Increase the total assistanceship hours  when every object created
    total_min_assist += _min_TA_hours;
    total_max_assist += _max_TA_hours;
}

void Course::Print(){

    std::cout<< code << " "
             << instructor_list.front().GetName() << " "
             << min_TA_hours << " " << max_TA_hours << " " << min_TA_number << " "
             << std::endl;
}

#endif // COURSE_H
