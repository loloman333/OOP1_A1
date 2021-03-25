//----------------------------------------------------------------------------------------------------------------------
// Assignment 1 - OOP1 SS2021
//
// Board-class represents the Board where roads and items are placed on.
//
// Author: Tutors
//----------------------------------------------------------------------------------------------------------------------
//

#ifndef A1_BOARD_HPP
#define A1_BOARD_HPP

#include <string>
#include <vector>

// Forward declarations of classes
class Field;
class Item;
/*
 * TODO begin: If you need any additional includes or forward declarations of
 * classes you can add them here.
 */

// TODO end

class Board
{
  private:
    size_t height_;
    size_t width_;
    size_t number_items_;

    std::vector<std::vector<Field*>> board_;
    std::vector<Item*> items_;

    /*
     * TODO begin: If you need additional attributes you can add them here.
     */

    // TODO end

  public:

    //------------------------------------------------------------------------------------------------------------------
    /// Constructor
    ///
    /// @param height - the height of the board_, read from the config file
    /// @param width - the width of the board_, read from the config file
    /// @param number_items - the number of items, read from the config file
    /// @param fields - the field as 2D-character-array, read from the config file
    //
    Board(size_t height, size_t width, size_t number_items, char** fields);

    //------------------------------------------------------------------------------------------------------------------
    /// Deleted Copy-Constructor
    //
    Board(Board&) = delete;

    //------------------------------------------------------------------------------------------------------------------
    /// Destructor
    //
    ~Board();

  private:

    //------------------------------------------------------------------------------------------------------------------
    /// Iterates through 2D-char-array, creates roads and items according to their type
    /// on the array and stores them on the board.
    ///
    /// @param field - the 2D-array of characters read from the config file
    //
    void initializeFields(char** fields);

    //------------------------------------------------------------------------------------------------------------------
    /// Frees the memory allocated for fields on the board.
    //
    void deleteFields(void);

  public:

    //------------------------------------------------------------------------------------------------------------------
    /// Get the item object with a specific name.
    ///
    /// @param name - the name of the item
    /// @return The item we looked for or NULL if the item was not found.
    //
    Item* getItemByName(std::string name);

    //------------------------------------------------------------------------------------------------------------------
    /// Checks if there exists a path between two items.
    ///
    /// @param from_item - the first item
    /// @param to_item - the second item
    /// @return true if there exists a path of roads, otherwise false
    //
    bool findPath(Item* from_item, Item* to_item);

  private:
    /*
     * TODO begin: If you need any helper methods for the path finding, feel free
     * to declare them here.
     */

    // TODO end

  public:

    //------------------------------------------------------------------------------------------------------------------
    /// Prints the board to stdout.
    ///
    void print(void);

  private:

    //------------------------------------------------------------------------------------------------------------------
    /// Helper function for print to display the border of the board.
    ///
    void printLines(void);
};

#endif // A1_BOARD_HPP
