//----------------------------------------------------------------------------------------------------------------------
// Assignment 1 - OOP1 SS2021
//
// Item-class TODO
//
// Author: 12007661 - Killer Lorenz
//----------------------------------------------------------------------------------------------------------------------
//

//TODO 
// copy and deconstructor?
// commenting

#ifndef A1_ITEM_HPP
#define A1_ITEM_HPP

#include "Field.hpp"

#include <cstdio>

class Item : public Field
{
  private:

    char name_;
  
  public:

    //------------------------------------------------------------------------------------------------------------------
    /// Constructor
    /// TODO
    ///
    /// @param pos
    //
    Item(char name, Coordinates pos);

    int getName();

    bool isBlocked(); 
    void print(); 
};

#endif // A1_ITEM_HPP