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

//CREATE TABLE students ((id, integer, 1000, 0), (nume, text,)128, ��, (grupa, text,50,�1000�))

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

	//operators
	CreateTable operator=(const CreateTable& newTable)
	{
		if (newTable.table_name == this->table_name)
		{
			return *this;
		}
		this->table_name = newTable.table_name;
		this->setDimension(newTable.dimension, newTable.noColumns);
		return *this;
	}

	CreateTable operator!()
	{
		CreateTable result = *this;
		result.getTableName() = "";
		result.dimension = nullptr;
		return result;
	}

	string operator[](int index)
	{
		if (index < 0 || index >= noColumns)
		{
			cout << "The index is wrong";
		}
		else
		{
			return this->column_name[index][250];
		}
	}

	explicit operator int()
	{
		return this->getNoColumns();
	}

	//post-incrementation
	CreateTable operator++(int)
	{
		CreateTable result = *this;
		result.dimension++;
		return result;
	}

	//pre-incrementation
	CreateTable operator++()
	{
		this->dimension++;
		return *this;
	}

	friend ostream& operator<<(ostream& console, CreateTable& selection);
	friend void operator>>(istream& input, CreateTable& selection);

};

int CreateTable::noColumns = -1;

ostream& operator <<(ostream& console, CreateTable& newTable)
{
	cout << endl << "----------------------" << endl;
	cout << "The table name is: " << newTable.getTableName() << endl;
	for (int i = 0; i < CreateTable::noColumns; i++)
	{
		cout << newTable.getColumnName(i) << " ";
	}
	cout << endl;
	if (newTable.noColumns > 0)
	{
		cout << "The number of columns is: " << newTable.noColumns << endl;
		for (int i = 0; i < newTable.noColumns; i++)
		{
			cout << "Name of column " << i << " is " << newTable.column_name[i] << endl;
		}
	}
	return console;
}

void operator >>(istream& input, CreateTable& newTable)
{
	cout << endl << "Table name ";
	input >> newTable.table_name;
	cout << "The number of columns is ";
	int no;
	input >> no;
	int* columns = new int[no];
	for (int i = 0; i < no; i++)
	{
		cout << endl << "The dimension of column " << i + 1 << " is: ";
		input >> newTable.dimension[i];
	}
	newTable.setDimension(columns, no);
}

bool operator>(CreateTable newTable1, CreateTable newTable2)
{
	if (newTable1.getNoColumns() > newTable2.getNoColumns())
		return true;
	else
		return false;
}

bool operator==(CreateTable newTable1, CreateTable newTable2)
{
	if (newTable1.getNoColumns() == newTable2.getNoColumns())
		return true;
	else
		return false;
};

class DropTable {
private:
	string args[100] = {};
	int argCount = 0;
public:

	DropTable(string args[], int argCount) {
		if (argCount == 3) {
			for (int i = 0; i < argCount; i++) {
				this->args[i] = args[i];
			}
			this->argCount = argCount;
			cout << endl << "You used the command: " << this->args[0] << " " << this->args[1];
			cout << endl << "Table name: " << this->args[2];
		}
		else if (argCount > 3) {
			cout << endl << "ERROR: Too many parameters";
		}
		else {
			cout << endl << "ERROR: Too few parameters";
		}
	}
};

class DisplayTable {
private:
	string args[100] = {};
	int argCount = 0;
public:

	DisplayTable(string args[], int argCount) {
		if (argCount == 3) {
			for (int i = 0; i < argCount; i++) {
				this->args[i] = args[i];
			}
			this->argCount = argCount;
			cout << endl << "You used the command: " << this->args[0] << " " << this->args[1];
			cout << endl << "Table name: " << this->args[2];
		}
		else if (argCount > 3) {
			cout << endl << "ERROR: Too many parameters";
		}
		else {
			cout << endl << "ERROR: Too few parameters";
		}
	}
};
class CreateIndex {
private:
	string args[100] = {};
	int argCount = 0;
public:

