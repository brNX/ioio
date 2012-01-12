#include "features.h"
#include "snes.h"
#include "protocol.h"
#include "protocol_defs.h"
#include "timer.h"
#include "pins.h"

#define FCY 32000000ULL
#include <libpic30.h>

static int SNESEnabled = 0;
static int SNESlatchpin = 0;
static int SNESdatapin = 0;
static int SNESclockpin = 0;

void SNESConfig(int data_pin,int clock_pin, int latch_pin){

    // clock and latch as output (open drain)
    // clock is normally high
    SetPinDigitalOut(clock_pin,1,1);

    // LATCH is Active HIGH
    SetPinDigitalOut(latch_pin,0,1);
    
    // data as input  pull up
    SetPinDigitalIn(data_pin,1);

    SNESdatapin=data_pin;
    SNESlatchpin=latch_pin;
    SNESclockpin=clock_pin;
    SNESEnabled=1;
}

void SNESTasks(){
    if (SNESEnabled){

	int i;
	unsigned char tmp=0;

        //SNES_LATCH_HIGH();
        //SetDigitalOutLevel?
        PinSetLat(SNESlatchpin,1);
        __delay_us(12);
	//_delay_us(12);
	//SNES_LATCH_LOW();

	/*for (i=0; i<8; i++)
	{
		_delay_us(6);
		SNES_CLOCK_LOW();

		tmp <<= 1;
		if (!SNES_GET_DATA()) { tmp |= 1; }

		_delay_us(6);

		SNES_CLOCK_HIGH();
	}
	last_read_controller_bytes[0] = tmp;
	for (i=0; i<8; i++)
	{
		_delay_us(6);

		SNES_CLOCK_LOW();

		// notice that this is different from above. We
		// want the bits to be in reverse-order
		tmp >>= 1;
		if (!SNES_GET_DATA()) { tmp |= 0x80; }

		_delay_us(6);
		SNES_CLOCK_HIGH();
	}
	last_read_controller_bytes[1] = tmp;

}

static char snesChanged(char id)
{
	static int first = 1;
	if (first) { first = 0;  return 1; }

	return memcmp(last_read_controller_bytes,
					last_reported_controller_bytes, GAMEPAD_BYTES);
}*/
    }
}

static inline void SNESReportStatus(BYTE byte1,BYTE byte2) {
  OUTGOING_MESSAGE msg;
  msg.type = SNES_STATUS;
  msg.args.snes_status.byte1 = byte1;
  msg.args.snes_status.byte2 = byte2;
  AppProtocolSendMessage(&msg);
}
