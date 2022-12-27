#include <iostream>
#include <vector>

using namespace std;

void displayBoard(char** board, int SIZEX, int SIZEY)
{
    for (int y = 0; y < SIZEY; y++)
    {
        for (int x = 0; x < SIZEX; x++)
        {
            cout << board[y][x] << (x == SIZEX-1 ? "" : "|");
        }
        cout << endl;
        if (y != SIZEY - 1)
        {
            for (int i = 0; i < SIZEX; i++)
            {
                cout << (i == SIZEX - 1 ? "-" : "-+");
            }
        }
        cout << endl;
    }
}

void populateBoard(char** board, int SIZEX, int SIZEY)
{
    for (int i = 0; i < SIZEY; i++)
        for (int j = 0; j < SIZEX; j++)
            board[i][j] = ' ';
}

bool checkRow(char** board, int SIZEX, int rowToCheck, char markPlayed)
{
    int totalMarks = 0;
    for (int i = 0; i < SIZEX; i++)
    {
        //cout << "Row to check: " << rowToCheck << ", Column: " << i << ", Total marks : " << totalMarks << ", board: " << board[rowToCheck][i] << endl;
        if (board[rowToCheck][i] == markPlayed)
            totalMarks++;
    }
    if (totalMarks == SIZEX)
        return true;
    return false;
}

bool checkCol(char** board, int SIZEY, int colToCheck, char markPlayed)
{
    int totalMarks = 0;
    for (int i = 0; i < SIZEY; i++)
    {
        //cout << "Row to check: " << i << ", Column: " << colToCheck << ", Total marks : " << totalMarks << ", board: " << board[i][colToCheck] << endl;
        if (board[i][colToCheck] == markPlayed)
            totalMarks++;
    }
    if (totalMarks == SIZEY)
        return true;
    return false;
}

bool checkDiag(char** board, int SIZEX, char markPlayed, bool topLeft)
{
    int totalMarks = 0;
    // starting at top left of the board
    if (topLeft)
    {
        for (int i = 0; i < SIZEX; i++)
        {
            if (board[i][i] == markPlayed)
                totalMarks++;
        }
    }
    else // starting at top right of the board
    {
        int x = 0;
        for (int i = SIZEX - 1; i >= 0; i--)
        {
            if (board[x][i] == markPlayed)
                totalMarks++;
            //cout << "x = " << x << ", i = " << i << ", board[x][i] = " << board[x][i] << endl;
            x++;
        }
    }

    if (totalMarks == SIZEX)
        return true;

    return false;
}

bool checkWinCondition(char** board, int SIZEX, int SIZEY, char markPlayed)
{
    // row the same is win
    // col the same is win
    // diagonal the same is win

    for (int i = 0; i < SIZEY; i++)
    {
        for (int j = 0; j < SIZEX; j++)
        {
            if (checkCol(board, SIZEY, j, markPlayed))
                return true;
        }
        if (checkRow(board, SIZEX, i, markPlayed))
            return true;
    }

    if (checkDiag(board, SIZEX, markPlayed, true))
        return true;
    if (checkDiag(board, SIZEX, markPlayed, false))
        return true;

    return false;
}

void computerPlayer()
{

}


int main()
{
    int SIZEX = 3;
    int SIZEY = 3;
    int userDifficulty = 2;

    cout << "Enter size of board (length): ";
    cin >> SIZEX;
    cout << endl << "Enter size of board (height): ";
    cin >> SIZEY;
    cout << endl;

    char** board;
    board = new char* [SIZEX];
    for (int i = 0; i < SIZEX; i++)
        board[i] = new char[SIZEY];


    populateBoard(board, SIZEX, SIZEY);

    int amountofspaces = 0;
    for (int i = 0; i < SIZEX; i++)
        if (board[0][i] == ' ')
            amountofspaces++;

    cout << "Welcome to tic-tac-toe!" << endl;
    cout << "What difficulty AI do you want to play against?" << endl;
    cout << "1 - Easy" << endl;
    cout << "2 - Medium" << endl;
    cout << "3 - Hard" << endl;
    cout << "Please enter the number corresponding to the difficulty: ";
    cin >> userDifficulty;
    cout << "Your difficulty: " << (userDifficulty == 1 ? "Easy" : (userDifficulty == 2) ? "Medium" : "Hard") << ", good luck!" << endl << endl;



    int player1MoveX = 0;
    int player1MoveY = 0;
    int player2MoveX = 0;
    int player2MoveY = 0;
    cout << "Player 1 is X" << endl << "Player 2 is O" << endl;
    cout << "Enter x,y coordinates. 0,0 is top left. X increases to the right. Y increases downwards" << endl;

    displayBoard(board, SIZEX, SIZEY);

    while (!checkWinCondition(board, SIZEX, SIZEY, 'X') && !checkWinCondition(board, SIZEX, SIZEY, 'O'))
    {
        cout << "Player 1 goes x y: ";
        cin >> player1MoveX;
        cin >> player1MoveY;
        board[player1MoveY][player1MoveX] = 'X';
        if (checkWinCondition(board, SIZEX, SIZEY, 'X'))
            break;

        cout << endl;
        displayBoard(board, SIZEX, SIZEY);
        cout << endl;

        cout << "Player 2 goes: ";
        cin >> player2MoveX;
        cin >> player2MoveY;
        board[player2MoveY][player2MoveX] = 'O';
        if (checkWinCondition(board, SIZEX, SIZEY, 'O'))
            break;

        displayBoard(board, SIZEX, SIZEY);
        cout << endl;
    }
    

    displayBoard(board, SIZEX, SIZEY);
    cout << endl << endl;

    if (checkWinCondition(board, SIZEX, SIZEY, 'X'))
        cout << "Player 1 wins!" << endl;
    else
        cout << "Player 2 wins!" << endl;

    return 0;
}
