/*
Name: Queenie Leung, NSHE 1007386899, CS 302 1004, Ast 1
Description: Create a connect four game with
             R = Red and B = Blue
Input: User 1 input then User 2 input and etc
Output: Program outputs and stacks a visual of
        connect
*/

#include "LL.h"
#include <iostream>
#include <string>

const int BOARD_SIZE = 7;

using namespace std;

//function declaration*********************
void print_list(LL <bool> linkList);
void print_board(LL <bool> board[]);
bool checkList(LL<bool> list);
bool checkColumn(LL <bool> board[]);
int elementAtCurrIndex(LL <bool>[], int i, int j);
bool checkRows(LL <bool> board[]);
bool checkDiagonal(LL<bool> board[]);
bool checkForWinner(LL <bool> board[]);
bool checkIfTie(LL <bool> board[]);
//****************************************

int main()
{   
    LL<bool> board[BOARD_SIZE];
    print_board(board);

    // Current player
    string player = "Red";
    string select = " Player Select a Row : ";
    
    while (true)
    {
        char chip;
        cout << player << select;
        cin >> chip;

        // insert true for Red and false for Blue at specified index
        bool isPlayerRed; // init a bool variable
        if(player == "Red") //check if player is red
        {
            isPlayerRed = true;    //set to true
        }
        else                    //else if not red
        {       
            isPlayerRed = false; //set to false
        }
        //tail insert function using the parameters of true or
                // validate input
        int inputValidation = tolower(chip) - 'a';

        // check if column is not within bounds
        if (inputValidation < 0 || inputValidation >= BOARD_SIZE )
            {
                cout << "Invalid Column" << endl;
                continue;
            }
        if ( board[inputValidation].size() >= BOARD_SIZE)
            {
                cout << "Invalid Move" << endl;
                continue;
            }
        board[inputValidation].tailInsert(isPlayerRed);

        // print the board again after inserting a chip
        print_board(board);

        // check board for winner
        if (checkForWinner(board))
        {
            cout << player << " wins !" << endl;
            break;
        }

        
        // check board for tie
        if (checkIfTie(board))
        {
            cout << "Player Red and Player Blue tie !" << endl;
            break;
        }

        // alternate player red and blue
        if(player == "Red")
        { player = "Blue";  }
        else
        { player = "Red";   }

    }

    return 0;
}

/*************Function Definition******************/

/*
    print_list prints the beginning of the linked list
    and keeps looping while iterator (itr) is not the
    end of the link list and increments itr
    and checks if deref itr value is R or B to print
*/
void print_list(LL<bool> linkList)
{
    for (auto itr = linkList.begin(); itr != linkList.end(); itr++)
        // std::cout << *i << " ";
        if(*itr == 'R')         //if the deref itr = R 
        {cout << "R "<< endl;}  //print R
        else if (*itr == 'B')    //else if not R
        {cout << "B " << endl;} //print B
    
        //std::cout << "\n"; //DEBUG

    //return; ???? //DEBUG
}

/*
    prints the 7x7 board
*/

void print_board(LL<bool> board[])
{
    int i = BOARD_SIZE - 1;
    for (i ; i >= 0; i--)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {   
            auto it = board[j].end();
            int numcheck = static_cast<int>(board[j].size());

            if (i < numcheck)
            {
                for (int k = 0; k <= i; k++)
                   { it++; }

                if(*it == true)
                  { cout << "R ";} // Adjusted spacing
                else 
                  { cout << "B ";}
     
            }
            else
              { cout << "- ";   } // Adjusted spacing
        }
        cout << endl;
    }

    cout << endl;

    for (char chipSelected = 'A'; chipSelected <= 'G'; chipSelected++)
    {   cout << chipSelected << " ";    } // Adjusted spacing

    cout << endl << endl; 
}


// Check if list has 4 similar consecutive chips
bool checkList(LL<bool> list)
{
    if (list.isEmpty()) 
        { return false; }
    else if(list.size() < 4)
        { return false; }

    // Declare 4 iterator pointers that point to the beginning
    //of the link list
    auto it1 = list.begin();
    auto it2 = list.begin();
    auto it3 = list.begin();
    auto it4 = list.begin();

    it2++; // points after it1
    it3++ = it3++; //it3++;// points after it2
  
    it4 = it3;
    it4++; // points after it3
    

    // Iterate through the list, comparing each iterator item
    // to the next 3 items
    for(it1, it2, it3, it4; it4 !=list.end();it1++,it2++,it3++, it4++)
    {
        if (*it1 == *it2 && *it2 == *it3 && *it3 == *it4)
        {  return true; }
        else if (*it1 != *it2 && *it2 != *it3 && *it3 != *it4)
        {  return false;}
    }
    //if it is not within conditions to just return false
     return false;
}

// check each col for winning combination
bool checkColumn(LL<bool> board[]) //i thnk i may put this into main
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        auto col = board[i];

        if (checkList(col))
        {
            // cout << "Winning col: " << i << "\n\n";
            print_list(col);
            return true;
        }
    }

    return false;
}

// Get element at specified coordiates in the board
int elementAtCurrIndex(LL<bool> board[], int i, int j)
{
    // returns 1 for true, 0 for false, -1 for empty

    // cout << "Size of col " << i << ": " << board[i].size() << endl;
    int col = static_cast<int>(board[i].size());
    if (j >= col || j < 0)
    {   //this is indicating we are out of bounds
        return -1; 
    }
    //declare instance of it set to board [i].begin();
    auto it = board[i].begin();

    // iterate to value at index
    for (int k = 0; k < j; k++)
        //increment iterator it
        { it++; }
    
    //check the deincremented value of "it"
    //return 1 if true else if not true return 0
    if(*it)
        {return 1;}
    else
        {return 0;}
    
}

