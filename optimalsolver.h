/**
    CS 509 Advanced C++ Programming - Project, optimalsolver.h
    Purpose: optimal linear solver [not complete].

    @author Yakup Gorur @ykpgrr
    @version 0.1 June 7, 2019
*/

#ifndef OPTIMALSOLVER_H
#define OPTIMALSOLVER_H

#include "greedysolver.h"

class OptimalSolver :  public GreedySolver
{
private:
    int cost; // Cost of the solver
    int in_solver_cost; // Cost of in solver cost.

public:


    /**
        Default constructor.

        @param Data, which includes courses and assistants
    */
    OptimalSolver(Data & _data): GreedySolver(_data), cost(0), in_solver_cost(0){}

    /**
        A optimal solving algorithms

        @param Null
        @return void
    */
    void Solver();
    int CalculateCost();

};

int OptimalSolver::CalculateCost(){

    // Iterate over assistances
    for ( auto& assistance : data.assistances_vec){
        // Assistant assigned to 2 courses at the same time -> 5 pts penalty
        if(assistance.get_assigned_course_number() == 2)
            this->cost  += 5;
        // Assistant assigned to 3 or more courses at the same time -> 20 pts penalty
        else if (assistance.get_assigned_course_number() >= 3)
            this->cost  += 20;

        // For each X h/week unassigned assistant time -> X pts bonus
        if(assistance.left_hours != 0)
            this->cost -= assistance.left_hours;
    }

    // Iterate over courses and assign assistant with greedily
    for ( auto& course : data.courses_vec) {

        // Course requirement not met -> 100 pts penalty
        if(course.get_TA_hours('b') > 0 || course.get_remaining_TA_number() > 0)
            this->cost += 100;
    }


    // Add the "In solver cost calculation" for speed.
    // Assistant with old course experience assigned to a new course -> 5 pts penalty per unexperienced course
    this->cost += this->in_solver_cost;

    return cost;
}

void OptimalSolver::Solver(){

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

                // In solver cost calculation for speed.
                // Assistant with old course experience assigned to a new course -> 5 pts penalty per unexperienced course
                if( ! assistance.IsGivenCourse(course.get_code()) )
                    this->in_solver_cost += 5;

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
                // In solver cost calculation for speed.
                // Assistant with old course experience assigned to a new course -> 5 pts penalty per unexperienced course
                if( ! assistance.IsGivenCourse(course.get_code()) )
                    this->in_solver_cost += 5;

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

#endif // OPTIMALSOLVER_H
