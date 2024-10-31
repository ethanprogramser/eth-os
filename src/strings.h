#include "vga.h"
#include "stdint.h"
#include "keyboard.h"


int comp(const char *first, const char *second) {
    uint8_t i = 0;
    uint8_t j = 0;
    while(first[i] != '\0') {
        i++;
    }
    while(second[j] != '\0') {
        if(second[j] != first[j]) {
            return 0;
        }
        j++;
    }
    if(i == j) {
      return 1;
    }
    else {
      return 0;
    }

}

void splitter(const char *tex) { 
}
