// Main for FilePlayer

#include <iostream>
#include <string>
#include <fstream>
#include "TextPlayer.h"

using namespace std;

int main()
{
	TextPlayer user;
	string fileName;
	char userChoice;

	cout << "You can choose to experience a tutorial. This will teach you how to write files to be played as music, and will provide the names of some files currently available to be played.\n"
	     << "Do you want a tutorial? (y/n): ";
	cin >> userChoice;
	cin.ignore();
	cout << endl;

	if (userChoice == 'y') {
		user.playTutorial();
	}

	cout << "Enter the name of the text file you want played (with .txt): ";
	getline(cin, fileName);

	user.playFileMusic(fileName);

	return 0;
}
