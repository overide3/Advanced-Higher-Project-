#include "Leaderboard.h"
#include <vector>
#include <string>
#include <sqlite3.h>
#include <iostream>

std::vector<int> Leaderboard::ID;
std::vector<std::string> Leaderboard::User;
std::vector<int> Leaderboard::Score;


//This is a callback function. It takes the data from the query and outputs it into the varibles. 
int Leaderboard::callback(void* unused, int count,char **data, char **collums)
{
	for(int i = 0; i < count; i++)
	{
		switch(i)
		{
			case(0):
				ID.push_back(stoi(data[i]));
				break;
			case(1):
				User.push_back(data[i]);
				break;
			case(2):
				Score.push_back(stoi(data[i]));
				break;
			
		}
	}
	return 0;
}

// the constructor opens the connection to the database and the destructor closes it. 
//!!!! VERY IMPORTANT TO USE DESTRUCTOR !!!!
Leaderboard::Leaderboard()
{
	sqlite3_open("Database.db",&sql);
}

Leaderboard::~Leaderboard()
{
	sqlite3_close(sql);
}


//executes the query, takes results and adds it into a record system
void Leaderboard::get_leaderboard(vector<score> *scores)
{
	score temporary;
	std::vector<score> temp;
	ID.clear();
	User.clear();
	Score.clear();
	std::string query = "SELECT * FROM Leaderboard;";
	char *error;
	sqlite3_exec(sql,query.c_str(),callback,0, &error);
	for (int x = 0; x < ID.size(); x++)
	{
		temporary.user = User[x];
		temporary.score = Score[x];
		temp.push_back(temporary);
	}
	*scores = temp;
}

//takes in a value and inserts it into the leaderboard.
void Leaderboard::new_value(string user, int _score)
{
	std::string query = "INSERT INTO Leaderboard VALUES(NULL,\"" + user + "\", " + to_string(_score) + ");";
	char *error;
	sqlite3_exec(sql,query.c_str(),NULL,0, &error);
}

//insertion sort to sort leaderboard
void Leaderboard::sort_leaderboard(vector<score> * scores)
{
	std::vector<score> temporary = *scores;
	score value;
	int index = 0;
	for(int i = 1; i < temporary.size(); i++)
	{
		value = temporary[i];
		index = i;
		while(index > 0 and value.score > temporary[index - 1].score)
		{
			temporary[index] = temporary[index - 1];
			index--;
		}
		temporary[index] = value;
	}
	*scores = temporary;
}

//display the leaderboard with scores. 
void Leaderboard::display_leaderboard(vector<score> scores)
{
	std::cout << "Leaderboard:" << endl;
	for(int x = 0;x < scores.size(); x++)
	{
		cout << x + 1 << ". " << scores[x].user << " | " << scores[x].score << endl;
		if(x == 9)
		{
			break;
		}
	}
}