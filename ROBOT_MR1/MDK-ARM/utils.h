#include <stdio.h>
#include <math.h>
#include "stm32f4xx.h"

#define PI 3.14159265359

void DATA_SPEED_RUN_LOOP() /// TOC DO <254
{
    int _k, _i;
    DMA_Cmd(DMA1_Stream6, ENABLE);
}

int map_int(int value, int inMin, int inMax, int outMin, int outMax)
{
    return (value - inMin) * (outMax - outMin) / (inMax - inMin) + outMin;
}

// float map_float(float value, float inMin, float inMax, float outMin, float outMax)
// {
//     return (outMin + (((value - inMin) / (inMax - inMin)) * (outMax - outMin))) * 1.0;
// }
//
float radians_to_degrees(float rad)
{
    return (float)(rad * (180.0 / PI));
}

float degrees_to_radians(float degree)
{
    return (float)(degree * (PI / 180.0));
}

// convert encoder counts to radians
float encoders_to_radians(int encoder_count, int encoder_resolution)
{
    return (float)((encoder_count / encoder_resolution) * 2 * PI * 1.0);
}

float encoders_to_degrees(int encoder_count, int encoder_resolution)
{
    return radians_to_degrees(encoders_to_radians(encoder_count, encoder_resolution));
}

// void polar_to_cartersian(float &rho, float &phi, int &x, int &y)
// {
//     x = rho * cos(phi);
//     y = rho * sin(phi);
// }

// void cartersian_to_polar(int &x, int &y, float &rho, float &phi)
// {
//     x = float(x);
//     rho = sqrt(pow(x, 2) + pow(y, 2));
//     phi = atan2(y, x);
// }

int map_MinMax(int value, int min, int max)
{
    value = value > max ? max : value;
    value = value < min ? min : value;
    return value;
}

//====TIMER ====
int _resetTime = 0;
void resetTimer()
{
    _resetTime = time_now;
}

// delay timer (mili seconds)
bool delayTimer(int mili_seconds)
{
    if (abs(time_now - _resetTime) > mili_seconds)
    {
        return true;
    }
    return false;
}