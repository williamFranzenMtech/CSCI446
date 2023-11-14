#ifndef PUZZLE_STATE_H
#define PUZZLE_STATE_H

#include <algorithm>
#include <iostream>

/*
Enumeration for directions the blank square can move in.
These represent binary states because I will be performing bitwise operators on these.
*/
enum moveDirection
{
    e_up = 1,   //0001
    e_down = 2, //0010
    e_left = 4, //0100
    e_right = 8 //1000
};

struct PuzzleState
{
    /*
    This will hold the values of each piece of the puzzle, numbered 1-9.
    The space character (0x20) will reperesent the blank space.
    I'm using chars (8 bits) instead of integers (16 bits) to optimize memory.
    If the array's values are: '1', ' ', '8', '2', '4', '3', '7', '5', '6'
    The puzzle state would be:
    1   8
    2 4 3
    7 5 6
    */
    unsigned char pState[9];

    /*
    Constructor for this struct.
    Takes an array of 9 values.
    */
    PuzzleState(unsigned char given[9])
    {
        for (int i=0; i<9; i++)
        {
            pState[i] = given[i];
        }
    }

    /*
    Equality Operator
    Params:
        other - Another puzzle state to test for equality.
                (Typically compare a state with the goal state.)
    Description:
        Compares two Puzzle States.
    Returns:
        true if the states are equal.
        false otherwise.
    */
    const bool operator==(PuzzleState other)
    {
        for (int i=0; i<9; i++)
        {
            if (this->pState[i] != other.pState[i])
            {
                return false;
            }
        }
        return true;
    }

    /*
    Out of Place
    Params:
        other - Another puzzle state to compare to.
                (Typically compare with the goal state.)
    Description:
        Checks how many pieces are out-of-place compared to the other vector.
    Returns:
        An integer containing the amount of pieces that are out of place.
    */
    const int outOfPlace(PuzzleState other)
    {
        int misplaced = 0;
        for (int i=0; i<9; i++)
        {
            if (this->pState[i] != other.pState[i])
            {
                misplaced += 1;
            }
        }
        return misplaced;
    }

    /*
    Get Blank Index
    Gets the index of the blank square in the array.
    */
    const int getBlankIndex()
    {
        for (int i=0; i<9; i++)
        {
            if (this->pState[i] == ' ')
            {
                return i;
            }
        }
        return -1;
    }

    /*
    Gets the movement options.
    Uses bitwise operators to store which moves are valid.
    The enumerations listed above are used for this.
    */
    char getMoveOptions()
    {
        /*
        Refer to this to see what the indeces are for the puzzle:
        0 1 2
        3 4 5
        6 7 8
        */

        char moves = 0;
        int blankIndex = getBlankIndex();

        /*
        If the blank square is below the top row,
        then up is a valid move.
        */
        if (blankIndex > 2)
        {
            moves |= e_up;
        }

        /*
        If the blank square is above the bottom row,
        then down is a valid move.
        */
        if (blankIndex < 6)
        {
            moves |= e_down;
        }

        /*
        If the blank square is to the right of the left column,
        then left is a valid move.
        */
        if (blankIndex % 3 != 0)
        {
            moves |= e_left;
        }

        /*
        If the blank square is to the left of the right column,
        then right is a valid move.
        */
        if ((blankIndex + 1) % 3 != 0)
        {
            moves |= e_right;
        }

        return moves;
    }

    /*
    Move
    Returns the next state after moving the blank square in a given direction.
    */
    PuzzleState move(moveDirection direction)
    {
        //Allocates memory for the array for the new state.
        unsigned char newArray[9];
        for (int i=0; i<9; i++)
        {
            newArray[i] = pState[i];
        }

        int blankIndex = getBlankIndex();

        /*
        Swaps the indeces based on the given direction.
        Refer to this to see what the indeces are for the puzzle:
        0 1 2
        3 4 5
        6 7 8
        */
        if (direction == e_up)
        {
            std::swap(newArray[blankIndex], newArray[blankIndex-3]);
        }
        if (direction == e_down)
        {
            std::swap(newArray[blankIndex], newArray[blankIndex+3]);
        }
        if (direction == e_left)
        {
            std::swap(newArray[blankIndex], newArray[blankIndex-1]);
        }
        if (direction == e_right)
        {
            std::swap(newArray[blankIndex], newArray[blankIndex+1]);
        }

        //Returns the state after swapping.
        return PuzzleState(newArray);
    }

    /*
    Uses cout to print the state to the terminal.
    */
    void printState()
    {
        for (int i=0; i<9; i++)
        {
            std::cout << pState[i];
            if ((i+1) % 3 == 0)
            {
                std::cout << '\n';
            }
        }
    }
};

#endif