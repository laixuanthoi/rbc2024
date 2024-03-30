#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_i2c.h"
#include "stm32f4xx_rcc.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "stdio.h"

vu8 DATA_SPEED[60] = {
	255, 1, 0, 0,
	255, 2, 0, 0,
	255, 3, 0, 0,
	255, 4, 0, 0,
	255, 5, 0, 0,
	255, 6, 0, 0,
	255, 7, 0, 0,
}

#define ADC1_DR_ADDRESS ((uint32_t)0x4001204C)

//--- 3 Wheels Omni
#define DIA_CHI_START1 DATA_SPEED[0] = 255
#define ID1 DATA_SPEED[1] = 1
#define MOTOR_0H DATA_SPEED[3]
#define MOTOR_0H_NEXT DATA_SPEED[2] = 0
#define MOTOR_0H_BACK DATA_SPEED[2] = 1

#define DIA_CHI_START2 DATA_SPEED[4] = 255
#define ID2 DATA_SPEED[5] = 2
#define MOTOR_4H DATA_SPEED[7]
#define MOTOR_4H_NEXT DATA_SPEED[6] = 1
#define MOTOR_4H_BACK DATA_SPEED[6] = 0


#define DIA_CHI_START3 DATA_SPEED[8] = 255
#define ID3 DATA_SPEED[9] = 3
#define MOTOR_8H DATA_SPEED[11]
#define MOTOR_8H_NEXT DATA_SPEED[10] = 1
#define MOTOR_8H_BACK DATA_SPEED[10] = 0



//-----------------------MAM XOAY TRUC X Y-----------------//
#define DIA_CHI_START4 DATA_SPEED[12] = 255
#define ID4 DATA_SPEED[13] = 4
#define Mor_Lat_Bong_Thuan DATA_SPEED[14] = 1
#define Mor_Lat_Bong_Nghich DATA_SPEED[14] = 0
#define Mor_Lat_Bong DATA_SPEED[15]

#define DIA_CHI_START5 DATA_SPEED[16] = 255
#define ID5 DATA_SPEED[17] = 5
#define Mor_Mam_Thuan DATA_SPEED[18] = 1
#define Mor_Mam_Nghich DATA_SPEED[18] = 0
#define Mor_Mam DATA_SPEED[19]

#define DIA_CHI_START6 DATA_SPEED[20] = 255
#define ID6 DATA_SPEED[21] = 6
#define Mor_Y_Xuong DATA_SPEED[22] = 0
#define Mor_Y_Len DATA_SPEED[22] = 1
#define Mor_Y DATA_SPEED[23]

#define DIA_CHI_START7 DATA_SPEED[24] = 255
#define ID7 DATA_SPEED[25] = 6
#define Mor_X_Vao DATA_SPEED[26] = 0
#define Mor_X_Ra DATA_SPEED[26] = 1
#define Mor_X DATA_SPEED[27]

#define Mor_Hut TIM5->CCR2

//=============================ADC DMI======================================//

#define cam_bien_laze_phai _ADC1_Value[6]
#define cam_bien_laze_trai _ADC1_Value[5]
#define cam_bien_laze_truoc _ADC1_Value[4]
// #define cam_bien_laze_sau								_ADC1_Value[7]



