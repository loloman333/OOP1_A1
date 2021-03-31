//----------------------------------------------------------------------------------------------------------------------
// Assignment 1 - OOP1 SS2021
//
// Road-class TODO
//
// Author: 12007661 - Killer Lorenz
//----------------------------------------------------------------------------------------------------------------------
//

//TODO 
// copy and deconstructor?
// commenting

#ifndef A1_Road_HPP
#define A1_Road_HPP

#include "Field.hpp"

#include <cstdio>

class Road : public Field
{
  private:

    bool blocked_;
    static int number_of_blocked_roads_;
  
  public:

    //------------------------------------------------------------------------------------------------------------------
    /// Constructor
    /// TODO
    ///
    /// @param pos
    //
    Road(bool blocked, Coordinates pos);

    ~Road() = default;

    static int getNumberOfBlockedRoads();

    bool isBlocked() override; 
    void print() override; 
};

#endif // A1_Road_HPP