// check each row for winning combination
bool checkRows(LL<bool> board[])
{   int i = 0;
    int j = 0;
    int four = 4;
    LL<bool> row, col;
    
     // create a linked list representing each row
    while (i < BOARD_SIZE)
    {
        // copy row to new linked list
        //add items to row
        while(j < BOARD_SIZE)
     
        {    //set the board = to col, easier to read
             col = board[j]; 
             //get the size of column
             int colSize = static_cast<int>(col.size() - 1);   
            
            if (i > colSize)
            {
                //if row is less than 4 
                if (row.size() < four)
                {
                    // reset row 
                    row = LL<bool>();
                    j++;
                    //go to next interation
                    continue;
                    
                }
                //breaks out of the inner if stmt 
                // if row.size() not less than 4
                break;
            }
            else 
            {   //sets the iterator it to the end
                auto it = board[j].end();
                // iterate to value at index
                for (int k = 0; k <= i; k++)
                {//increment it to get thru board indexs
                    it++;
                }
                //else at this row 
                row.tailInsert(*it);
                j++;
            }
        }

        // check each row
        if (checkList(row))
        {
            // cout << "Winning row: " << i << "\n\n";
            // printList(row);
            return true;
        }
        //increment i
        i++;
    }

    return false;
}
/*
    check for diagonal top left going down towards
    the right
    then check
*/
bool checkDiagonal(LL<bool> board[]) 
{

    // Diagonals from top-left to bottom-right
    for (int i = 0; i < BOARD_SIZE; i++) {
        int k = i;

        // copy diagonal to new linked list
       // LL<bool> diag, clear;
            LL<bool> diag;
            LL<bool> reset;
        int j = 0;
        if(k >= 0) //checks if k is greater than or equal to 0
        { k = k;  } //if it is then let k = k
        else      //else if it is not set k equal to 0
        {k = 0;   }
        while (k >=0 && j < 7) //while k is >= 0 and j <7 keep
                                //looping
        {
            // std::cout << arr[k][j] << " "; //DEBUG
            int element = elementAtCurrIndex(board, k, j);

            if (element == -1) // nothing/empty
            {   //checks if size is less than 4
                if (diag.size() < 4) 
                {
                    // reset diagonal 
                    diag = reset;
                    //continue;
                }
                else //size is not less than 4
                {  break;   }
            }
            else //size is greater than 4
            {       //1 is win condition
                diag.tailInsert(element == 1);
            }
            //increment j and decrement k
            j++; //traverse towards the 
            k--; //traverse downward
        }
        
        // check each diagonal
        if (checkList(diag))
        {
            // cout << "Winner: << endl; //DEBUG
            return true;
        }
        
    }

    for (int i = 1; i < BOARD_SIZE; i++) {
        int k = i;

        // copy diagonal to new linked list
        LL<bool> diag, reset;

        for (int j = 6; k < 7 && j >= 0; j--, k++) {
            // std::cout << std::setw(2) << arr[k][j] << " ";
            int element = elementAtCurrIndex(board, k, j);

            if (element == -1) // empty slot
            {
                if (diag.size() < 4)
                {
                    // reset diag
                    diag = reset;
                    //continue;
                }
                else
                {
                    break;
                }
            }
            else
            {
                diag.tailInsert(element == 1);
            }
        }

        // check each diagonal
        if (checkList(diag))
        {
            return true;
        }
    }

    // Diagonals from top-right to bottom-left
    for (int i = 0; i < 7; i++) {
        int k = i;

        // copy diagonal to new linked list
        LL<bool> diag, clear;

        for (int j = 6; k >= 0 && j >= 0; j--, k--) {
            //std::cout << std::setw(2) << arr[k][j] << " ";
            int element = elementAtCurrIndex(board, k, j);

            if (element == -1) // empty slot
            {
                if (diag.size() < 4)
                {
                    // cout << "diag " << i << " will reset.\n";
                    diag = clear;
                    continue;
                }
                else
                {
                    break;
                }
            }
            else
            {
                diag.tailInsert(element == 1);
            }
        }
        
        // check each diagonal
        if (checkList(diag))
        {
            // cout << "Winning diag: " << i << "\n\n";
            // printList(diag);
            return true;
        }
    }

    for (int i = 1; i < 7; i++) {
        int k = i;

        // copy diagonal to new linked list
        LL<bool> diag, clear;

        for (int j = 0; k < 7 && j < 7; j++, k++) {
            // std::cout << std::setw(2) << arr[k][j] << " ";
            int element = elementAtCurrIndex(board, k, j);

            if (element == -1) // empty slot
            {
                if (diag.size() < 4)
                {
                    // cout << "diag " << i << " will reset.\n";
                    diag = clear;
                    continue;
                }
                else
                {
                    break;
                }
            }
            else
            {
                diag.tailInsert(element == 1);
            }
        }
        
        // check each diagonal
        if (checkList(diag))
        {
            // cout << "Winning diag: " << i << "\n\n";
            // printList(diag);
            return true;
        }
    } 

    return false;
} 

// checks if there is a winner
/*
    this checks between the earlier functions
    if column or rows or diagonal has a match
    on the board resulting in true
    else no winner 
*/
bool checkForWinner(LL<bool> board[])
{
    if (checkColumn(board) || checkRows(board)
        || checkDiagonal(board))
    {
        return true;
    }

    return false;
}

/*
    check if we have a tie as long as we
    are within the 7x7 board
    this is basically the board maxed out
    with no other plays that any player can
    make
*/
bool checkIfTie(LL<bool> board[])
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        // check if any column is not maxed out
        if (board[i].size() != BOARD_SIZE)
        {
            return false;
        }
    }
    // board is full
    return true;
}