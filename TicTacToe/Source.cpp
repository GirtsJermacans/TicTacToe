#include <iostream>  // io
#include <stdlib.h>  // random number
#include <Windows.h> // countdown
#include <iomanip>   // allows 'getline'
#include <string>
using namespace std;
struct player
{
	string name;
	string xOrO;
};
void pickNames(player&, player&);
void startGame(bool&);
void displayBoard(string[][3], int);
void checkAndUpdateBoard(string[][3], string, player, bool&, int&);
void checkWinner(string[][3], player, bool&, bool&);
void announceWinner(bool, bool, bool, player, player);
void playAgain(bool&, bool&, bool&, bool&);
void pickTurn(bool&, player);
void checkDraw(int, bool&, bool&);
void computerMove(string&, string[][3]);

int main()
{
	player human;
	player computer;
	const string x = "X";
	const string o = "O";
	bool gameOn = true;
	bool gameInProgress = false;
	bool player1Winner = false;
	bool computerWinner = false;
	bool draw = false;
	bool turn = true;
	string insertNumber;
	const int row = 3;
	const int col = 3;

	// prompt for player names
	pickNames(human, computer); 

	// main flow of the program
	while (gameOn) 
	{
		int attempts = 0; // determines draw
		string mainBoard[row][col] = { { "1", "2", "3" }, // main board
		{ "4", "5", "6" },
		{ "7", "8", "9" } };
		pickTurn(turn, human);

		if (turn)
		{
			cout << "Hi " << human.name << ", you are the second player (which is 'O')." << endl;
			human.xOrO = o;
			computer.xOrO = x;
		}
		else if (!turn)
		{
			cout << "Hi " << human.name << ", you are the first player (which is 'X')." << endl;
			human.xOrO = x;
			computer.xOrO = o;
		}

		startGame(gameInProgress); // Starts the countdown
		while (gameInProgress)
		{
			displayBoard(mainBoard, col);
			if (turn)
			{
				computerMove(insertNumber, mainBoard);
				cout << computer.name << " turn: ";
				Sleep(1000); // .. computer "thinks" :)
				cout << insertNumber;
				Sleep(1000); // .. computer "IsAlive" :)
				checkAndUpdateBoard(mainBoard, insertNumber, computer, turn, attempts); 
				checkWinner(mainBoard, computer, gameInProgress, computerWinner);
				checkDraw(attempts, draw, gameInProgress);
			}
			else if (!turn)
			{
				cout << human.name << " turn: ";
				cin >> insertNumber;
				checkAndUpdateBoard(mainBoard, insertNumber, human, turn, attempts);
				checkWinner(mainBoard, human, gameInProgress, player1Winner);
				checkDraw(attempts, draw, gameInProgress);
			}
		}
		displayBoard(mainBoard, col);
		announceWinner(computerWinner, player1Winner, draw, computer, human); // only if condition is met (boolean value)
		playAgain(gameOn, player1Winner, computerWinner, draw); // only if condition is met

	}
	cout << "\n\nThank You For Playing " + human.name + "! \n\nGAME OVER\n\n";
	return 0;
}

// selects names
void pickNames(player &player1, player &player2)
{
	cout << "Hello! Welcome to Noughts and Crosses game." << endl;

	cout << "Insert your name: ";
	cin.ignore(0); // helps with buffer issue in case player wants to insert more than one word for his name
	getline(cin, player1.name);

	cout << "\nInsert computer name: ";
	getline(cin, player2.name);
	cout << "\n";
}

// decides who starts the game
void pickTurn(bool &whoFirst, player humanPlayer)
{
	string answer;
	const string bePlayer1 = "1";
	const string bePlayer2 = "2";
	cout << "Hi " << humanPlayer.name << "\n\nTO GO FIRST ---- PRESS '1'\n\nTO GO SECOND --- PRESS '2'" << endl;
	cin >> answer;
	while ((answer != bePlayer1) && (answer != bePlayer2)) // validation
	{
		system("CLS");
		cout << humanPlayer.name << ", What Are You Doing?\nWrong Input. Please Try Again.\n" << endl;
		cout << "TO GO FIRST ---- PRESS '1'\n" << endl;
		cout << "TO GO SECOND --- PRESS '2'\n" << endl;
		cin >> answer;
	}
	if (answer == bePlayer1)
		whoFirst = false;
	else if (answer == bePlayer2)
		whoFirst = true;
	system("CLS");
}

