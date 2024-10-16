#include "vga.h"

void main(void);
void set_screen_color(uint8_t color);

void set_screen_color(uint8_t color) {
    uint8_t* video_memory = (uint8_t*)0xB8000;

    for (int i = 0; i < width * height * 2; i += 2) {
        video_memory[i + 1] = color; // Set the background color byte
    }
}

void main(void) {
  print("hello");
  set_screen_color(0x1F);
  //print("#######welcome to ethos######\n");
  //print("login:");
}
