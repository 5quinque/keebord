#include <Keyboard.h>

int keyboardPins[18] = {2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 10, 16, 14, 15, 18, 19, 20, 21};
int rowPins[10] = {keyboardPins[0],
                     keyboardPins[1],
                     keyboardPins[4],
                     keyboardPins[5],
                     keyboardPins[8],
                     keyboardPins[9],
                     keyboardPins[12],
                     keyboardPins[13],
                     keyboardPins[16],
                     keyboardPins[17]
                   };
int columnPins[8] = {keyboardPins[2],
                       keyboardPins[3],
                       keyboardPins[6],
                       keyboardPins[7],
                       keyboardPins[10],
                       keyboardPins[11],
                       keyboardPins[14],
                       keyboardPins[15]
                     };

int key[6] = {0,0,0,0,0,0};

int keymap[] = {
  0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
  56, 55, 54, 53, 52, 51, 50, 49, 48, '7',
  '3', '5', '1', 40, 41, 42, 43, 44, 45, 46,
  36, 35, ']', 33, 'p', 'i', 'r', 'y', 'w', 25,
  'n', 'x', '/', 17, 18, 19, 26, 27, '[', 29,
  'o', 'u', 'e', 't', 'q', 2, 3, 4, 14, 15,
  21, 22, 23, 24, '\'', 20, 'l', 'j', 'd', 'g',
  'a', 5, ',', 'v', 10, 14, 15, 16, 17, 18,
  60, 6, ';', 351, 'f', 'h', 's', 2106, 2187, 138,
  61, 7, 76, 350, 2120, 2114, 175, 2116, 2167, 10,
  'v', 'n', 'x', KEY_LEFT_SHIFT, 1210, 2124, 165, 2126, 2107, 11,
  63, 9, 74, 348, 1410, 2134, 'c', 2136, 'z', 12,
  64, 50, 73, 347, 1610, 144, 415, 2146, 147, 13,
  65, 51, 72, 346, 120, 154, 135, 515, 137, 14,
  66, 52, 71, 345, 130, 164, 215, 116, 127, 15,
  67, 53, 70, 344, 140, 184, 115, 106, 117, 16};  

void setup() {
  Serial.begin(9600); 

  for (int i=0; i<18; i++) {
    pinMode(keyboardPins[i], INPUT);
    digitalWrite(keyboardPins[i], HIGH);
  }
}

void loop() {
  int keyDown;
  int keyUp;
  int i;

  for (int row = 0; row < 10; row++) {
    pinMode(rowPins[row], OUTPUT);
    digitalWrite(rowPins[row], LOW);
  
    for (int col = 0; col < 8; col++) {
      if (!digitalRead(columnPins[col])) {
        keyDown = (row << 4) ^ col;
        setKey( keyDown );
        Serial.print(keyDown);
        Serial.print("\n");
        Serial.print(keymap[keyDown]);
        Serial.print("\n");
        Serial.print("\n");
      } else {
        /* Is this the best way? */
        keyUp = (row << 4) ^ col;
        if (keyUp == 0) {
          continue;
        }
        for (i = 0; i < 6; i++) {
          if ( key[i] == keyUp ) {
            Keyboard.release(keymap[key[i]]);
            //Serial.print("Untting keynumber:");
            //Serial.print(i);
            //Serial.print(" : ");
            //Serial.print(keymap[keyUp]);
            //Serial.print("\n");
            key[i] = 0;
          } 
        }
      }
    }
    
    pinMode(rowPins[row], INPUT);
    digitalWrite(rowPins[row], HIGH);
  }

  sendKey();
  delay(10);
}

/* check if key already set?? */
void setKey (int keyPress) {
  int i;
  for(i = 0; i < 6; i++){
    if (key[i] == 0 || key[i] == keyPress) {
      key[i] = keyPress;
      break;
    }
  }

  // Serial.print("Setting keynumber:");
  // Serial.print(i);
  // Serial.print(" : ");
  // Serial.print(keymap[keyPress]);
  // Serial.print("\n");
}

void sendKey(){
  int i;
  
  for (i = 0; key[i] != 0; i++) {
    if (key[i] != 0) {
      Keyboard.press(keymap[key[i]]);
    }
  }
}

