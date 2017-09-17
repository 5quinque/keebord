#include <Keyboard.h>

// [TODO] fn
#define KEY_FN  0X00
#define ROWS    10
#define COLUMNS 8

int keyboardPins[18] = {2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 10, 16, 14, 15, 18, 19, 20, 21};
int rowPins[10] = {
                    keyboardPins[0],
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
int colPins[8]  = {
                    keyboardPins[2],
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
  '=', KEY_DELETE, '0', '8', '4', '6', '2', KEY_ESC, 0, 0,
  0, 0, 0, 0, 0, 0, '-', '\\', '9', '7',
  '3', '5', '1', 0, 0, 0, 0, 0, 0, 0,
  0, 35, ']', KEY_HOME, 'p', 'i', 'r', 'y', 'w', KEY_TAB,
  'n', 'x', '/', 0, 0, 0, 0, 0, '[', KEY_BACKSPACE,
  'o', 'u', 'e', 't', 'q', 0, 0, 0, 0, 0,
  0, 0, 0, 0, '\'', KEY_RETURN, 'l', 'j', 'd', 'g',
  'a', 0, ',', 'v', 0, 0, 0, 0, 0, 0,
  KEY_RETURN, KEY_PAGE_UP, ';', 0, 'f', 'h', 's', KEY_LEFT_CTRL, 0, 0,
  0, 0, 0, 0, 0, 0, 0, KEY_PAGE_DOWN, 0, ',',
  'v', 'n', 'x', KEY_LEFT_SHIFT, 0, 0, 0, 0, 0, 0,
  0, 0, KEY_UP_ARROW, 0, '/', 'm', 'c', 0, 'z', 0,
  0, 0, 0, 0, 0, 0, 0, 0, KEY_DOWN_ARROW, 0,
  0, ' ', 0, 0, KEY_LEFT_GUI, KEY_END, 0, 0, 0, 0,
  0, 0, 0, 0, KEY_RIGHT_ARROR, 0, KEY_LEFT_ARROW, 0, ' ', 0,
  KEY_LEFT_ALT, KEY_FN};

/*


ESC  1    2    3    4    5    6    7    8    9    0    -    =    \    DEL 
7,   22,  6,   20,  4,   21,  5,   19,  3,   18,  2,   16,  0,   17,  1, 

TAB  Q    W    E    R    T    Y    U    I    O    P    {    }    BS   HOME
39,  54,  38,  52,  36,  53,  37,  51,  35,  50,  34,  48,  32,  49,  33, 

CTL  A    S    D    F    G    H    J    K    L    ;    '    RT   RT   PGUP
87,  70,  86,  68,  84,  69,  85,  67,  83,  66,  82,  64,  80,  65,  81, 

SHT  Z    X    C    V    B    N    M    ,    .    /    UP             PGDN
103, 118, 102, 116, 100, 117, 101, 115, 99,  114, 98,  112, 96,  113, 97,

FN   SP   Alt       Sp             Sp             LEFT DOWN RIGHT     END
151, 134, 150, 132, 148, 133, 149, 131, 147, 130, 146, 128, 144, 129, 145, 


*/

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

  for (int row = 0; row < ROWS; row++) {
    pinMode(rowPins[row], OUTPUT);
    digitalWrite(rowPins[row], LOW);
  
    for (int col = 0; col < COLUMS; col++) {
      if (!digitalRead(colPins[col])) {
        keyDown = (row << 4) ^ col;
        setKey( keyDown );
      } else {
        keyUp = (row << 4) ^ col;
        if (keyUp == 0) {
          continue;
        }
        
        for (int i = 0; i < 6; i++) {
          if ( key[i] == keyUp ) {
            Keyboard.release(keymap[key[i]]);
            key[i] = 0;
            break;
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

void setKey (int keyPress) {
  for(int i = 0; i < 6; i++){
    if (key[i] == 0 || key[i] == keyPress) {
      key[i] = keyPress;
      break;
    }
  }

  Serial.print("Setting keynumber:");
  Serial.print(i);
  Serial.print(" : ");
  Serial.print(keymap[keyPress]);
  Serial.print("\n");
}

void sendKey(){
  for (int i = 0; key[i] != 0; i++) {
    Keyboard.press(keymap[key[i]]);
  }
}

