#pragma once
#include <vector>
#include <sqlite3.h>
#include <string>
using namespace std;

class Leaderboard
{
	private:
	sqlite3* sql;
	static int callback(void* unused, int count,char **data, char **collums);
	static vector<int> ID;
	static vector<string> User;
	static vector<int> Score;

	public:
	struct score
	{
		string user;
		int score;
	};
	Leaderboard();
	~Leaderboard();
	void get_leaderboard(vector<score> *scores);
	void new_value(string user, int _score);
	void sort_leaderboard(vector<score> *scores);
	void display_leaderboard(vector<score> scores);
};