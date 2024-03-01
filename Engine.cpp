#include "Engine.h"
#include <iostream>
#include <future>
#include <chrono>
#include <string>
#include "Leaderboard.h"
#include "Words.h"
using namespace std;

vector<char> Engine::Input;
vector <Words> Engine::Array_of_words;
vector<Leaderboard::score> Engine::scores;
int Engine::lives;
int Engine::score;


//this takes an input without having to press enter. 
char Engine::u_input()
{
	char input;
	system("stty raw");
	cin >> input;
	system("stty cooked");
	return input;
}

//a simple check lives function
int Engine::reduce_lives()
{
	lives--;
	if(lives == 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

//checks the given character against the word that is currently selected. returns 1 if sucessful, 2 if the word is completed and 0 if failed. 
int Engine::check(char character)
{
	int test = 0;
	string guess(Input.begin(),Input.end());
	guess = guess + character;
	for(int index = 0; index < Array_of_words.size(); index++)
	{
		if(Array_of_words[index].Word.substr(0,guess.size()) == guess)
		{
			test = 1;
			if(Array_of_words[index].Word == guess)
			{
				test = 2;
				score += Array_of_words[index].Score;
				Array_of_words[index].~Words();
				Array_of_words[index] = Words();
			}
			break;
		}
	}
	
	return test;
}

//takes the input from the console using the u_input and then checks it and reduces lives. returns 1 if the input is succesful and there needs to be a display update, 2 if a word was completed and 0 if they run out of lives.
int Engine::input()
{
	char in = u_input();
	int test = check(in);
	if(test == 1)
	{
		Input.push_back(in);
		return 1;
	}
	if(test == 2)
	{
		Input.clear();
		return 2;
	}
	else
	{
		int x = reduce_lives();
		if(x == 0)
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}
}

//returns 0 when nothing changes. returns 1 when a word expires and needs to update the console. returns 2 if they run out of lives. 
int Engine::update()
{
	int y = 0;
	for(int x = 0; x < Array_of_words.size();x++)
	{
		int test = Array_of_words[x].update();
		if(test == 1)
		{
			int test2 = reduce_lives();
			if(test2 == 0)
			{
				Array_of_words[x].~Words();
				Array_of_words[x] = Words();
				y = 1;
			}
			else
			{
				y = 2;
				break;
			}
		}
	}
	return y;
}

//clears the console and then displays the layout. 
void Engine::display()
{
	system("clear");
	cout << "Words:" << endl << " | ";
	for(int x = 0; x < Array_of_words.size(); x++)
	{
		cout << Array_of_words[x].Word << " | ";
	}
	cout << endl;
	cout << "Lives: " << lives <<  "   Score:" << score <<  endl;
	cout << "Input:" << endl;
	cout << ">> ";
	for(int x = 0; x < Input.size(); x++)
	{
		cout << Input[x];
	}
}

//initiates the engine object and sets up leaderboard and the lives.
Engine::Engine()
{
	lives = 3;
	leaderboard.get_leaderboard(&scores);
	leaderboard.sort_leaderboard(&scores);
}

//closes off final connections
Engine::~Engine()
{
	leaderboard.~Leaderboard();
	for(int index = 0; index > Array_of_words.size();index++)
	{
		Array_of_words[index].~Words();
	}
}
//displays the leaderboard 
void Engine::leaderboard_display()
{
	leaderboard.display_leaderboard(scores);
}

//inserts a new value and then sorts it. 
void Engine::leaderboard_insert(string user)
{
	leaderboard.new_value(user,score);
	leaderboard.sort_leaderboard(&scores);
}

//the main part of the game. 
void Engine::Run()
{
	for(int x = 0; x < 3; x++)
	{
		Array_of_words.push_back(Words());
	}
	bool run = true;
	while(run)
	{
		display();
		auto future = async(input);
		auto status = future.wait_for(chrono::nanoseconds(1));
		while(status != future_status::ready)
		{
			int test = update();
			if(test == 1)
			{
				display();
			}
			else if(test  == 2)
			{
				run = false;
				break;
			}
			status = future.wait_for(chrono::nanoseconds(1));
		}
		if(run)
		{
			int input_return = future.get();
			if(input_return == 0)
			{
				run = false;
			}
		}
		else
		{
			status = future.wait_for(chrono::nanoseconds(1));
			cout << endl;
			cout << "Press type something and press enter..." << endl;
			if(status == future_status::ready)
			{
				future.get();
			}
			else
			{
				u_input();
			}
			cout << "Press Enter to continue..." << endl;
			string blank;
			getline(cin,blank);
		}
	}
	system("clear");
	cout << "Game over" << endl;
	cout << "Score: " << score << endl;
	cout << "Press enter to continue..." << endl;
	cin.ignore();
	system("clear");
	cout << "Enter Username:" << endl;
	cout << ">>";
	string name;
	getline(cin,name);
	system("clear");
	leaderboard_insert(name);
	Leaderboard::score temp;
	temp.user = name;
	temp.score = score;
	scores.push_back(temp);
	leaderboard.sort_leaderboard(&scores);
	leaderboard_display();
}

void Engine::Reset()
{
	lives = 3;
	leaderboard.get_leaderboard(&scores);
	leaderboard.sort_leaderboard(&scores);
	Array_of_words.clear();
}