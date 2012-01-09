#include "features.h"
#include "snes.h"
#include "protocol.h"
#include "protocol_defs.h"


void SNESConfig(int data_pin,int clock_pin, int latch_pin){
    /*SetPinDigitalOut(clock_pin);
    SetPinDigitalOut(latch_pin);
    SetPinDigitalIn(data_pin);*/
}

static inline void SNESSendStatus(BYTE byte1,BYTE byte2) {
  OUTGOING_MESSAGE msg;
  msg.type = SNES_STATUS;
  msg.args.snes_status.byte1 = byte1;
  msg.args.snes_status.byte2 = byte2;
  AppProtocolSendMessage(&msg);
}
