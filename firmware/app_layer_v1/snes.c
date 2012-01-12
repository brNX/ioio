#include "features.h"
#include "snes.h"
#include "protocol.h"
#include "protocol_defs.h"
#include "timer.h"
#include "pins.h"

#define FCY 16000000ULL
#include <libpic30.h>

static int SNESEnabled = 0;
static int SNESlatchpin = 0;
static int SNESdatapin = 0;
static int SNESclockpin = 0;

static BYTE lastvalues[2]={0,0};

static inline void SNESReportStatus(BYTE byte1, BYTE byte2) {
    OUTGOING_MESSAGE msg;
    msg.type = SNES_STATUS;
    msg.args.snes_status.byte1 = byte1;
    msg.args.snes_status.byte2 = byte2;
    AppProtocolSendMessage(&msg);
}

void SNESConfig(int data_pin, int clock_pin, int latch_pin) {

    // clock and latch as output (open drain)
    // clock is normally high
    SetPinDigitalOut(clock_pin, 1, 1);

    // LATCH is Active HIGH
    SetPinDigitalOut(latch_pin, 0, 1);

    // data as input  pull up
    SetPinDigitalIn(data_pin, 1);

    SNESdatapin = data_pin;
    SNESlatchpin = latch_pin;
    SNESclockpin = clock_pin;
    SNESEnabled = 1;
    lastvalues[0]=0;
    lastvalues[1]=0;
}

void SNESTasks() {
    if (SNESEnabled) {

        int i;
        BYTE byte1 = 0;
        BYTE byte2 = 0;

        //SNES_LATCH_HIGH();
        //SetDigitalOutLevel?
        PinSetLat(SNESlatchpin, 1);
        __delay_us(12);
        //SNES_LATCH_LOW();
        PinSetLat(SNESlatchpin, 0);

        for (i = 0; i < 8; i++) {

            __delay_us(6);
            //SNES_CLOCK_LOW();
            PinSetLat(SNESclockpin, 0);

            byte1 <<= 1;
            if (!PinGetPort(SNESdatapin)) {
                byte1 |= 1;
            }

            __delay_us(6);

            //SNES_CLOCK_HIGH();
            PinSetLat(SNESclockpin, 1);
        }


        for (i = 0; i < 8; i++) {
            
            __delay_us(6);
            //SNES_CLOCK_LOW();
            PinSetLat(SNESclockpin, 0);

            byte1 <<= 1;
            if (!PinGetPort(SNESdatapin)) {
                byte1 |= 1;
            }

            __delay_us(6);

            //SNES_CLOCK_HIGH();
            PinSetLat(SNESclockpin, 1);
        }

        if(byte1!=lastvalues[0] || byte2!=lastvalues[1]){
            lastvalues[0]=byte1;
            lastvalues[1]=byte2;
            SNESReportStatus(byte1, byte2);
        }
    }
}


