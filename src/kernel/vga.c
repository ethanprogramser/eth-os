#include "vga.h"

uint16_t column = 0;
uint16_t line = 0;

uint16_t* const vga = (uint16_t* const) 0xB8000;
const uint16_t default_c = (COLOR8_BLACK << 8) |
(GREEN << 12);

uint16_t curr = default_c;

void Reset() {
    line = 0;
    column = 0;
    //curr = default_c;
    for(uint16_t y = 0; y<height; y++) {
        for(uint16_t x = 0; x<width; x++) {
            vga[y*width+x] = ' ' | curr;
        }
    }
}

void newLine() {
    if(line < height - 1) {
      line++;
      column = 0;
    }
    else {
      scrollUp();
      column = 0;
    }
}

void scrollUp() {
      for(uint16_t y = 0; y<height; y++) {
          for(uint16_t x=0; x<width; x++) {
              vga[(height-1) * width+x] = vga[y*width+x];
          } 
      }

      for(uint16_t x=0; x<width; x++) {
          vga[(height-1) * width + x] = ' ' | curr;
      }
}

void print(const char *s) {
    while(*s) {
      switch(*s) {
        case '\n':
          newLine();
          break;
        case '\r':
          column = 0;
          break;
        case '\t':
          if(column == width) {
              newLine();
          }
          uint16_t tab = 4 - (column % 4);
          while(tab != 0) {
              vga[line*width+(column++)] = ' ' | curr;
              tab--;
          }
          break;
        default: 
          if(column == width) {
              print("hello");
              newLine();
          }
          vga[line * width + (column++)] = *s | curr;
          break;
      }
      s++;
    }
}
