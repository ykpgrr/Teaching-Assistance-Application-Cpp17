/**
    CS 509 Advanced C++ Programming - Project, Lecturer.h
    Purpose: Create Lecturer with name and given courses
    Comment: In this project creating class for lecturer is not necessary but
    it is created because of the probable usage area in the next years.

    @author Yakup Gorur @ykpgrr
    @version 0.1 June 7, 2019
*/

#ifndef LECTURER_H
#define LECTURER_H

#include <iostream>
#include <list>

struct Lecturer{
    std::string name;
    std::list<std::string> courses;
public:
    Lecturer(std::string _name= "unknown", std::string course= ""): name(_name){
        if (!course.empty()){
            courses.push_back(course);
        }
    }

    auto GetName(){ return name;}
};

#endif // LECTURER_H
