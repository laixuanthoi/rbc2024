#define MINIMUM_ENCODER_CANH_TAY_DRIFF 20 // encoder truot

#define MIN_MOTOR_CANH_TAY_SPEED 0
#define NEURAL_MOTOR_CANH_TAY_SPEED 2
#define MAX_MOTOR_CANH_TAY_SPEED 250

// Y = 44cm
// X1 = 61cm
// X2 = 25cm
// X = 86cm

// Encoder canh tay X
// 1 vong 360 do = 2500 xung
// canh tay bi nguoc

int current_encoderCanhTayX = 0;
int speed_MotorCanhTayX = 0;
int min_encoderCanhTayX = -5000;
int max_encoderCanhTayX = 0;
int target_encoderCanhTayX = 0;

int min_milimetsCanhTayX = 0;
int max_milimetsCanhTayX = 0;

// trang thai motor truc X:
//  0: giu im
//  1: ra
//  2: vao
int state_MotorCanhTayX = 0;

// void resetEncoderCanhTayY()
// {
//     TIM5->CNT = 0;
//     num_over_t5 = 0;
// }

int getCurrentEncoderCanhTayX()
{
    current_encoderCanhTayX = Chong_Nhieu_ADC(ENCODER_CANH_TAY_X);
    return current_encoderCanhTayX;
}

int getStateCanhTayX()
{
    return state_MotorCanhTayX;
}

void resetEncoderCanhTayX()
{
    TIM3->CNT = 0;
    num_over_t3 = 0;
}

bool isStopCanhTayX()
{
    bool isStop = false;

    if (abs(getCurrentEncoderCanhTayX() - target_encoderCanhTayX) < MINIMUM_ENCODER_CANH_TAY_DRIFF)
    {
        isStop = true;
    }

    if (CAM_BIEN_TU_X_VAO && state_MotorCanhTayX == 2)
    {
        isStop = true;
    }

    if (getCurrentEncoderCanhTayX() < min_encoderCanhTayX || getCurrentEncoderCanhTayX() > max_encoderCanhTayX)
    {
        isStop = true;
    }

    return isStop;
}

void _setMotorCanhTayX()
{
    target_encoderCanhTayX = target_encoderCanhTayX > max_encoderCanhTayX ? max_encoderCanhTayX : target_encoderCanhTayX;
    target_encoderCanhTayX = target_encoderCanhTayX < min_encoderCanhTayX ? min_encoderCanhTayX : target_encoderCanhTayX;

    if (isStopCanhTayX())
    {
        state_MotorCanhTayX = 0;
    }
    else
    {
        if (target_encoderCanhTayX > current_encoderCanhTayX)
        {
            state_MotorCanhTayX = 1; // ra
        }
        else
        {
            state_MotorCanhTayX = 2; // vao
        }
    }

    switch (state_MotorCanhTayX)
    {
    case 0:
        speed_MotorCanhTayX = NEURAL_MOTOR_CANH_TAY_SPEED;
        MOTOR_CANH_TAY_X = speed_MotorCanhTayX;
        break;

    case 1:
        speed_MotorCanhTayX = MAX_MOTOR_CANH_TAY_SPEED;
        MOTOR_CANH_TAY_X = speed_MotorCanhTayX;
        MOTOR_CANH_TAY_X_RA;
        break;

    case 2:
        speed_MotorCanhTayX = MAX_MOTOR_CANH_TAY_SPEED;
        MOTOR_CANH_TAY_X = speed_MotorCanhTayX;
        MOTOR_CANH_TAY_X_VAO;
        break;
    }
}

void moveEncoderCanhTayX(int target_encoders)
{
    target_encoderCanhTayX = target_encoders;
    _setMotorCanhTayX();
}

void moveMilimetsCanhTayX(int target_milimets)
{
    int target_encoders = mapRange_int(target_milimets, min_milimetsCanhTayX, max_milimetsCanhTayX, min_encoderCanhTayX, max_encoderCanhTayX);
    target_encoderCanhTayX = target_encoders;
    _setMotorCanhTayX();
}

void resetCanhTayX()
{
    while (CAM_BIEN_TU_X_VAO)
    {
        MOTOR_CANH_TAY_X = MAX_MOTOR_CANH_TAY_SPEED;
        MOTOR_CANH_TAY_X_VAO;
        vTaskDelay(5);
    }

    MOTOR_CANH_TAY_X = NEURAL_MOTOR_CANH_TAY_SPEED;
    speed_MotorCanhTayX = 0;
    state_MotorCanhTayX = 0;
    resetEncoderCanhTayX();
    vTaskDelay(5);

    while (ENCODER_CANH_TAY_X > -3000)
    {
        MOTOR_CANH_TAY_X = MAX_MOTOR_CANH_TAY_SPEED;
        MOTOR_CANH_TAY_X_RA;
        vTaskDelay(5);
    }

    MOTOR_CANH_TAY_X = NEURAL_MOTOR_CANH_TAY_SPEED;
    vTaskDelay(5);
}