/*
  Music player that plays 4 different songs. I have not created these songs
  and give complete credit to those that took the ridiculous amount of time
  to make them. The only edits to the songs have been better naming practices and proper formatting.
*/

#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

// Tracks the current screen/page
int screen = 0;
// Right button state
int rightSwitchState;
// Right button pin
int rightButtonPin = 3;
// Left button state
int leftSwitchState;
// Left button pin
int leftButtonPin = 2;
// Tracks if the song was played
boolean played = false;
// Red light
int redPin = 5;
// Blue light
int bluePin = 4;

//Defines macros for the specic frequency of each note
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

// NB: ALL NOTES DEFINED WITH STANDARD ENGLISH NAMES, EXCEPT FROM "A" 
// THAT IS CALLED WITH THE ITALIAN NAME "LA" BECAUSE A0,A1...ARE THE ANALOG PINS ON ARDUINO.
// (Ab IS CALLED Ab AND NOT LAb)
#define C0  16.35
#define Db0 17.32
#define D0  18.35
#define Eb0 19.45
#define E0  20.60
#define F0  21.83
#define Gb0 23.12
#define G0  24.50
#define Ab0 25.96
#define LA0 27.50
#define Bb0 29.14
#define B0  30.87
#define C1  32.70
#define Db1 34.65
#define D1  36.71
#define Eb1 38.89
#define E1  41.20
#define F1  43.65
#define Gb1 46.25
#define G1  49.00
#define Ab1 51.91
#define LA1 55.00
#define Bb1 58.27
#define B1  61.74
#define C2  65.41
#define Db2 69.30
#define D2  73.42
#define Eb2 77.78
#define E2  82.41
#define F2  87.31
#define Gb2 92.50
#define G2  98.00
#define Ab2 103.83
#define LA2 110.00
#define Bb2 116.54
#define B2  123.47
#define C3  130.81
#define Db3 138.59
#define D3  146.83
#define Eb3 155.56
#define E3  164.81
#define F3  174.61
#define Gb3 185.00
#define G3  196.00
#define Ab3 207.65
#define LA3 220.00
#define Bb3 233.08
#define B3  246.94
#define C4  261.63
#define Db4 277.18
#define D4  293.66
#define Eb4 311.13
#define E4  329.63
#define F4  349.23
#define Gb4 369.99
#define G4  392.00
#define Ab4 415.30
#define LA4 440.00
#define Bb4 466.16
#define B4  493.88
#define C5  523.25
#define Db5 554.37
#define D5  587.33
#define Eb5 622.25
#define E5  659.26
#define F5  698.46
#define Gb5 739.99
#define G5  783.99
#define Ab5 830.61
#define LA5 880.00
#define Bb5 932.33
#define B5  987.77
#define C6  1046.50
#define Db6 1108.73
#define D6  1174.66
#define Eb6 1244.51
#define E6  1318.51
#define F6  1396.91
#define Gb6 1479.98
#define G6  1567.98
#define Ab6 1661.22
#define LA6 1760.00
#define Bb6 1864.66
#define B6  1975.53
#define C7  2093.00
#define Db7 2217.46
#define D7  2349.32
#define Eb7 2489.02
#define E7  2637.02
#define F7  2793.83
#define Gb7 2959.96
#define G7  3135.96
#define Ab7 3322.44
#define LA7 3520.01
#define Bb7 3729.31
#define B7  3951.07
#define C8  4186.01
#define Db8 4434.92
#define D8  4698.64
#define Eb8 4978.03
// DURATION OF THE NOTES 
#define BPM 120     // you can change this value changing all the others
#define H 2*Q       // half 2/4
#define Q 60000/BPM // quarter 1/4 
#define E Q/2       // eighth 1/8
#define S Q/4       // sixteenth 1/16
#define W 4*Q       // whole 4/4

