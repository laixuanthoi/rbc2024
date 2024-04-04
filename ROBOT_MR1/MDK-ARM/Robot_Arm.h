#define PI 3.14159265358979323846

struct Gripper
{
    int minMotorHut;
    int maxMotorHut;
    int motorHutGetBall;

    int minMotorSpeed;
    int maxMotorSpeed;

    int minBienTro;
    int maxBienTro;
    int bienTroDropBall;

    int tagetBienTro;
};
struct Gripper gripper;

struct ArmProperties
{
    int minEncoders;
    int maxEncoders;

    int minMilimets;
    int maxMilimets;

    int minMotorSpeed;
    int maxMotorSpeed;

    int currentEncoders;
    int currentMotorSpeed;
    int currentMotorDirection;
    int targetEncoders;
    int targetMotorSpeed;

    int isRunning;
    int isReady;
};

struct ArmProperties armX;
struct ArmProperties armY;
int temp_x = 0;
int temp_y = 100;

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
    u16 i = 0;
    while (i < 2)
    {
        en = Encoder_Arm_Y;
        if (abs(en - enOld) < 50)
            i++;
        enOld = en;
    }
    return en;
}

void initArm()
{
    // Arm X
    armX.minEncoders = -7000; // 7000 hz
    armX.maxEncoders = -700;
    armX.minMilimets = 0; // 50 cm
    armX.maxMilimets = 450;

    armX.minMotorSpeed = 2;
    armX.maxMotorSpeed = 250;

    armX.currentEncoders = 0;
    armX.currentMotorSpeed = armX.minMotorSpeed;
    armX.currentMotorDirection = 0;

    armX.targetEncoders = armX.maxEncoders;
    armX.targetMotorSpeed = armX.minMotorSpeed;

    armX.isRunning = 0;
    armX.isReady = 0;

    // Arm Y
    armY.minEncoders = 10;
    armY.maxEncoders = 1160;
    armY.minMilimets = 0;
    armY.maxMilimets = 420; // 37cm

    armY.minMotorSpeed = 3;
    armY.maxMotorSpeed = 40;

    armY.currentEncoders = 0;
    armY.currentMotorSpeed = armY.minMotorSpeed;
    armY.currentMotorDirection = 0;

    armY.targetEncoders = armY.minEncoders;
    armY.targetMotorSpeed = armX.minMotorSpeed;

    armY.isRunning = 0;
    armY.isReady = 0;

    // gripper
    gripper.minMotorHut = 400;
    gripper.maxMotorHut = 1200;
    gripper.motorHutGetBall = 950;

    gripper.minMotorSpeed = 2;
    gripper.maxMotorSpeed = 100;

    gripper.minBienTro = 330;
    gripper.maxBienTro = 800;
    gripper.bienTroDropBall = 450;
    gripper.tagetBienTro = gripper.minBienTro;

    Motor_Hut = gripper.minMotorHut;
}

bool isEqualEncoders(int encoderA, int encoderB)
{
    return abs(encoderA - encoderB) < 20;
}

void resetArmXToReady()
{

    Motor_Arm_X_Speed = armX.maxMotorSpeed;
    Motor_Arm_X_Direct_In;
    // check cham cam bien tu
    for (i = 0; i < 50; i++)
        while (Cam_Bien_Tu_Arm_X_In)
        {
            vTaskDelay(1);
        }

    // dung lai va set motor dung yen , reset encoder x
    Motor_Arm_X_Speed = armX.minMotorSpeed;
    TIM5->CNT = 0;
    num_over_t5 = 0;
    vTaskDelay(5);

    // cho motor chay ra vi tri min
    Motor_Arm_X_Speed = armX.maxMotorSpeed;
    Motor_Arm_X_Direct_Out;
    for (i = 0; i < 50; i++)
        while (getEncoderArmX() > armX.maxEncoders)
        {
            vTaskDelay(1);
        }
    Motor_Arm_X_Speed = armX.minMotorSpeed;
}

int convertXMilimetsToEnoders(int milimets)
{
    // conver mm to encoder
    return (int)milimets * armX.minEncoders / armX.maxMilimets;
}

