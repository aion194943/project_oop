#pragma once
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class FileParser {
private:
	string fileName = "";
	CommandParser command;
public:

	FileParser() {
		this->fileName = fileName;
	}

	FileParser(string str) {
		this->fileName = str;
		ifstream file(this->fileName);
		if (file.is_open()) {
			while (getline(file, command.command)) {
				if (command.checkExtraSpaces(command.command)) {				//Check if your command has any extra spaces
					cout << endl << "ERROR: Make sure your command has no extra spaces (this is something we were unable to make work, sorry!)";
				}
				else if (!command.checkExtraSpaces(command.command)) {			//If the command respects the no extra space format, we can calculate the number of arguments in the string and verify it
					command.computeArgCount(command.command);
					command.breakString(command.command);
					if (command.returnArg1() == "CREATE") {
						if (command.returnArg2() == "INDEX") {
							CreateIndex cmd(command.args, command.getArgCount());
						}
						else if (command.returnArg2() == "TABLE") {
							CreateTable cmd(command.args, command.getArgCount());
						}
						else cout << endl << "ERROR: Invalid command format, check 'help' for the correct formats";
					}
					else if (command.returnArg1() == "DELETE") {
						if (command.returnArg2() == "FROM") {
							DeleteFrom cmd(command.args, command.getArgCount());
						}
						else cout << endl << "ERROR: Invalid command format, check 'help' for the correct formats";
					}
					else if (command.returnArg1() == "DISPLAY") {
						if (command.returnArg2() == "TABLE") {
							DisplayTable cmd(command.args, command.getArgCount());
						}
						else cout << endl << "ERROR: Invalid command format, check 'help' for the correct formats";
					}
					else if (command.returnArg1() == "DROP") {
						if (command.returnArg2() == "INDEX") {
							DropIndex cmd(command.args, command.getArgCount());
						}
						else if (command.returnArg2() == "TABLE") {
							DropTable cmd(command.args, command.getArgCount());
						}
						else cout << endl << "ERROR: Invalid command format, check 'help' for the correct formats";
					}
					else if (command.returnArg1() == "INSERT") {
						if (command.returnArg2() == "INTO") {
							InsertInto cmd(command.args, command.getArgCount());
						}
						else cout << endl << "ERROR: Invalid command format, check 'help' for the correct formats";
					}
					else if (command.returnArg1() == "SELECT") {
						Select cmd(command.args, command.getArgCount());
					}
					else if (command.returnArg1() == "UPDATE") {
						Update cmd(command.args, command.getArgCount());
					}
					else if (command.returnArg1() == "IMPORT") {
						Import cmd(command.args, command.getArgCount());
					}
					else cout << endl << "ERROR: Invalid command format, check 'help' for the correct formats";
					file.close();
				}
			}
		}
	}
};


