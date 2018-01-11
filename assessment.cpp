//  assessment.cpp
//  Solution to Return Path's interview test, by Josh Walker.

#include <iostream>
#include <string>
#include <sys/stat.h>
#include <cstring>
#include "assessment.h"

using namespace std;

Parser::Parser()
{
	m_arEmailData = new vector<EMAIL_DATA>();
}

Parser::~Parser()
{
	if (m_inFile.is_open())
		m_inFile.close();
	delete m_arEmailData;
}

bool Parser::ParseDirectory(string sInput)
{
	string sDir;
	m_outFile.open("log");
	struct dirent *dirp;
	struct stat fileStat;
	if (sInput == "")
		sDir = "smallset/";
	else
	{
		if (sInput[sInput.size() - 1] != '/')
			sDir = sInput + '/';
	}
	DIR *dPath = opendir(sDir.c_str());
	cout << "sDir:  " << sDir << endl;
	if (dPath == NULL)
	{
		cout << "Error accessing directory" << endl;
		return false;
	}
	while (dirp = readdir(dPath))
	{
		if (S_ISDIR(fileStat.st_mode) || dirp->d_name[0] == '.')
			continue;
		string sPath = sDir + dirp->d_name;
		m_inFile.open(sPath.c_str());
		if (m_inFile)
		{
			bool bSuccess = ParseFile();
			if (!bSuccess)
				cout << "Error parsing " << sPath << endl;
			m_inFile.close();
		}
		else
			cout << dirp->d_name  << " error:  " << strerror(errno) << endl;
	}
	return true;
}

//Parse info out of each file.  Maybe order of data can vary from server to server, so
//remain generic about the order of information in the header.  Returns false if a given field was not found
bool Parser::ParseFile()
{
	string sLine = "";
	string sTo = "", sFrom = "", sDate = "", sSubject = "", sMID = "";
	bool bAllFound = false;
	bool bCheckSubject = false;
	while (getline(m_inFile, sLine) && !bAllFound)
	{
		if (sLine.size() < 3 && !bCheckSubject)
			continue;

		string sTemp3 = sLine.substr(0, 3), sTemp5 = sLine.substr(0, 5), sTemp11 = sLine.substr(0, 11);
		if (sTemp3 == "To:")		//To found; copy it and remove "To: " from the front
		{
			sTo = sLine.erase(0, sTemp3.size() + 1);  //To take account for space, add 1:  .erase(0, 4)
			bCheckSubject = false;
			continue;
		}
		if (sTemp5 == "From:")		//From found; copy and remove "From: " from the front
		{
			sFrom = sLine.erase(0, sTemp5.size() + 1);  //.erase(0, 6)
			bCheckSubject = false;
			continue;
		}
		if (sTemp5 == "Date:")		//Date found; copy and remove "Date: " from the front
		{
			sDate = sLine.erase(0, sTemp5.size() + 1);  //.erase(0, 6)
			bCheckSubject = false;
			continue;
		}
		if (sTemp11 == "Message-ID:")//MID found; copy and remove "Message-ID: " from the front
		{
			sMID = sLine.erase(0, sTemp11.size() + 1);  //.erase(0, 11)
			bCheckSubject = false;
			continue;
		}

		if (bCheckSubject)
		{
			int i = 0;
			if (sLine[i] == ' ')	//Observation:  Subsequent lines of multi-line subjects always start with space.
			{						//Ergo, check for space after subject line and append if part of subject
				while (sLine[i] == ' ')
					i++;
				sSubject += sLine.substr(i - 1);
			}
			else					//Subject is finished, reset bCheckSubject
				bCheckSubject = false;
		}
		if (sLine.substr(0, 8) == "Subject:")	//Subject found; copy and remove "Subject: " from the front
		{
			sSubject = sLine.erase(0, 9);
			bCheckSubject = true;
		}

		if (sTo != "" && sFrom != "" && sDate != "" && sSubject != "" && sMID != "" && !bCheckSubject)
			bAllFound = true;
	}
	m_arEmailData->push_back(EMAIL_DATA(sTo, sFrom, sDate, sSubject, sMID));
	m_outFile << "To: " << sTo << endl << "From: " << sFrom << endl << "Date: " << sDate << endl << "Subject: " << sSubject << endl << "Message-ID: " << sMID << endl << endl;
	if (bAllFound)
		return true;
	else
		return false;
}

//Print all records that have been processed and added to Vector array
void Parser::PrintData()
{
	for (vector<EMAIL_DATA>::const_iterator i = m_arEmailData->begin(); i != m_arEmailData->end(); i++)
		cout << "To: " << i->sTo << endl << "From: " << i->sFrom << endl << "Date: " << i->sDate << endl 
			 << "Subject: " << i->sSubject << endl << "Message-ID: " << i->sMID << endl << endl;
}


int main(int argc, char *argv[])
{
	Parser rpParser;
	string sInput = "";
	if (argc == 2)
		sInput = string(argv[1]);
	rpParser.ParseDirectory(sInput);
	rpParser.PrintData();
	cout << "Finished!";

	return 0;
}