	CreateIndex(string args[], int argCount) {
		if (argCount == 6) {
			if (args[3] == "ON") {
				if (CheckColumnName(args[5]) == true) {
					for (int i = 0; i < argCount; i++) {
						this->args[i] = args[i];
					}
					args[5].pop_back();
					args[5].erase(args[5].begin());
					this->args[5] = args[5];
					this->argCount = argCount;
					if (this->args[5] != "") {
						cout << endl << "You used the command: " << this->args[0] << " " << this->args[1];
						cout << endl << "Index name: " << this->args[2];
						cout << endl << "Table name: " << this->args[4];
						cout << endl << "Column name: " << this->args[5];
					}
					else cout << endl << "ERROR: Unspecified column name";
				}
				else cout << endl << "ERROR: Invalid column name format";
			}
		}
		else if (argCount == 9) {
			if (args[2] == "IF" && args[3] == "NOT" && args[4] == "EXISTS" && args[6] == "ON") {
				if (CheckColumnName(args[8]) == true) {
					for (int i = 0; i < argCount; i++) {
						this->args[i] = args[i];
					}
					args[8].pop_back();
					args[8].erase(args[8].begin());
					this->args[8] = args[8];
					this->argCount = argCount;
					if (this->args[8] != "") {
						cout << endl << "You used the command: " << this->args[0] << " " << this->args[1];
						cout << endl << "Index name: " << this->args[5];
						cout << endl << "Table name: " << this->args[7];
						cout << endl << "Column name: " << this->args[8];
					}
					else cout << endl << "ERROR: Unspecified column name";
				}
				else cout << endl << "ERROR: Invalid column name format";
			}
			else cout << endl << "ERROR: Invalid command format, check 'help' for the correct formats";
		}
		else if (argCount > 9) {
			cout << endl << "ERROR: Too many parameters";
		}
		else if (argCount < 6 || (argCount > 6 && argCount < 9)) {
			cout << endl << "ERROR: Too few parameters";
		}
	}

	bool CheckColumnName(string arg) {
		if (arg.front() == '(' && arg.back() == ')') {
			return true;
		}
		else return false;
	}
};

class DropIndex {
private:
	string args[100] = {};
	int argCount = 0;
public:

	DropIndex(string args[], int argCount) {
		if (argCount == 3) {
			for (int i = 0; i < argCount; i++) {
				this->args[i] = args[i];
			}
			this->argCount = argCount;
			cout << endl << "You used the command: " << this->args[0] << " " << this->args[1];
			cout << endl << "Table name: " << this->args[2];
		}
		else if (argCount > 3) {
			cout << endl << "ERROR: Too many parameters";
		}
		else {
			cout << endl << "ERROR: Too few parameters";
		}
	}

};

class InsertInto {
private:
	string args[100] = {};
	int argCount = 0;
	string table_name = "";
	string column_name = "";
	string type = "";
	int dimension = 0;
	string default_value = "";
public:

	InsertInto(string args[], int argCount) {
		if (argCount == 5) {
			if (args[3] == "VALUES") {
				if (CheckColumnName(args[4]) == true) {
					args[4].pop_back();
					args[4].erase(args[4].begin());
					string copy = args[4];
					size_t pos = 0;
					string token;
					string argsCopy[100] = {};
					int i = 0;
					while ((pos = copy.find(",")) != string::npos) {
						token = copy.substr(0, pos);
						argsCopy[i] = token;
						i++;
						argCount++;
						copy.erase(0, pos + 1);
					}
					argsCopy[i] = copy;
					for (int j = 0; j <= i; j++) {
						args[j + 4] = argsCopy[j];
					}
					if (argCount == 8) {
						for (int i = 0; i < argCount; i++) {
							this->args[i] = args[i];
						}
						this->argCount = argCount;
						cout << endl << "You used the command: " << this->args[0] << " " << this->args[1];
						cout << endl << "Table name: " << this->args[2];
						//setTableName(this->args[2]);
						cout << endl << "Column name: " << this->args[4];
						//setColumnName(this->args[4]);
						cout << endl << "Column type: " << this->args[5];
						//setType(this->args[5]);
						cout << endl << "Column size: " << this->args[6];
						//setDimension(stoi(this->args[6]));
						cout << endl << "Column default value: " << this->args[7];
						//setDefaultValue(this->args[7]);
					}
					else cout << endl << "ERROR: Invalid parameter column format";
				}
				else cout << endl << "ERROR: Invalid column format";
			}
			else cout << endl << "ERROR: Invalid command format, check 'help' for the correct formats";
		}
		else if (argCount > 5) {
			cout << endl << "ERROR: Too many parameters";
		}
		else {
			cout << endl << "ERROR: Too few parameters";
		}
	}

	bool CheckColumnName(string arg) {
		if (arg.front() == '(' && arg.back() == ')') {
			return true;
		}
		else return false;
	}

	InsertInto(string newName, string newType)
	{
		this->column_name = newName;
		this->type = newType;
	}

