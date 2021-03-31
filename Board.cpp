//----------------------------------------------------------------------------------------------------------------------
// Assignment 1 - OOP1 SS2021
//
// Board-class represents the Board where roads and items are placed on.
//
// Author: Tutors
//----------------------------------------------------------------------------------------------------------------------
//

#include "Board.hpp"
#include "Road.hpp"
#include "Item.hpp"
#include <cstdio>
/*
 * TODO begin: If you need any additional includes you can add them here.
 */

#include <iostream>


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

  for (unsigned row_index = 0; row_index < height_; row_index++)
  {
    std::vector<Field*> column = std::vector<Field*>{};

    for (unsigned col_index = 0; col_index < width_; col_index++) 
    {
      char field = fields[row_index][col_index];

      if (field == ' ')
      {
        column.push_back(nullptr);
      }
      else
      {
        Coordinates cords = Coordinates{row_index, col_index};

        if (field == '#')
        { 
          column.push_back(new Road{false, cords});
        }
        else if (field == '%')
        {
          column.push_back(new Road{true, cords});
        }
        else
        {
          //TODO check if char (name) is valid?
          Item* item = new Item{field, cords};
          column.push_back(item);
          items_.push_back(item);
        }
      }

    }
    board_.push_back(column);
  }
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

  for (std::vector<Field*> row : board_)
  {
    for (Field* field : row)
    {
      if (field != nullptr)
      {
        delete field;
      }
    }
  }

  // for (Item* item : items_)
  // {
  //   delete item;
  // }

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

  // Best-First Search

  // Phase 0: Preparation
  Field* current_field = from_item;
  std::set<Field*> seen{current_field};
  std::set<Field*> unvisited{current_field};

  while (current_field != nullptr)
  {

    // Phase 1: Add neighbors
    bool found_path = addNeighbors(current_field, to_item, seen, unvisited);

    // Stop if neighbor is to_item
    if (found_path)
    {
      return true;
    }

    // Phase 2: Choose next field to explore
    current_field = chooseNextField(to_item, unvisited);
  }

  return false;

  //TODO end
}

//----------------------------------------------------------------------------------------------------------------------
/*
 * TODO begin: If you need any helper methods for the path finding, feel free
 * to implement them here.
 */

bool Board::addNeighbors(Field* current_field, Item* to_item, std::set<Field*>& seen, std::set<Field*>& unvisited)
{
  std::vector<Field*> neighbors = getNeighborsOfField(current_field);
  for (Field* neighbor : neighbors)
  {
    if (neighbor != nullptr)
    {
      if (neighbor == to_item)
      {
        return true;
      } 
      else if (!neighbor->isBlocked())
      {
        bool inserted = seen.insert(neighbor).second;
        if (inserted)
        {
          unvisited.insert(neighbor);
        }
      }  
    } 
  }

  return false;
}

Field* Board::chooseNextField(Item* to_item, std::set<Field*>& unvisited)
{
  Field* next_field = nullptr;
  int min_distance = width_ + height_; 
  for (Field* field : unvisited)
  { 
    int col_distance = abs((int)field->getPositon().column_ - (int)to_item->getPositon().column_);
    int row_distance = abs((int)field->getPositon().row_ - (int)to_item->getPositon().row_);
    int distance = col_distance + row_distance;
    if (distance < min_distance)
    {
      min_distance = distance;
      next_field = field;
      
    }
  }

  unvisited.erase(next_field);
  return next_field;
}

//TODO: kinda ugly lul
std::vector<Field*> Board::getNeighborsOfField(Field* field)
{
  Coordinates cords = field->getPositon();
  std::vector<Field*> neighbors{};
  
  // Upper Neighbor
  Coordinates neighbor_cords{cords};
  neighbor_cords.row_--;
  if (areCoordinatesOnBoard(neighbor_cords))
  {
    neighbors.push_back(board_[neighbor_cords.row_][neighbor_cords.column_]);
  }

  // Right Neighbor
  neighbor_cords = cords;
  neighbor_cords.column_++;
  if (areCoordinatesOnBoard(neighbor_cords))
  {
    neighbors.push_back(board_[neighbor_cords.row_][neighbor_cords.column_]);
  }

  // Down Neighbor
  neighbor_cords = cords;
  neighbor_cords.row_++;
  if (areCoordinatesOnBoard(neighbor_cords))
  {
    neighbors.push_back(board_[neighbor_cords.row_][neighbor_cords.column_]);
  }

  // Left Neighbor
  neighbor_cords = cords;
  neighbor_cords.column_--;
  if (areCoordinatesOnBoard(neighbor_cords))
  {
    neighbors.push_back(board_[neighbor_cords.row_][neighbor_cords.column_]);
  }

  return neighbors;
}

bool Board::areCoordinatesOnBoard(Coordinates& cords)
{
  if (cords.column_ >= width_ || cords.column_ < 0) // TODO: remove checking for smaller (size_t is unsigned)
  {
    return false;
  }

  if (cords.row_ >= height_ || cords.row_ < 0)
  {
    return false;
  }

  return true;
}

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
