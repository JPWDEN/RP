Solution to Return Path's interview test, by Josh Walker.  Written in C++.

assessment.h and assessment.cpp contain class "Parser".  In these files, Parser uses Linux system calls in ParseDirectory() to traverse a directory of emails.  The Parser class parses each email, extracts, and stores the following information from each email:
-  To
-  From
-  Date
-  Subject
-  Message-ID

The above information parsed from each email is stored in a Vector array.  Public method PrintData() allows the user to print the contents of the Vector to the screen or to a file.

compile:  g++ ./assessment.cpp -o assessment

Usage:  ./assessment (path)

Parser can be executed with no command line arguments.  In this case, Parser will attempt to scan for email files from the ./smallset/ path.  Alternatively, Parser can accept a single argument as a string containing the directory path where it should search for email files to parse.

WindowsFiles Directory:  
assessment_win.h and assessment_win.cpp contain the same definition of the Parser, but with the addition of a ParseDirectoryWin() method that utilizes Windows calls to traverse a directory of emails.  This Windows version of Parser also includes several preprocessor directives which alter what code is compiled, and could theoretically work on most Linux systems as well.

DockerFiles Directory:
The DockerFiles directory contains 2 files.  Dockerfile is the script for Docker, providing commands to start up a linux image, install necessary tools, download the source code from Github, compile, and run.  docker_compose.yml contains the configuration information, and any services needed for this project.  In this simple case, the compose file is only the version number and the image name used for the project.

A huge thank you in advance for taking the time to look at this project and offer consider me for this role.  I am incredibly excited about this opportunity and look forward to meeting the Return Path team in person.

Regards,
Josh
