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
