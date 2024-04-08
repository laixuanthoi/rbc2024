// ARM X
#define MIN_ARM_X_ENCODER -6000
#define MAX_ARM_X_ENCODER -10
#define MIN_ARM_X_MOTOR_SPEED 2
#define MAX_ARM_X_MOTOR_SPEED 250
#define ARM_X_LENGTH 380 // 38cm

// ARM Y
#define MIN_ARM_Y_ENCODER 10
#define MAX_ARM_Y_ENCODER 1800
#define MIN_ARM_Y_MOTOR_SPEED 2
#define MAX_ARM_Y_MOTOR_SPEED 50
#define ARM_Y_LENGTH 360 // 36 cm

// BASE
#define MIN_BIEN_TRO_BASE 70
#define MAX_BIEN_TRO_BASE 890
#define MIN_ANGLE_BASE 0
#define MAX_ANGLE_BASE 270
#define MIN_BASE_MOTOR_SPEED 2
#define MAX_BASE_MOTOR_SPEED 180

// GRIPPER
#define MIN_BIEN_TRO_GRIPPER 300
#define MAX_BIEN_TRO_GRIPPER 800
#define MIN_ANGLE_GRIPPER 0
#define MAX_ANGLE_GRIPPER 120
#define MIN_GRIPPER_MOTOR_SPEED 2
#define MAX_GRIPPER_MOTOR_SPEED 90

// MOTOR HUT
#define MIN_MOTOR_HUT_SPEED 800
#define MAX_MOTOR_HUT_SPEED 2000

#define IMAGE_WIDTH 320
#define IMAGE_HEIGHT 240

#define MY_PI 3.14159265358979323846

int xBall = 0, yBall = 0;
int checkBallgan = 3;


// SEND uart --> Ras

void UART_SendToRaspberry()
{
    if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0)
    {
        USART_SendData(USART3, (uint8_t)0);
    }
    if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 1)
    {
        USART_SendData(USART3, (uint8_t)1);
    }
    vTaskDelay(100);
}
// receive uart from ras
void UART_ReceiveFromRaspberry(int *x, int *y)
{
    if (GP_BTN[0] > 0 && GP_BTN[0] < 255)
    {
        *x = map_int(GP_BTN[0], 1, 254, 1, IMAGE_WIDTH - 1);
    }
    else
    {
        *x = -1;
    }

    if (GP_BTN[1] > 0 && GP_BTN[1] < 255)
    {
        *y = map_int(GP_BTN[1], 1, 254, 1, IMAGE_HEIGHT - 1);
    }
    else
    {
        *y = -1;
    }
}

void resetEncoderArmX()
{
    TIM5->CNT = 0;
    num_over_t5 = 0;
}

void resetEncoderArmY()
{
    TIM3->CNT = 0;
    num_over_t3 = 0;
}

int getEncoderArmX()
{
    int en, enOld = Encoder_Arm_X;
    int i = 0;
    while (i < 2)
    {
        en = Encoder_Arm_X;
        if (abs(en - enOld) < 50)
            i++;
        enOld = en;
    }
    return en;
}

int getEncoderArmY()
{
    int en, enOld = Encoder_Arm_Y;
    int i = 0;
    while (i < 2)
    {
        en = Encoder_Arm_Y;
        if (abs(en - enOld) < 50)
            i++;
        enOld = en;
    }
    return en;
}

int getBienTroBase()
{
    int en, enOld = Bien_Tro_Base;
    int i = 0;
    while (i < 2)
    {
        en = Bien_Tro_Base;
        if (abs(en - enOld) < 50)
            i++;
        enOld = en;
    }
    return abs(en);
}

int getBienTroGripper()
{
    int en, enOld = Bien_Tro_Gripper;
    int i = 0;
    while (i < 2)
    {
        en = Bien_Tro_Gripper;
        if (abs(en - enOld) < 50)
            i++;
        enOld = en;
    }
    return abs(en);
}

