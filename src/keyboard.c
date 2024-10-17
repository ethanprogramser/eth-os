#include "stdint.h"
#include "util.h"
#include "idt.h"
#include "stdlib/stdio.h"
#include "keyboard.h"
#include "vga.h"

bool capsOn;
bool capsLock;

char text[100] = { 0 };

const uint32_t UNKNOWN = 0xFFFFFFFF;
const uint32_t ESC = 0xFFFFFFFF - 1;
const uint32_t CTRL = 0xFFFFFFFF - 2;
const uint32_t LSHFT = 0xFFFFFFFF - 3;
const uint32_t RSHFT = 0xFFFFFFFF - 4;
const uint32_t ALT = 0xFFFFFFFF - 5;
const uint32_t F1 = 0xFFFFFFFF - 6;
const uint32_t F2 = 0xFFFFFFFF - 7;
const uint32_t F3 = 0xFFFFFFFF - 8;
const uint32_t F4 = 0xFFFFFFFF - 9;
const uint32_t F5 = 0xFFFFFFFF - 10;
const uint32_t F6 = 0xFFFFFFFF - 11;
const uint32_t F7 = 0xFFFFFFFF - 12;
const uint32_t F8 = 0xFFFFFFFF - 13;
const uint32_t F9 = 0xFFFFFFFF - 14;
const uint32_t F10 = 0xFFFFFFFF - 15;
const uint32_t F11 = 0xFFFFFFFF - 16;
const uint32_t F12 = 0xFFFFFFFF - 17;
const uint32_t SCRLCK = 0xFFFFFFFF - 18;
const uint32_t HOME = 0xFFFFFFFF - 19;
const uint32_t UP = 0xFFFFFFFF - 20;
const uint32_t LEFT = 0xFFFFFFFF - 21;
const uint32_t RIGHT = 0xFFFFFFFF - 22;
const uint32_t DOWN = 0xFFFFFFFF - 23;
const uint32_t PGUP = 0xFFFFFFFF - 24;
const uint32_t PGDOWN = 0xFFFFFFFF - 25;
const uint32_t END = 0xFFFFFFFF - 26;
const uint32_t INS = 0xFFFFFFFF - 27;
const uint32_t DEL = 0xFFFFFFFF - 28;
const uint32_t CAPS = 0xFFFFFFFF - 29;
const uint32_t NONE = 0xFFFFFFFF - 30;
const uint32_t ALTGR = 0xFFFFFFFF - 31;
const uint32_t NUMLCK = 0xFFFFFFFF - 32;


const uint32_t lowercase[128] = {
UNKNOWN,ESC,'1','2','3','4','5','6','7','8',
'9','0','-','=','\b','\t','q','w','e','r',
't','y','u','i','o','p','[',']','\n',CTRL,
'a','s','d','f','g','h','j','k','l',';',
'\'','`',LSHFT,'\\','z','x','c','v','b','n','m',',',
'.','/',RSHFT,'*',ALT,' ',CAPS,F1,F2,F3,F4,F5,F6,F7,F8,F9,F10,NUMLCK,SCRLCK,HOME,UP,PGUP,'-',LEFT,UNKNOWN,RIGHT,
'+',END,DOWN,PGDOWN,INS,DEL,UNKNOWN,UNKNOWN,UNKNOWN,F11,F12,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,
UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,
UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,
UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN
};
const uint32_t uppercase[128] = {
    UNKNOWN,ESC,'!','@','#','$','%','^','&','*','(',')','_','+','\b','\t','Q','W','E','R',
'T','Y','U','I','O','P','{','}','\n',CTRL,'A','S','D','F','G','H','J','K','L',':','"','~',LSHFT,'|','Z','X','C',
'V','B','N','M','<','>','?',RSHFT,'*',ALT,' ',CAPS,F1,F2,F3,F4,F5,F6,F7,F8,F9,F10,NUMLCK,SCRLCK,HOME,UP,PGUP,'-',
LEFT,UNKNOWN,RIGHT,'+',END,DOWN,PGDOWN,INS,DEL,UNKNOWN,UNKNOWN,UNKNOWN,F11,F12,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,
UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,
UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,
UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN
};

