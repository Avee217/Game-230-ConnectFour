#include <iostream>
using namespace std;
//Structure containing player details
struct playerInfo
{
	char playerName[81];
	char playerID;
};

int PlayerDrop(char board[][7], playerInfo activePlayer);
int CheckFour(char board[][7], playerInfo activePlayer);
int FullBoard(char board[][7]);
void PlayerWin(playerInfo activePlayer);
int restart(char board[][7]);
void DisplayBoard(char board[][7]);

int main()
{
	playerInfo playerOne, playerTwo;
	char board[6][7]; // need to change values for better board-too big
	int trueWidth = 7; // not used	 
	int trueLength = 6; //not used 
	int dropChoice, win, full, again, gameMode;

	gameMode = 1;

	cout << "Let's Play Connect 4" << endl << endl;
	cout << "Player One please enter your name: ";
	cin >> playerOne.playerName;
	playerOne.playerID = 'X';
	cout << "Player Two please enter your name: ";
	cin >> playerTwo.playerName;
	playerTwo.playerID = 'O';

	//Make loop
	cout << "Select A  Game Mode:" << endl;
	cout << "1. Normal" << endl;
	cout << "2. Wrap Around" << endl;
	cout << "3. Cascade" << endl;
	cin >> gameMode;

	full = 0;
	win = 0;
	again = 0;
	do
	{
		DisplayBoard(board);
		PlayerDrop(board, playerOne);


		win = CheckFour(board, playerOne);
		if (win == 1)
		{
			DisplayBoard(board);
			PlayerWin(playerOne);
			again = restart(board);
			if (again == 2)
			{
				break;
			}
			else
				continue;
		}

		DisplayBoard(board);
		PlayerDrop(board, playerTwo);


		win = CheckFour(board, playerTwo);
		if (win == 1)
		{
			DisplayBoard(board);
			PlayerWin(playerTwo);
			again = restart(board);
			if (again == 2)
			{
				break;
			}
			else
				continue;
		}
		// do this again
		full = FullBoard(board);
		if (full == 7)
		{
			if (win == 0)
			{
				cout << "The board is full, it is a draw!" << endl;
				again = restart(board);
			}

		}

	} while (again != 2);


	cout << "Goodbye!" << endl;
	return 0;
}
// Checks if you can drop in the given column- ie not full column

int PlayerDrop(char board[][7], playerInfo activePlayer)
{
	int dropChoice;
	int length, turn;
	length = 5;
	turn = 0;
	cout << activePlayer.playerName << "'s Turn ";
	do
	{

		cout << "Please select a column between 1 and 7: ";
		cin >> dropChoice;
		if (dropChoice > 7 || dropChoice < 1)
		{
			cout << "Enter a valid column number" << endl;
		}

		while (board[1][dropChoice] == 'X' || board[1][dropChoice] == 'O')
		{
			cout << "That column is full, please select a new column: ";
			cin >> dropChoice;
		}

	} while (dropChoice < 1 || dropChoice > 7);

	dropChoice -= 1;



	do
	{
		if (board[length][dropChoice] != 'X' && board[length][dropChoice] != 'O')
		{
			board[length][dropChoice] = activePlayer.playerID;
			turn = 1;
		}
		else
			--length;
	} while (turn != 1);
}

void DisplayBoard(char board[][7])
{
	int rows = 6, columns = 7, i, ix;
	cout << "\t1\t2\t3\t4\t5\t6\t7" << endl;

	for (i = 0; i < rows; i++)
	{
		cout << "|\t";
		for (ix = 0; ix < columns; ix++)
		{
			if (board[i][ix] != 'X' && board[i][ix] != 'O')
				board[i][ix] = '*';

			cout << board[i][ix] << "\t";

		}

		cout << "|" << endl;
	}

}

int CheckFour(char board[][7], playerInfo activePlayer)
{
	char XO;
	int win;

	XO = activePlayer.playerID;
	win = 0;

	for (int i = 5; i >= 0; --i)
	{

		for (int ix = 6; ix >= 0; --ix)
		{
			// Diagonal 
			if (board[i][ix] == XO &&
				board[i - 1][ix - 1] == XO &&
				board[i - 2][ix - 2] == XO &&
				board[i - 3][ix - 3] == XO)
			{
				win = 1;
			}

			// Left
			if (board[i][ix] == XO &&
				board[i][ix - 1] == XO &&
				board[i][ix - 2] == XO &&
				board[i][ix - 3] == XO)
			{
				win = 1;
			}

			// Vertical	
			if (board[i][ix] == XO &&
				board[i - 1][ix] == XO &&
				board[i - 2][ix] == XO &&
				board[i - 3][ix] == XO)
			{
				win = 1;
			}
			// Diagonal left	
			if (board[i][ix] == XO &&
				board[i - 1][ix + 1] == XO &&
				board[i - 2][ix + 2] == XO &&
				board[i - 3][ix + 3] == XO)
			{
				win = 1;
			}
			// Right		
			if (board[i][ix] == XO &&
				board[i][ix + 1] == XO &&
				board[i][ix + 2] == XO &&
				board[i][ix + 3] == XO)
			{
				win = 1;
			}
		}

	}

	return win;
}

int FullBoard(char board[][7])
{
	int full;
	full = 0;
	for (int i = 0; i <= 6; i++)
	{
		if (board[0][i] != '*')
			++full;
	}

	return full;
}

void PlayerWin(playerInfo activePlayer)
{
	cout << endl << activePlayer.playerName << " Connected Four, You Win!" << endl;
}

int restart(char board[][7])
{
	char ch;
	int restart;
	restart = 0;

	do
	{
		cout << "Would you like to restart? Yes(y) or  No(n): ";
		cin >> ch;
		if (ch == 'y') restart = 1;
		else if (ch == 'n') restart = 2;
		else cout << "Enter a valid character  please" << endl;
		if (restart == 1)
		{
			for (int i = 0; i <= 5; i++)
			{
				for (int ix = 0; ix <= 6; ix++)
				{
					board[i][ix] = '*';
				}
			}
		}
	} while (restart == 0);
	return restart;
}
