//----------------------------------------------------------------------------------------------------------------------
// Assignment 1 - OOP1 SS2021
//
// Pathfinding-Algorithm on a 2D-Board. Determines if there exists a path
// consisting of unblocked roads between two items.
//
// Author: Tutors
//----------------------------------------------------------------------------------------------------------------------
//

#include <fstream>
#include <string>
#include <iostream>
#include <cstdio>
#include "Board.hpp"
#include "Item.hpp"
#include "Road.hpp"

#define QUIT_COMMAND "QUIT"

enum ErrorValues
{
  OK = 0,
  WRONG_PARAMETER_COUNT = -1,
  COULD_NOT_OPEN_FILE = -2,
  INVALID_CONFIG = -3
};

enum Part
{
  FIRST_ITEM = 1,
  SECOND_ITEM = 2
};

//----------------------------------------------------------------------------------------------------------------------
/// Reads the user input and returns it as an uppercase string.
///
/// @param current - determines whether the first or second item will be read
/// @return input - the user input
//
std::string readUserInput(Part current)
{
  printf("Enter %d. item: ", current);
  std::string input;
  std::cin >> input;
  for (char& character : input)
  {
    character = toupper(character);
  }
  return input;
}

//----------------------------------------------------------------------------------------------------------------------
/// The program starts here. 
/// In each round of the while-loop the program waits for the user to insert two items. Then it checks
/// if there exists a path between the two items.
/// The while-loop will be exited when the user input equals "quit".
///
/// @param board - a reference to the board
//
void run(Board& board)
{
  printf("On the board %d road(s) are blocked!\n", Road::getNumberOfBlockedRoads());
  board.print();

  while (1)
  {
    bool input_correct = false;
    Item* first_item;
    Item* second_item;
    while (!input_correct)
    {
      std::string user_input = readUserInput(FIRST_ITEM);
      if (user_input == QUIT_COMMAND)
        return;
      first_item = board.getItemByName(user_input);
      if (first_item == NULL)
        puts("Item not found!");
      else
        input_correct = true;
    }

    input_correct = false;
    while (!input_correct)
    {
      std::string user_input = readUserInput(SECOND_ITEM);
      if (user_input == QUIT_COMMAND)
        return;
      second_item = board.getItemByName(user_input);
      if (second_item == NULL)
        puts("Item not found!");
      else
        input_correct = true;
    }

    if (board.findPath(first_item, second_item))
    {
      printf("The path from %c to %c exists.\n\n", first_item->getName(), second_item->getName());
    }
    else
    {
      printf("The path from %c to %c does NOT exist.\n\n", first_item->getName(), second_item->getName());
    }
  }
}

//----------------------------------------------------------------------------------------------------------------------
/// Deletes the char 2D array from the config file.
///
/// @param field - pointer to the 2D array
/// @param field_height - the height of the 2D array
//
void deleteArray(char** field, size_t field_height)
{
  for (size_t row = 0; row < field_height; row++)
  {
    delete[] field[row];
  }
  delete[] field;
  field = NULL;
}

//----------------------------------------------------------------------------------------------------------------------
/// This function parses the input of the config file into dedicated data types.
///
/// @param file - the opened config file
/// @param field_height - the height of the field
/// @param field_width - the width of the field
/// @param nr_items - number of items expected to be on the field
/// @param field - 2D array
/// @return ErrorValue, which indicates errors during parsing the file
//
int parseFile(std::ifstream& file, size_t& field_height, size_t& field_width, 
  size_t& nr_items, char**& field)
{
  file >> field_height;
  if (!file.good() || file.get() != '\n')
  {
    puts("[ERROR] Field height invalid!");
    return ErrorValues::INVALID_CONFIG;
  }

  file >> field_width;
  if (!file.good() || file.get() != '\n')
  {
    puts("[ERROR] Field width invalid!");
    return ErrorValues::INVALID_CONFIG;
  }

  file >> nr_items;
  if (!file.good() || file.get() != '\n')
  {
    puts("[ERROR] Number of items invalid!");
    return ErrorValues::INVALID_CONFIG;
  }

  field = new char*[field_height];
  for (size_t row = 0; row < field_height; row++)
  {
    field[row] = new char[field_width];
    file.read(field[row], field_width);

    if (!file.good() || file.get() != '\n')
    {
      for (size_t eraser = 0; eraser < row; eraser++)
        delete[] field[eraser];
      delete[] field;
      puts("[ERROR] Size of board not correct or newline missing!");
      return ErrorValues::INVALID_CONFIG;
    }
  }
  if (file.peek() != EOF)
  {
    deleteArray(field, field_height);
    puts("[ERROR] Board too high or additional chars in front of EOF!");
    return ErrorValues::INVALID_CONFIG;
  }

  size_t item_counter = 0;
  for (size_t row = 0; row < field_height; row++)
  {
    for (size_t column = 0; column < field_width; column++)
    {
      if (field[row][column] != '%' && field[row][column] != '#' &&
          field[row][column] != ' ' &&
          !('A' <= field[row][column] && field[row][column] <= 'Z'))
      {
        deleteArray(field, field_height);
        puts("[ERROR] Invalid symbols in board!");
        return ErrorValues::INVALID_CONFIG;
      }
      if ('A' <= field[row][column] && field[row][column] <= 'Z')
        item_counter++;
    }
  }
  if (item_counter != nr_items)
  {
    deleteArray(field, field_height);
    puts("[ERROR] Wrong item count!");
    return ErrorValues::INVALID_CONFIG;
  }

  return ErrorValues::OK;
}

//----------------------------------------------------------------------------------------------------------------------
/// The main function.
///
/// @param argc - number of command line parameters
/// @param argv - content of the command line parameters
/// @return ErrorValue, which indicates errors
//
int main(int argc, char* argv[])
{
  std::ifstream file;
  size_t field_height = 0;
  size_t field_width = 0;
  size_t nr_items = 0;
  char** field = NULL;

  if (argc != 2)
  {
    printf("[ERROR] Usage: %s <filename>.txt\n", argv[0]);
    return ErrorValues::WRONG_PARAMETER_COUNT;
  }

  file.open(argv[1], std::ifstream::in);
  if (!file.is_open())
  {
    puts("[ERROR] Could not open file!");
    return ErrorValues::COULD_NOT_OPEN_FILE;
  }

  if (parseFile(file, field_height, field_width, nr_items, field) == ErrorValues::INVALID_CONFIG)
  {
    puts("\tInvalid config file!");
    file.close();
    return ErrorValues::INVALID_CONFIG;
  }
  file.close();

  Board board(field_height, field_width, nr_items, field);

  deleteArray(field, field_height);
  run(board);

  return ErrorValues::OK;
}
