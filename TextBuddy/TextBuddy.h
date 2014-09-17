#include <iostream>
#include <string>

using namespace std;

//TextBuddy allows users to create a .txt file for adding, displaying, deleting and clearing records.
class TextBuddy {
public:
	//For creating a .txt file for the user.
	TextBuddy(string fileName);
	~TextBuddy();
	//The program begins here.
	void mainProgram();

	void showUser(string message);
	//For displaying the items numbers sequentially in the items list.
	void showUserItemNumber(int itemNumber);
	void showWelcome();
	void requestCommand();
	//For returning the number of lines in the user's .txt file.
	int countNumberOfLines();

	string getUserInput();
	void executeCommand(string userCommand);
	void addItem(string item);
	void displayItem();
	void deleteItem(int itemNumber);
	void clearItem();

private:
	static const string MESSAGE_WELCOME_USER;
	static const string MESSAGE_REQUEST_COMMAND;
	static const string MESSAGE_ADD_IS_EXECUTED;
	static const string MESSAGE_FILE_IS_EMPTY;
	static const string MESSAGE_ITEM_LIST;
	static const string MESSAGE_DELETE_IS_EXECUTED;
	static const string MESSAGE_ALL_ITEMS_ARE_CLEARED;
	static const string MESSAGE_INPUT_ERROR;

	static const string COMMAND_ADD;
	static const string COMMAND_DISPLAY;
	static const string COMMAND_DELETE;
	static const string COMMAND_CLEAR;
	static const string COMMAND_EXIT;

	string fileName;
};