// Plays the Star Wars theme
void playStarWars() {
 // tone(pin, note, duration)
    tone(6,LA3,Q); 
    switchLights(0);
    delay(1+Q); // delay duration should always be 1 ms more than the note in order to separate them.
    tone(6,LA3,Q);
    switchLights(1);
    delay(1+Q);
    tone(6,LA3,Q);
    switchLights(2);
    delay(1+Q);
    tone(6,F3,E+S);
    switchLights(0);
    delay(1+E+S);
    tone(6,C4,S);
    switchLights(3);
    delay(1+S);
    
    tone(6,LA3,Q);
    switchLights(0);
    delay(1+Q);
    tone(6,F3,E+S);
    switchLights(2);
    delay(1+E+S);
    tone(6,C4,S);
    switchLights(1);
    delay(1+S);
    tone(6,LA3,H);
    switchLights(2);
    delay(1+H);
    
    tone(6,E4,Q);
    switchLights(0);
    delay(1+Q); 
    tone(6,E4,Q);
    switchLights(2);
    delay(1+Q);
    tone(6,E4,Q);
    switchLights(1);
    delay(1+Q);
    tone(6,F4,E+S);
    switchLights(2);
    delay(1+E+S);
    tone(6,C4,S);
    switchLights(0);
    delay(1+S);
    
    tone(6,Ab3,Q);
    switchLights(1);
    delay(1+Q);
    tone(6,F3,E+S);
    switchLights(0);
    delay(1+E+S);
    tone(6,C4,S);
    switchLights(2);
    delay(1+S);
    tone(6,LA3,H);
    switchLights(0);
    delay(1+H);
    
    tone(6,LA4,Q);
    switchLights(2);
    delay(1+Q);
    tone(6,LA3,E+S);
    switchLights(1);
    delay(1+E+S);
    tone(6,LA3,S);
    switchLights(0);
    delay(1+S);
    tone(6,LA4,Q);
    switchLights(1);
    delay(1+Q);
    tone(6,Ab4,E+S);
    switchLights(2);
    delay(1+E+S);
    tone(6,G4,S);
    switchLights(1);
    delay(1+S);
    
    tone(6,Gb4,S);
    switchLights(0);
    delay(1+S);
    tone(6,E4,S);
    switchLights(2);
    delay(1+S);
    tone(6,F4,E);
    switchLights(0);
    delay(1+E);
    delay(1+E); // PAUSE
    tone(6,Bb3,E);
    switchLights(1);
    delay(1+E);
    tone(6,Eb4,Q);
    switchLights(2);
    delay(1+Q);
    tone(6,D4,E+S);
    switchLights(1);
    delay(1+E+S);
    tone(6,Db4,S);
    switchLights(2);
    delay(1+S);
    
    tone(6,C4,S);
    switchLights(1);
    delay(1+S);
    tone(6,B3,S);
    switchLights(0);
    delay(1+S);
    tone(6,C4,E);
    switchLights(2);
    delay(1+E);
    delay(1+E); // PAUSE QUASI FINE RIGA
    tone(6,F3,E);
    switchLights(1);
    delay(1+E);
    tone(6,Ab3,Q);
    switchLights(0);
    delay(1+Q);
    tone(6,F3,E+S);
    switchLights(2);
    delay(1+E+S);
    tone(6,LA3,S);
    switchLights(1);
    delay(1+S);
    
    tone(6,C4,Q);
    switchLights(2);
    delay(1+Q);
    tone(6,LA3,E+S);
    switchLights(0);
    delay(1+E+S);
    tone(6,C4,S);
    switchLights(1);
    delay(1+S);
    tone(6,E4,H);
    switchLights(0);
    delay(1+H);
    
    tone(6,LA4,Q);
    switchLights(2);
    delay(1+Q);
    tone(6,LA3,E+S);
    switchLights(1);
    delay(1+E+S);
    tone(6,LA3,S);
    switchLights(0);
    delay(1+S);
    tone(6,LA4,Q);
    switchLights(2);
    delay(1+Q);
    tone(6,Ab4,E+S);
    switchLights(1);
    delay(1+E+S);
    tone(6,G4,S);
    switchLights(2);
    delay(1+S);
    
    tone(6,Gb4,S);
    switchLights(0);
    delay(1+S);
    tone(6,E4,S);
    switchLights(2);
    delay(1+S);
    tone(6,F4,E);
    switchLights(0);
    delay(1+E);
    delay(1+E); // PAUSE
    tone(6,Bb3,E);
    switchLights(1);
    delay(1+E);
    tone(6,Eb4,Q);
    switchLights(0);
    delay(1+Q);
    tone(6,D4,E+S);
    switchLights(2);
    delay(1+E+S);
    tone(6,Db4,S);
    switchLights(1);
    delay(1+S);
    
    tone(6,C4,S);
    switchLights(0);
    delay(1+S);
    tone(6,B3,S);
    switchLights(1);
    delay(1+S);
    tone(6,C4,E);
    switchLights(2);
    delay(1+E);
    delay(1+E); // PAUSE QUASI FINE RIGA
    tone(6,F3,E);
    switchLights(0);
    delay(1+E);
    tone(6,Ab3,Q);
    switchLights(1);
    delay(1+Q);
    tone(6,F3,E+S);
    switchLights(0);
    delay(1+E+S);
    tone(6,C4,S);
    switchLights(2);
    delay(1+S);
    
    tone(6,LA3,Q);
    switchLights(1);
    delay(1+Q);
    tone(6,F3,E+S);
    switchLights(2);
    delay(1+E+S);
    tone(6,C4,S);
    switchLights(0);
    delay(1+S);
    tone(6,LA3,H);
    switchLights(1);
    delay(1+H);
    
    delay(2*H);
    switchLights(3);
}

