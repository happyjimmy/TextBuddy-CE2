#include "TextBuddy.h"

using namespace std;

const string INPUT_ERROR_MESSAGE = "Invalid input! Please enter TextBuddy.exe followed by your text-file name!";

//This functions validates if the user has entered TextBuddy.exe followed by the text-file name
//If yes, then the user can continue
//If no, tell the user the correct commands to input
bool checkNumberOfArguments(int numberOfArguments) {
	if (numberOfArguments == 2) {
		return true;
	}
	else {
		return false;
	}
}

void printMessage(string message) {
	cout << message << endl;
}

void main (int argc,char *argv[]) {
	if ((checkNumberOfArguments(argc)) == true) {
		TextBuddy run(argv[1]);
		run.mainProgram();
	}
	else if ((checkNumberOfArguments(argc)) == false) {
		printMessage(INPUT_ERROR_MESSAGE);
		}
}