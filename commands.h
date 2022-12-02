#pragma once
#include <iostream>
#include <string>
using namespace std;

class CommandParser {
private:
	string command = "";
	int argCount = 0;
public:
	string args[100] = {};
	//constructor here

	CommandParser() {
		this->command = command;
		this->argCount = argCount;
	}

	//get the inputted command
	string getCommand() {
		return this->command;
	}

	string returnArg1() {
		return this->args[0];
	}

	string returnArg2() {
		return this->args[1];
	}

	int getArgCount() {
		return this->argCount;
	}

	//a function to determine the amount of arguments from the received string
	void computeArgCount(string command) {
		int count = 1;
		for (int i = 0; command[i] != '\0'; i++) {
			if (command[i] == ' ') {
				count++;
			}
		}
		this->argCount = count;
	}

	//Breaks the inputted command into smaller strings that can be stored as arguments
	void breakString(string command) {
		size_t pos = 0;
		string token;
		int i = 0;
		while ((pos = command.find(" ")) != string::npos) {
			token = command.substr(0, pos);
			this->args[i] = token;
			i++;
			command.erase(0, pos + 1);
		}
		this->args[i] = command;

		//displayArguments();
	}

	//Displays the saved arguments that we have in our command processor, it is for testing purposes
	void displayArguments() {
		for (int i = 0; i < this->argCount; i++) {
			cout << endl << this->args[i];
		}
	}

	//a function to verify the string format (no extra spaces or such). (If the command does have extra spaces, a function removeExtraSpaces() would normally be called, but we didn't do that yet due to lack of time)
	bool checkExtraSpaces(string command) {
		if (command[0] == ' ' || command[command.length() - 1] == ' ') {
			return true;
		}
		else {
			bool hasExtraSpaces = false;
			for (int i = 1; command[i + 1] != '\0' && hasExtraSpaces == false; i++) {
				if (command[i] == ' ' && (command[i - 1] == ' ' || command[i + 1] == ' ')) {
					hasExtraSpaces = true;
				}
			}
			return hasExtraSpaces;
		}
	}

	friend void operator>>(istream& input, CommandParser& command);
	friend void operator<<(ostream& console, CommandParser command);
};

//Overloading >> to read the command
void operator>>(istream& input, CommandParser& command) {
	getline(input, command.command);
	if (command.checkExtraSpaces(command.command)) {				//Check if your command has any extra spaces
		cout << endl << "ERROR: Make sure your command has no extra spaces (we didn't manage to make a function to remove extra spaces yet, perhaps in phase 2)";
	}
	else if (!command.checkExtraSpaces(command.command)) {			//If the command respects the no extra space format, we can calculate the number of arguments in the string and verify it
		command.computeArgCount(command.command);
		command.breakString(command.command);
	}
}

//Overloading << to display the raw command (for testing purposes)
void operator<<(ostream& console, CommandParser command) {
	console << endl << command.command;
}

//From the list of command examples that shouldn't work in the google docs, this CreateTable should be able to pass all of them
//However, there is one example of command that went through our mind (it isn't listed in the google docs) that will not give an error:

//CREATE TABLE students ((id, integer, 1000, 0), (nume, text,)128, ’’, (grupa, text,50,’1000’))

//This will work regardless of where the parantheses are positioned due to the way we conceived the validation (by counting the number of parantheses)
//We do have an idea on how to fix it and it involves checking if the first and last character, respectively, of each 1st and 4th parameter, contain a left/right paranthesis and the beginning/end
//However, we did not implement it yet due to lack of time on our part
//This should be fixed at the end of phase 2
class CreateTable {
private:
	string args[100] = {};
	int argCount = 0;
	string table_name = "";
	string column_name[50][250];
	string type[50][25];
	int* dimension = nullptr;
	string default_value[50][100];
	static int noColumns;
public:

