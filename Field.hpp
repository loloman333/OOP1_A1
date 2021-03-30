//----------------------------------------------------------------------------------------------------------------------
// Assignment 1 - OOP1 SS2021
//
// TODO
//
// Author: 12007661 - Killer Lorenz
//----------------------------------------------------------------------------------------------------------------------
//

//TODO 
// copy and deconstructor?
// commenting

#ifndef A1_FIELD_HPP
#define A1_FIELD_HPP

typedef struct _Coordinates_ 
{
  size_t row_;
  size_t column_;
} Coordinates;

class Field
{
  private:

    int field_id_;
    Coordinates position_;
    static field_id_counter = 0;
  
  public:

    //------------------------------------------------------------------------------------------------------------------
    /// Constructor
    /// TODO
    ///
    /// @param pos
    //
    Field(Coordinates pos);

    int getFieldId();
    Coordinates getPositon();

    virtual bool isBlocked() = 0; 
    virtual void print() = 0; 
}

#endif // A1_FIELD_HPP