#include <iostream>
#include <tuple>
#include <vector>
#include <algorithm>
#include <string>
#include "Node.h"
#include "PuzzleState.h"
#include "LinkedList.cpp"
#include "Queue.cpp"

/*
Is Visited
Params:
    st - A pointer to a puzzle state.
    vList - A pointer to a linked list of visited states.
Description:
    Checks if the given state is in the visited list.
    Adds it to the list if it's absent.
Returns:
    True if the state has already been visited.
    False otherwise.
*/
bool isVisited(PuzzleState* st, LinkedList<PuzzleState>* vList)
{
    //This pointer will iterate through the nodes in the linked list.
    Node<PuzzleState>* cur = vList->getHead();
    while (cur != nullptr)
    {
        if (*st == cur->item)
        {
            //Exit this function and return true if the state has been visited.
            return true;
        }
        //Iterate to the next step in the linked list.
        cur = cur->next;
    }
    vList->append(*st);
    return false;
}

/*
Get Min Index
Params:
    vec - A pointer to a vector of tuples.
        0: Puzzle States
        1: Vector of moves made by the blank square
        2: The value to determine the order of the search.
        3: The current depth.
Description:
    Returns the index of the tuple in the vector with the smallest value (index 2).
*/
int getMinIndex(std::vector<std::tuple<PuzzleState, std::vector<moveDirection>, int, int>>* vec)
{
    int minIndex = 0;
    int min = std::get<2>(vec->at(0));
    for (unsigned int i=1; i<vec->size(); i++)
    {
        int curVal = std::get<2>(vec->at(i));
        if (curVal < min)
        {
            minIndex = i;
            min = curVal;
        }
    }
    return minIndex;
}

/*
Breadth First Search
Params:
    qu - A pointer to a queue of states.
    goal - The goal state.
    visitedList - A pointer to a linked list of visited states.
*/
std::vector<moveDirection> bfs(Queue<std::tuple<PuzzleState, std::vector<moveDirection>>>* qu, PuzzleState goal, LinkedList<PuzzleState>* visitedList)
{
    while (qu->getSize() > 0)
    {
        /*
        Reads the current queue head and dequeues it.
        Stores the list of moves made in a vector.
        The puzzle state is stored at index 0 in the tuple.
        The vector of moves is stored at index 1 in the tuple.
        */
        PuzzleState cur = std::get<0>(qu->read());
        std::vector<moveDirection> directionList = std::get<1>(qu->read());
        //cur.printState();
        qu->dequeue();
        
        //Check if the current state in the queue is the goal state
        if (cur == goal)
        {
            return directionList;
        }

        /*
        Continue to search states while the queue is not empty.
        */
        char validMoves = cur.getMoveOptions();

        //Queue Up
        if (validMoves & e_up)
        {
            PuzzleState up = cur.move(e_up);
            if (!isVisited(&up, visitedList))
            {
                std::vector<moveDirection> moveUp(directionList);
                moveUp.push_back(e_up);
                qu->enqueue(std::make_tuple(up, moveUp));
            }
        }

        //Queue Down
        if (validMoves & e_down)
        {
            PuzzleState down = cur.move(e_down);
            if (!isVisited(&down, visitedList))
            {
                std::vector<moveDirection> moveDown(directionList);
                moveDown.push_back(e_down);
                qu->enqueue(std::make_tuple(down, moveDown));
            }
        }

        //Queue Left
        if (validMoves & e_left)
        {
            PuzzleState left = cur.move(e_left);
            if (!isVisited(&left, visitedList))
            {
                std::vector<moveDirection> moveLeft(directionList);
                moveLeft.push_back(e_left);
                qu->enqueue(std::make_tuple(left, moveLeft));
            }
        }

        //Queue Right
        if (validMoves & e_right)
        {
            PuzzleState right = cur.move(e_right);
            if (!isVisited(&right, visitedList))
            {
                std::vector<moveDirection> moveRight(directionList);
                moveRight.push_back(e_right);
                qu->enqueue(std::make_tuple(right, moveRight));
            }
        }
    }
    //Returns an empty vector if no solution is found.
    std::vector<moveDirection> noSolution;
    std::cout << "No solution found." << '\n';
    return noSolution;
}

