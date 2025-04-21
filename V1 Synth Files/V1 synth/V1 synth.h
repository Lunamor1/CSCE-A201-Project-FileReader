#include <windows.h>
#include <conio.h>
#include <iostream>
#include <cmath>

using namespace std;

const int duration = 390;

char getKey() {
    if (_kbhit()) {
        return _getch();
    }
    return '\0'; // no key pressed
}

void playNote(char key, int oct) {
    double freq = 0;
    // While I would like to use the real frencwencys the Beep fucntion uses DWORD or a 32 bit bases inter so I rounded the notes to make it closer to what they really are so say if it was 38.89 it wouldnt be 38 it would be 39 becasue it is closer
    switch (key) {
    case 'a': freq = 33; break;  // C
    case 'w': freq = 35; break;  // C#
    case 's': freq = 37; break;  // D
    case 'e': freq = 39; break;  // D#
    case 'd': freq = 42; break;  // E
    case 'f': freq = 44; break;  // F
    case 't': freq = 46; break;  // F#
    case 'g': freq = 49; break;  // G
    case 'y': freq = 52; break;  // G#
    case 'h': freq = 55; break;  // A
    case 'u': freq = 58; break;  // A#
    case 'j': freq = 62; break;  // B
    case 'k': freq = 33 * pow(2, 1); break;  // C2
    case 'o': freq = 35 * pow(2, 1); break;  // C#2
    case 'l': freq = 37 * pow(2, 1); break;  // D2
    case 'p': freq = 39 * pow(2, 1); break;  // D#2
    case ';': freq = 42 * pow(2, 1); break;  // E2
    default:
        cout << "Unknown key." << endl;
        return;
    }

    int finalFreq = static_cast<int>(freq * pow(2, oct));
    if (finalFreq >= 37 && finalFreq <= 32767)
        Beep(finalFreq, duration);
    else
        cout << "Note out of Beep range: " << finalFreq << " Hz" << endl;
}

int main() {
    int oct = 4; // I use 4 because c4 is known at the home key 

    cout << "Virtual Piano (C4 and beyond)" << endl;
    cout << "Whole steps: a s d f g h j k l ; '" << endl;
    cout << "Half steps: w e t y u o p" << endl;
    cout << "Octave down: z | Octave up: x | Quit: q" << endl;

    while (true) {
        char key = getKey();

        if (key == '\0') continue; // no key pressed

        if (key == 'q') break;

        if (key == 'z') {
            if (oct > 0) oct--;
            cout << "Octave down > C" << oct << endl;
            continue;
        }

        if (key == 'x') {
            if (oct < 8) oct++;
            cout << "Octave up > C" << oct << endl;
            continue;
        }

        playNote(key, oct);
    }

    cout << "Thanks for jamming!" << endl;
    return 0;
}
