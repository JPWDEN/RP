//  assessment.h
//  Solution to Return Path's interview test, by Josh Walker.

#pragma once

#include <fstream>
#include <vector>
#ifdef __linux__
#include <dirent.h>
#elif _WIN32
#include <windows.h>
#endif

using namespace std;

typedef struct EMAIL_DATA
{
	string sTo;
	string sFrom;
	string sDate;
	string sSubject;
	string sMID;
	EMAIL_DATA(string to, string from, string date, string subject, string mid) : 
		sTo(to), sFrom(from), sDate(date), sSubject(subject), sMID(mid) {}
} EMAIL_DATA;

class Parser
{
public:
	Parser();
	~Parser();

#ifdef _WIN32
	bool ParseDirectoryWin(string sInput);		//Grab files from specified directory--Linux
#else
	bool ParseDirectory(string sInput);	//Grab files from specified directory--Windows
#endif
	bool ParseFile();						//Process each file for requested data
	void PrintData(bool bFile = true);		//Print email data contained in memory

private:
	ifstream			m_inFile;		//Used for file read operations
	ofstream			m_outFile;		//Output file for writing requested data
	vector<EMAIL_DATA>	*m_arEmailData;	//Holding space in memory for requested data
};
