
struct BaseProperties
{
    int minBienTro;
    int maxBienTro;
    int minMotorSpeed;
    int maxMotorSpeed;

    int currentBienTro;
    int currentMotorSpeed;
    int currentMotorDirection;

    int targetBienTro;
    int targetMotorSpeed;

    int isRunning;
    int isReady;
};

struct BaseProperties base;

int getBienTroBase()
{
    int en, enOld = Bien_Tro_Base;
    u16 i = 0;
    while (i < 2)
    {
        en = Bien_Tro_Base;
        if (abs(en - enOld) < 50)
            i++;
        enOld = en;
    }
    return abs(en);
}

void initBase()
{
    base.minBienTro = 0; // set bien tro range
    base.maxBienTro = 1024;

    base.minMotorSpeed = 2; // set motor speed range
    base.maxMotorSpeed = 100;

    base.currentBienTro = (int)((base.minBienTro + base.maxBienTro) / 2);
    base.currentMotorSpeed = base.minMotorSpeed;
    base.currentMotorDirection = 0;

    base.targetBienTro = (int)((base.minBienTro + base.maxBienTro) / 2);
    base.targetMotorSpeed = base.minMotorSpeed;

    base.isRunning = 1; // check base is running
    base.isReady = 0;   // check ready
}

float calculateAngleBase(int bienTro)
{
}

int calculateBienTroBase(float angle)
{
}

bool isEqualBienTro(int bientroA, int bientroB)
{
    return abs(bientroA - bientroB) < 20;
}

void updateBase()
{
    base.currentBienTro = getBienTroBase();
    base.currentMotorDirection = Motor_Base_Direct;
    base.currentMotorSpeed = Motor_Base_Speed;
    base.isRunning = base.currentMotorSpeed > base.minMotorSpeed ? 1 : 0;
}

void setMotorBase()
{
    base.targetBienTro = map_MinMax(base.targetBienTro, base.minBienTro, base.maxBienTro);
    base.targetMotorSpeed = map_MinMax(base.targetMotorSpeed, base.minMotorSpeed, base.maxMotorSpeed);

    if (!isEqualBienTro(base.currentBienTro, base.targetBienTro)) // chua toi target
    {
        if (base.targetBienTro > base.currentBienTro) // xoay phai
        {
            Motor_Base_Direct_Right;
            Motor_Base_Speed = base.targetMotorSpeed;
        }
        else
        {
            Motor_Base_Direct_Left;
            Motor_Base_Speed = base.targetMotorSpeed;
        }
    }
    else // xoay trai
    {
        Motor_Base_Speed = base.minMotorSpeed;
    }
}

void moveBaseToBienTro(int targetBienTro, int targetSpeed)
{
}

void moveBaseToAngle(float angle, int speed)
{
}

static void taskBase(void *p)
{
    initBase();
    while (1)
    {
        vTaskDelay(5);
        updateBase();
        if (!base.isReady)
            continue;

        setMotorBase();
    }
}