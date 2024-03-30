
#define MIN_MOTOR_BAN_TAY_SPEED 0
#define NEURAL_MOTOR_BAN_TAY_SPEED 2
#define MAX_MOTOR_BAN_TAY_SPEED 250

// Bien Tro Ban Tay
int Bien_Tro_Ban_Tay = 0;
int Min_Bien_Tro_Ban_Tay = 0;
int Max_Bien_Tro_Ban_Tay = 0;
int Target_Bien_Tro_Ban_Tay = 0;

int Angle_Ban_Tay = 0;
int Min_Angle_Ban_Tay = 0;
int Max_Angle_Ban_Tay = 0;
int Target_Angle_Ban_Tay = 0;

// Trang Thai
// 0: dung im
// 1: xoay thuan
// 2: xoay nghich
int Trang_Thai_Ban_Tay = 0;

int reset_Ban_Tay = 0;

int get_Bien_Tro_Ban_Tay()
{
    return Chong_Nhieu_ADC(BIEN_TRO_BAN_TAY);
}
void move_Ban_Tay()
{
}