	CreateTable(string args[], int argCount) {
		if (argCount >= 4 && args[3] != "IF" && args[4] != "NOT" && args[5] != "EXISTS") {
			string copy;
			for (int i = 3; i < argCount; i++) {
				args[i].erase(remove(args[i].begin(), args[i].end(), ' '), args[i].end());
				copy += args[i];
				args[i] = "";
			}
			args[3] = copy;
			if (CheckColumnName(args[3]) == true) {
				args[3].pop_back();
				args[3].erase(args[3].begin());
				int countParaLeft = 0;
				int countParaRight = 0;
				for (int j = 0; j < args[3].size(); j++) {
					if (args[3][j] == '(') {
						countParaLeft++;
					}
				}
				for (int j = 0; j < args[3].size(); j++) {
					if (args[3][j] == ')') {
						countParaRight++;
					}
				}
				args[3].erase(remove(args[3].begin(), args[3].end(), '('), args[3].end());
				args[3].erase(remove(args[3].begin(), args[3].end(), ')'), args[3].end());
				size_t pos = 0;
				copy = args[3];
				string argsCopy[100] = {};
				string token;
				int i = 0;
				if (copy.find(",") != string::npos) {
					while ((pos = copy.find(",")) != string::npos) {
						token = copy.substr(0, pos);
						argsCopy[0 + i] = token;
						i++;
						argCount++;
						copy.erase(0, pos + 1);
					}
					argsCopy[i] = copy;
					i++;
					if (i % 4 == 0 && i / 4 == countParaLeft && i / 4 == countParaRight) {
						for (int j = 0; j <= i; j++) {
							args[j + 3] = argsCopy[j];
						}
						bool validType = true;
						int count = 0;
						for (int j = 1; j <= i / 4; j++) {
							if (args[(i / 4) * j + 1 + count] != "text" && args[(i / 4) * j + 1 + count] != "integer" && args[(i / 4) * j + 1 + count] != "float") {
								validType = false;
							}
							count++;
						}
						if (validType) {
							for (int i = 0; i < argCount; i++) {
								this->args[i] = args[i];
							}
							this->argCount = argCount;
							for (int i = 0; i < argCount; i++) {
								this->args[i] = args[i];
							}
							this->argCount = argCount;
							cout << endl << "You used the command: " << this->args[0] << " " << this->args[1];
							count = 0;
							for (int j = 1; j <= i / 4; j++) {
								cout << endl << "Parameters for column " << j << ": ";
								cout << endl << "  Column name: " << this->args[(i / 4) * j + count];
								cout << endl << "  Column type: " << this->args[(i / 4) * j + 1 + count];
								cout << endl << "  Column size: " << this->args[(i / 4) * j + 2 + count];
								cout << endl << "  Default value: " << this->args[(i / 4) * j + 3 + count];
								count++;
							}
						}
						else cout << endl << "ERROR: Invalid column type (must be text/integer/float)";
					}
					else cout << endl << "ERROR: Incomplete column description or missing parantheses";
				}
			}
			else cout << endl << "ERROR: Invalid column or table format";
		}
		else if (argCount >= 4 && args[3] == "IF" && args[4] == "NOT" && args[5] == "EXISTS") {
			string copy;
			for (int i = 6; i < argCount; i++) {
				args[i].erase(remove(args[i].begin(), args[i].end(), ' '), args[i].end());
				copy += args[i];
				args[i] = "";
			}
			args[6] = copy;
			if (CheckColumnName(args[6]) == true) {
				args[6].pop_back();
				args[6].erase(args[6].begin());
				int countParaLeft = 0;
				int countParaRight = 0;
				for (int j = 0; j < args[6].size(); j++) {
					if (args[6][j] == '(') {
						countParaLeft++;
					}
				}
				for (int j = 0; j < args[6].size(); j++) {
					if (args[6][j] == ')') {
						countParaRight++;
					}
				}
				args[6].erase(remove(args[6].begin(), args[6].end(), '('), args[6].end());
				args[6].erase(remove(args[6].begin(), args[6].end(), ')'), args[6].end());
				size_t pos = 0;
				copy = args[6];
				string argsCopy[100] = {};
				string token;
				int i = 0;
				if (copy.find(",") != string::npos) {
					while ((pos = copy.find(",")) != string::npos) {
						token = copy.substr(0, pos);
						argsCopy[0 + i] = token;
						i++;
						argCount++;
						copy.erase(0, pos + 1);
					}
					argsCopy[i] = copy;
					i++;
					if (i % 4 == 0 && i / 4 == countParaLeft && i / 4 == countParaRight) {
						for (int j = 0; j <= i; j++) {
							args[j + 6] = argsCopy[j];
						}
						bool validType = true;
						int count = 0;
						for (int j = 1; j <= i / 4; j++) {
							if (args[(i / 4) * (j + 1) + 1 + count] != "text" && args[(i / 4) * (j + 1) + 1 + count] != "integer" && args[(i / 4) * (j + 1) + 1 + count] != "float") {
								validType = false;
							}
							count++;
						}
						if (validType) {
							for (int i = 0; i < argCount; i++) {
								this->args[i] = args[i];
							}
							this->argCount = argCount;
							for (int i = 0; i < argCount; i++) {
								this->args[i] = args[i];
							}
							this->argCount = argCount;
							cout << endl << "You used the command: " << this->args[0] << " " << this->args[1];
							count = 0;
							for (int j = 1; j <= i / 4; j++) {
								cout << endl << "Parameters for column " << j << ": ";
								cout << endl << "  Column name: " << this->args[(i / 4) * (j + 1) + count];
								cout << endl << "  Column type: " << this->args[(i / 4) * (j + 1) + 1 + count];
								cout << endl << "  Column size: " << this->args[(i / 4) * (j + 1) + 2 + count];
								cout << endl << "  Default value: " << this->args[(i / 4) * (j + 1) + 3 + count];
								count++;
							}
						}
						else cout << endl << "ERROR: Invalid column type (must be text/integer/float)";
					}
					else cout << endl << "ERROR: Incomplete column description or missing parantheses";
				}
			}
		}
		else cout << endl << "ERROR: Invalid column or table format";
	}

