#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
#include "Engine.h"
#include "Leaderboard.h"
using namespace std;

int main()
{
	srand(time(0));
	Engine eng;
	Leaderboard board;
	vector <Leaderboard::score> Leaderboard;
	bool exit = false;
	string empty;
	//game loop
	while(!exit)
	{
		system("clear");
		string user_input;
		int choice = 0;
		cout << "Menu:" << endl;
		cout << "1.Play game" << endl;
		cout << "2.Leaderboard" << endl;
		cout << "3.How to play" << endl;
		cout << "4.Exit" << endl;
		cout << "Enter number choice:" << endl;
		cout << ">>";
		getline(cin,user_input);
		if(int(user_input[0]) >= 48 && int(user_input[0]) <= 57 && user_input.size() == 1)
		{
			choice = stoi(user_input);
		}
		system("clear");
		switch(choice)
		{
		case(1):
			eng.Run();
			eng.Reset();
			cout << "Press enter to continue..." << endl;
			getline(cin,empty);
			break;
		case(2):
			board.get_leaderboard(&Leaderboard);
			board.display_leaderboard(Leaderboard);
			cout << "Press enter to continue..." << endl;
			getline(cin,empty);
			break;
		case(3):
			cout << "At the top of the screen will be the words you have to type." << endl;
			cout << "If you miss a letter or miss input a letter you will lose a life." << endl;
			cout << "Each word has a time limit. If they run out of time then you will lose a life and the word will change." << endl;
			cout << "If you complete a word in the time then you score points based on how long the word is." << endl;
			cout << "Have fun!" << endl;
			cout << "Press enter to continue..." << endl;
			getline(cin,empty);
			break;
		case(4):
			exit = true;
			break;
		default:
			cout << "Invalid input. Please try again." << endl;
			cout << "Press enter to continue..." << endl;
			getline(cin,empty);
			break;
		}
	}
	cout << "Thank you for playing." << endl;
	eng.~Engine();
	board.~Leaderboard();
}

