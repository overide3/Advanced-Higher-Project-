#pragma once
#include "Words.h"
#include "Leaderboard.h"
#include <vector> 
class Engine
{
	private:
	static char u_input();
	static int check(char character);
	static std::vector<Words> Array_of_words;
	static std::vector<char> Input;
	static std::vector<Leaderboard::score> scores; 
	Leaderboard leaderboard;
	static int lives;
	static int score;
	static int reduce_lives();
	static int input();
	int update();
	void display();
	void leaderboard_display();
	void leaderboard_insert(std::string user);
	public:
	Engine();
	void Run();
	void Reset();
	~Engine();
};