// === ARM X ===
bool moveArmXByEncoder(int targetEncoder, int targetSpeed)
{
    int currentEncoder = getEncoderArmX();
    targetEncoder = map_MinMax(targetEncoder, MIN_ARM_X_ENCODER, MAX_ARM_X_ENCODER);
    targetSpeed = map_MinMax(targetSpeed, MIN_ARM_X_MOTOR_SPEED, MAX_ARM_X_MOTOR_SPEED);

    if (abs(currentEncoder - targetEncoder) < 10)
    {
        // Motor_Arm_X_Speed = MIN_ARM_X_MOTOR_SPEED;
        return false;
    }
    else
    {
        if (currentEncoder > targetEncoder)
        {
            Motor_Arm_X_Direct_Out;
        }
        else
        {
            Motor_Arm_X_Direct_In;
        }
        Motor_Arm_X_Speed = targetSpeed;
        return true;
    }
}

bool moveArmXByMilimet(int targetMilimet, int targetSpeed)
{
    int targetEncoder = map_int(targetMilimet, 0, ARM_X_LENGTH, MAX_ARM_X_ENCODER, MIN_ARM_X_ENCODER);
    return moveArmXByEncoder(targetEncoder, targetSpeed);
}

void stopArmX()
{
    Motor_Arm_X_Speed = 2;
}

// === ARM Y ===
bool moveArmYByEncoder(int targetEncoder, int targetSpeed)
{
    targetEncoder = map_MinMax(targetEncoder, MIN_ARM_Y_ENCODER, MAX_ARM_Y_ENCODER);
    targetSpeed = map_MinMax(targetSpeed, MIN_ARM_Y_MOTOR_SPEED, MAX_ARM_Y_MOTOR_SPEED);

    if (abs(getEncoderArmY() - targetEncoder) < 20)
    {
        // Motor_Arm_Y_Speed = MIN_ARM_Y_MOTOR_SPEED;
        return false;
    }
    else
    {
        if (getEncoderArmY() > targetEncoder)
        {
            Motor_Arm_Y_Direct_Up;
        }
        else
        {
            Motor_Arm_Y_Direct_Down;
        }
        Motor_Arm_Y_Speed = targetSpeed;
        return true;
    }
}

bool moveArmYByMilimet(int targetMilimet, int targetSpeed)
{
    int targetEncoder = map_int(targetMilimet, 0, ARM_Y_LENGTH, MIN_ARM_Y_ENCODER, MAX_ARM_Y_ENCODER);
    return moveArmYByEncoder(targetEncoder, targetSpeed);
}

void moveArmYToTop()
{
    Motor_Arm_Y_Speed = 40;
    Motor_Arm_Y_Direct_Up;
    for (i = 0; i < 50; i++)
        while (Cam_Bien_Tu_Arm_Y_Top)
            vTaskDelay(5);

    for (i = 0; i < 50; i++)
        while (getEncoderArmY() < 20)
            vTaskDelay(5);

    Motor_Arm_Y_Speed = 2;
}

void moveArmYToBottom()
{
    Motor_Arm_Y_Speed = 40;
    Motor_Arm_Y_Direct_Down;
    for (i = 0; i < 50; i++)
        while (Cam_Bien_Tu_Arm_Y_Bottom)
            vTaskDelay(5);

    for (i = 0; i < 50; i++)
        while (getEncoderArmY() < 20)
            vTaskDelay(5);

    Motor_Arm_Y_Speed = 2;
}

void stopArmY()
{
    Motor_Arm_Y_Speed = 2;
}

// === BASE ===
bool rotateBaseByBienTro(int targetBienTro, int targetSpeed)
{
    int currentBienTro = getBienTroBase();
    int speed_temp;

    targetBienTro = map_MinMax(targetBienTro, MIN_BIEN_TRO_BASE, MAX_BIEN_TRO_BASE);
    targetSpeed = map_MinMax(targetSpeed, MIN_BASE_MOTOR_SPEED, MAX_BASE_MOTOR_SPEED);

    if (abs(currentBienTro - targetBienTro) < 2)
    {
        // Motor_Base_Speed = MIN_BASE_MOTOR_SPEED;
        return false;
    }
    else
    {
        if (currentBienTro > targetBienTro) // rotate right
        {
            Motor_Base_Direct_Left;
        }
        else // rotate left
        {
            Motor_Base_Direct_Right;
        }
        // sua cho loi nay
        speed_temp = (int)targetSpeed * abs(currentBienTro - targetBienTro) / 1000;
        speed_temp = map_MinMax(speed_temp, 20, MAX_BASE_MOTOR_SPEED);
        Motor_Base_Speed = speed_temp;
        return true;
    }
}

