#import "pitches.h"

const int buzz = 2, red = 3, green = 4, blue = 5, red2 = 6;
int level = 0;
const int maxLevel = 10;
int currentColor;

const short notes[] = {NOTE_C6, NOTE_E6, NOTE_G6, NOTE_A6};

const short TheFinalNotes[] = {NOTE_CS5, NOTE_CS5, NOTE_E5, NOTE_D5, NOTE_B4, NOTE_B4, NOTE_CS5, NOTE_CS5, NOTE_E5, NOTE_DS5, NOTE_B4};
const short TheFinalNotesTime[] = {100, 100, 100, 200, 100, 100, 200, 100, 100, 300, 100};

char colors[10];

void randomize();
void setOutput();
void setInput();

void showing();
int playing();

void winSound();


void setup() {
  pinMode(buzz, OUTPUT);
  Serial.begin(9600);
  Serial.print("seed: "); Serial.print(analogRead(0)); Serial.print("\nsequence:");

  randomSeed(analogRead(0));
  randomize();
}

void loop() { // ######## gameloop
  if(level==10) {
    winSound();
    randomize();
    level = 0;
  }

  showing();
  level += playing();
  Serial.print(' ');
  delay(300);
}

// ### helper functions

void setOutput() {
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(red2, OUTPUT);
}

void setInput() {
  pinMode(red, INPUT);
  pinMode(green, INPUT);
  pinMode(blue, INPUT);
  pinMode(red2, INPUT);
}

// ### game functions

void randomize(){
  for(int i=0; i<maxLevel; i++) {
    char k = (char)random(3, 7);
    Serial.print(k, DEC); Serial.print(" - ");
    colors[i] = k;
  } Serial.print('\n');
}

void showing(){

  setOutput();
  for(int i=0; i<(level+1); i++) {
    delay(100);
    digitalWrite(colors[i], HIGH);
    tone(buzz, notes[colors[i]-3]);
    delay(1000 - (level*50));
    noTone(buzz);
    digitalWrite(colors[i], LOW);
  }
}

int playing(){
  setInput();

  int currentButton, currentLevel = 0;

  while(currentLevel < level+1) {
    for (int i = 3; i < 7; i++) {
     currentButton = digitalRead(i);
     if(currentButton==1){
      Serial.print(i, DEC);
      if(i == colors[currentLevel]){
        currentLevel++; delay(10); while(digitalRead(i)); 
      }else
        return 0;
      }
    }
  }

  return 1;
}

void winSound(){
  for (int i=0; i<11; i++) {
    tone(buzz, TheFinalNotes[i], TheFinalNotesTime[i]);
    delay(TheFinalNotesTime[i] + 50);
  }

  delay(300);
}
