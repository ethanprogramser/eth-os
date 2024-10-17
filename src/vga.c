#include "vga.h"
#include "stdint.h"

uint16_t column = 0;
uint16_t line = 0;
uint16_t* const vga = (uint16_t* const) 0xB8000;
const uint16_t defaultColor = (COLOR8_WHITE << 8) | (COLOR8_BLUE << 12);
uint16_t currentColor = defaultColor;

void Reset(){
    line = 0;
    column = 0;
    currentColor = defaultColor;

    for (uint16_t y = 0; y < height; y++){
        for (uint16_t x = 0; x < width; x++){
            vga[y * width + x] = ' ' | defaultColor;
        }
    }
}

void newLine(){
    if (line < height - 1){
        line++;
        column = 0;
    }
    else{
      scrollUp();
      column = 0;
    }
}

void scrollUp(){
    for (uint16_t y = 0; y < height; y++){
        for (uint16_t x = 0; x < width; x++){
            vga[(y-1) * width + x] = vga[y*width+x];
        }
    }

    for (uint16_t x = 0; x < width; x++){
        vga[(height-1) * width + x] = ' ' | currentColor;
    }
}

void print(const char* s){
    while(*s){
        switch(*s){
            case '\n':
                newLine();
                break;
            case '\r':
                column = 0;
                break;
            case '\b':
                if(column == 8) {
                    vga[line * width + (++column)] = ' ' | currentColor;
                    break;
                }
                if (column == 0 && line != 0){
                    line--;
                    column = width;
                }
                vga[line * width + (--column)] = ' ' | currentColor;
                break;
            case '\t':
                if (column == width){
                    newLine();
                }
                uint16_t tabLen = 4 - (column % 4);
                while (tabLen != 0){
                    vga[line * width + (column++)] = ' ' | currentColor;
                    tabLen--;
                }
                break;
            default:
                if (column == width){
                    newLine();
                }

                vga[line * width + (column++)] = *s | currentColor;
                break;
        }
        s++;
    }
}
