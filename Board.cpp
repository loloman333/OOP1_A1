//----------------------------------------------------------------------------------------------------------------------
// Assignment 1 - OOP1 SS2021
//
// Board-class represents the Board where roads and items are placed on.
//
// Author: Tutors
//----------------------------------------------------------------------------------------------------------------------
//

#include "Board.hpp"
#include "Field.hpp"
#include "Road.hpp"
#include "Item.hpp"
#include <cstdio>
/*
 * TODO begin: If you need any additional includes you can add them here.
 */

// TODO end

//----------------------------------------------------------------------------------------------------------------------
Board::Board(size_t height, size_t width, size_t nr_items, char** fields):
  height_(height),
  width_(width),
  number_items_(nr_items),
  board_(0),
  items_(0)
{
  initializeFields(fields);
}

//----------------------------------------------------------------------------------------------------------------------
Board::~Board()
{
  deleteFields();
}

//----------------------------------------------------------------------------------------------------------------------
void Board::initializeFields(char** fields)
{
  /* 
   * TODO begin: 
   * - iterate over the 2D-array fields
   * - create "Road" and "Item" objects on the heap and store them in the board_ std::vector
   * - add items to the items_ std::vector
   */

  // TODO end
}

//----------------------------------------------------------------------------------------------------------------------
void Board::deleteFields(void)
{
  /*
   * TODO begin:
   * - free/delete the memory of each "Road" and "Item" object on the board_
   * - if you call the destructor of a "Field" object, make sure, that it is
   *   declared as virtual - as well as the destructor of "Road" and "Item" -
   *   so that the entire "Road" or "Item" object will be destroyed
   */

  // TODO end
}

//----------------------------------------------------------------------------------------------------------------------
Item* Board::getItemByName(std::string name)
{
  if (name.length() != 1)
    return NULL;
  char character = name[0];
  for (size_t current_item_it = 0; current_item_it < number_items_; current_item_it++)
  {
    Item* current_item = items_.at(current_item_it);
    if (current_item != NULL && current_item->getName() == character)
      return current_item;
  }
  return NULL;
}

//----------------------------------------------------------------------------------------------------------------------
bool Board::findPath(Item* from_item, Item* to_item)
{
  /*
   * TODO begin:
   * implement your path-finding algorithm here
   * if you want to use subroutines, implement them directly below this method and add them to the Board.hpp
   */

  //TODO end
}

//----------------------------------------------------------------------------------------------------------------------
/*
 * TODO begin: If you need any helper methods for the path finding, feel free
 * to implement them here.
 */

// TODO end

//----------------------------------------------------------------------------------------------------------------------
void Board::print(void)
{
  printLines();

  for (size_t row = 0; row < height_; row++)
  {
    printf("│");
    for (size_t column = 0; column < width_; column++)
    {
      if (board_.at(row).at(column))
        board_.at(row).at(column)->print();
      else
        printf(" ");
    }
    printf("│\n");
  }

  printLines();
}

//----------------------------------------------------------------------------------------------------------------------
void Board::printLines(void)
{
  printf("┼");
  for (size_t column = 0; column < width_; column++)
  {
    printf("─");
  }
  printf("┼\n");
}