bool rotateBaseByAngle(int targetAngle, int targetSpeed)
{
    int targetBienTro = map_int(targetAngle, MIN_ANGLE_BASE, MAX_ANGLE_BASE, MIN_BIEN_TRO_BASE, MAX_BIEN_TRO_BASE);
    return rotateBaseByBienTro(targetBienTro, targetSpeed);
}

void stopBase()
{
    Motor_Base_Speed = 2;
}
// === GRIPPER ===
bool rotateGripperByBienTro(int targetBienTro, int targetSpeed)
{
    int currentBienTro = getBienTroGripper();
    targetBienTro = map_MinMax(targetBienTro, MIN_BIEN_TRO_GRIPPER, MAX_BIEN_TRO_GRIPPER);
    targetSpeed = map_MinMax(targetSpeed, MIN_GRIPPER_MOTOR_SPEED, MAX_GRIPPER_MOTOR_SPEED);

    if (abs(currentBienTro - targetBienTro) < 10)
    {
        return false;
    }
    else
    {
        if (currentBienTro > targetBienTro) // rotate up
        {
            Motor_Gripper_Direct_Down;
        }
        else // rotate down
        {

            Motor_Gripper_Direct_Up;
        }
        Motor_Gripper_Speed = targetSpeed;
        return true;
    }
}

bool rotateGripperByAngle(int targetAngle, int targetSpeed)
{
    int targetBienTro = map_int(targetAngle, MIN_ANGLE_GRIPPER, MAX_ANGLE_GRIPPER, MIN_BIEN_TRO_GRIPPER, MAX_BIEN_TRO_GRIPPER);
    return rotateGripperByBienTro(targetBienTro, targetSpeed);
}

void stopGripper()
{
    Motor_Gripper_Speed = 2;
}

// === reset

void resetGripper()
{
    Motor_Hut = MIN_MOTOR_HUT_SPEED;
    Xi_Lanh_Gripper_On;
    while (rotateGripperByAngle(0, 50))
    {
        vTaskDelay(5);
    }
    stopGripper();
}

void resetRobotArm()
{
    int i;
    int motorSpeedX = 250;
    int motorSpeedY = 50;
    Motor_Hut = 800;
    // == 1. reset Arm Y
    Motor_Arm_Y_Speed = motorSpeedY;
    Motor_Arm_Y_Direct_Up;
    for (i = 0; i < 50; i++)
        while (Cam_Bien_Tu_Arm_Y_Top)
            vTaskDelay(5);
    // 1.1 stop
    Motor_Arm_Y_Speed = 2;
    delay_ms(100);

    // 1.2 reset Encoder
    resetEncoderArmY();

    Motor_Arm_Y_Speed = motorSpeedY;
    Motor_Arm_Y_Direct_Down;

    // 1.3 Move down 1000 encoders
    for (i = 0; i < 50; i++)
        while (getEncoderArmY() < 500)
            vTaskDelay(5);
    Motor_Arm_Y_Speed = 2;

    resetGripper();

    // == 2. reset Arm X
    Motor_Arm_X_Speed = motorSpeedX;
    Motor_Arm_X_Direct_In;
    for (i = 0; i < 50; i++)
        while (Cam_Bien_Tu_Arm_X_In)
            vTaskDelay(5);
    // 2.1 stop
    Motor_Arm_X_Speed = 2;
    delay_ms(100);

    // 2.2 reset Encoder
    resetEncoderArmX();

    // 2.3 move Out
    Motor_Arm_X_Speed = motorSpeedX;
    Motor_Arm_X_Direct_Out;
    for (i = 0; i < 50; i++)
        while (getEncoderArmX() > -1000)
            vTaskDelay(5);
    // 2.4 stop
    Motor_Arm_X_Speed = 2;
}

void resetBase()
{
    while (rotateBaseByAngle(180, 40))
    {
        vTaskDelay(5);
    }
    stopBase();
}

// === calculate
int getMilimetArmX()
{
    return map_int(getEncoderArmX(), MAX_ARM_X_ENCODER, MIN_ARM_X_ENCODER, 0, ARM_X_LENGTH);
}