	InsertInto(string newTableName, string newName, string newType, int size, string newDefaultValue)
	{
		this->table_name = newTableName;
		this->column_name = newName;
		this->type = newType;
		this->dimension = size;
		this->default_value = newDefaultValue;
	}

	InsertInto(const InsertInto& column)
	{
		this->table_name = column.table_name;
		this->column_name = column.column_name;
		this->type = column.type;
		this->dimension = column.dimension;
		this->default_value = column.default_value;
	}

	string getTableName()
	{
		return this->table_name;
	}

	string getColumn()
	{
		return this->column_name;
	}

	string getType()
	{
		return this->type;
	}

	int getDimension()
	{
		return this->dimension;
	}

	string getDefaultValue()
	{
		return this->default_value;
	}

	void setTableName(string newTableName)
	{
		if (newTableName != "")
		{
			this->table_name = newTableName;
		}
		else
		{
			cout << "ERROR: Table name is missing";
		}
	}

	void setColumnName(string newColumnName)
	{
		if (newColumnName != "")
		{
			this->column_name = newColumnName;
		}
		else
		{
			cout << "ERROR: Column name is missing";
		}
	}

	void setType(string newType)
	{
		if (newType == "integer" || newType == "float" || newType == "text")
		{
			this->type = newType;
		}
		else
		{
			cout << "The type of the column is not correct";
		}
	}

	void setDimension(int newDimension)
	{
		if (newDimension != 0 && newDimension > 0)
		{
			this->dimension = newDimension;
		}
		else
		{
			cout << "Incorrect dimension value";
		}
	}

	void setDefaultValue(string newDefaultValue)
	{
		if (newDefaultValue != "")
		{
			this->default_value = newDefaultValue;
		}
		else
		{
			cout << "ERROR: Default value not specified";
		}
	}

class Select {
private:
	string args[100] = {};
	int argCount = 0;
	string table_name = "";
	string* column_names = nullptr;
	static int noColumns;
public:

	Select(string args[], int argCount) {
		if (argCount >= 4) {
			if (args[1] == "ALL" && args[2] == "FROM") {
				if (args[4] == "WHERE" && args[6] == "=") {
					for (int i = 0; i < argCount; i++) {
						this->args[i] = args[i];
					}
					this->argCount = argCount;
					cout << endl << "You used the command: " << this->args[0];
					cout << endl << "You selected the columns: " << this->args[1];
					cout << endl << "Table name: " << this->args[3];
					cout << endl << "Has filter: yes";
					cout << endl << "Column being checked in WHERE: " << this->args[5];
					cout << endl << "Value being checked in WHERE: " << this->args[7];
				}
				else if (args[4] == "WHERE" && (args[5] == "" || args[6] != "=" || args[7] == "")) {
					cout << endl << "ERROR: WHERE formatting incorrectly specified";
				}
				else if (args[4] == "") {
					for (int i = 0; i < argCount; i++) {
						this->args[i] = args[i];
					}
					this->argCount = argCount;
					cout << endl << "You used the command: " << this->args[0];
					cout << endl << "You selected the columns: " << this->args[1];
					cout << endl << "Table name: " << this->args[3];
					cout << endl << "Has filter: no";
				}
				else cout << endl << "ERROR: Invalid WHERE or table name format";
			}
			else if (args[1] != "ALL" && args[2] == "FROM") {
				if (CheckColumnName(args[1]) == true) {
					if (args[4] == "WHERE" && args[6] == "=" && args[7] != "" && args[8] == "") {
						args[1].pop_back();
						args[1].erase(args[1].begin());
						size_t pos = 0;
						string copy = args[1];
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
						
							for (int j = argCount - 1; j > i; j--) {
								args[j] = args[j - i + 1];
							}
							for (int j = 0; j <= i; j++) {
								args[j + 1] = argsCopy[j];
							}
							for (int i = 0; i < argCount; i++) {
								this->args[i] = args[i];
							}
							this->argCount = argCount;
							for (int i = 0; i < argCount; i++) {
								this->args[i] = args[i];
							}
							this->argCount = argCount;
							cout << endl << "You used the command: " << this->args[0];
							cout << endl << "You selected the columns: ";
							for (int j = 1; j <= i + 1; j++) {
								cout << this->args[j] << " ";
							}
							cout << endl << "Table name: " << this->args[i + 2];
							cout << endl << "Has filter: yes";
							cout << endl << "Column being checked in WHERE: " << this->args[i + 4];
							cout << endl << "Value being checked in WHERE: " << this->args[i + 6];
						}
						else {
							for (int i = 0; i < argCount; i++) {
								this->args[i] = args[i];
							}
							this->argCount = argCount;
							for (int i = 0; i < argCount; i++) {
								this->args[i] = args[i];
							}
							cout << endl << "You used the command: " << this->args[0];
							cout << endl << "You selected the columns: " << this->args[1];
							cout << endl << "Table name: " << this->args[3];
							cout << endl << "Has filter: yes";
							cout << endl << "Column being checked in WHERE: " << this->args[5];
							cout << endl << "Value being checked in WHERE: " << this->args[7];
						}
						
					}
					else if (args[4] == "WHERE" && (args[5] == "" || args[6] != "=" || args[7] == "")) {
						cout << endl << "ERROR: WHERE formatting incorrectly specified";
					}
					else if (args[4] == "")
					{
						args[1].pop_back();
						args[1].erase(args[1].begin());
						size_t pos = 0;
						string copy = args[1];
						string argsCopy[100] = {};
						string token;
						int i = 0;
						if (copy.find(",") != string::npos) {
							while ((pos = copy.find(",")) != string::npos) {
								token = copy.substr(0, pos);
								argsCopy[i] = token;
								i++;
								argCount++;
								copy.erase(0, pos + 1);
							}
							argsCopy[i] = copy;
							for (int j = argCount - 1; j > i; j--) {
								args[j] = args[j - i + 1];
							}
							for (int j = 0; j <= i; j++) {
								args[j + 1] = argsCopy[j];
							}
							for (int i = 0; i < argCount; i++) {
								this->args[i] = args[i];
							}
							this->argCount = argCount;
							for (int i = 0; i < argCount; i++) {
								this->args[i] = args[i];
							}
							this->argCount = argCount;
							cout << endl << "You used the command: " << this->args[0];
							cout << endl << "You selected the columns: ";
							for (int j = 1; j <= i + 1; j++) {
								cout << this->args[j] << " ";
							}
							cout << endl << "Table name: " << this->args[i + 2];
							cout << endl << "Has filter: no";
						}
						else {
							for (int i = 0; i < argCount; i++) {
								this->args[i] = args[i];
							}
							this->argCount = argCount;
							for (int i = 0; i < argCount; i++) {
								this->args[i] = args[i];
							}
							cout << endl << "You used the command: " << this->args[0];
							cout << endl << "You selected the columns: " << this->args[1];
							cout << endl << "Table name: " << this->args[3];
							cout << endl << "Has filter: no";
						}
					} 
					else cout <<  endl << "ERROR: Invalid WHERE or table name format";
				}
				else cout << endl << "ERROR: Invalid column format";
			}
			else cout << endl << "ERROR: Invalid command format, check 'help' for the correct formats";
		}
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

