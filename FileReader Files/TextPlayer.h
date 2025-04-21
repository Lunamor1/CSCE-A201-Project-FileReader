// This class is made to take a file that user writes and play music after reading through the file.
// Instructions on how to use the class and how to make a .txt file that is readable are included in playTutorial().

#pragma once

#ifndef TEXT_PLAYER_H
#define Text_PLAYER_H

#include <map> 
#include <string>
class TextPlayer
{
private:
	std::map<std::string, double> noteFreq;

	int bpm;
	double quarterNote;
	double eighthNote;
	double sixteenthNote;
	double halfNote;
	double dottedHalfNote;
	double dottedEighthNote;
	double wholeNote;

public:
	TextPlayer();
	int roundDouble(double num);
	double findNoteLength(int noteLength) const;
	void playFileMusic(std::string& fileName);
	void playTutorial();
};

#endif