int getMilimetArmY()
{
    return map_int(getEncoderArmY(), MIN_ARM_Y_ENCODER, MAX_ARM_Y_ENCODER, 0, ARM_Y_LENGTH);
}

int getAngleBase()
{
    return map_int(getBienTroBase(), MIN_BIEN_TRO_BASE, MAX_BIEN_TRO_BASE, MIN_ANGLE_BASE, MAX_ANGLE_BASE);
}

int getAngleGripper()
{
    return map_int(getBienTroGripper(), MIN_BIEN_TRO_GRIPPER, MAX_BIEN_TRO_GRIPPER, MIN_ANGLE_GRIPPER, MAX_ANGLE_GRIPPER);
}

// === other ===
void cartersianToPolar(int x, int y, float *r, float *theta)
{
    *r = sqrt(x * x + y * y);
    *theta = atan2(y, x) * (180.0 / PI);
}

void polarToCartersian(float r, float theta, int *x, int *y)
{
    theta = theta * (PI / 180.0);
    *x = r * cos(theta);
    *y = r * sin(theta);
}

bool moveArmToXY(int x, int y)
{
    float r, theta;
    int i = 0;

    cartersianToPolar(x, y, &r, &theta);
    theta = map_int(theta, 0, 180, 270, 90);

    if (!rotateBaseByAngle(theta, 250))
    {
        i++;
        stopBase();
    }
    if (!moveArmXByMilimet(r, 250))
    {
        i++;
        stopArmX();
    }
    if (i > 1)
    {
        return false;
    }
    return true;
}

void getArmPos2D(int *x, int *y)
{
    float r = getMilimetArmX();
    float theta = map_int(getAngleBase(), 270, 90, 0, 180);
    polarToCartersian(r, theta, x, y);
}

bool trackingBall()
{
    int xBall = 0, yBall = 0;
    int xBallDistance, yBallDistance;
    float r, theta;
    int realWidth = 300;
    int realHeight = 300;

    int armPosX, armPosY;
    int i;

    // 1. Move Arm To Top
    while (moveArmYByMilimet(10, 40))
        vTaskDelay(5);
    stopArmY();

    // 2. Move Arm To position 0 100
    while (moveArmToXY(0, 100))
        vTaskDelay(5);
    stopBase();
    stopArmX();

    // 3. Set gripper to 0 and Xilanh On
    while (rotateGripperByAngle(0, 50))
        vTaskDelay(5);
    stopGripper();
    Xi_Lanh_Gripper_Off;

reset_position:
    while (Nut_1)
        vTaskDelay(5);

    // move robot to 0 100
    while (moveArmToXY(0, 100))
        vTaskDelay(5);
    stopBase();
    stopArmX();

    while (1)
    {
        vTaskDelay(5);
        if (!Nut_1)
            goto reset_position;

        UART_ReceiveFromRaspberry(&xBall, &yBall);
        if (xBall == -1 || yBall == -1) // ko thay bong
        {
            stopBase();
            stopArmX();
            continue;
        }

        xBallDistance = map_int(xBall - 160, -160, 160, -160, 160);
        yBallDistance = map_int(120 - yBall, -120, 120, -160, 160);

        if (abs(xBallDistance) < 15 && abs(yBallDistance) < 15)
        {
            stopArmX();
            stopBase();
        }
        else
        {
            getArmPos2D(&armPosX, &armPosY);
            armPosX += (int)xBallDistance / 10;
            armPosY += (int)yBallDistance / 10;
            moveArmToXY(armPosX, armPosY);
        }
    }

    // loop forever
    while (1)
        vTaskDelay(5);
}