	string* getColumns()
	{
		return this->column_names;
	}

	string getTableName()
	{
		return this->table_name;
	}

	static int getNoColumns()
	{
		return Select::noColumns;
	}

	void setColumns(string* newColumns, int newNoColumns)
	{
		if (newColumns != nullptr && newNoColumns > 0)
		{
			if (this->column_names)
			{
				delete[] this->column_names;
			}
			this->column_names = new string[newNoColumns];
			memcpy(this->column_names, newColumns, sizeof(string) * newNoColumns);
			this->noColumns = newNoColumns;
		}
	}

	void setTableName(string newTableName)
	{
		if (newTableName != "")
		{
			this->table_name = newTableName;
		}
		else
		{
			cout << "ERROR: Table name is missing";
		}
	}

	Select(string newTableName)
	{
		this->table_name = newTableName;
	}

	Select(string newTableName, string* newPoints, int noColumns)
	{
		this->table_name = newTableName;
		this->setColumns(newPoints, noColumns);
	}

	Select(const Select& selection)
	{
		this->table_name = selection.table_name;
		this->setColumns(selection.column_names, selection.noColumns);
	}

	~Select()
	{
		if (this->column_names)
		{
			delete[] this->column_names;
		}
	}

	//operators

	Select operator=(const Select& selection)
	{
		if (selection.table_name == this->table_name)
		{
			return *this;
		}
		this->table_name = selection.table_name;
		this->setColumns(selection.column_names, selection.noColumns);
		return *this;
	}

	Select operator!()
	{
		Select result = *this;
		result.column_names = nullptr;
		result.noColumns = 0;
		return result;
	}

	explicit operator int()
	{
		return this->getNoColumns();
	}

	friend ostream& operator<<(ostream& console, Select& selection);
	friend void operator>>(istream& input, Select& selection);
	friend Select operator+(Select& selection, string text);
};