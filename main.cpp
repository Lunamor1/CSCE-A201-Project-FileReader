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

	cout << "Do you want a tutorial? (y/n): ";
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