// starts the game
void startGame(bool &game)
{
	cout << "Lets start the game!\n\n\n";

	cout << "Game will start in 4\n\n";
	for (int i = 3; i>0; i--) // countdown ---> 4, 3, 2, 1
	{
		Sleep(1000); // creates interval into 1 sec
		cout << i << "\n\n";
	}
	Sleep(1000);
	system("CLS");
	game = true; // initiates the gameplay
}

// displays the main board
void displayBoard(string array1[][3], int limit)
{
	cout << "\n";
	for (int i = 0; i<limit; i++)
	{
		cout << "\t\t";
		for (int j = 0; j<limit; j++)
		{
			if (j<2)
				cout << array1[i][j] + " | ";
			if (j == 2 && i<2)
			{
				cout << array1[i][j] << endl;
				cout << "\t\t=========" << endl;
			}
			else if (j == 2 && i == 2)
				cout << array1[i][j] << endl;
		}
	}
	cout << "\n";
}

// updates board and checks if input is valid
void checkAndUpdateBoard(string array_1[][3], string input, player anyPlayer, bool &turn1, int &addAttempt)
{
	int check = 0;
	for (int i = 0; i<3; i++)
		for (int j = 0; j<3; j++)
		{
			if (array_1[i][j] == input) // checks if selected square is available
			{
				array_1[i][j] = anyPlayer.xOrO;
				turn1 = !turn1; // sets next players turn
				check += 1; // provides info for next conditions - input was valid
			}
		}
	system("CLS");
	if (check == 0)
		cout << "Wrong Input! Try Again and Use The Valid Range." << endl;
	else
	{
		cout << anyPlayer.name + " picked number: " << input << endl;
		addAttempt += 1; // if attempts reach 9, then it is a definite draw
	}

	check = 0;
}

// checks for a winning combo
void checkWinner(string array_1[][3], player anyPlayer, bool &continueGame, bool &updateWinner)
{
	int winningCombination = 0;

	for (int firstRow = 0; firstRow<3; firstRow++) // checks if the first row is a winning combo
	{
		if (array_1[0][firstRow] == anyPlayer.xOrO)
			winningCombination += 1; // needs to be +3 for a win combo
	}
	if (winningCombination == 3)
	{
		continueGame = false; // breaks the game continuing loop
		updateWinner = true; // informs the winner
	}
	else
		winningCombination = 0;


	for (int secondRow = 0; secondRow<3; secondRow++) // checks if the second row is a winning combo
	{
		if (array_1[1][secondRow] == anyPlayer.xOrO) // checks for the specific string within array and if it is equal to specific player symbol ( X or O )
			winningCombination += 1; // if it is - adds 1 - need 3 for it to be considered a win
	}
	if (winningCombination == 3)
	{
		continueGame = false; // the same as before
		updateWinner = true; // the same as before
	}
	else
		winningCombination = 0; // the same as before


	for (int thirdRow = 0; thirdRow<3; thirdRow++) // checks if the third row is a winning combo
	{
		if (array_1[2][thirdRow] == anyPlayer.xOrO) // checks for the specific string within array and if it is equal to specific player symbol ( X or O )
			winningCombination += 1; // if it is - adds 1 - need 3 for it to be considered a win
	}
	if (winningCombination == 3)
	{
		continueGame = false; // the same as before
		updateWinner = true; // the same as before
	}
	else
		winningCombination = 0; // the same as before


	for (int firstCol = 0; firstCol<3; firstCol++) // checks if the first column is a winning combo
	{
		if (array_1[firstCol][0] == anyPlayer.xOrO) // checks for the specific string within array and if it is equal to specific player symbol ( X or O )
			winningCombination += 1; // if it is - adds 1 - need 3 for it to be considered a win
	}
	if (winningCombination == 3)
	{
		continueGame = false; // the same as before
		updateWinner = true; // the same as before
	}
	else
		winningCombination = 0; // the same as before


	for (int secondCol = 0; secondCol<3; secondCol++) // checks if the second column is a winning combo
	{
		if (array_1[secondCol][1] == anyPlayer.xOrO) // checks for the specific string within array and if it is equal to specific player symbol ( X or O )
			winningCombination += 1; // if it is - adds 1 - need 3 for it to be considered a win
	}
	if (winningCombination == 3)
	{
		continueGame = false; // the same as before
		updateWinner = true; // the same as before
	}
	else
		winningCombination = 0; // the same as before


	for (int thirdCol = 0; thirdCol<3; thirdCol++) // checks if the third column is a winning combo
	{
		if (array_1[thirdCol][2] == anyPlayer.xOrO) // checks for the specific string within array and if it is equal to specific player symbol ( X or O )
			winningCombination += 1; // if it is - adds 1 - need 3 for it to be considered a win
	}
	if (winningCombination == 3)
	{
		continueGame = false; // the same as before
		updateWinner = true; // the same as before
	}
	else
		winningCombination = 0; // the same as before


	if (array_1[0][0] == anyPlayer.xOrO)  // checks diagonal is a winning combo going from top-left - through centre - to bottom-right
		winningCombination += 1;
	if (array_1[1][1] == anyPlayer.xOrO)
		winningCombination += 1;
	if (array_1[2][2] == anyPlayer.xOrO)
		winningCombination += 1;

	if (winningCombination == 3)
	{
		continueGame = false; // the same as before
		updateWinner = true; // the same as before
	}
	else
		winningCombination = 0; // the same as before


	if (array_1[0][2] == anyPlayer.xOrO)  // checks diagonal is a winning combo going from top-right - through centre - to bottom-left
		winningCombination += 1;
	if (array_1[1][1] == anyPlayer.xOrO)
		winningCombination += 1;
	if (array_1[2][0] == anyPlayer.xOrO)
		winningCombination += 1;

	if (winningCombination == 3)
	{
		continueGame = false; // the same as before
		updateWinner = true; // the same as before
	}
	else
		winningCombination = 0; // the same as before
}

