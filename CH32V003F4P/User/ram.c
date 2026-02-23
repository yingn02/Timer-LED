#include <ch32v00x.h>
#include "debug.h"
#include "ram.h"
#include "core_riscv.h"



/*led type*/
//



/*PWM&SPI*/
u8 color_data[COLOR_DATA_LEN];



/*control sequence*/
Sequence sequence[MAX_SEQUENCE] = {0};
u8 seq_i = 0;



/*led*/
Led led;



/*button*/
u8 button_flag = 0;
u8 button_cnt = 0;



/*mode*/
volatile u8 tick = 0;



/*strobe*/
u16 strobe_cnt = 0;
u8 strobe_on_flag = 0;



/*dimming*/
u8 r_dimming_brightness = 0;
u8 g_dimming_brightness = 0;
u8 b_dimming_brightness = 0;
u16 dimming_cnt = 0;
u8 dimming_direction = 1;



/*streaming*/
u8 led_current;
u8 led_next;
u8 streaming_b = 0;
u8 streaming_g = 0;
u8 streaming_r = 0;
u8 streaming_b2 = 0;
u8 streaming_g2 = 0;
u8 streaming_r2 = 0;
u8 target_animation = 0;
u16 streaming_color_cnt = 0;
u8 streaming_color[COLOR_DATA_LEN/4][3];