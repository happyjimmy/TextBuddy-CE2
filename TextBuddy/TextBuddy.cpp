//@Author: Leung Kwan Pui
//@Matric No.: A0128461H
//Assumptions: The user can input a maximum of 1024 items. Each item's maximum length is also 1024.
//Assumptions: The user will not input a non-existing item number to delete an non-existing item.

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#include "TextBuddy.h"

//Default messages/commands that will prompt out according to the user's input.
//They are put here because they cannot be initialized in the header file.
const string TextBuddy::MESSAGE_WELCOME_USER = "Welcome to TextBuddy. %s is ready for use\n";
const string TextBuddy::MESSAGE_REQUEST_COMMAND = "command: ";
const string TextBuddy::MESSAGE_ADD_IS_EXECUTED = "added to %s: \"%s\"\n";
const string TextBuddy::MESSAGE_FILE_IS_EMPTY = "%s is empty.\n";
const string TextBuddy::MESSAGE_ITEM_LIST = ". %s\n";
const string TextBuddy::MESSAGE_DELETE_IS_EXECUTED = "deleted from %s: \"";
const string TextBuddy::MESSAGE_ALL_ITEMS_ARE_CLEARED = "all content deleted from %s\n";
const string TextBuddy::MESSAGE_INPUT_ERROR = "Wrong command! You can only input add, clear, delete, display or exit!\n";

const string TextBuddy::COMMAND_ADD = "add";
const string TextBuddy::COMMAND_DISPLAY = "display";
const string TextBuddy::COMMAND_DELETE = "delete";
const string TextBuddy::COMMAND_CLEAR = "clear";
const string TextBuddy::COMMAND_EXIT = "exit";

const int MAX_BUFFER_SIZE = 255;
const int FIRST_SPACE_CHARACTER_POSITION = 1;
char buffer[MAX_BUFFER_SIZE];

TextBuddy::TextBuddy(string file) {
	fileName = file;
	ofstream fout(file, ios::app);
}

TextBuddy::~TextBuddy() {
}

void TextBuddy::mainProgram() {
	showWelcome();
	requestCommand();
}

void TextBuddy::showUser(string message) {
	cout << message;
}

void TextBuddy::showUserItemNumber(int itemNumber) {
	cout << itemNumber;
}

void TextBuddy::showWelcome() {
	sprintf_s(buffer, MESSAGE_WELCOME_USER.c_str(), fileName.c_str());
	showUser(buffer);
}

void TextBuddy::requestCommand() {
	while(true) {
		string command;
		showUser(MESSAGE_REQUEST_COMMAND);
		command = getUserInput();
		executeCommand(command);
		if (command == COMMAND_EXIT) {
			break;
		}
	}
}

int TextBuddy::countNumberOfLines() {
	int numberOfLines = 1;
	ifstream fin (fileName);
	char characterOfTextfile;
	while(fin.get(characterOfTextfile)) {
		if (characterOfTextfile == '\n') {
			numberOfLines++;
		}
	}
	return numberOfLines;
}

string TextBuddy::getUserInput() {
	string userInput;
	cin >> userInput;
	return userInput;
}

//The five options users can choose are respectively add, display, delete, clear or exit.
void TextBuddy::executeCommand(string userCommand) {
	string itemToBeAdded;
	int lineNumberToBeDeleted;

	if (userCommand == COMMAND_ADD) {
		getline(cin, itemToBeAdded);
		if (itemToBeAdded != "") {
			itemToBeAdded = itemToBeAdded.substr(FIRST_SPACE_CHARACTER_POSITION);
		}
		addItem(itemToBeAdded);
	} else if (userCommand == COMMAND_DISPLAY) {
		displayItem();
	} else if (userCommand == COMMAND_DELETE) {
		cin >> lineNumberToBeDeleted;
		deleteItem(lineNumberToBeDeleted);
	} else if (userCommand == COMMAND_CLEAR) {
		clearItem();
	} else if (userCommand == COMMAND_EXIT) {
	} else {
		showUser(MESSAGE_INPUT_ERROR);
	}
}

void TextBuddy::addItem(string item) {
	ofstream fout(fileName, ios::app);
	fout << item << endl;		
	fout.close();
	sprintf_s(buffer, MESSAGE_ADD_IS_EXECUTED.c_str(), fileName.c_str(), item.c_str());
	showUser(buffer);
}

void TextBuddy::displayItem() {
	ifstream fin(fileName);
	if (fin.peek() == EOF) {
		sprintf_s(buffer, MESSAGE_FILE_IS_EMPTY.c_str(), fileName.c_str());
		showUser(buffer);
	}

	string eachLineOfItemList;
	int numberOfItems = 1;
	while(getline(fin,eachLineOfItemList)) { 
		showUserItemNumber(numberOfItems++);
		sprintf_s(buffer, MESSAGE_ITEM_LIST.c_str(), eachLineOfItemList.c_str());
		showUser(buffer);
	}
}

void TextBuddy::deleteItem(int itemNumber) {
	ifstream fin(fileName);
	int numberOfLines = countNumberOfLines();

	const int MAX_STORAGE_SIZE = 1024;
	char* storageOfItems[MAX_STORAGE_SIZE+1];
	for(int i = 1; i <= MAX_STORAGE_SIZE; i++) {
		storageOfItems[i] = new char[MAX_STORAGE_SIZE+1];
	}
	for(int i = 1; i <= numberOfLines; i++) {
		fin.getline(storageOfItems[i], MAX_STORAGE_SIZE);
	}

	sprintf_s(buffer, MESSAGE_DELETE_IS_EXECUTED.c_str(), fileName.c_str());
	showUser(buffer);
	showUser(storageOfItems[itemNumber]);
	showUser("\"\n");

	for(int i = itemNumber; i < countNumberOfLines(); i++) {
		storageOfItems[itemNumber] = storageOfItems[itemNumber+1];
		itemNumber++;
	}

	storageOfItems[itemNumber+1] = "";
	ofstream firstFout(fileName);
	firstFout << "";
    //Not writing the last item to the .txt file here
	//This is to prevent an extra newline character after the last item to be produced by the for-loop below
	for(int i = 1; i <= (numberOfLines - 2); i++) { 
		firstFout << storageOfItems[i] << endl;
	}
	
	//The last item is written to the .txt file here:
	ofstream secondFout(fileName,ios::app);
	secondFout << storageOfItems[numberOfLines - 1];
	firstFout.close();
	secondFout.close();
}

void TextBuddy::clearItem() {
	ofstream fout(fileName);
	fout << "";
	fout.close();
	sprintf(buffer, MESSAGE_ALL_ITEMS_ARE_CLEARED.c_str(), fileName.c_str());
	showUser(buffer);
}

void main(int argc, char* argv[]) {
	string fileName;
	fileName = argv[1];
	TextBuddy run(fileName);
	run.mainProgram();
}