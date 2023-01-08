#include "commands.h"
#include "console.h"
//#include WIP 

int main(int argc, char* argv[]) {
	if (argc > 1 && argc <= 6) {
		bool found = 1;
		for (int i = 1; i < argc; i++) {
			char* p = strrchr(argv[i], '.');
			if (p) {
				if (strcmp(p, ".txt") != 0) {
					found = 0;
				}
			}
			else found = 0;
		}
		if (found) {
			for (int i = 1; i < argc; i++) {
				FileParser file(argv[i]);
			}
		}
		else cout << endl << "ERROR: Invalid text file extension detected";
	}
	else if (argc > 6) {
		cout << endl << "ERROR: Too many arguments (maximum 5)";
	}
	else {
		initialize();
	}
}