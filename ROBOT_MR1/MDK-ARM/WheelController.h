
// === GETTER ===
int getEncoderWheelRearLeft()
{
    int en, enOld = Encoder_Wheel_Rear_Left;
    int i = 0;
    while (i < 2)
    {
        en = Encoder_Wheel_Rear_Left;
        if (abs(en - enOld) < 50)
            i++;
        enOld = en;
    }
    return abs(en);
}
int getEncoderWheelFront()
{
    int en, enOld = Encoder_Wheel_Front;
    int i = 0;
    while (i < 2)
    {
        en = Encoder_Wheel_Front;
        if (abs(en - enOld) < 50)
            i++;
        enOld = en;
    }
    return abs(en);
}

int getEncoderWheelRearRight()
{
    int en, enOld = Encoder_Wheel_Rear_Right;
    int i = 0;
    while (i < 2)
    {
        en = Encoder_Wheel_Rear_Right;
        if (abs(en - enOld) < 50)
            i++;
        enOld = en;
    }
    return abs(en);
}

int getEncoderTwoRearWheels()
{
    return getEncoderWheelRearLeft() + getEncoderWheelRearRight();
}

// === RESET ===
void resetEncoderWheelFront()
{
    TIM4->CNT = 0;
    num_over_t4 = 0;
}

void resetEncoderWheelRearLeft()
{
    TIM1->CNT = 0;
    num_over_t1 = 0;
}

void resetEncoderWheelRearRight()
{
    TIM2->CNT = 0;
    num_over_t2 = 0;
}

void resetEncoderAllWheels()
{
    resetEncoderWheelFront();
    resetEncoderWheelRearLeft();
    resetEncoderWheelRearRight();
}