	bool CheckColumnName(string arg) {
		if (arg.front() == '(' && arg.back() == ')') {
			string copy = arg;
			copy.pop_back();
			copy.erase(copy.begin());
			if (copy != "") {
				return true;
			}
			else return false;
		}
		else return false;
	}

	string getTableName()
	{
		return this->table_name;
	}

	string getColumnName(int index)
	{
		return this->column_name[index][250];
	}

	string getType(int index)
	{
		return this->type[index][25];
	}

	int* getDimension()
	{
		return this->dimension;
	}

	string getDefaultValue(int index)
	{
		return this->default_value[index][100];
	}

	void setTableName(string newTableName)
	{
		if (newTableName != "")
		{
			this->table_name = newTableName;
		}
		else
		{
			cout << "ERROR: Missing table name";
		}
	}

	void setColumnName(string newColumnName)
	{
		if (newColumnName != "")
		{
			this->column_name[++CreateTable::noColumns];
		}
		else
		{
			cout << "ERROR: Missing column name";
		}
	}

	void setType(string newType)
	{
		if (newType == "integer" || newType == "float" || newType == "text")
		{
			this->type[CreateTable::noColumns][25] = newType;
		}
		else
			cout << "The type of the column is not correct";
	}

	void setDimension(int* newDimension, int newNo)
	{
		if (newDimension != nullptr && newNo > 0)
		{
			if (this->dimension)
			{
				delete[] this->dimension;
			}
			this->dimension = new int[newNo];
			memcpy(this->dimension, newDimension, sizeof(int) * newNo);
			this->noColumns = newNo;
		}
	}

	void setDefaultValue(string newDefaultValue)
	{
		this->default_value[CreateTable::noColumns][100] = newDefaultValue;
	}

	CreateTable(string newTableName)
	{
		this->table_name = newTableName;
	}

	CreateTable(string newTableName, int* newDimension, int noColumns)
	{
		this->table_name = newTableName;
		this->setDimension(newDimension, noColumns);
	}

	CreateTable(const CreateTable& newTable)
	{
		this->table_name = newTable.table_name;
		this->setDimension(newTable.dimension, newTable.noColumns);
	}

	~CreateTable()
	{
		if (this->dimension)
		{
			delete[] this->dimension;
		}
	}

	static int getNoColumns()
	{
		return CreateTable::noColumns;
	}
};