#define SOUND_B0  31
#define SOUND_C1  33
#define SOUND_CS1 35
#define SOUND_D1  37
#define SOUND_DS1 39
#define SOUND_E1  41
#define SOUND_F1  44
#define SOUND_FS1 46
#define SOUND_G1  49
#define SOUND_GS1 52
#define SOUND_A1  55
#define SOUND_AS1 58
#define SOUND_B1  62
#define SOUND_C2  65
#define SOUND_CS2 69
#define SOUND_D2  73
#define SOUND_DS2 78
#define SOUND_E2  82
#define SOUND_F2  87
#define SOUND_FS2 93
#define SOUND_G2  98
#define SOUND_GS2 104
#define SOUND_A2  110
#define SOUND_AS2 117
#define SOUND_B2  123
#define SOUND_C3  131
#define SOUND_CS3 139
#define SOUND_D3  147
#define SOUND_DS3 156
#define SOUND_E3  165
#define SOUND_F3  175
#define SOUND_FS3 185
#define SOUND_G3  196
#define SOUND_GS3 208
#define SOUND_A3  220
#define SOUND_AS3 233
#define SOUND_B3  247
#define SOUND_C4  262
#define SOUND_CS4 277
#define SOUND_D4  294
#define SOUND_DS4 311
#define SOUND_E4  330
#define SOUND_F4  349
#define SOUND_FS4 370
#define SOUND_G4  392
#define SOUND_GS4 415
#define SOUND_A4  440
#define SOUND_AS4 466
#define SOUND_B4  494
#define SOUND_C5  523
#define SOUND_CS5 554
#define SOUND_D5  587
#define SOUND_DS5 622
#define SOUND_E5  659
#define SOUND_F5  698
#define SOUND_FS5 740
#define SOUND_G5  784
#define SOUND_GS5 831
#define SOUND_A5  880
#define SOUND_AS5 932
#define SOUND_B5  988
#define SOUND_C6  1047
#define SOUND_CS6 1109
#define SOUND_D6  1175
#define SOUND_DS6 1245
#define SOUND_E6  1319
#define SOUND_F6  1397
#define SOUND_FS6 1480
#define SOUND_G6  1568
#define SOUND_GS6 1661
#define SOUND_A6  1760
#define SOUND_AS6 1865
#define SOUND_B6  1976
#define SOUND_C7  2093
#define SOUND_CS7 2217
#define SOUND_D7  2349
#define SOUND_DS7 2489
#define SOUND_E7  2637
#define SOUND_F7  2794
#define SOUND_FS7 2960
#define SOUND_G7  3136
#define SOUND_GS7 3322
#define SOUND_A7  3520
#define SOUND_AS7 3729
#define SOUND_B7  3951
#define SOUND_C8  4186
#define SOUND_CS8 4435
#define SOUND_D8  4699
#define SOUND_DS8 4978

