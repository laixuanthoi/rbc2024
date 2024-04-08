
// #include "cmsis_os.h"
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include "FreeRTOS.h"
#include "task.h"

#include "config.h"
#include "utils.h"

#include "doc_tay_game.h"
#include "4OmniControler.h"


#include "BasicFunction.h"
#include "ROBOTRUN.h"
#include "WheelController.h"
#include "Arm.h"

vs32 HMI_LOOP;

int xBall_Main, yBall_Main;
int realWith = 300, realHeight = 300;
int armPosX, armPosY;

void HMI_TRAN(vs32 _so_dong)
{
	char *camera = "11111111111111111111110111111111";
	vs32 _i, _chua_cac_bit = 0;
	char _ghep_bit[40];
	char _chu_cac_bit[40];
	_ghep_bit[0] = 0;
	_chu_cac_bit[0] = 0;
	switch (_so_dong)
	{
	case 0:
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1))
		{
			GPIO_WriteBit(GPIOC, GPIO_Pin_15, 0);
			HMI_DMI("ROBOT 2 DANG CHAY SAN XANH:   ", GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_15), 0);
		}
		else
		{
			GPIO_WriteBit(GPIOC, GPIO_Pin_15, 1);
			HMI_DMI("ROBOT 2 DANG CHAY SAN DO:   ", GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_15), 0);
		}

		break;
	case 1:
		HMI_DMI("IMU:", _robotIMUAngle, 1);
		break;
	case 2:
		HMI_DMI("LAZER FRONT:", _lazerFront, 2);
		break;
	case 3:
		HMI_DMI("LAZER LEFT:", _lazerLeft, 3);
		break;
	case 4:
		HMI_DMI("LAZER RIGHT:", _lazerRight, 4);
		break;
	case 5:
		HMI_DMI("EN WH LEFT:", getEncoderRearLeft(), 5);
		break;
	case 6:
		HMI_DMI("EN WH RIGHT:", getEncoderRearRight(), 6);
		break;
	case 7:
		HMI_DMI("EN Front:", getEncoderFront(), 7);
		break;

	case 8:
		HMI_DMI("EN ARM X:", Encoder_Arm_X, 8);
		break;
	case 9:
		HMI_DMI("EN ARM Y:", Encoder_Arm_Y, 9);
		break;
	case 10:
		HMI_DMI("BT BASE:", Bien_Tro_Base, 10);
		break;
	case 11:
		UART_ReceiveFromRaspberry(&xBall_Main, &yBall_Main);
		xBall_Main = map_int(xBall_Main - 160, -160, 160, -160, 160);
		HMI_DMI("X BALL:", xBall_Main, 11);
		break;
	case 12:
		yBall_Main = map_int(120 - yBall_Main, -120, 120, -160, 160);
		HMI_DMI("Y BALL:", yBall_Main, 12);
		break;
	case 13:
		getArmPos2D(&armPosX, &armPosY);
		HMI_DMI("ARM POS X:", armPosX, 13);
		break;
	case 14:
		HMI_DMI("ARM POS Y:", armPosY, 14);
		break;
	case 15:
		//	hien thi phan ngo vao
		sprintf(_ghep_bit, "%d", GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_0)); //
		strcat(_chu_cac_bit, _ghep_bit);
		sprintf(_ghep_bit, "%d", GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_1)); //
		strcat(_chu_cac_bit, _ghep_bit);
		sprintf(_ghep_bit, "%d", GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_14));
		strcat(_chu_cac_bit, _ghep_bit);
		sprintf(_ghep_bit, "%d", GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_15)); //
		strcat(_chu_cac_bit, _ghep_bit);
		sprintf(_ghep_bit, "%d", GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3));
		strcat(_chu_cac_bit, _ghep_bit);
		sprintf(_ghep_bit, "%d", GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_8)); //
		strcat(_chu_cac_bit, _ghep_bit);
		sprintf(_ghep_bit, "%d", GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2)); // CB bong
		strcat(_chu_cac_bit, _ghep_bit);
		sprintf(_ghep_bit, "%d", GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_7));
		strcat(_chu_cac_bit, _ghep_bit);
		sprintf(_ghep_bit, "%d", GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_6));
		strcat(_chu_cac_bit, _ghep_bit);
		sprintf(_ghep_bit, "%d", GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_10));
		strcat(_chu_cac_bit, _ghep_bit);
		sprintf(_ghep_bit, "%d", GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_12));
		strcat(_chu_cac_bit, _ghep_bit);
		sprintf(_ghep_bit, "%d", GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_13));
		strcat(_chu_cac_bit, _ghep_bit);
		sprintf(_ghep_bit, "%d", GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_5)); // nut xanh
		strcat(_chu_cac_bit, _ghep_bit);
		sprintf(_ghep_bit, "%d", GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4));
		strcat(_chu_cac_bit, _ghep_bit);
		sprintf(_ghep_bit, "%d", GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13));
		strcat(_chu_cac_bit, _ghep_bit);
		sprintf(_ghep_bit, "%d", GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_14));
		strcat(_chu_cac_bit, _ghep_bit);
		//										sprintf(_ghep_bit,"%d",cb_dung_chan_da);
		//										strcat(_chu_cac_bit,_ghep_bit);

		HMI_PUTS("I:", _chu_cac_bit, 16);
		break;
	case 16:
		// hien thi phan ngo ra
		sprintf(_ghep_bit, "%d", GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_10));
		strcat(_chu_cac_bit, _ghep_bit);
		sprintf(_ghep_bit, "%d", GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_7));
		strcat(_chu_cac_bit, _ghep_bit);
		sprintf(_ghep_bit, "%d", GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_9));
		strcat(_chu_cac_bit, _ghep_bit);
		sprintf(_ghep_bit, "%d", GPIO_ReadOutputDataBit(GPIOD, GPIO_Pin_10));
		strcat(_chu_cac_bit, _ghep_bit);
		sprintf(_ghep_bit, "%d", GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_11));
		strcat(_chu_cac_bit, _ghep_bit);
		sprintf(_ghep_bit, "%d", GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_12));
		strcat(_chu_cac_bit, _ghep_bit);
		sprintf(_ghep_bit, "%d", GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_13));
		strcat(_chu_cac_bit, _ghep_bit);
		sprintf(_ghep_bit, "%d", GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_14));
		strcat(_chu_cac_bit, _ghep_bit);
		sprintf(_ghep_bit, "%d", GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_15)); // nut do 1
		strcat(_chu_cac_bit, _ghep_bit);
		sprintf(_ghep_bit, "%d", GPIO_ReadOutputDataBit(GPIOD, GPIO_Pin_10));
		strcat(_chu_cac_bit, _ghep_bit);
		sprintf(_ghep_bit, "%d", GPIO_ReadOutputDataBit(GPIOD, GPIO_Pin_14));
		strcat(_chu_cac_bit, _ghep_bit);
		sprintf(_ghep_bit, "%d", GPIO_ReadOutputDataBit(GPIOD, GPIO_Pin_11)); // nut do 2
		strcat(_chu_cac_bit, _ghep_bit);
		sprintf(_ghep_bit, "%d", GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_8)); // nut xanh
		strcat(_chu_cac_bit, _ghep_bit);
		sprintf(_ghep_bit, "%d", GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_11));
		strcat(_chu_cac_bit, _ghep_bit);
		sprintf(_ghep_bit, "%d", GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_12));
		strcat(_chu_cac_bit, _ghep_bit);
		sprintf(_ghep_bit, "%d", GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_6));
		strcat(_chu_cac_bit, _ghep_bit);
		HMI_PUTS("OUT:", _chu_cac_bit, 17);
		break;
	}
}
void HMI_RUN_LOOP(vs32 _cause)
{
	if (HMI_LOOP > _cause)
		HMI_LOOP = 0;
	else
		HMI_LOOP++;
	HMI_TRAN(HMI_LOOP);
}
void Config_Robot(void)
{
	Config_Out_Mode();
	Config_In_Mode();
	Config_pwm_time_t8();
	Config_encoder_timer2_timer3();
	Config_encoder_timer1();

	// Config_encoder_timer4();

	Config_ADC1_DMA();

	Config_int_time6();
	Config_int_time7();

	UART1_DMA_RX(115200);
	UART2_DMA_TX(115200);
	UART3_DMA_RX(115200);
	UART4_DMA_RX(115200);
	UART5_DMA_TX(921600);

	Config_encoder_timer5();
	Config_encoder_timer4();

	vTaskDelay(5);
}
static void taskLCD(void *pvParameters)
{
	while (1)
	{
		HMI_RUN_LOOP(16);
		vTaskDelay(15);
	}
}

