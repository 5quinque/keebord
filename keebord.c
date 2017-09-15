#include <Keyboard.h>

int keyboardPins[18] = {2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 10, 16, 14, 15, 18, 19, 20, 21};
int rowPins[10] = {keyboardPins[0], keyboardPins[1], keyboardPins[4], keyboardPins[5], keyboardPins[8], keyboardPins[9], keyboardPins[12], keyboardPins[13], keyboardPins[16], keyboardPins[17]};
int columnPins[8] = {keyboardPins[2], keyboardPins[3], keyboardPins[6], keyboardPins[7], keyboardPins[10], keyboardPins[11], keyboardPins[14], keyboardPins[15]};

int key[] = {0,0,0,0,0,0};

void setup() {
  Serial.begin(9600); 

  for (int i=0; i<18; i++) {
    pinMode(keyboardPins[i], INPUT);
    digitalWrite(keyboardPins[i], HIGH);
  }
}

void loop() {
  getkeyboardStatus();
}

void setKey (int keyPress) {
  int i;
  for(i = 0; key[i] != 0; i++){}

  key[i] = keyPress;
  Serial.print("Setting keynumber:");
  Serial.print(i);
  Serial.print(" : ");
  Serial.print(keyPress);
  Serial.print("\n");

  // Keyboard.set_modifier(mod[0]|mod[1]);
  // Keyboard.set_key1(key[0]);
  // Keyboard.set_key2(key[1]);
  // Keyboard.set_key3(key[2]);
  // Keyboard.set_key4(key[3]);
  // Keyboard.set_key5(key[4]);
  // Keyboard.set_key6(key[5]);
}

void sendKey(){
  int i;
  //Keyboard.send_now();
  
  
  //Keyboard.set_modifier(mod[0]);

  for (i = 0; key[i] != 0; i++) {
    Keyboard.press(key[i]);
  }
  
  Keyboard.releaseAll();

  clearBuffer();
  // Keyboard.set_key2(key[1]);
  // Keyboard.set_key3(key[2]);
  // Keyboard.set_key4(key[3]);
  // Keyboard.set_key5(key[4]);
  // Keyboard.set_key6(key[5]);
}

void clearBuffer(){
  for(int x = 0; x < 6; x++){ key[x] = 0; }
  //for(int x = 0; x < 2; x++){ mod[x] = 0; }
}

void getkeyboardStatus() {
  int keyboardStatus = 0;
  
  for (int row = 0; row < 10; row++) {
    pinMode(rowPins[row], OUTPUT);
    digitalWrite(rowPins[row], LOW);
  
    for (int col = 0; col < 8; col++) {
      if (!digitalRead(columnPins[col])) {
        setKey( (row << 4) ^ col );
      }
    }
    
    pinMode(rowPins[row], INPUT);
    digitalWrite(rowPins[row], HIGH);
  }

  sendKey();
  delay(10);
}
