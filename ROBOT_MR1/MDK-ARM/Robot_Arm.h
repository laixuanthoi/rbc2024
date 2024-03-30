
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
    armX.maxEncoders = 0;
    armX.minMilimets = 0; // 50 cm
    armX.maxMilimets = 500;

    armX.minMotorSpeed = 2;
    armX.maxMotorSpeed = 200;

    armX.currentEncoders = 0;
    armX.currentMotorSpeed = armX.minMotorSpeed;
    armX.currentMotorDirection = 0;

    armX.targetEncoders = (armX.minEncoders + armX.maxEncoders) / 2;
    armX.targetMotorSpeed = armX.minMotorSpeed;

    armX.isRunning = 0;
    armX.isReady = 0;

    // Arm Y
    armY.minEncoders = 0;
    armY.maxEncoders = 3000;
    armY.minMilimets = 0;
    armY.maxMilimets = 370; // 37cm

    armY.minMotorSpeed = 2;
    armY.maxMotorSpeed = 40;

    armY.currentEncoders = 0;
    armY.currentMotorSpeed = armY.minMotorSpeed;
    armY.currentMotorDirection = 0;

    armY.targetEncoders = (armY.minEncoders + armY.maxEncoders) / 2;
    armY.targetMotorSpeed = armX.minMotorSpeed;

    armY.isRunning = 0;
    armY.isReady = 0;
}

bool isEqualEncoders(int encoderA, int encoderB)
{
    return abs(encoderA - encoderB) < 30;
}

void updateArm()
{
    armX.currentEncoders = getEncoderArmX();
    armX.currentMotorDirection = Motor_Arm_X_Direct;
    armX.currentMotorSpeed = Motor_Arm_X_Speed;
    armX.isRunning = armX.currentMotorSpeed > armX.minMotorSpeed ? 1 : 0;

    armY.currentEncoders = getEncoderArmY();
    armY.currentMotorDirection = Motor_Arm_Y_Direct;
    armY.currentMotorSpeed = Motor_Arm_Y_Speed;
    armY.isRunning = armY.currentMotorSpeed > armY.minMotorSpeed ? 1 : 0;
}

void resetArmXToReady()
{
    while (Cam_Bien_Tu_Arm_X_In)
    {
        Motor_Arm_X_Speed = 150;
        Motor_Arm_X_Direct_In;
        vTaskDelay(5);
    }

    // reset Encoder
    TIM5->CNT = 0;
    num_over_t5 = 0;

    while (getEncoderArmX() > -2000)
    {
        Motor_Arm_X_Speed = 150;
        Motor_Arm_X_Direct_Out;
        vTaskDelay(5);
    }

    Motor_Arm_X_Speed = 2;
    armX.isReady = 1;
}

void setMotorArmX()
{
    armX.targetEncoders = map_MinMax(armX.targetEncoders, armX.minEncoders, armX.maxEncoders);
    armX.targetMotorSpeed = map_MinMax(armX.targetMotorSpeed, armX.minMotorSpeed, armX.maxMotorSpeed);
    if (!isEqualEncoders(armX.currentEncoders, armX.targetEncoders))
    {
        if (armX.targetEncoders > armX.currentEncoders) // in
        {
            Motor_Arm_X_Direct_In;
            if (Cam_Bien_Tu_Arm_X_In)
            {
                Motor_Arm_X_Speed = armX.minMotorSpeed;
            }
            else
            {
                Motor_Arm_X_Speed = armX.targetMotorSpeed;
            }
        }
        else // out
        {
            Motor_Arm_X_Direct_Out;
            Motor_Arm_X_Speed = armX.targetMotorSpeed;
        }
    }
    else // reach to target
    {
        Motor_Arm_X_Speed = armX.minMotorSpeed;
    }
}

void moveArmXToEncoders(int targetEncoders, int targetSpeed)
{
    armX.targetEncoders = targetEncoders;
    armX.targetMotorSpeed = targetSpeed;
}

void moveArmXToMilimets(int targetMilimets, int targetSpeed)
{
    armX.targetEncoders = map_int(targetMilimets, armX.minMilimets, armX.maxMilimets, armX.minEncoders, armX.maxEncoders);
    armX.targetMotorSpeed = targetSpeed;
}

// ===== ARM Y =====
void resetArmYToReady()
{
    while (Cam_Bien_Tu_Arm_Y_Top)
    {
        vTaskDelay(5);
        Motor_Arm_Y_Speed = 50;
        Motor_Arm_Y_Direct_Up;
    }

    Motor_Arm_Y_Speed = 2;

    // reset Encoder
    TIM3->CNT = 0;
    num_over_t3 = 0;
    vTaskDelay(5);

    while (getEncoderArmY() < 500)
    {
        vTaskDelay(5);
        Motor_Arm_Y_Speed = 50;
        Motor_Arm_Y_Direct_Down;
    }

    Motor_Arm_Y_Speed = 2;
    armY.isReady = 1;
}

void setMotorArmY()
{
    armY.targetEncoders = map_MinMax(armY.targetEncoders, armY.minEncoders, armY.maxEncoders);
    armY.targetMotorSpeed = map_MinMax(armY.targetMotorSpeed, armY.minMotorSpeed, armY.maxMotorSpeed);

    if (!isEqualEncoders(armY.currentEncoders, armY.targetEncoders))
    {
        if (armY.targetEncoders > armY.currentEncoders) // down
        {
            Motor_Arm_Y_Direct_Down;
            if (Cam_Bien_Tu_Arm_Y_Bottom)
            {
                Motor_Arm_Y_Speed = armY.minMotorSpeed;
            }
            else
            {
                Motor_Arm_Y_Speed = armY.targetMotorSpeed;
            }
        }
        else
        {
            Motor_Arm_Y_Direct_Up;
            if (Cam_Bien_Tu_Arm_Y_Top)
            {
                Motor_Arm_Y_Speed = armY.minMotorSpeed;
            }
            else
            {
                Motor_Arm_Y_Speed = armY.targetMotorSpeed;
            }
        }
    }
    else // reach to target
    {
        Motor_Arm_Y_Speed = armY.minMotorSpeed;
    }
}

void moveArmYToEncoders(int targetEncoders, int targetSpeed)
{
    armY.targetEncoders = targetEncoders;
    armY.targetMotorSpeed = targetSpeed;
}

void moveArmYToMilimets(int targetMilimets, int targetSpeed)
{
    armY.targetEncoders = map_int(targetMilimets, armY.minMilimets, armY.maxMilimets, armY.minEncoders, armY.maxEncoders);
    armY.targetMotorSpeed = targetSpeed;
}

static void taskArm(void *p)
{
    initArm();
    resetArmYToReady();
    while (1)
    {
        vTaskDelay(5);
        // updateArm();
        // if (!armY.isReady || !armX.isReady)
        // {
        //     resetArmYToReady();
        //     resetArmXToReady();
        // }
        // else
        // {
        //     setMotorArmX();
        //     setMotorArmY();
        // }
    }
}
