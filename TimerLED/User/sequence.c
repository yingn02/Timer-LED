#include "ram.h"
#include "sequence.h"

void led_sequence_init() //operation sequence init (ex. color, strobe, dimming, ...)
{
    sequence[0].r=0; sequence[0].g=0; sequence[0].b=0; sequence[0].ms=0; sequence[0].mode=STROBE;
    sequence[1].r=255; sequence[1].g=255; sequence[1].b=255; sequence[1].ms=1000/ACTIVE_TICK; sequence[1].mode=STROBE;
    sequence[2].r=50; sequence[2].g=50; sequence[2].b=50; sequence[2].ms=500/ACTIVE_TICK; sequence[2].mode=DIMMING;
    sequence[3].r=255; sequence[3].g=255; sequence[3].b=255; sequence[3].ms=100/ACTIVE_TICK; sequence[3].mode=STREAMING;

    led.r = sequence[0].r;
    led.g = sequence[0].g;
    led.b = sequence[0].b;
    led.ms = sequence[0].ms;
    led.mode = sequence[0].mode;
}