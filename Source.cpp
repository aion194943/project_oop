include "commands.h"

int main() {
	cout << "**VDN Project**" << endl;
	cout << "OOP project phase1" << endl;
	cout << "Creators: Dimian Andrei, Enescu Andra, Girtoman Ionut, Ion Ana-Maria" << endl << "------------------------------------------------------------" << endl;
	cout << "Type 'exit' to close this program" << endl;
	cout << "Type 'help' to see  commands" << endl;
	while (true) {
		CommandParser command;
		cout << endl << "Enter your command: ";
		cin >> command;
		if (command.getCommand() == "exit") {
			cout << endl << "Closing program...";
			return 0;
		}
		if (command.getCommand() == "help") {
			cout << endl << "Available commands: " << endl;
			cout << "  CREATE TABLE table_name " << endl;
			cout << "  DROP TABLE table_name" << endl;
			cout << "  DISPLAY TABLE table_name" << endl;
			cout << "  CREATE INDEX " << endl;
			cout << "  DROP INDEX index_name" << endl;
			cout << "  INSERT INTO table VALUES " << endl;
			cout << "  DELETE FROM table_name WHERE column_name = value" << endl;
			cout << "  SELECT * FROM table_name " << endl;
			cout << "  UPDATE table_name SET column_name = value WHERE column_name = value" << endl;
		}
		else {
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
			else cout << endl << "ERROR: Invalid command format, check 'help' for the correct formats";

		}
	}
}