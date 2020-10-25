#include <iostream>
using namespace std;

//Structure containing player details
struct playerInfo
{
	char playerName[81];
	char playerID;
};

void PlayerDrop(char board[][7], playerInfo activePlayer, int gameMode); //Drops token into column | In game mode 2 removes token as well
int CheckFour(char board[][7], playerInfo activePlayer, int gameMode); // checks for win conditions in normal and wrap mode
int FullBoard(char board[][7]); //checks if board is full
void PlayerWin(playerInfo activePlayer); //Displays the winner
int restart(char board[][7]); // restarts the game
void DisplayBoard(char board[][7]); // Displays the current board state

int main()
{
	playerInfo playerOne, playerTwo;
	char board[6][7]; 
	int trueWidth = 7; // not used	 
	int trueLength = 6; //not used 
	int win, full, again, gameMode;



	cout << "Let's Play Connect 4" << endl << endl;
	cout << "Player One please enter your name: ";
	cin >> playerOne.playerName;
	playerOne.playerID = 'X';
	cout << "Player Two please enter your name: ";
	cin >> playerTwo.playerName;
	playerTwo.playerID = 'O';

	// Game start
	do
	{
		full = 0;
		win = 0;
		again = 0;
		gameMode = 1;
		cout << "Select A  Game Mode:" << endl;
		cout << "1. Normal" << endl;
		cout << "2. Wrap Around" << endl;
		cout << "3. Cascade" << endl;
		cin >> gameMode;
		
		if (gameMode != 1 && gameMode != 2 && gameMode != 3)
		{
			cout << "Enter a Valid Game Mode";
			continue;
		}
		
		do
		{
			DisplayBoard(board);
			PlayerDrop(board, playerOne, gameMode);

			win = CheckFour(board, playerOne, gameMode);
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
			if (gameMode == 3)
			{
				win = CheckFour(board, playerTwo, gameMode);
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
			}

			DisplayBoard(board);
			PlayerDrop(board, playerTwo, gameMode);

			win = CheckFour(board, playerTwo, gameMode);
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
			if (gameMode == 3)
			{
				win = CheckFour(board, playerOne, gameMode);
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
			}
			full = FullBoard(board);
			if (full == 7)
			{
				if (win == 0)
				{
					cout << "The board is full, it is a draw!" << endl;
					DisplayBoard(board);
					again = restart(board);
					if (again != 2)
						win = 1;

				}

			}
		} while (win != 1);

	} while (again != 2);


	cout << "Goodbye!" << endl;
	return 0;
}
// Checks if you can drop in the given column- ie not full column

void PlayerDrop(char board[][7], playerInfo activePlayer,int gameMode)
{
	int choice,option;
	int length, turn;
	int i = 0;
	length = 5;
	turn = 0;
	option = 1;
	cout << activePlayer.playerName << "'s Turn ";
	do
	{
	lable:
		if (gameMode == 3)
		{
			
			cout << "Do you want to add or remove a token- add(1) | remove (2)" << endl;
				cin >> option;
		}
		cout << "Please select a column between 1 and 7: ";
		cin >> choice;

		if (choice > 7 || choice < 1)
		{
			cout << "Enter a valid column number" << endl;
			
		}
		else
		{
			if (option == 2)
			{
				if (activePlayer.playerID == board[5][choice - 1])
				{
					for (i = 5; i >= 1; i--)
					{
						board[i][choice - 1] = board[i - 1][choice - 1];
					}
					board[0][choice - 1] = '*';
				}
				else
				{
					cout << "Bottom Token of the column "<<choice<<" does not belong to " << activePlayer.playerName<<endl;
					choice = 0;
				}
			}
			else
			{
				while (board[0][choice - 1] == 'X' || board[0][choice - 1] == 'O')
				{
					cout << "That column is full "<<endl;
					goto lable;
				}
				do
				{
					if (board[length][choice - 1] != 'X' && board[length][choice - 1] != 'O')
					{
						board[length][choice - 1] = activePlayer.playerID;
						turn = 1;
					}
					else
					{
						--length;
						if (length < 0) length = 0;
					}
				} while (turn != 1);
			}
		}
		

	} while (choice < 1 || choice > 7);

	
	
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

int CheckFour(char board[][7], playerInfo activePlayer, int gameMode)
{
	char XO;
	int win,a,b,c;

	XO = activePlayer.playerID;
	win = 0;
	
	for (int i = 5; i >= 0; --i)
	{
		
		for (int ix = 6; ix >= 0; --ix)
		{
			

			if (gameMode == 2)
			{
				// Diagonal right down wrapping
				if (i < 3) 
				{
					if (board[(i)][(ix) % 7] == XO &&
						board[(i + 1)][(ix + 1) % 7] == XO &&
						board[(i + 2)][(ix + 2) % 7] == XO &&
						board[(i + 3)][(ix + 3) % 7] == XO)
					{
						win = 1;
					}
				}
				// Diagonal right up wrapping
				if (board[(i)][(ix) % 7] == XO &&
					board[(i - 1)][(ix + 1) % 7] == XO &&
					board[(i - 2)][(ix + 2) % 7] == XO &&
					board[(i - 3)][(ix + 3) % 7] == XO)
				{
					win = 1;
				}
				// Horizontal wrapping		
				if (board[(i)][(ix) % 7] == XO &&
					board[(i)][(ix + 1) % 7] == XO &&
					board[(i)][(ix + 2) % 7] == XO &&
					board[(i)][(ix + 3) % 7] == XO)
				{
					win = 1;
				}

			}
			// Vertical
			if (i > 2)
			{
				if (board[i][ix] == XO &&
					board[i - 1][ix] == XO &&
					board[i - 2][ix] == XO &&
					board[i - 3][ix] == XO)
				{
					win = 1;
				}
			}

			//horizontal
			if ((ix > 2))
			{
				if (board[i][ix] == XO &&
					board[i][ix-1] == XO &&
					board[i][ix-2] == XO &&
					board[i][ix-3] == XO)
				{
					win = 1;
				}
			}

			//Diagonal 
			if(i > 2)
			{
				// Left up
				if (ix > 2 )
				{
					if (board[i][ix] == XO &&
						board[i - 1][ix-1] == XO &&
						board[i - 2][ix-2] == XO &&
						board[i - 3][ix-3] == XO)
					{
						win = 1;
					}
				}
				// Right Up
				if (ix < 4)
				{
					if (board[i][ix] == XO &&
						board[i - 1][ix + 1] == XO &&
						board[i - 2][ix + 2] == XO &&
						board[i - 3][ix + 3] == XO)
					{
						win = 1;
					}
				}
			
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