bool trackingBallBySon(){
    int xBallDistance, yBallDistance;
    float r, theta;
    int realWidth = 300;
    int realHeight = 300;

    int armPosX, armPosY;
    int i;

    checkBallgan = 2;
    // 1. Move Arm To Top
    while (moveArmYByMilimet(10, 40))
        vTaskDelay(5);
    stopArmY();

    // 2. Move Arm To position 0 100
    while (moveArmToXY(0, 100))
        vTaskDelay(5);
    stopBase();
    stopArmX();

    // 3. Set gripper to 0 and Xilanh On
    while (rotateGripperByAngle(0, 50))
        vTaskDelay(5);
    stopGripper();
    Xi_Lanh_Gripper_Off;

    vTaskDelay(2000);

    // move robot to 0 100
    while (moveArmToXY(0, 100))
        vTaskDelay(5);
    stopBase();
    stopArmX();
    vTaskDelay(3000);
    while (1)
    {
        vTaskDelay(5);
        UART_ReceiveFromRaspberry(&xBall, &yBall);
        if (xBall == -1 || yBall == -1) // ko thay bong
        {
            stopBase();
            stopArmX();
            return true;
        }

        xBallDistance = map_int(xBall - 160, -160, 160, -160, 160);
        yBallDistance = map_int(120 - yBall, -120, 120, -160, 160);

        if (abs(xBallDistance) < 15 && abs(yBallDistance) < 15)
        {
            stopArmX();
            stopBase();
            return false;
        }
        else
        {
            getArmPos2D(&armPosX, &armPosY);
            armPosX += (int)xBallDistance / 10;
            armPosY += (int)yBallDistance / 10;
            moveArmToXY(armPosX, armPosY);
        }
    }
    return true;

}



bool robotRunByCamera(int xBall,int yBall,int speed){
    int goc_temp = 0;
    
    if(yBall < -92) {
        return false;
    }
    goc_temp = 1800 + (int)xBall*900/160;

    if(goc_temp > 2400) goc_temp = 2400;
    if(goc_temp < 1200) goc_temp = 1200;
    robotRunAngle(goc_temp,speed,0,0.5);
    return true;
}

void robotRunToBall()
{
    int xBallDistance,yBallDistance;
    // while (moveArmYByMilimet(10, 50))
    //     vTaskDelay(5);
    // stopArmY();

    // // move arm to XY
    // while (moveArmToXY(0, 100))
    //     vTaskDelay(5);
    // stopArmX();
    // stopBase();

    // while (rotateGripperByAngle(40, 50))
    //     vTaskDelay(5);
    // stopGripper();
    while(1){
        delay_ms(200);
        UART_ReceiveFromRaspberry(&xBall,&yBall);
        xBallDistance = map_int(xBall - 160, -160, 160, -160, 160);
        yBallDistance = map_int(120 - yBall, -120, 120, -160, 160);
        
        if(xBall == -1 || yBall == -1){ vTaskDelay(1000);continue;}
        if(!robotRunByCamera(xBallDistance,yBallDistance,20)) {robotStop(0);break;}
    }
    robotStop(0);
}



void getBallFullXanh(int silo){
    int listLazerSilo[5] = {20, 100, 170, 246, 320};
    robotRunToBall();
    RESET_ENCODER_WH();
    robotStop(0);
check_bong:
    trackingBallBySon();
    Motor_Hut = 2200;
    Motor_Arm_Y_Direct_Down;
    Motor_Arm_Y_Speed = 40;
    for ( i = 0; i < 50; i++)
    {
       while (Cam_Bien_Tu_Arm_Y_Bottom)
       {
            vTaskDelay(1);
       }
       
    }
    stopArmY();
    vTaskDelay(1000);
    Xi_Lanh_Gripper_On;
    vTaskDelay(3000);
    while (moveArmYByMilimet(250, 50))
		vTaskDelay(5);
	stopArmY();
    
    while (moveArmYByMilimet(90, 50)){
        if(!rotateGripperByAngle(110, 240)) stopGripper();
        vTaskDelay(5);
    }
	stopArmY();
    while (rotateGripperByAngle(110, 200))
        vTaskDelay(5);
    stopGripper();

    if(Cam_Bien_Quang_Bong) {Motor_Hut = 800; goto check_bong;}
    Motor_Hut = 800;
    delay_ms(1500);
    
     while(moveArmXByMilimet(135, 250)){
        vTaskDelay(1);
    }
    stopArmX();
    Motor_Hut = 2200;
    delay_ms(1500);
    while(rotateBaseByAngle(0,120)){
        vTaskDelay(1);
    }
    stopBase();
    
    Motor_Hut = 2000;
    stopArmX();
    robotStop(0);
    stopArmY();

    RESET_ENCODER_WH();
    robotRunAngle(0,40,0,0.2);
    for(i=0;i<50;i++) while (_lazerLeft < 400 ){
        vTaskDelay(1);
    }
    robotStop(0);
    delay_ms(1000);
    for(i=0;i<50;i++) while (_lazerFront > 20){
        Bam_thanh_laser_phai(20,0,listLazerSilo[silo],2);
    }
    robotStop(0);
    for(i=0;i<50;i++) while(abs(_lazerRight - listLazerSilo[silo]) > 2){
        if(_lazerRight > listLazerSilo[silo]) robotRunAngle(900,8,0,0.2);
        else robotRunAngle(-900,8,0,0.2);
    }
    stopBase();
    robotStop(0);
    stopArmX();
    stopArmY();
    delay_ms(1000);
    
    Motor_Hut = 800;
    Xi_Lanh_Gripper_Off;
    vTaskDelay(1000);
    checkBallgan = 3;


}

