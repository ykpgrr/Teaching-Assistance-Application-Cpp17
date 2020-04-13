/**
    CS 509 Advanced C++ Programming - Project, assistant.h
    Purpose: keeping an assistant information from asistants.csv

    @author Yakup Gorur @ykpgrr
    @version 0.1 June 7, 2019
*/

#ifndef ASSISTANT_H
#define ASSISTANT_H

#include <iostream>
#include <list>

class Assistant
{
private:
    std::string name;   // Assistance name
    int hours2assist;   // Total Assistanceship service hours
    int max_course;    // Maximum course count
    std::list<std::string> old_assisted_courses;

    int assigned_course;    // hours of given assistanceship duty

public:
    int left_hours;    // hours of given assistanceship duty
    static uint total_assistance_hour;

    /**
        Default ctor.

        @param string;int;int;std::list<std::string>; "name", "hours2assist",
        "max_course", "old_assisted_courses"
    */
    Assistant(std::string _name, int _hours2assist,
              int _max_course, std::list<std::string> _old_assisted_courses);

    // Getter for name
    auto get_name() { return name;}

    // Getter for assigned_course
    auto get_assigned_course_number() { return assigned_course;}

    // Getter for hours2assist
    auto get_hours2assist() { return hours2assist; }

    // Getter for remain course number
    auto get_remain_course_num() { return max_course - assigned_course; }

    void inc_assigned_course()  { ++this->assigned_course; }

    // Print information of Assistant
    void Print();

    /**
        Searching the input whether is it given course before or not. If it's
        given it will return True. If it's not False.

        @param std::string, searched course_name
        @return bool
    */
    bool IsGivenCourse(std::string course_name);
};


Assistant::Assistant(
        std::string _name, int _hours2assist = 20, int _max_course = 3,
        std::list<std::string> _old_assisted_courses = std::list<std::string>{}
        )
    : name(_name), hours2assist(_hours2assist), max_course(_max_course),
      old_assisted_courses(_old_assisted_courses)
{
    left_hours = hours2assist; // initialize the "used_hours" as zero
    // Increase the total assistanceship hours when every object created
    total_assistance_hour += _hours2assist;
};

// Print information of Assistant
void Assistant::Print()
{
    std::cout<< this->name << " " << this->hours2assist << " " << this->max_course;

    for(auto x : old_assisted_courses)
    {
        std::cout<< x << " ";
    }
    std::cout<< std::endl;
}

bool Assistant::IsGivenCourse(std::string course_name){

    // Find the iterator if element in list
    auto it = std::find(old_assisted_courses.begin(), old_assisted_courses.end(), course_name);

    // return if iterator points to end or not. It points to end then it means element
    // does not exists in list. If given before it will return True
    return it != old_assisted_courses.end();
}

#endif // ASSISTANT_H