// Mario theme melody
int melody[] = {
  SOUND_E7, SOUND_E7, 0, SOUND_E7, 
  0, SOUND_C7, SOUND_E7, 0,
  SOUND_G7, 0, 0,  0,
  SOUND_G6, 0, 0, 0, 

  SOUND_C7, 0, 0, SOUND_G6, 
  0, 0, SOUND_E6, 0, 
  0, SOUND_A6, 0, SOUND_B6, 
  0, SOUND_AS6, SOUND_A6, 0, 

  SOUND_G6, SOUND_E7, SOUND_G7, 
  SOUND_A7, 0, SOUND_F7, SOUND_G7, 
  0, SOUND_E7, 0,SOUND_C7, 
  SOUND_D7, SOUND_B6, 0, 0,

  SOUND_C7, 0, 0, SOUND_G6, 
  0, 0, SOUND_E6, 0, 
  0, SOUND_A6, 0, SOUND_B6, 
  0, SOUND_AS6, SOUND_A6, 0, 

  SOUND_G6, SOUND_E7, SOUND_G7, 
  SOUND_A7, 0, SOUND_F7, SOUND_G7, 
  0, SOUND_E7, 0,SOUND_C7, 
  SOUND_D7, SOUND_B6, 0, 0
};

// Mario main them tempo
int tempo[] = {
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
};

// Play the Mario theme song
void playMario(){
  int size = sizeof(melody) / sizeof(int);
  for (int thisNote = 0; thisNote < size; thisNote++) {
    // To calculate the note duration, take one second divided by the note type.
    // e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 900 / tempo[thisNote];

    // Start the tone
    buzz(6, melody[thisNote], noteDuration);
    // Pattern of lights based on modulo of thisNote
    if (thisNote % 4 == 0) {
      switchLights(0);
    } else if (thisNote % 3 == 0) {
      switchLights(1);
    } else if (thisNote % 2 == 0) {
      switchLights(2);
    }

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.10;
    delay(pauseBetweenNotes);

    // stop the tone playing:
    buzz(6, 0, noteDuration);
  }
  // Turn lights off
  switchLights(3);
}

// Starts and stops the tone
void buzz(int targetPin, long frequency, long length) {
  long delayValue = 1000000 / frequency / 2; // calculate the delay value between transitions
  // 1 second's worth of microseconds, divided by the frequency, then split in half since
  // there are two phases to each cycle
  long numCycles = frequency * length / 1000; // calculate the number of cycles for proper timing
  // multiply frequency, which is really cycles per second, by the number of seconds to
  // get the total number of cycles to produce
  for (long i = 0; i < numCycles; i++) { // for the calculated length of time...
    digitalWrite(targetPin, HIGH); // write the buzzer pin high to push out the diaphram
    delayMicroseconds(delayValue); // wait for the calculated delay value
    digitalWrite(targetPin, LOW);  // write the buzzer pin low to pull back the diaphram
    delayMicroseconds(delayValue); // wait again or the calculated delay value
  }
}

// Defining note frequency
#define MUSIC_C4  262   
#define MUSIC_D4  294
#define MUSIC_E4  330
#define MUSIC_F4  349
#define MUSIC_G4  392
#define MUSIC_A4  440
#define MUSIC_B4  494
#define MUSIC_C5  523
#define MUSIC_D5  587
#define MUSIC_E5  659
#define MUSIC_F5  698
#define MUSIC_G5  784
#define MUSIC_A5  880
#define MUSIC_B5  988

