#include "ram.h"
#include "color_data.h"



void set_color_data(u8*color_data, u8 r, u8 g, u8 b)
{
	//set led color of number i
	for (u8 i = 0; i < (COLOR_DATA_LEN/4); i++)
    {
	    //apply color (led number 0~29)
        color_data[i*4 + 1] = b;
		color_data[i*4 + 2] = g;
	 	color_data[i*4 + 3] = r;
	}
}



void half_set_color_data_streaming(u8*color_data, u16 pulse_width)
{
    for (u8 i = 0; i < (COLOR_DATA_LEN/8); i++) //set led color of number i
    {
        led_current = (target_animation + i) % (COLOR_DATA_LEN/8);
        led_next = (led_current + 1) % (COLOR_DATA_LEN/8);

        //make color (led number 0~14)
        streaming_b = streaming_color[led_current][0] + ((streaming_color[led_next][0] - streaming_color[led_current][0]) * streaming_color_cnt) / pulse_width;
        streaming_g = streaming_color[led_current][1] + ((streaming_color[led_next][1] - streaming_color[led_current][1]) * streaming_color_cnt) / pulse_width;
        streaming_r = streaming_color[led_current][2] + ((streaming_color[led_next][2] - streaming_color[led_current][2]) * streaming_color_cnt) / pulse_width;

        //make color (led number 15~29)
        streaming_b2 = streaming_color[led_current+(COLOR_DATA_LEN/8)][0] + ((streaming_color[led_next+(COLOR_DATA_LEN/8)][0] - streaming_color[led_current+(COLOR_DATA_LEN/8)][0]) * streaming_color_cnt) / pulse_width;
        streaming_g2 = streaming_color[led_current+(COLOR_DATA_LEN/8)][1] + ((streaming_color[led_next+(COLOR_DATA_LEN/8)][1] - streaming_color[led_current+(COLOR_DATA_LEN/8)][1]) * streaming_color_cnt) / pulse_width;
        streaming_r2 = streaming_color[led_current+(COLOR_DATA_LEN/8)][2] + ((streaming_color[led_next+(COLOR_DATA_LEN/8)][2] - streaming_color[led_current+(COLOR_DATA_LEN/8)][2]) * streaming_color_cnt) / pulse_width;

        //apply color (led number 0~14)
        color_data[((COLOR_DATA_LEN/2)-1) - (i*4) - 2] = streaming_b;
        color_data[((COLOR_DATA_LEN/2)-1) - (i*4) - 1] = streaming_g;
        color_data[((COLOR_DATA_LEN/2)-1) - (i*4) - 0] = streaming_r;

        //apply color (led number 15~29)
        color_data[(i+(COLOR_DATA_LEN/8))*4 + 1] = streaming_b2;
        color_data[(i+(COLOR_DATA_LEN/8))*4 + 2] = streaming_g2;
        color_data[(i+(COLOR_DATA_LEN/8))*4 + 3] = streaming_r2;
    }
}



void color_data_init()
{
    for (u8 i = 0; i < NUMBER_OF_LED*4; i+=4)
    {
        color_data[i] = 255;
        color_data[i+1] = 0;
        color_data[i+2] = 0;
        color_data[i+3] = 0;
    }
}



void half_streaming_color_init() //half is front, half is rear
{
    u8 half_value = NUMBER_OF_LED/2;
    u8 color_value;
    u8 bgr[3];

    for (u8 i = 0; i < half_value; i++) 
    {
        //calculate
        color_value = 255 - ((i * 256) / half_value);

        if(color_value < 85) //red-- blue++
        {
            bgr[2] = 255 - color_value * 3; //red
            bgr[1] = 0; //green
            bgr[0] = color_value * 3; //blue
        } 
        else if(color_value < 170) //blue-- green++
        {
            color_value -= 85;
            bgr[2] = 0; //red
            bgr[1] = color_value * 3; //green
            bgr[0] = 255 - color_value * 3; //blue
        } 
        else //green-- red++
        {
            color_value -= 170;
            bgr[2] = color_value * 3; //red
            bgr[1] = 255 - color_value * 3; //green
            bgr[0] = 0; //blue
        }
        
        //set front led color
        streaming_color[i][0] = bgr[0]; 
        streaming_color[i][1] = bgr[1];
        streaming_color[i][2] = bgr[2];

        //set rear led color
        streaming_color[i + (NUMBER_OF_LED/2)][0] = bgr[0]; 
        streaming_color[i + (NUMBER_OF_LED/2)][1] = bgr[1]; 
        streaming_color[i + (NUMBER_OF_LED/2)][2] = bgr[2];
    }
}
