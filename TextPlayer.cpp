#include "TextPlayer.h"
#include <iostream>
#include <Windows.h>
#include <map>
#include <string>
#include <fstream>

TextPlayer::TextPlayer()
{
	/* Full values stored in case needed for later use, but will be rounded & converted to int if used in playFileMusic().
	Currently contains the full range of a piano, but can be added to for even more notes!
	Note: includes duplicates such as "A#0" and "Bb0" for more user freedom in .txt file */
	noteFreq = {
		{"A0", 27.5}, {"A#0", 29.13524}, {"Bb0", 29.13524}, {"B0", 30.86771},
		{"C1", 32.70320}, {"C#1", 34.64783}, {"Db1", 34.64783}, {"D1", 36.70810},
		{"D#1", 38.89087}, {"Eb1", 38.89087}, {"E1", 41.20344}, {"F1", 43.65353},
		{"F#1", 46.24930}, {"Gb1", 46.24930}, {"G1", 48.99943}, {"G#1", 51.91309},
		{"Ab1", 51.91309}, {"A1", 55.0}, {"A#1", 58.27047}, {"Bb1", 58.27047},
		{"B1", 61.73541}, {"C2", 65.40639}, {"C#2", 69.29566}, {"Db2", 69.29566},
		{"D2", 73.41619}, {"D#2", 77.78175}, {"Eb2", 77.78175}, {"E2", 82.40689},
		{"F2", 87.30706}, {"F#2", 92.49861}, {"Gb2", 92.49861}, {"G2", 97.99886},
		{"G#2", 103.8262}, {"Ab2", 103.8262}, {"A2", 110.0}, {"A#2", 116.5409},
		{"Bb2", 116.5409}, {"B2", 123.4708}, {"C3", 130.8128}, {"C#3", 138.5913},
		{"Db3", 138.5913}, {"D3", 146.8324}, {"D#3", 155.5635}, {"Eb3", 155.5635},
		{"E3", 164.8138}, {"F3", 174.6141}, {"F#3", 184.9972}, {"Gb3", 184.9972},
		{"G3", 195.9977}, {"G#3", 207.6523}, {"Ab3", 207.6523}, {"A3", 220.0},
		{"A#3", 233.0819}, {"Bb3", 233.0819}, {"B3", 246.9417}, {"C4", 261.6256},
		{"C#4", 277.1826}, {"Db4", 277.1826}, {"D4", 293.6648}, {"D#4", 311.1270},
		{"Eb4", 311.1270}, {"E4", 329.6276}, {"F4", 349.2282}, {"F#4", 369.9944},
		{"Gb4", 369.9944}, {"G4", 391.9954}, {"G#4", 415.3047}, {"Ab4", 415.3047},
		{"A4", 440.0}, {"A#4", 466.1638}, {"Bb4", 466.1638}, {"B4", 493.8833},
		{"C5", 523.2511}, {"C#5", 554.3653}, {"Db5", 554.3653}, {"D5", 587.3295},
		{"D#5", 622.2540}, {"Eb5", 622.2540}, {"E5", 659.2551}, {"F5", 698.4565},
		{"F#5", 739.9888}, {"Gb5", 739.9888}, {"G5", 783.9909}, {"G#5", 830.6094},
		{"Ab5", 830.6094}, {"A5", 880.0}, {"A#5", 932.3275}, {"Bb5", 932.3275},
		{"B5", 987.7666}, {"C6", 1046.502}, {"C#6", 1108.731}, {"Db6", 1108.731},
		{"D6", 1174.659}, {"D#6", 1244.508}, {"Eb6", 1244.508}, {"E6", 1318.510},
		{"F6", 1396.913}, {"F#6", 1479.978}, {"Gb6", 1479.978}, {"G6", 1567.982},
		{"G#6", 1661.219}, {"Ab6", 1661.219}, {"A6", 1760.0}, {"A#6", 1864.655},
		{"Bb6", 1864.655}, {"B6", 1975.533}, {"C7", 2093.005}, {"C#7", 2217.461},
		{"Db7", 2217.461}, {"D7", 2349.318}, {"D#7", 2489.016}, {"Eb7", 2489.016},
		{"E7", 2637.020}, {"F7", 2793.826}, {"F#7", 2959.955}, {"Gb7", 2959.955},
		{"G7", 3135.963}, {"G#7", 3322.438}, {"Ab7", 3322.438}, {"A7", 3520.0},
		{"A#7", 3729.310}, {"Bb7", 3729.310}, {"B7", 3951.066}, {"C8", 4186.009}
	};

	bpm = 0.0;
	quarterNote = 0.0;
	eighthNote = 0.0;
	sixteenthNote = 0.0;
	halfNote = 0.0;
	dottedHalfNote = 0.0;
	dottedEighthNote = 0.0;
	wholeNote = 0.0;
}
// Seems like a useful function to have access to for these things
int TextPlayer::roundDouble(double num)
{
	return static_cast<int>(round(num));
}

double TextPlayer::findNoteLength(int noteLength) const
{
	if (noteLength == 1) {
		return wholeNote;
	}
	else if (noteLength == 2) {
		return halfNote;
	}
	else if (noteLength == 3) {
		return dottedHalfNote;
	}
	else if (noteLength == 4) {
		return quarterNote;
	}
	else if (noteLength == 8) {
		return eighthNote;
	}
	else if (noteLength == 7) {
		return dottedEighthNote;
	}
	else if (noteLength == 16) {
		return sixteenthNote;
	}
	else {
		return -1;
	}
}

void TextPlayer::playFileMusic(std::string& fileName)
{
	std::ifstream file(fileName);

	if (!file.is_open()) {
		std::cout << "Error: unable to open file " << fileName << std::endl;
		return;
	}

	std::string line;
	int lineNum = 0;

	file >> bpm;
	if (bpm <= 0) {
		std::cout << "Error: provided bpm was not greater than 0. Check line 1 of your file.\n";
		return;
	}
	lineNum++;

	quarterNote = (60.0 / bpm) * 1000.0; // *1000 converts to milliseconds for Beep(), 60/bpm finds how many seconds are necessary
	eighthNote = (quarterNote / 2.0);
	sixteenthNote = (quarterNote / 4.0);
	halfNote = (quarterNote * 2.0);
	dottedHalfNote = (quarterNote * 3.0);
	dottedEighthNote = (quarterNote * 0.75);
	wholeNote = (quarterNote * 4.0);

	std::string currentNote;
	int noteLengthNum;

	while (file >> currentNote >> noteLengthNum) {
		lineNum++;
		double noteLength = findNoteLength(noteLengthNum);
		if (noteLength == -1) {
			std::cout << "Error: invalid note length in file line " << lineNum << std::endl;
			break;
		}
		else {
			if (currentNote == "rest") {
				Sleep(roundDouble(noteLength));
			}
			else {
				if (noteFreq.find(currentNote) == noteFreq.end()) {
					std::cout << "Error: unknown note \"" << currentNote << "\" at line " << lineNum << std::endl;
					break;
				}
				else {
					double freq = noteFreq[currentNote];
					Beep(roundDouble(freq), roundDouble(noteLength));
					Sleep(50);
				}
			}
		}
	}
	
	file.close();
}