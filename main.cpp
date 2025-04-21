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
		cout << "This program will take a file and turn it into music!\n";
		cout << "To use this program you must make a txt file, put the bpm of your song on the first line, and put notes and their duration on each following line.\n";
		cout << "To write notes, you write the letter name of the note, whether it is flat or sharp (or nothing), then a space, and the length of the note in number form.\n\n";
		cout << "Ex:\n";
		cout << "120 //(<- The bpm)\n";
		cout << "Ab4 4 //(<- A flat 4, for a quarter note)\n";
		cout << "rest 2 //(<- Rest in the song for a half measure)\n";
		cout << "D#6 8 //(<- D sharp 6 for an eigth note)\n";
		cout << "C5 1 //(<- C 5 for a whole note)\n\n";
		cout << "The current list of supported note lengths and their numbers is as follows:\n";
		cout << "1: whole note\n";
		cout << "2: half note\n";
		cout << "3: dotted half note\n";
		cout << "4: quarter note\n";
		cout << "7: dotted eighth note\n";
		cout << "8: eighth note\n";
		cout << "16: sixteenth note\n";
		cout << endl;
	}
	cout << "Enter the name of the text file you want played (with .txt): ";
	getline(cin, fileName);

	user.playFileMusic(fileName);

	return 0;
}