void giu_Tay_X(void)
{
    int temp = 0;
    // func loop giu tay X task dieu khien
    armX.isRunning = Motor_Arm_X_Speed > armX.minMotorSpeed ? 1 : 0;
    temp = getEncoderArmX();
    if (!isEqualEncoders(armX.targetEncoders, temp))
    {
        // do lech giua encoder taget > encoder der hien tai lon hon sai so
        if (armX.targetEncoders > temp)
            Motor_Arm_X_Direct_In;
        else
            Motor_Arm_X_Direct_Out;
        Motor_Arm_X_Speed = armX.maxMotorSpeed;
        armX.isRunning = 1;
    }
    else
    {
        Motor_Arm_X_Speed = armX.minMotorSpeed;
        armX.isRunning = 0;
    }
}

void moveXByActualLength(int length)
{

    int temp = 0;
    temp = convertXMilimetsToEnoders(length);
    if (temp < armX.minEncoders)
        temp = armX.minEncoders;
    if (temp > armX.maxEncoders)
        temp = armX.maxEncoders;
    armX.targetEncoders = temp;
}

void reset_Encoder_Canh_Tay_Y()
{
    TIM3->CNT = 0;
    num_over_t3 = 0;
}

int convertYMilimetsToEnoders(int milimets)
{
    // conver mm to encoder
    return (int)milimets * armY.maxEncoders / armY.maxMilimets;
}

void giu_Tay_Y(void)
{
    int temp = 0;
    // func loop giu tay X task dieu khien
    temp = getEncoderArmY();
    if (!isEqualEncoders(armY.targetEncoders, temp))
    {
        // do lech giua encoder taget > encoder der hien tai lon hon sai so
        if (armY.targetEncodersres > temp)
            Motor_Arm_Y_Direct_Down;
        else
            Motor_Arm_Y_Direct_Up;
        Motor_Arm_Y_Speed = armY.maxMotorSpeed;
    }
    else
        Motor_Arm_Y_Speed = armY.minMotorSpeed;
}
void moveYByActualLength(int length)
{
    int temp = 0;
    temp = convertYMilimetsToEnoders(length);
    armY.targetEncoders = temp;
}

// ===== ARM Y =====
void resetArmYToReady()
{
    Motor_Arm_Y_Speed = armY.maxMotorSpeed;
    Motor_Arm_Y_Direct_Up;
    for (i = 0; i < 50; i++)
        while (Cam_Bien_Tu_Arm_Y_Top)
        {
            vTaskDelay(1);
        }
    reset_Encoder_Canh_Tay_Y();
    Motor_Arm_Y_Speed = armY.minMotorSpeed;
    vTaskDelay(5);
    Motor_Arm_Y_Speed = armY.maxMotorSpeed;
    Motor_Arm_Y_Direct_Down;
    for (i = 0; i < 50; i++)
        while (getEncoderArmY() < 1000)
        {
            vTaskDelay(1);
        }
    Motor_Arm_Y_Speed = armY.minMotorSpeed;
}

void cartesianToPolar(int x, int y, float *r, float *theta)
{
    *r = sqrt(x * x + y * y);
    *theta = atan2(y, x) * (180.0 / PI);
}

void moveArmToXYWithDelta(int x, int y, int delta)
{
    float r, theta;
    cartesianToPolar(x, y, &r, &theta);
    if (theta > 100)
        theta -= delta;
    else
        theta += delta;
    moveXByActualLength(r);
    moveBaseByAngle(theta);
}

void moveArmToXY(int x, int y)
{
    float r, theta;
    cartesianToPolar(x, y, &r, &theta);
    moveXByActualLength(r);
    moveBaseByAngle(theta);
}

// gripper

bool isEqualBienTroGripper(int bt_a, int bt_b)
{
    return abs(bt_a - bt_b) < 25;
}

int getBienTroGripper()
{
    int en, enOld = Bien_Tro_Gripper;
    u16 i = 0;
    while (i < 2)
    {
        en = Bien_Tro_Gripper;
        if (abs(en - enOld) < 50)
            i++;
        enOld = en;
    }
    return abs(en);
}

void resetArmGripperToReady()
{
    int temp = 0;
    temp = getBienTroGripper();
    for (i = 0; i < 50; i++)
        while (!isEqualBienTroGripper(gripper.tagetBienTro, temp))
        {
            if (gripper.tagetBienTro > temp)
                Motor_Gripper_Direct_Up;
            else
                Motor_Gripper_Direct_Down;
            Motor_Gripper_Speed = gripper.maxMotorSpeed;
            temp = getBienTroGripper();
        }
    Motor_Gripper_Speed = gripper.minMotorSpeed;
}