void runtoResetPointXanh(){
     
    int lazerFrontPoint = 190;
    int lazerRightPoint = 170;
    Xi_Lanh_Gripper_Off;
    for ( i = 0; i < 50; i++) while (abs(_lazerFront - lazerFrontPoint) > 2)
    {
        if(_lazerFront > lazerFrontPoint) Bam_thanh_laser_phai(15,0,lazerRightPoint,2);
        else Bam_thanh_laser_phai_lui(15,0,lazerRightPoint,2);

        if(!moveArmYByMilimet(10, 50)) stopArmY();
        if(!moveArmToXY(0, 100)) {stopArmX(); stopBase();}
        if(!rotateGripperByAngle(40, 80)) stopGripper();

        vTaskDelay(1);
    }
    for ( i = 0; i < 50; i++) while (abs(_lazerRight - lazerRightPoint) > 2){
        if(_lazerRight > lazerRightPoint) robotRunAngle(900,20,0,0.2);
        else robotRunAngle(-900,20,0,0.2);

        if(!moveArmYByMilimet(10, 50)) stopArmY();
        if(!moveArmToXY(0, 100)) {stopArmX(); stopBase();}
        if(!rotateGripperByAngle(50, 50)) stopGripper();

        vTaskDelay(1);
    }
    stopArmY();
    stopBase();
    stopArmX();
    stopGripper();
    while (moveArmYByMilimet(10, 50))
        vTaskDelay(5);
    stopArmY();

    // move arm to XY
    while (moveArmToXY(0, 100))
        vTaskDelay(5);
    stopArmX();
    stopBase();

    while (rotateGripperByAngle(50, 50))
        vTaskDelay(5);
    stopGripper();
    robotStop(0);
    Xi_Lanh_Gripper_Off;   

}


void restartXanh(){
    int k = 0;
    robotRunAngle(450,40,0,0.2);
    for ( i = 0; i < 50; i++) while (_lazerRight > 30)
    {
        vTaskDelay(1);
    }
    RESET_ENCODER_WH();
    robotRunAngle(0,80,0,0.2);
    for ( i = 0; i < 50; i++) while (getEncoderTong() < 2200)
    {
        vTaskDelay(1);
    }
    robotRunAngle(0,40,0,0.2);
    for ( i = 0; i < 50; i++) while (_lazerRight < 40)
    {
        vTaskDelay(1);
    }
    RESET_ENCODER_WH();
    for ( i = 0; i < 50; i++) while (getEncoderTong() < 400)
    {
        vTaskDelay(1);
    }
    robotRunAngle(900,50,0,0.2);
    for ( i = 0; i < 50; i++) while (getEncoderTong() < 2200)
    {
        vTaskDelay(1);
    }
    while(1){
        runtoResetPointXanh();
        robotStop(0);
        delay_ms(1000);
        getBallFullXanh(getEncoderTong()%5);
        robotStop(0);
        vTaskDelay(1000);
    }

    

}
void startSanXanh()
{
    RESET_ENCODER_WH();
    robotRunAngle(900, 70, 0, 0.5);

    for (i = 0; i < 50; i++)
        while (getEncoderTong() < 3800)
        {
            vTaskDelay(1);
        }
    robotRunAngle(900, 50, 0, 0.5);
    for (i = 0; i < 50; i++)
        while (getEncoderTong() < 4200)
        {
            vTaskDelay(1);
        }
    robotRunAngle(900, 40, 0, 0.2);
    for (i = 0; i < 50; i++)
        while (_lazerRight > 50)
        {
            vTaskDelay(1);
        }
    RESET_ENCODER_WH();
    robotRunAngle(0, 70, 0, 0.2);
    for (i = 0; i < 50; i++)
        while (getEncoderTong() < 2600)
        {
            vTaskDelay(1);
        }
    robotRunAngle(0, 40, 0, 0.2);
    for (i = 0; i < 50; i++)
        while (_lazerRight < 45)
        {
            vTaskDelay(1);
        }
    RESET_ENCODER_WH();
    for (i = 0; i < 50; i++)
        while (getEncoderTong() < 350)
        {
            vTaskDelay(1);
        }
    robotRunAngle(900, 50, 0, 0.2);
    for (i = 0; i < 50; i++)
        while (getEncoderTong() < 2200)
        {
            vTaskDelay(1);
        }

    for (i = 0; i < 50; i++)
        while (_lazerRight > 180)
        {
            if (_lazerRight > 113)
                robotRunAngle(850, 20, 0, 0.3);
            else if (lazerTruocValue < 113)
                robotRunAngle(950, 20, 0, 0.3);
            else
                robotRunAngle(900, 20, 0, 0.3);
        }
    while(1){
        runtoResetPointXanh();
        robotStop(0);
        delay_ms(1000);
        getBallFullXanh(getEncoderTong()%5);
        robotStop(0);
        vTaskDelay(1000);
    }

}


