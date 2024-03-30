#define MIN_MOTOR_MAM_XOAY_SPEED 0    // toc do mam xoay toi da
#define NEURAL_MOTOR_MAM_XOAY_SPEED 2 // toc do mam xoay giu nguyen
#define MAX_MOTOR_MAM_XOAY_SPEED 40   // toc do mam xoay toi da

#define MINIMUM_BIEN_TRO_MAM_XOAY_DISTANCE 10

// Bien Tro Mam Xoay
// 0 - 1024
int Bien_Tro_Mam_Xoay = 0;
int Min_Bien_Tro_Mam_Xoay = 0;
int Max_Bien_Tro_Mam_Xoay = 0;
int Target_Bien_Tro_Mam_Xoay = 0;

int Angle_Mam_Xoay = 0; // angle in degree (0-360)
int Min_Angle_Mam_Xoay = 0;
int Max_Angle_Mam_Xoay = 0;
int Target_Angle_Mam_Xoay = 0;

// Trang Thai
// 0: dung im
// 1: xoay thuan
// 2: xoay nghich
int Trang_Thai_Mam_Xoay = 0;

// Reset
int reset_Mam_Xoay = 0;

int get_Bien_Tro_Mam_Xoay()
{
    return Chong_Nhieu_ADC(BIEN_TRO_MAM_XOAY);
}
void move_Mam_Xoay()
{
    Bien_Tro_Mam_Xoay = Chong_Nhieu_ADC(BIEN_TRO_MAM_XOAY);
    Angle_Mam_Xoay = mapRange_int(Bien_Tro_Mam_Xoay, Min_Bien_Tro_Mam_Xoay, Max_Bien_Tro_Mam_Xoay, Min_Angle_Mam_Xoay, Max_Angle_Mam_Xoay);

    if (abs(Target_Bien_Tro_Mam_Xoay - Bien_Tro_Mam_Xoay) < MINIMUM_BIEN_TRO_MAM_XOAY_DISTANCE)
    {
        Trang_Thai_Mam_Xoay = 0;
    }
    else
    {
        if (Target_Bien_Tro_Mam_Xoay > Bien_Tro_Mam_Xoay)
        { // xoay thuan
            Trang_Thai_Mam_Xoay = 1;
        }
        else
        { // xoay nghich
            Trang_Thai_Mam_Xoay = 2;
        }
    }

    if (Bien_Tro_Mam_Xoay > Max_Bien_Tro_Mam_Xoay || Bien_Tro_Mam_Xoay < Min_Bien_Tro_Mam_Xoay)
    {
        Trang_Thai_Mam_Xoay = 0;
    }

    switch (Trang_Thai_Mam_Xoay)
    {
    case 0:
        MOTOR_MAM_XOAY = NEURAL_MOTOR_MAM_XOAY_SPEED;
        break;

    case 1:
        MOTOR_MAM_XOAY = MAX_MOTOR_MAM_XOAY_SPEED;
        MOTOR_MAM_XOAY_THUAN;
        break;

    case 2:
        MOTOR_MAM_XOAY = MAX_MOTOR_MAM_XOAY_SPEED;
        MOTOR_MAM_XOAY_NGHICH;
        break;
    }
}

void set_Target_Bien_Tro_Mam_Xoay(int bientro)
{
    Target_Bien_Tro_Mam_Xoay = bientro;
    Target_Bien_Tro_Mam_Xoay = map_Min_Max(Target_Bien_Tro_Mam_Xoay, Min_Bien_Tro_Mam_Xoay, Max_Bien_Tro_Mam_Xoay);
    Target_Angle_Mam_Xoay = mapRange_int(Target_Bien_Tro_Mam_Xoay, Min_Bien_Tro_Mam_Xoay, Max_Bien_Tro_Mam_Xoay, Min_Angle_Mam_Xoay, Max_Angle_Mam_Xoay);
}

void set_Target_Angle_Mam_Xoay(float radians)
{
    Target_Angle_Mam_Xoay = radians;
    Target_Angle_Mam_Xoay = map_Min_Max(Target_Angle_Mam_Xoay, Min_Angle_Mam_Xoay, Max_Angle_Mam_Xoay);
    Target_Bien_Tro_Mam_Xoay = mapRange_int(Target_Angle_Mam_Xoay, Min_Angle_Mam_Xoay, Max_Angle_Mam_Xoay, Min_Bien_Tro_Mam_Xoay, Max_Bien_Tro_Mam_Xoay);
}

int get_Trang_Thai_Mam_Xoay()
{
    return Trang_Thai_Mam_Xoay;
}