/*
Heuristic Search
Params:
    vec - A pointer to a vector of tuples.
        0: Puzzle States
        1: Vector of moves made by the blank square
        2: The value to determine the order of the search.
        3: The current depth.
    goal - The goal state.
    visitedList - A pointer to a linked list of visited states.
*/
std::vector<moveDirection> heuristic(std::vector<std::tuple<PuzzleState, std::vector<moveDirection>, int, int>>* vec, PuzzleState goal, LinkedList<PuzzleState>* visitedList)
{
    while (vec->size() > 0)
    {
        /*
        Obtains the value with the lowest value, and stores the associated data into variables.
        */
        int minIndex = getMinIndex(vec);
        PuzzleState cur = std::get<0>(vec->at(minIndex));
        std::vector<moveDirection> directionList = std::get<1>(vec->at(minIndex));
        int depth = std::get<3>(vec->at(minIndex));

        /*
        Removes the tuple from the vector.
        */
        vec->erase(vec->begin()+minIndex);

        if (cur == goal)
        {
            return directionList;
        }

        /*
        Continue to search states while the vector is not empty.
        */
        char validMoves = cur.getMoveOptions();

        //Push Up
        if (validMoves & e_up)
        {
            PuzzleState up = cur.move(e_up);
            if (!isVisited(&up, visitedList))
            {
                std::vector<moveDirection> moveUp(directionList);
                moveUp.push_back(e_up);
                int addVal = up.outOfPlace(goal);
                vec->push_back(std::make_tuple(up, moveUp, addVal + depth + 1, depth + 1));
            }
        }

        //Push Down
        if (validMoves & e_down)
        {
            PuzzleState down = cur.move(e_down);
            if (!isVisited(&down, visitedList))
            {
                std::vector<moveDirection> moveDown(directionList);
                moveDown.push_back(e_down);
                int addVal = down.outOfPlace(goal);
                vec->push_back(std::make_tuple(down, moveDown, addVal + depth + 1, depth + 1));
            }
        }

        //Push Left
        if (validMoves & e_left)
        {
            PuzzleState left = cur.move(e_left);
            if (!isVisited(&left, visitedList))
            {
                std::vector<moveDirection> moveLeft(directionList);
                moveLeft.push_back(e_left);
                int addVal = left.outOfPlace(goal);
                vec->push_back(std::make_tuple(left, moveLeft, addVal + depth + 1, depth + 1));
            }
        }

        //Push Right
        if (validMoves & e_right)
        {
            PuzzleState right = cur.move(e_right);
            if (!isVisited(&right, visitedList))
            {
                std::vector<moveDirection> moveRight(directionList);
                moveRight.push_back(e_right);
                int addVal = right.outOfPlace(goal);
                vec->push_back(std::make_tuple(right, moveRight, addVal + depth + 1, depth + 1));
            }
        }
    }
    //Returns an empty vector if no solution is found.
    std::vector<moveDirection> noSolution;
    std::cout << "No solution found." << '\n';
    return noSolution;
}

int main()
{
    /*
    Takes user input for the states and which algorithm to perform.
    The states must be formatted as the following:
    71458263_ (Replace the underscore with the space character!!!!)
    This would represent the following game board:
    7 1 4
    5 8 2
    6 3  
    */
    std::string startString;
    std::cout << "Enter the start state: " << '\n';
    std::getline(std::cin, startString);

    std::string endString;
    std::cout << "Enter the goal state: " << '\n';
    std::getline(std::cin, endString);

    std::string type;
    std::cout << "Enter the type of search\nh: heuristic\nb: breadth-first: " << '\n';
    std::getline(std::cin, type);

    unsigned char startArray[9];
    unsigned char goalArray[9];

    for (int i=0; i<9; i++){
        startArray[i] = startString[i];
        goalArray[i] = endString[i];
    }

    PuzzleState startState = PuzzleState(startArray);
    PuzzleState goalState = PuzzleState(goalArray);


    std::vector<moveDirection> solution;
    LinkedList<PuzzleState>* visitedList = new LinkedList<PuzzleState>;
    std::vector<moveDirection> memoryList;

    if (type == "b")
    {
        Queue<std::tuple<PuzzleState, std::vector<moveDirection>>>* bfsQueue = new Queue<std::tuple<PuzzleState, std::vector<moveDirection>>>();
        bfsQueue->enqueue(std::make_tuple(startArray, memoryList));
        solution = bfs(bfsQueue, goalState, visitedList);
    }
    else if (type == "h")
    {
        std::vector<std::tuple<PuzzleState, std::vector<moveDirection>, int, int>>* heuristicVec = new std::vector<std::tuple<PuzzleState, std::vector<moveDirection>, int, int>>();
        heuristicVec->push_back(std::make_tuple(startState, memoryList, 0, 0));
        solution = heuristic(heuristicVec, goalState, visitedList);
    }
    else
    {
        std::cout << "Invalid search type." << '\n';
        return 1;
    }

    //Iterates through the solution vector and prints the steps needed to solve the puzzle.
    for (unsigned int i=0; i<solution.size(); i++)
    {
        switch (solution[i])
        {
            case e_up:
                std::cout << "U";
                break;
            case e_down:
                std::cout << "D";
                break;
            case e_left:
                std::cout << "L";
                break;
            case e_right:
                std::cout << "R";
                break;
        }
    }
    std::cout << '\n';
}