static void taskUartCommunicateWithRas(void *pvParameters)
{
	while (1)
	{
		UART_SendToRaspberry();
		vTaskDelay(5);
	}
}

static void taskChongNhieuLazer(void *p)
{
	int lazerLeftCount = 0, lazerLeftSum = 0;
	int lazerRightCount = 0, lazerRightSum = 0;
	int lazerFrontCount = 0, lazerFrontSum = 0;

	int numCounter = 100;
	while (1)
	{
		vTaskDelay(5);

		// front
		if (lazerFrontCount++ < numCounter)
		{
			lazerFrontSum += Lazer_Front;
		}
		else
		{
			_lazerFront = lazerFrontSum / numCounter;
			lazerFrontCount = 0;
			lazerFrontSum = 0;
		}

		// right
		if (lazerRightCount++ < numCounter)
		{
			lazerRightSum += Lazer_Right;
		}
		else
		{
			_lazerRight = lazerRightSum / numCounter;
			lazerRightCount = 0;
			lazerRightSum = 0;
		}
		// left
		if (lazerLeftCount++ < numCounter)
		{
			lazerLeftSum += Lazer_Left;
		}
		else
		{
			_lazerLeft = lazerLeftSum / numCounter;
			lazerLeftCount = 0;
			lazerLeftSum = 0;
		}
	}
}