const uint32_t val[128] = {'c'};


void append(char *part) {
  uint8_t i = 0;
  uint8_t j = 0;
  while(text[i] != '\0') {
      i++;
  }
  while(part[j] != '\0') {
    text[i] = part[j];
    i++;
    j++;
  }
}

void rm() {
    uint8_t i = 0;
    while(text[i] != '\0') {
        i++;
    }
    text[--i] = text[i];
}

void clear() {
  uint8_t p = 0;
  while(text[p] != '\0') {
      text[p] = '\0';
      p++;
  }
}

void delp(char p, char *t) {
    if(p == 0) {
      append(t);
      print(t);
    }
}

void parser(uint8_t code) {
    char buff[100];
    uint8_t i = 0;
    while(text[i] != lowercase[code]) {
        i++;
    }
    for(uint8_t p = 0;p > i;p++) {
        buff[p] = text[p];
    }
    print(buff);
}


void keyboardHandler(struct InterruptRegisters *regs){
    char scanCode = inPortB(0x60) & 0x7F; //What key is pressed
    char press = inPortB(0x60) & 0x80; //Press down, or released

    switch(scanCode){
        case 1:
        case 29:
        case 16:
          delp(press, "q");
          print("\n");
          print(text);
          break;
        case 17:
          delp(press, "w");
          break;
        case 18:
          delp(press, "e");
          break;
        case 19:
          delp(press, "r");
          break;
        case 20:
          delp(press, "t");
          break;
        case 21:
          delp(press, "y");
          break;
        case 22:
          delp(press, "u");
          break;
        case 23:
          delp(press, "i");
          break;
        case 24:
          delp(press, "o");
          break;
        case 25:
          delp(press, "p");
          break;
        case 30:
          delp(press, "a");
          break;
        case 31:
          delp(press, "s");
          break;
        case 32:
          delp(press, "d");
          break;
        case 33:
          delp(press, "f");
          break;
        case 34:
          delp(press, "g");
          break;
        case 35:
          delp(press, "h");
          break;
        case 36:
          delp(press, "j");
          break;
        case 37:
          delp(press, "k");
          break;
        case 38:
          delp(press, "l");
          break;
        case 45:
          delp(press, "z");
          break;
        case 46:
          delp(press, "c");
          break;
        case 47:
          delp(press, "v");
          break;
        case 48:
          delp(press, "b");
          break;
        case 49:
          delp(press, "n");
          break;
        case 50:
          delp(press, "m");
          break;
        case 57:
          delp(press, " "); 
          break;
        case 56:
        case 59:
        case 60:
        case 61:
        case 62:
        case 63:
        case 64:
        case 65:
        case 66:
        case 67:
        case 68:
        case 87:
        case 88:
            break;
        case 42:
            //shift key
            if (press == 0){
                capsOn = true;
            }else{
                capsOn = false;
            }
            break;
        case 58:
            if (!capsLock && press == 0){
                capsLock = true;
            }else if (capsLock && press == 0){
                capsLock = false;
            }
            break;
        default:
            if (press == 0){
                if(lowercase[scanCode] == '\b') {
                    rm();
                }
                if(lowercase[scanCode] == '\n') {
                    //print("\nethos-->");
                    print("\n");
                    print(text);
                    print("\nethos-->");
                    //parser(57);
                    clear();
                }
                else {
                  if (capsOn || capsLock){
                    printf("%c", uppercase[scanCode]);
                  }
                  else{
                    printf("%c", lowercase[scanCode]);
                  } 
                }
            }

            
    }
    
}

void initKeyboard(){
    capsOn = false;
    capsLock = false;
    irq_install_handler(1,&keyboardHandler);
}