void giuMotorGripper()
{
    int temp = 0;
    temp = getBienTroGripper();
    // dua motor xuong duoi goc 0 do
    if (!isEqualBienTroGripper(gripper.tagetBienTro, temp))
    {
        if (gripper.tagetBienTro > temp)
            Motor_Gripper_Direct_Up;
        else
            Motor_Gripper_Direct_Down;
        Motor_Gripper_Speed = gripper.maxMotorSpeed;
    }
    else
        Motor_Gripper_Speed = gripper.minMotorSpeed;
}

void gripperGetBall()
{

    Motor_Hut = gripper.maxMotorHut;
    vTaskDelay(5);
    Motor_Arm_Y_Direct_Down;
    Motor_Arm_Y_Speed = armY.maxMotorSpeed;
    for (i = 0; i < 50; i++)
        while (Cam_Bien_Tu_Arm_Y_Bottom)
        {
            vTaskDelay(1);
        }
    Motor_Arm_Y_Speed = armY.minMotorSpeed;

    Xi_Lanh_Gripper_Off;

    vTaskDelay(4000);
    // gripper.tagetBienTro = gripper.minBienTro;
    // vTaskDelay(5);
    // for (i = 0; i < 50; i++) while(!isEqualBienTroGripper(gripper.tagetBienTro,temp)){temp = getBienTroGripper();vTaskDelay(1);}

    // temp = getBienTroGripper();
    // gripper.tagetBienTro = gripper.maxBienTro;

    // vTaskDelay(5);
    // for (i = 0; i < 50; i++) while(!isEqualBienTroGripper(gripper.tagetBienTro,temp)){temp = getBienTroGripper();vTaskDelay(1);}

    Xi_Lanh_Gripper_On;
    vTaskDelay(4000);
    // Motor_Hut = gripper.motorHutGetBall;
    Motor_Arm_Y_Speed = armY.maxMotorSpeed;
    Motor_Arm_Y_Direct_Up;
    for (i = 0; i < 50; i++)
        while (Cam_Bien_Tu_Arm_Y_Top)
        {
            vTaskDelay(1);
        }
    Motor_Arm_Y_Speed = armY.minMotorSpeed;
}

void gripperDropBall()
{
    int temp = 0;
    temp = getBienTroGripper();

    Motor_Hut = gripper.maxMotorHut;
    gripper.tagetBienTro = gripper.bienTroDropBall;
    vTaskDelay(5);

    for (i = 0; i < 50; i++)
        while (!isEqualBienTroGripper(gripper.tagetBienTro, temp))
        {
            temp = getBienTroGripper();
            vTaskDelay(1);
        }
    Motor_Hut = gripper.minMotorHut;
    Xi_Lanh_Gripper_On;
    vTaskDelay(500);
}

void gripperGetBallByXY(int x, int y)
{
    float r, theta;
    int temp;
    cartesianToPolar(x, y, &r, &theta);
    armX.isRunning = 1;
    base.isRunning = 1;

    moveXByActualLength(r);
    moveBaseByAngle(theta);

    for (i = 0; i < 50; i++)
        while (armX.isRunning == 1 || base.isRunning == 1)
        {
            vTaskDelay(1);
        }
    temp = getBienTroGripper();
    Motor_Hut = gripper.maxMotorHut;
    gripper.tagetBienTro = gripper.minBienTro;
    vTaskDelay(5);
    for (i = 0; i < 50; i++)
        while (!isEqualBienTroGripper(gripper.tagetBienTro, temp))
        {
            temp = getBienTroGripper();
            vTaskDelay(1);
        }

    Motor_Arm_Y_Speed = armY.maxMotorSpeed;
    Motor_Arm_Y_Direct_Down;
    for (i = 0; i < 50; i++)
        while (Cam_Bien_Tu_Arm_Y_Bottom)
        {
            vTaskDelay(1);
        }
    Motor_Arm_Y_Speed = armY.minMotorSpeed;
    Xi_Lanh_Gripper_On;
    vTaskDelay(4000);

    temp = getBienTroGripper();
    gripper.tagetBienTro = gripper.maxBienTro;

    vTaskDelay(5);
    for (i = 0; i < 50; i++)
        while (!isEqualBienTroGripper(gripper.tagetBienTro, temp))
        {
            temp = getBienTroGripper();
            vTaskDelay(1);
        }

    Xi_Lanh_Gripper_On;
    vTaskDelay(4000);
    Motor_Hut = gripper.motorHutGetBall;
    Motor_Arm_Y_Speed = armY.maxMotorSpeed;
    Motor_Arm_Y_Direct_Up;
    for (i = 0; i < 50; i++)
        while (Cam_Bien_Tu_Arm_Y_Top)
        {
            vTaskDelay(1);
        }
    Motor_Arm_Y_Speed = armY.minMotorSpeed;
}