static void taskRobotAnalytics(void *pvParameters)
{
	while (1)
	{
		robotAnalytics();
		vTaskDelay(5);
	}
}
static void taskMain(void *pvParameters)
{
	Config_Robot();

	xTaskCreate(taskUartCommunicateWithRas, (signed char *)"taskUartCommunicateWithRas", 256, NULL, 0, NULL);
	xTaskCreate(taskChongNhieuLazer, (signed char *)"taskChongNhieuLazer", 256, NULL, 0, NULL);
	xTaskCreate(taskRobotAnalytics, (signed char *)"taskRobotAnalytics", 256, NULL, 0, NULL);
	// reset encoder chay va imu
	robotResetIMU();
	RESET_ENCODER_WH();

	resetRobotArm();
	resetBase();

	// while (moveArmYByMilimet(10, 50))
	// 	vTaskDelay(5);
	// stopArmY();

	// // move arm to XY
	// while (moveArmToXY(0, 100))
	// 	vTaskDelay(5);
	// stopArmX();
	// stopBase();

	// // while (rotateGripperByAngle(60, 50))
	// // 	vTaskDelay(5);
	// // stopGripper();

	// trackingBall();
	//trackingBall();
	while (1)
	{
		if (!Nut_1)
		{
			if(SanNe) startSanXanh();
			else startSanDo();
			vTaskDelay(5);
		}
		if (!Nut_2)
		{
			if(SanNe) restartXanh();
			else restartDo();
			vTaskDelay(5);
		}
		
	}
}
int main(void)
{
	xTaskCreate(taskMain, (signed char *)"taskMain", 256, NULL, 0, NULL);
	xTaskCreate(taskLCD, (signed char *)"taskLCD", 256, NULL, 0, NULL);

	vTaskStartScheduler();
}