//Note of the song, 0 is a rest/pulse
int notes[] = {       
  MUSIC_E4, MUSIC_G4, MUSIC_A4, MUSIC_A4, 0, 
  MUSIC_A4, MUSIC_B4, MUSIC_C5, MUSIC_C5, 0, 
  MUSIC_C5, MUSIC_D5, MUSIC_B4, MUSIC_B4, 0,
  MUSIC_A4, MUSIC_G4, MUSIC_A4, 0,
   
  MUSIC_E4, MUSIC_G4, MUSIC_A4, MUSIC_A4, 0, 
  MUSIC_A4, MUSIC_B4, MUSIC_C5, MUSIC_C5, 0, 
  MUSIC_C5, MUSIC_D5, MUSIC_B4, MUSIC_B4, 0,
  MUSIC_A4, MUSIC_G4, MUSIC_A4, 0,
   
  MUSIC_E4, MUSIC_G4, MUSIC_A4, MUSIC_A4, 0, 
  MUSIC_A4, MUSIC_C5, MUSIC_D5, MUSIC_D5, 0, 
  MUSIC_D5, MUSIC_E5, MUSIC_F5, MUSIC_F5, 0,
  MUSIC_E5, MUSIC_D5, MUSIC_E5, MUSIC_A4, 0,
   
  MUSIC_A4, MUSIC_B4, MUSIC_C5, MUSIC_C5, 0, 
  MUSIC_D5, MUSIC_E5, MUSIC_A4, 0, 
  MUSIC_A4, MUSIC_C5, MUSIC_B4, MUSIC_B4, 0,
  MUSIC_C5, MUSIC_A4, MUSIC_B4, 0,
  MUSIC_A4, MUSIC_A4, 
   
  // Repeat of first part
  MUSIC_A4, MUSIC_B4, MUSIC_C5, MUSIC_C5, 0, 
  MUSIC_C5, MUSIC_D5, MUSIC_B4, MUSIC_B4, 0,
  MUSIC_A4, MUSIC_G4, MUSIC_A4, 0,
  MUSIC_E4, MUSIC_G4, MUSIC_A4, MUSIC_A4, 0, 
  MUSIC_A4, MUSIC_B4, MUSIC_C5, MUSIC_C5, 0, 
  MUSIC_C5, MUSIC_D5, MUSIC_B4, MUSIC_B4, 0,
  MUSIC_A4, MUSIC_G4, MUSIC_A4, 0,
   
  MUSIC_E4, MUSIC_G4, MUSIC_A4, MUSIC_A4, 0, 
  MUSIC_A4, MUSIC_C5, MUSIC_D5, MUSIC_D5, 0, 
  MUSIC_D5, MUSIC_E5, MUSIC_F5, MUSIC_F5, 0,
  MUSIC_E5, MUSIC_D5, MUSIC_E5, MUSIC_A4, 0,
  
  MUSIC_A4, MUSIC_B4, MUSIC_C5, MUSIC_C5, 0, 
  MUSIC_D5, MUSIC_E5, MUSIC_A4, 0, 
  MUSIC_A4, MUSIC_C5, MUSIC_B4, MUSIC_B4, 0,
  MUSIC_C5, MUSIC_A4, MUSIC_B4, 0,
  // End of Repeat
   
  MUSIC_E5, 0, 0, MUSIC_F5, 0, 0,
  MUSIC_E5, MUSIC_E5, 0, MUSIC_G5, 0, MUSIC_E5, MUSIC_D5, 0, 0,
  MUSIC_D5, 0, 0, MUSIC_C5, 0, 0,
  MUSIC_B4, MUSIC_C5, 0, MUSIC_B4, 0, MUSIC_A4,
  MUSIC_E5, 0, 0, MUSIC_F5, 0, 0,
  MUSIC_E5, MUSIC_E5, 0, MUSIC_G5, 0, MUSIC_E5, MUSIC_D5, 0, 0,
  MUSIC_D5, 0, 0, MUSIC_C5, 0, 0,
  MUSIC_B4, MUSIC_C5, 0, MUSIC_B4, 0, MUSIC_A4
};

// Duration of each note (in ms) Quarter Note is set to 250 ms
int duration[] = {         
  125, 125, 250, 125, 125, 
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 375, 125, 
  
  125, 125, 250, 125, 125, 
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 375, 125, 
  
  125, 125, 250, 125, 125, 
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 125, 250, 125,
  125, 125, 250, 125, 125, 
  250, 125, 250, 125, 
  125, 125, 250, 125, 125,
  125, 125, 375, 375,
  250, 125,
  
  // Repeat of First Part
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 375, 125, 
  
  125, 125, 250, 125, 125, 
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 375, 125, 
  
  125, 125, 250, 125, 125, 
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 125, 250, 125,
  125, 125, 250, 125, 125, 
  250, 125, 250, 125, 
  125, 125, 250, 125, 125,
  125, 125, 375, 375,
  // End of Repeat
  
  250, 125, 375, 250, 125, 375,
  125, 125, 125, 125, 125, 125, 125, 125, 375,
  250, 125, 375, 250, 125, 375,
  125, 125, 125, 125, 125, 500,
  250, 125, 375, 250, 125, 375,
  125, 125, 125, 125, 125, 125, 125, 125, 375,
  250, 125, 375, 250, 125, 375,
  125, 125, 125, 125, 125, 500
};

