#include "features.h"
#include "snes.h"
#include "protocol.h"
#include "protocol_defs.h"

static int SNESEnabled = 0;


void SNESConfig(int data_pin,int clock_pin, int latch_pin){

    // clock and latch as output (open drain)
    // clock is normally high
    SetPinDigitalOut(clock_pin,1,1);

    // LATCH is Active HIGH
    SetPinDigitalOut(latch_pin,0,1);

    // data as input  pull up
    SetPinDigitalIn(data_pin,1);

    SNESEnabled=1;
}

void SNESTasks(){
    if (SNESEnabled){
        //TODO: check shift register and send report
    }
}

static inline void SNESReportStatus(BYTE byte1,BYTE byte2) {
  OUTGOING_MESSAGE msg;
  msg.type = SNES_STATUS;
  msg.args.snes_status.byte1 = byte1;
  msg.args.snes_status.byte2 = byte2;
  AppProtocolSendMessage(&msg);
}