/// ham run

void runToSilo0Red()
{
    armX.targetEncoders = -3000;
    RESET_ENCODER_WH();
    robotRunAngle(0, 50, 0, 0.3);
    for (i = 0; i < 50; i++)
        while (lazerTruocValue > 30)
        {
            if (lazerTraiValue > 170)
                robotRunAngle(-50, 50, 0, 0.3);
            else if (lazerTraiValue < 170)
                robotRunAngle(50, 50, 0, 0.3);
            else
                robotRunAngle(0, 50, 0, 0.3);
            vTaskDelay(1);
        }
    robotRunAngle(0, 10, 0, 0.3);
    for (i = 0; i < 50; i++)
        while (lazerTruocValue > 5)
        {
            vTaskDelay(1);
        }
    for (i = 0; i < 50; i++)
        while (abs(lazerTraiValue - 170) > 1)
        {
            if (lazerTraiValue > 170)
                robotRunAngle(-950, 10, 0, -0.3);
            else
                robotRunAngle(950, 10, 0, 0.3);
        }
    robotStop(0);
    // gripperGetBallByXY(0,300);
}

// void test_gap_bong()
// {

//     temp_x = 0;
//     temp_y = 100;
//     // RESET_ENCODER_WH();
//     Motor_Arm_Y_Speed = armY.maxMotorSpeed;
//     Motor_Arm_Y_Direct_Up;
//     for (i = 0; i < 50; i++)
//         while (Cam_Bien_Tu_Arm_Y_Top)
//         {
//             vTaskDelay(1);
//         }
//     Motor_Arm_Y_Speed = armY.minMotorSpeed;
//     moveArmToXY(temp_x, temp_y);
//     armX.isRunning = 1;
//     base.isRunning = 1;
//     for (i = 0; i < 50; i++)
//         while (armX.isRunning == 1 || base.isRunning == 1)
//         {
//             vTaskDelay(1);
//         }
//     // robotRunAngle(1800,50,0,0.3);
//     // for(i=0;i<50;i++) while (getEncoderTong() < 2800){
//     //     if(lazerTraiValue > 170) robotRunAngle(1850,50,0,0.3);
//     //     else if (lazerTraiValue < 170) robotRunAngle(1750,50,0,0.3);
//     //     else robotRunAngle(1800,50,0,0.3);
//     //     vTaskDelay(1);}
//     // robotStop(0);
//     vTaskDelay(20000);
//     getXYFromXuanThoi();
//     temp_x += X_Thoi;
//     temp_y += Y_Thoi;
//     armX.isRunning = 1;
//     base.isRunning = 1;
//     moveArmToXYWithDelta(temp_x, temp_y, 10);
//     for (i = 0; i < 50; i++)
//         while (armX.isRunning == 1 || base.isRunning == 1)
//         {
//             vTaskDelay(1);
//         }
//     // gripperGetBall();
//     //  base.targetBienTro = 77; // xoay mam ve sau
//     //  RESET_ENCODER_WH();
//     //  robotRunAngle(0,50,0,0.3);
//     //  for(i=0;i<50;i++) while (getEncoderTong() < 1300){
//     //      if(lazerTraiValue > 170) robotRunAngle(-50,50,0,0.3);
//     //      else if (lazerTraiValue < 170) robotRunAngle(50,50,0,0.3);
//     //      else robotRunAngle(0,50,0,0.3);
//     //      vTaskDelay(1);}
//     //  for(i=0;i<50;i++) while (lazerTruocValue > 170){
//     //      if(lazerTraiValue > 170) robotRunAngle(-50,10,0,0.3);
//     //      else if (lazerTraiValue < 170) robotRunAngle(50,10,0,0.3);
//     //      else robotRunAngle(0,10,0,0.3);
//     //      vTaskDelay(1);
//     //  }
//     robotStop(0);
// }
