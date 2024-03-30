
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
    armX.maxEncoders = -700;
    armX.minMilimets = 0; // 50 cm
    armX.maxMilimets = 450;

    armX.minMotorSpeed = 2;
    armX.maxMotorSpeed = 50;

    armX.currentEncoders = 0;
    armX.currentMotorSpeed = armX.minMotorSpeed;
    armX.currentMotorDirection = 0;

    armX.targetEncoders = armX.maxEncoders;
    armX.targetMotorSpeed = armX.minMotorSpeed;

    armX.isRunning = 0;
    armX.isReady = 0;

    // Arm Y
    armY.minEncoders = -10;
    armY.maxEncoders = -1200;
    armY.minMilimets = 0;
    armY.maxMilimets = 420; // 37cm

    armY.minMotorSpeed = 2;
    armY.maxMotorSpeed = 50;

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
    return abs(encoderA - encoderB) < 20;
}

// void updateArm()
// {
//     armX.currentEncoders = getEncoderArmX();
//     armX.currentMotorDirection = Motor_Arm_X_Direct;
//     armX.currentMotorSpeed = Motor_Arm_X_Speed;
//     armX.isRunning = armX.currentMotorSpeed > armX.minMotorSpeed ? 1 : 0;

//     armY.currentEncoders = getEncoderArmY();
//     armY.currentMotorDirection = Motor_Arm_Y_Direct;
//     armY.currentMotorSpeed = Motor_Arm_Y_Speed;
//     armY.isRunning = armY.currentMotorSpeed > armY.minMotorSpeed ? 1 : 0;
// }

void resetArmXToReady()
{

    Motor_Arm_X_Speed = armX.maxMotorSpeed;
    Motor_Arm_X_Direct_In;
		//check cham cam bien tu
    for (i = 0; i < 50; i++)while (Cam_Bien_Tu_Arm_X_In) {vTaskDelay(1);}
    
    //dung lai va set motor dung yen , reset encoder x
    Motor_Arm_X_Speed = armX.minMotorSpeed;
    TIM5->CNT = 0;
    num_over_t5 = 0;
	vTaskDelay(5);
		
	//cho motor chay ra vi tri min
	Motor_Arm_X_Speed =  armX.maxMotorSpeed;
    Motor_Arm_X_Direct_Out;
	for (i = 0; i < 50; i++) while (getEncoderArmX() > armX.maxEncoders)  {vTaskDelay(1);}
	Motor_Arm_X_Speed = armX.minMotorSpeed;
}

int convertXMilimetsToEnoders(int milimets){
	//conver mm to encoder
	return (int)milimets*armX.minEncoders/armX.maxMilimets;
}


void giu_Tay_X(void){
    int temp = 0;
	//func loop giu tay X task dieu khien 
    temp = getEncoderArmX();
	if (!isEqualEncoders(armX.targetEncoders,temp)){
		//do lech giua encoder taget > encoder der hien tai lon hon sai so
		if(armX.targetEncoders > temp) Motor_Arm_X_Direct_In ;
		else Motor_Arm_X_Direct_Out;
		Motor_Arm_X_Speed = armX.maxMotorSpeed;
		
	}
	else Motor_Arm_X_Speed = armX.minMotorSpeed;
}


void moveXByActualLength(int length){
    int temp = 0;
	temp = convertXMilimetsToEnoders(length);
	armX.targetEncoders = temp;
}



void reset_Encoder_Canh_Tay_Y(){
    TIM3->CNT = 0;
    num_over_t3 = 0;

}

int convertYMilimetsToEnoders(int milimets){
	//conver mm to encoder
	return (int)milimets*armY.minEncoders/armY.maxMilimets;
}

void giu_Tay_Y(void){
    int temp = 0;
	//func loop giu tay X task dieu khien 
    temp = getEncoderArmY();
	if (!isEqualEncoders(armY.targetEncoders,temp)){
		//do lech giua encoder taget > encoder der hien tai lon hon sai so
		if(armY.targetEncoders > temp) Motor_Arm_Y_Direct_Down ;
		else Motor_Arm_Y_Direct_Up;
		Motor_Arm_Y_Speed = armY.maxMotorSpeed;
		
	}
	else Motor_Arm_Y_Speed = armY.minMotorSpeed;
}
void moveYByActualLength(int length){
    int temp = 0;
	temp = convertYMilimetsToEnoders(length);
	armY.targetEncoders = temp;
}

// ===== ARM Y =====
void resetArmYToReady()
{
    Motor_Arm_Y_Speed = armY.maxMotorSpeed;
    Motor_Arm_Y_Direct_Down;
    for (i = 0; i < 50; i++) while (Cam_Bien_Tu_Arm_Y_Bottom){vTaskDelay(1);}
	Motor_Arm_Y_Speed = armY.minMotorSpeed;
    reset_Encoder_Canh_Tay_Y();
	Motor_Arm_Y_Speed = armY.maxMotorSpeed;
    Motor_Arm_Y_Direct_Up;
    for (i = 0; i < 50; i++) while (Cam_Bien_Tu_Arm_Y_Top){vTaskDelay(1);}
    Motor_Arm_Y_Speed = armY.minMotorSpeed;
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
