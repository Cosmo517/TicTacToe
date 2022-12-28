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

bool isBoardFilled(char** board, int SIZEX, int SIZEY)
{
    for (int i = 0; i < SIZEY; i++)
        for (int j = 0; j < SIZEX; j++)
            if (board[i][j] == ' ')
                return false;
    return true;
}

int minimax(char** board, int SIZEX, int SIZEY, int depth, bool maximizingPlayer, char markMaximizing, int difficulty)
{
    char notMaximizing = ' ';
    if (markMaximizing == 'X')
        notMaximizing = 'O';
    else
        notMaximizing = 'X';

    if (checkWinCondition(board, SIZEX, SIZEY, markMaximizing))
        return 1;
    else if (checkWinCondition(board, SIZEX, SIZEY, notMaximizing))
        return -1;
    else if (isBoardFilled(board, SIZEX, SIZEY) || depth == difficulty)
        return 0;

    if (maximizingPlayer)
    {
        int bestScore = -INT_MAX;
        for (int i = 0; i < SIZEY; i++)
        {
            for (int j = 0; j < SIZEX; j++)
            {
                if (board[i][j] == ' ')
                {
                    board[i][j] = markMaximizing;
                    int score = minimax(board, SIZEX, SIZEY, depth + 1, false, markMaximizing, difficulty);
                    board[i][j] = ' ';
                    bestScore = max(score, bestScore);
                }

            }
        }
        return bestScore;
    }
    else
    {
        int bestScore = INT_MAX;
        for (int i = 0; i < SIZEY; i++)
        {
            for (int j = 0; j < SIZEX; j++)
            {
                if (board[i][j] == ' ')
                {
                    board[i][j] = notMaximizing;
                    int score = minimax(board, SIZEX, SIZEY, depth + 1, true, markMaximizing, difficulty);
                    board[i][j] = ' ';
                    bestScore = min(score, bestScore);
                }
            }
        }
        return bestScore;
    }
}


void bestMove(char** board, int SIZEX, int SIZEY, int markPlayed, int difficulty)
{
    int bestScore = -INT_MAX;
    int bestMove[2] = { 0, 0 };
    for (int i = 0; i < SIZEY; i++)
    {
        for (int j = 0; j < SIZEX; j++)
        {
            if (board[i][j] == ' ')
            {
                board[i][j] = markPlayed;
                int score = minimax(board, SIZEX, SIZEY, 0, false, markPlayed, difficulty);
                board[i][j] = ' ';
                if (score > bestScore)
                {
                    bestScore = score;
                    bestMove[0] = j;
                    bestMove[1] = i;
                }
            }
        }
    }
    board[bestMove[1]][bestMove[0]] = markPlayed;
}

int main()
{
    int SIZEX = 3;
    int SIZEY = 3;
    int userDifficulty = 2;
    int userPlayer = 1;
    char userMark = 'O';
    char computerMark = 'X';

    cout << "Enter size of board (length): ";
    cin >> SIZEX;
    cout << endl << "Enter size of board (height): ";
    cin >> SIZEY;
    cout << endl;
    cout << "Do you want to be player 1 (X) or player 2 (O)? Type 1 or 2: ";
    cin >> userPlayer;

    if (userPlayer == 1)
    {
        userMark = 'X';
        computerMark = 'O';
    }
    else
    {
        userMark = 'O';
        computerMark = 'X';
    }

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



    int playerMoveX = 0;
    int playerMoveY = 0;

    cout << "Player 1 is X" << endl << "Player 2 is O" << endl;
    cout << "Enter x,y coordinates. 0,0 is top left. X increases to the right. Y increases downwards" << endl;

    displayBoard(board, SIZEX, SIZEY);

    while (!checkWinCondition(board, SIZEX, SIZEY, 'X') && !checkWinCondition(board, SIZEX, SIZEY, 'O') && !isBoardFilled(board, SIZEX, SIZEY))
    {
        if (userPlayer == 1)
        {
            cout << "Player 1 goes x y: ";
            cin >> playerMoveX;
            cin >> playerMoveY;
            board[playerMoveY][playerMoveX] = userMark;
            cout << endl;

            if (playerMoveX == 'q' || playerMoveY == 'q')
                break;

            if (checkWinCondition(board, SIZEX, SIZEY, userMark))
            {
                cout << "Player 1 Wins!" << endl << endl;
                displayBoard(board, SIZEX, SIZEY);
                break;
            }
            else if (isBoardFilled(board, SIZEX, SIZEY))
            {
                cout << "Draw!" << endl << endl;
                displayBoard(board, SIZEX, SIZEY);
                break;
            }

            displayBoard(board, SIZEX, SIZEY);
            cout << "AI goes." << endl;
            bestMove(board, SIZEX, SIZEY, computerMark, userDifficulty + 2);
            cout << endl;

            if (checkWinCondition(board, SIZEX, SIZEY, computerMark))
            {
                cout << "The AI Wins!" << endl << endl;
                displayBoard(board, SIZEX, SIZEY);
                break;
            }
            else if (isBoardFilled(board, SIZEX, SIZEY))
            {
                cout << "Draw!" << endl << endl;
                displayBoard(board, SIZEX, SIZEY);
                break;
            }

            cout << endl;
            displayBoard(board, SIZEX, SIZEY);
            cout << endl;
        }
        else
        {
            cout << "AI goes";
            bestMove(board, SIZEX, SIZEY, 'X', userDifficulty + 2);
            cout << endl;
            if (checkWinCondition(board, SIZEX, SIZEY, 'X'))
            {
                break;
            }
            else if (isBoardFilled(board, SIZEX, SIZEY))
            {
                cout << "Draw!" << endl << endl;
                displayBoard(board, SIZEX, SIZEY);
                break;
            }

            cout << endl;
            displayBoard(board, SIZEX, SIZEY);
            cout << endl;

            cout << "Player 2 goes x y: ";
            cin >> playerMoveX;
            cin >> playerMoveY;
            if (playerMoveX == 'q' || playerMoveY == 'q')
                break;
            board[playerMoveY][playerMoveX] = 'O';
            if (checkWinCondition(board, SIZEX, SIZEY, 'O'))
            {
                break;
            }
            else if (isBoardFilled(board, SIZEX, SIZEY))
            {
                cout << "Draw!" << endl << endl;
                displayBoard(board, SIZEX, SIZEY);
                break;
            }
            displayBoard(board, SIZEX, SIZEY);
            cout << endl;
        }
    }

    return 0;
}