// Play Pirates of the Caribbean theme
void playPirates() {
  // 203 is the total number of music notes in the song
  for (int i = 0; i < 203; i++){      
    int wait = duration[i] * 1.5;
    // tone(pin,frequency,duration)
    tone(6,notes[i],wait);
    // Pattern of lights based on modulo of i
    if (i % 4 == 0) {
      switchLights(0);
    } else if (i % 3 == 0) {
      switchLights(1);
    } else if (i % 2 == 0) {
      switchLights(2);
    }
    delay(wait);
  }
  noTone(6);
  // Turn lights off
  switchLights(3);
}

#define Groove_A   550
#define Groove_As  582
#define Groove_B   617
#define Groove_C   654
#define Groove_Cs  693
#define Groove_D   734
#define Groove_Ds  777
#define Groove_E   824
#define Groove_F   873
#define Groove_Fs  925
#define Groove_G   980
#define Groove_Gs  1003
#define Groove_A2  1100
#define Groove_A2s 1165
#define Groove_B2  1234
#define Groove_C3  1308
#define Groove_C3s 1385
#define Groove_D3  1555

float half = 0.5;
float one = 1.0;
float one_half = 1.5;
float two = 2.0;
float two_half = 2.5;
int timing = 400;

// Set the correct tone
void setTone(int pin, int note, int duration) {
  tone(pin, note, duration);
  delay(duration);
  noTone(pin);
}

// Play the Harry Potter them song
void playHarryPotter() {
  setTone(6, Groove_B, timing * one);
  switchLights(0);
  setTone(6, Groove_E, timing * one_half);
  switchLights(1);
  setTone(6, Groove_G, timing * half);
  switchLights(2);
  setTone(6, Groove_F, timing * one);
  switchLights(0);
  setTone(6, Groove_E, timing * two);
  switchLights(1);
  setTone(6, Groove_B2, timing * one);
  switchLights(0);
  setTone(6, Groove_A2, timing * two_half);
  switchLights(2);
  setTone(6, Groove_Fs, timing * two_half);
  switchLights(2);
  
  setTone(6, Groove_E, timing * one_half);
  switchLights(1);
  setTone(6, Groove_G, timing * half);
  switchLights(2);
  setTone(6, Groove_F, timing * one);
  switchLights(0);
  setTone(6, Groove_Ds, timing * two);
  switchLights(1);
  setTone(6, Groove_F, timing * one);
  switchLights(0);
  setTone(6, Groove_B, timing * two_half);
  switchLights(2);

  setTone(6, Groove_B, timing * one);
  switchLights(0);
  setTone(6, Groove_E, timing * one_half);
  switchLights(1);
  setTone(6, Groove_G, timing * half);
  switchLights(2);
  setTone(6, Groove_F, timing * one);
  switchLights(0);
  setTone(6, Groove_E, timing * two);
  switchLights(1);
  setTone(6, Groove_B2, timing * one);
  switchLights(0);
  setTone(6, Groove_A2, timing * two_half);
  switchLights(2);
  setTone(6, Groove_Fs, timing * two_half);
  switchLights(2);
  
  setTone(6, Groove_E, timing * one_half);
  switchLights(1);
  setTone(6, Groove_G, timing * half);
  switchLights(2);
  setTone(6, Groove_F, timing * one);
  switchLights(0);
  setTone(6, Groove_Ds, timing * two);
  switchLights(1);
  setTone(6, Groove_F, timing * one);
  switchLights(0);
  setTone(6, Groove_B, timing * two_half);
  switchLights(2);
  switchLights(3);
}

// Initialize the pins and LCD screen
void setup() {
  // Initialize buttons
  pinMode(leftButtonPin, INPUT);
  pinMode(rightButtonPin, INPUT);
  // Initialize piezo
  pinMode(6, OUTPUT);
  // Initalize screen size
  lcd.begin(16, 2);
  // Initialize lights to low
  digitalWrite(bluePin, LOW);
  digitalWrite(redPin, LOW);
}

