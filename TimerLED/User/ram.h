#include "debug.h"



/*led type*/
#define PWM 0
#define SPI 1
#define LED_TYPE PWM



/*PWM&SPI*/
#define NUMBER_OF_LED 30
#define COLOR_DATA_LEN NUMBER_OF_LED*4

extern u8 color_data[COLOR_DATA_LEN];



/*control sequence*/
#define MAX_SEQUENCE 4

typedef struct{
	u8 r;
	u8 g;
	u8 b;
	u16 ms;
	u8 mode;
}Sequence;

extern Sequence sequence[MAX_SEQUENCE];
extern u8 seq_i;



/*led*/
typedef struct{
	u8 r;
	u8 g;
	u8 b;
	u16 ms;
	u8 mode;
}Led;

extern Led led;



/*button*/
extern u8 button_flag;
extern u8 button_cnt;



/*mode*/
#define STROBE 1
#define DIMMING 2
#define STREAMING 3

extern volatile u8 tick;
#define ACTIVE_TICK 5



/*strobe*/
extern u16 strobe_cnt;
extern u8 strobe_on_flag;



/*dimming*/
extern u8 r_dimming_brightness;
extern u8 g_dimming_brightness;
extern u8 b_dimming_brightness;
extern u16 dimming_cnt;
extern u8 dimming_direction;



/*streaming*/
extern u8 led_current;
extern u8 led_next;
extern u8 streaming_b;
extern u8 streaming_g;
extern u8 streaming_r;
extern u8 streaming_b2;
extern u8 streaming_g2;
extern u8 streaming_r2;
extern u8 target_animation;
extern u16 streaming_color_cnt;
extern u8 streaming_color[COLOR_DATA_LEN/4][3];