void getBallFullDo(int silo){
    int listLazerSilo[5] = {20, 100, 170, 246, 320};
    robotRunToBall();
    RESET_ENCODER_WH();
    robotStop(0);
check_bong:
    trackingBallBySon();
    Motor_Hut = 2200;
    Motor_Arm_Y_Direct_Down;
    Motor_Arm_Y_Speed = 40;
    for ( i = 0; i < 50; i++)
    {
       while (Cam_Bien_Tu_Arm_Y_Bottom)
       {
            vTaskDelay(1);
       }
       
    }
    stopArmY();
    vTaskDelay(1000);
    Xi_Lanh_Gripper_On;
    vTaskDelay(3000);
    while (moveArmYByMilimet(250, 50))
		vTaskDelay(5);
	stopArmY();
    
    while (moveArmYByMilimet(90, 50)){
        if(!rotateGripperByAngle(110, 240)) stopGripper();
        vTaskDelay(5);
    }
	stopArmY();
    while (rotateGripperByAngle(110, 200))
        vTaskDelay(5);
    stopGripper();

    if(Cam_Bien_Quang_Bong) {Motor_Hut = 800; goto check_bong;}
    Motor_Hut = 800;
    delay_ms(1500);
    
     while(moveArmXByMilimet(145, 250)){
        vTaskDelay(1);
    }
    stopArmX();
    Motor_Hut = 2200;
    delay_ms(1500);
    while(rotateBaseByAngle(0,120)){
        vTaskDelay(1);
    }
    stopBase();
    
    Motor_Hut = 2000;
    stopArmX();
    robotStop(0);
    stopArmY();

    RESET_ENCODER_WH();
    robotRunAngle(0,40,0,0.2);
    for(i=0;i<50;i++) while (_lazerRight < 400 ){
        vTaskDelay(1);
    }
    robotStop(0);
    delay_ms(1000);
    for(i=0;i<50;i++) while (_lazerFront > 20){
        Bam_thanh_laser_trai(20,0,listLazerSilo[silo],2);
    }
    robotStop(0);
    for(i=0;i<50;i++) while(abs(_lazerLeft - listLazerSilo[silo]) > 2){
        if(_lazerLeft > listLazerSilo[silo]) robotRunAngle(-900,8,0,0.2);
        else robotRunAngle(900,8,0,0.2);
    }
    stopBase();
    robotStop(0);
    stopArmX();
    stopArmY();
    delay_ms(1000);
    
    Motor_Hut = 800;
    Xi_Lanh_Gripper_Off;
    vTaskDelay(1000);
    checkBallgan = 3;


}