// This will run continuously FOR-EV-ER, FOR-EV-ER, FOR-EV-ER
void loop() {
  // Delay is a hack to prevent the crazy LED flicker. Would like to put the screens outside of the loop.
  delay(500);
  
  // Determine the screen and display the correct one
  switch (screen) {
    // Home screen
    case 0: clearScreen();
            // Print title
            lcd.print("Too Cool Music!");
            // Reset the cursor
            lcd.setCursor(0, 1);
            lcd.print("1=left, 2=right");
            // See if the right button have been pressed. Disregard a left button
            // ... because we didn't give them that option
            rightSwitchState = digitalRead(rightButtonPin);
            // If pressed, increment the screen
            if (rightSwitchState == HIGH) {
              screen++;
            }
            break;
            
    // Star Wars theme song
    case 1: // Song has not played yet
            if (!played) {
              clearScreen();
              lcd.print("2. Star wars");
              lcd.setCursor(0, 1);
              lcd.print("1. Play 2. Next");
              // See if the left or right button have been pressed
              rightSwitchState = digitalRead(rightButtonPin);
              leftSwitchState = digitalRead(leftButtonPin);
              // If left button is pressed, play the song
              if (leftSwitchState == HIGH) {
                // Let them know what awesome song is playing
                clearScreen();
                lcd.print("Playing ");
                lcd.setCursor(0, 1);
                lcd.print(" Star Wars");
                // Play the song!
                playStarWars();
                // Set played to true
                played = true;
              // They don't want to hear this song..
              } else if (rightSwitchState == HIGH) {
                screen++;
              }
            // Song has played
            } else {
              clearScreen();
              lcd.print("1. Repeat");
              // Reset the cursor
              lcd.setCursor(0, 1);
              lcd.print("2. Next");
              // See if the left or right button have been pressed
              rightSwitchState = digitalRead(rightButtonPin);
              leftSwitchState = digitalRead(leftButtonPin);
              // If right button is pressed, increment the screen
              if (rightSwitchState == HIGH) {
                nextScreen();
              }
              // If left button is pressed, repeat the song
              if (leftSwitchState == HIGH) {
                clearScreen();
                // Let them know what awesome song is playing
                lcd.print("Playing ");
                lcd.setCursor(0, 1);
                lcd.print(" Star Wars");
                playStarWars();
              }
            }
            break;
            
    // Mario theme song
    case 2: // Song has not played yet
            if (!played) {
              clearScreen();
              lcd.print("2. Mario Bros");
              lcd.setCursor(0, 1);
              lcd.print("1. Play 2. Next");
              // See if the left or right button have been pressed
              rightSwitchState = digitalRead(rightButtonPin);
              leftSwitchState = digitalRead(leftButtonPin);
              // If left button is pressed, play the song
              if (leftSwitchState == HIGH) {
                clearScreen();
                // Let them know what awesome song is playing
                lcd.print("Playing ");
                lcd.setCursor(0, 1);
                lcd.print(" Mario Bros");
                // Play the song!
                playMario();
                // Set played to true
                played = true;
              // They don't want to hear this song..
              } else if (rightSwitchState == HIGH) {
                screen++;
              }
            // Song has played
            } else {
              clearScreen();
              lcd.print("1. Repeat");
              // Reset the cursor
              lcd.setCursor(0, 1);
              lcd.print("2. Next");
              // See if the left or right button have been pressed
              rightSwitchState = digitalRead(rightButtonPin);
              leftSwitchState = digitalRead(leftButtonPin);
              // If right button is pressed, increment the screen
              if (rightSwitchState == HIGH) {
                nextScreen();
              }
              // If left button is pressed, repeat the song
              if (leftSwitchState == HIGH) {
                clearScreen();
                // Let them know what awesome song is playing
                lcd.print("Playing ");
                lcd.setCursor(0, 1);
                lcd.print(" Mario Bros");
                // Play the song!
                playMario();
              }
            }
            break;
            
    // Harry Potter theme song
    case 3: // Song has not played yet
            if (!played) {
              clearScreen();
              lcd.print("3. Harry Potter");
              lcd.setCursor(0, 1);
              lcd.print("1. Play 2. Next");
              // See if the left or right button have been pressed
              rightSwitchState = digitalRead(rightButtonPin);
              leftSwitchState = digitalRead(leftButtonPin);
              // If left button is pressed, play the Harry Potter song
              if (leftSwitchState == HIGH) {
                clearScreen();
                // Let them know what awesome song is playing
                lcd.print("Playing ");
                lcd.setCursor(0, 1);
                lcd.print(" Harry Potter");
                // Play the song!
                playHarryPotter();
                // Set played to true
                played = true;
              // They don't want to hear this song..
              } else if (rightSwitchState == HIGH) {
                screen++;
              }
            // Song has played
            } else {
              clearScreen();
              lcd.print("1. Repeat");
              // Reset the cursor
              lcd.setCursor(0, 1);
              lcd.print("2. Next");
              // See if the left or right button have been pressed
              rightSwitchState = digitalRead(rightButtonPin);
              leftSwitchState = digitalRead(leftButtonPin);
              // If right button is pressed, increment the screen
              if (rightSwitchState == HIGH) {
                nextScreen();
              }
              // If left button is pressed, repeat the song
              if (leftSwitchState == HIGH) {
                clearScreen();
                // Let them know what awesome song is playing
                lcd.print("Playing ");
                lcd.setCursor(0, 1);
                lcd.print(" Harry Potter");
                // Play the song!                  
                playHarryPotter();
              }
            }
            break;
            
    // Pirates of the Caribbean theme song
    case 4: // Song has not played yet
            if (!played) {
              clearScreen();
              lcd.print("4. Pirates");
               lcd.setCursor(0, 1);
              lcd.print("1. Play 2. Next");
              // See if the left or right button have been pressed
              rightSwitchState = digitalRead(rightButtonPin);
              leftSwitchState = digitalRead(leftButtonPin);
              // If left button is pressed, play the Harry Potter song
              if (leftSwitchState == HIGH) {
                clearScreen();
                // Let them know what awesome song is playing
                lcd.print("Playing ");
                lcd.setCursor(0, 1);
                lcd.print(" Rick Roll");
                // Play the song!
                playPirates();
                // Set played to true
                played = true;
              // They don't want to hear this song..
              } else if (rightSwitchState == HIGH) {
                screen = 0;
              }
            // Song has played
            } else {
              clearScreen();
              lcd.print("1. Repeat");
              // Reset the cursor
              lcd.setCursor(0, 1);
              lcd.print("2. Next");
              // See if the left or right button have been pressed
              rightSwitchState = digitalRead(rightButtonPin);
              leftSwitchState = digitalRead(leftButtonPin);
              // If right button is pressed, increment the screen
              if (rightSwitchState == HIGH) {
                nextScreen();
              }
              // If left button is pressed, repeat the song
              if (leftSwitchState == HIGH) {
                clearScreen();
                // Let them know what awesome song is playing
                lcd.print("Playing ");
                lcd.setCursor(0, 1);
                lcd.print(" Rick Roll");
                // Play the song!                  
                playPirates();
              }
            }
            break;
      
    // If they made it this far, things have gone terribly wrong..      
    default:  // Just get this
              screen = 0;
              break;
  }
}

// Clear the LCD screen
void clearScreen() {
  // Clear the screen
  lcd.clear();
  // Reset the cursor
  lcd.setCursor(0,0);
}

// Increment the screen and set played to false
void nextScreen() {
  played = false;
  screen++;
}

// Turn on/off lights with 4 different patterns according to parameter given
void switchLights(int pattern) {
  switch (pattern) {
    // 1 red light on
    case 0: digitalWrite(redPin, HIGH);
            digitalWrite(bluePin, LOW);
            break;
    
    // 1 blue light on
    case 1: digitalWrite(bluePin, HIGH);
            digitalWrite(redPin, LOW);
            break;
            
    // Both lights on
    case 2: digitalWrite(bluePin, HIGH);
            digitalWrite(redPin, HIGH);
    
    // Both lights off
    case 3: digitalWrite(bluePin, LOW);
            digitalWrite(redPin, LOW);
            break;
            
    // Default off
    default:  digitalWrite(bluePin, LOW);
              digitalWrite(redPin, LOW);
              break;
  }
}