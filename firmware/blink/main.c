#define GetSystemClock()            32000000UL
#define GetPeripheralClock()        (GetSystemClock())
#define GetInstructionClock()       (GetSystemClock() / 2)

#define FCY 32000000ULL
#include <libpic30.h>

#include "Compiler.h"
#include "timer.h"

int main() {
  LATFbits.LATF3 = 0;
  while (1) {
    TRISFbits.TRISF3 = 0;
    int i;
    for(i=0;i<5000;i++){
        __delay_us(100);
    }
    //DelayMs(500);
    TRISFbits.TRISF3 = 1;

    for(i=0;i<5000;i++){
        __delay_us(100);
    }
    
    //DelayMs(500);
  }
  return 0;
}
