#pragma once
#include <string>
#include <sqlite3.h>
#include <vector>
#include <chrono>
class Words
{
	private:
	sqlite3 *sql;
	static std::vector<int> score;
	static std::vector<std::string> word;
	float time;
	void choose_word();
	void import_words();
	static int callback(void* unused, int count,char **data, char **collums);
	std::chrono::time_point<std::chrono::high_resolution_clock> start;
std::chrono::time_point<std::chrono::high_resolution_clock> stop;
	std::chrono::duration<float,std::ratio<1>> time_used;
	public:
	Words();
	~Words();
	std::string Word;
	int Score;
	int update();
};