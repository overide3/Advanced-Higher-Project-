#include <sqlite3.h>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

// The test file is the compiled code. This was to keep the main compiled file free incase something went wrong. 

int main()
{
	ifstream file;
	file.open("wordlist.txt");
	//opens file
	string line;
	sqlite3 *sql;
	sqlite3_open("Database.db",&sql);
	//opens database connection
	while(getline(file,line)) // for each line in the file
	{
		int score = 10*line.size();//score equals length of the word * 10
		string query = "INSERT INTO Words VALUES(\"" + line + "\", " + to_string(score) + ");";
		char *error;
		sqlite3_exec(sql,query.c_str(),NULL,0,&error);
		//insert into table. 
	}
	sqlite3_close(sql);//close connection
}