void runtoResetPointDo(){
     
    int lazerFrontPoint = 190;
    int lazerLeftPoint = 170;
    Xi_Lanh_Gripper_Off;
    for ( i = 0; i < 50; i++) while (abs(_lazerFront - lazerFrontPoint) > 2)
    {
        if(_lazerFront > lazerFrontPoint) Bam_thanh_laser_trai(15,0,lazerLeftPoint,2);
        else Bam_thanh_laser_trai_lui(15,0,lazerLeftPoint,2);

        if(!moveArmYByMilimet(10, 50)) stopArmY();
        if(!moveArmToXY(0, 100)) {stopArmX(); stopBase();}
        if(!rotateGripperByAngle(40, 80)) stopGripper();

        vTaskDelay(1);
    }
    for ( i = 0; i < 50; i++) while (abs(_lazerLeft - lazerLeftPoint) > 2){
        if(_lazerLeft > lazerLeftPoint) robotRunAngle(-900,20,0,0.2);
        else robotRunAngle(900,20,0,0.2);

        if(!moveArmYByMilimet(10, 50)) stopArmY();
        if(!moveArmToXY(0, 100)) {stopArmX(); stopBase();}
        if(!rotateGripperByAngle(50, 50)) stopGripper();

        vTaskDelay(1);
    }
    stopArmY();
    stopBase();
    stopArmX();
    stopGripper();
    while (moveArmYByMilimet(10, 50))
        vTaskDelay(5);
    stopArmY();

    // move arm to XY
    while (moveArmToXY(0, 100))
        vTaskDelay(5);
    stopArmX();
    stopBase();

    while (rotateGripperByAngle(50, 50))
        vTaskDelay(5);
    stopGripper();
    robotStop(0);
    Xi_Lanh_Gripper_Off;   

}

void restartDo(){
    int k = 0;
    robotRunAngle(-450,40,0,0.2);
    for ( i = 0; i < 50; i++) while (_lazerLeft > 30)
    {
        vTaskDelay(1);
    }
    RESET_ENCODER_WH();
    robotRunAngle(0,80,0,0.2);
    for ( i = 0; i < 50; i++) while (getEncoderTong() < 2200)
    {
        vTaskDelay(1);
    }
    robotRunAngle(0,40,0,0.2);
    for ( i = 0; i < 50; i++) while (_lazerLeft < 40)
    {
        vTaskDelay(1);
    }
    RESET_ENCODER_WH();
    for ( i = 0; i < 50; i++) while (getEncoderTong() < 400)
    {
        vTaskDelay(1);
    }
    robotRunAngle(-900,50,0,0.2);
    for ( i = 0; i < 50; i++) while (getEncoderTong() < 2200)
    {
        vTaskDelay(1);
    }
    while(1){
        runtoResetPointDo();
        robotStop(0);
        delay_ms(1000);
        getBallFullDo(getEncoderTong()%5);
        robotStop(0);
        vTaskDelay(1000);
    }

    

}


void startSanDo(){
    RESET_ENCODER_WH();
    robotRunAngle(-900, 70, 0, 0.5);

    for (i = 0; i < 50; i++)
        while (getEncoderTong() < 3800)
        {
            vTaskDelay(1);
        }
    robotRunAngle(-900, 50, 0, 0.5);
    for (i = 0; i < 50; i++)
        while (getEncoderTong() < 4200)
        {
            vTaskDelay(1);
        }
    robotRunAngle(-900, 40, 0, 0.2);
    for (i = 0; i < 50; i++)
        while (_lazerLeft > 50)
        {
            vTaskDelay(1);
        }
    RESET_ENCODER_WH();
    robotRunAngle(0, 70, 0, 0.2);
    for (i = 0; i < 50; i++)
        while (getEncoderTong() < 2600)
        {
            vTaskDelay(1);
        }
    robotRunAngle(0, 40, 0, 0.2);
    for (i = 0; i < 50; i++)
        while (_lazerLeft < 45)
        {
            vTaskDelay(1);
        }
    RESET_ENCODER_WH();
    for (i = 0; i < 50; i++)
        while (getEncoderTong() < 400)
        {
            vTaskDelay(1);  
        }
    
    
    robotRunAngle(-900, 50, 0, 0.2);
    for (i = 0; i < 50; i++)
        while (getEncoderTong() < 2200)
        {
            vTaskDelay(1);
        }
    robotStop(0);
    while(1){
        runtoResetPointDo();
        robotStop(0);
        delay_ms(1000);
        getBallFullDo(getEncoderTong()%5);
        robotStop(0);
        vTaskDelay(1000);
    }


}