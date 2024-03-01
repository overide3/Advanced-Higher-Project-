#include "Words.h"
#include <iostream>
#include <sqlite3.h>
#include <string>
#include <cstdlib>
#include <chrono>
std::vector<int> Words::score;
std::vector<std::string> Words::word;

//constructor to open the database connection and to set the varibles in the class.
Words::Words()
{
	sqlite3_open("Database.db",&sql);
	import_words();
	choose_word();
	time = Word.size() + 2;
	//time = 100000000;
	start = std::chrono::high_resolution_clock::now();
}

Words::~Words()
{
	sqlite3_close(sql);	
}

//callback for sql
int Words::callback(void* unused, int count,char **data, char **collums)
{
	for(int i = 0; i < count; i++)
	{
		switch(i)
		{
			case(0):
				word.push_back(data[i]);
				break;
			case(1):
				score.push_back(std::stoi(data[i]));
				break;
		}
	}
	return 0;
}

//imports the words from the database
void Words::import_words()
{
	std::string query = "SELECT * FROM Words;";
	char *error;
	sqlite3_exec(sql,query.c_str(),callback,0, &error);
}

//choses the word used from the database. 
void Words::choose_word()
{
	int random = rand() % word.size();
	Word = word[random];
	Score = score[random];
};

//check if the class has changed and return 1 if the time has run out. 
int Words::update()
{
	stop = std::chrono::high_resolution_clock::now();
	time_used = std::chrono::duration_cast<std::chrono::seconds> (stop - start);
	if(time_used.count() >= time)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}