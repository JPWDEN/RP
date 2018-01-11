//  assessment.h
//  Solution to Return Path's interview test, by Josh Walker.

#pragma once

#include <fstream>
#include <vector>
#include <dirent.h>
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

	bool ParseDirectory(string sInput);	//Grab files from specified directory--Windows
	bool ParseFile();						//Process each file for requested data
	void PrintData();						//Print email data contained in memory

private:
	ifstream			m_inFile;		//Used for file read operations
	ofstream			m_outFile;		//Output file for writing requested data
	vector<EMAIL_DATA>	*m_arEmailData;	//Holding space in memory for requested data
};