// checks for the draw
void checkDraw(int isItDraw, bool &noMoreMoves, bool &continueGame)
{
	if (isItDraw == 9) // if moves together equal 9
	{
		noMoreMoves = true;
		continueGame = false;
	}
	else
		noMoreMoves = false; // game carries on
}

// announces the winner - which ever bool value is true
void announceWinner(bool winComp, bool winP1, bool P1DrawComp, player compPlayer, player humPlayer)
{
	if (winComp)
		cout << compPlayer.name << " has won the game! It is Unbelievable!\n" << endl;
	else if (winP1)
		cout << humPlayer.name << " has won the game! It is Unbelievable!\n" << endl;
	else if (P1DrawComp)
		cout << "It Is a Draw!! Well Played Both Of You!\n" << endl;
}

// either exits program or plays again - resets boolean values
void playAgain(bool &playAgain, bool &resetHum, bool &resetComp, bool &resetDraw)
{
	string answer;
	const string play = "1";
	const string exit = "2";
	cout << "PLAY AGAIN ------- PRESS '1' \n\nOR\n\nEXIT THE GAME ---- PRESS '2'" << endl;
	cin >> answer;

	while ((answer != play) && (answer != exit)) // validation
	{
		system("CLS");
		cout << "What Are You Doing?\nWrong Input. Please Try Again.\n" << endl;
		cout << "PLAY AGAIN ------- PRESS '1' \n\nOR\n\nEXIT THE GAME ---- PRESS '2'" << endl;
		cin >> answer;
	}

	if (answer == play) // plays again
	{
		playAgain = true;
		resetHum = false;
		resetComp = false;
		resetDraw = false;
		system("CLS");
	}
	else if (answer == exit) // exits program
		playAgain = false;
}

// computer move - little manual int to string convertion just for fun :)))
void computerMove(string &convertToString, string array_1[][3])
{
	bool noGoodInput = false; // will loop until computer picks a good input
	while (!noGoodInput)
	{
		int computerNumber = 1 + rand() % 9; // gets random number as computer input
		if (computerNumber == 1)
			convertToString = "1"; // this is fun
		else if (computerNumber == 2)
			convertToString = "2";
		else if (computerNumber == 3)
			convertToString = "3";
		else if (computerNumber == 4)
			convertToString = "4"; // not so fun...
		else if (computerNumber == 5)
			convertToString = "5";
		else if (computerNumber == 6)
			convertToString = "6";
		else if (computerNumber == 7)
			convertToString = "7";
		else if (computerNumber == 8)
			convertToString = "8"; // seriously......
		else if (computerNumber == 9)
			convertToString = "9"; // to_string() next time, huh?? :)))

		for (int i = 0; i<3; i++) // checks if input is valid
			for (int j = 0; j<3; j++)
			{
				if (array_1[i][j] == convertToString)
					noGoodInput = true;
			}
	}
}
