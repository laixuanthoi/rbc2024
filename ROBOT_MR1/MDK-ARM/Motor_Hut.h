#define MIN_MOTOR_HUT_SPEED 0
#define NEURAL_MOTOR_HUT_SPEED 2
#define MAX_MOTOR_HUT_SPEED 40

// angle motor hut
int Trang_Thai_Motor_Hut = 0;
int Trang_Thai_Xi_Lanh = 0;

void run_Motor_Hut()
{
    switch (Trang_Thai_Motor_Hut)
    {
    case 0:
        MOTOR_HUT = NEURAL_MOTOR_HUT_SPEED;
        break;

    case 1:
        MOTOR_HUT = MAX_MOTOR_HUT_SPEED;
        break;
    }
}

void run_Xi_Lanh()
{
    switch (Trang_Thai_Xi_Lanh)
    {
    case 0:
        XI_LANH_NANG_BONG_OFF;
        break;

    case 1:
        XI_LANH_NANG_BONG_ON;
        break;
    }
}

void set_Trang_Thai_Motor_Hut(int trang_thai)
{
    Trang_Thai_Motor_Hut = trang_thai;
}

void set_Trang_Thai_Xi_Lanh(int trang_thai)
{
    Trang_Thai_Xi_Lanh = trang_thai;
}

int get_Trang_Thai_Motor_Hut()
{
    return Trang_Thai_Motor_Hut;
}

int get_Trang_Thai_Xi_Lanh()
{
    return Trang_Thai_Xi_Lanh;
}