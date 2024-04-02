
struct BaseProperties
{
    int minBienTro;
    int maxBienTro;
    int minMotorSpeed;
    int maxMotorSpeed;
    float oneAngleToBienTro;

    int currentBienTro;
    int currentMotorSpeed;
    int currentMotorDirection;

    int targetBienTro;
    int targetMotorSpeed;

    int isRunning;
    int isReady;
    int isAutoRobot;
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
    base.minBienTro = 3; // set bien tro range
    base.maxBienTro = 885;
    base.oneAngleToBienTro = 10/3; // 600 bt la goc 90* 900 bt la goc 0 do => 300 bt = 90* => 1 do = 300/90 = 10/3

    base.minMotorSpeed = 2; // set motor speed range
    base.maxMotorSpeed = 30;

    base.currentBienTro = (int)((base.minBienTro + base.maxBienTro) / 2);
    base.currentMotorSpeed = base.minMotorSpeed;
    base.currentMotorDirection = 0;

    base.targetBienTro = 500;
    base.targetMotorSpeed = base.minMotorSpeed;

    base.isRunning = 0; // check base is running
    base.isReady = 0;   // check ready
    base.isAutoRobot = 0;
}

bool isEqualBienTro(int bientroA, int bientroB)
{
    return abs(bientroA - bientroB) < 10;
}

void giuBase()
{
    if (base.isAutoRobot == 0){
    //ham chay loop trong task con de dich chuyen mam xoay khi thay doi tagetbt
        int temp = 0;
        temp = getBienTroBase();
        if(!isEqualBienTro(base.targetBienTro,temp)){
            if(base.targetBienTro > temp) Motor_Base_Direct_Right;
            else Motor_Base_Direct_Left;
            Motor_Base_Speed = base.maxMotorSpeed;
            base.isRunning = 1;
        }
        else {Motor_Base_Speed = base.minMotorSpeed;base.isRunning = 0;}
    }
}



int calculateBienTroBase(float angle)
{
    //ham tinh toan taget bien tro  tu angle 
    // cong thuc se bang maxbt = 900 la goc 0 do - di goc muon quay*so bien trocua 1 do
    return (int)base.maxBienTro - angle*base.oneAngleToBienTro; 
}
// float calcuta

void moveBaseByAngle(float angle){
    //func di chyen mam xoay by angle
    if(angle < 0) angle = 0;
    if(angle > 270) angle = 270;
    base.targetBienTro = calculateBienTroBase(angle);
}


float calculateAngleBase(int bienTro)
{

}





// void updateBase()
// {
//     base.currentBienTro = getBienTroBase();
//     base.currentMotorDirection = Motor_Base_Direct;
//     base.currentMotorSpeed = Motor_Base_Speed;
//     base.isRunning = base.currentMotorSpeed > base.minMotorSpeed ? 1 : 0;
// }

// void setMotorBase()
// {
//     base.targetBienTro = map_MinMax(base.targetBienTro, base.minBienTro, base.maxBienTro);
//     base.targetMotorSpeed = map_MinMax(base.targetMotorSpeed, base.minMotorSpeed, base.maxMotorSpeed);

//     if (!isEqualBienTro(base.currentBienTro, base.targetBienTro)) // chua toi target
//     {
//         if (base.targetBienTro > base.currentBienTro) // xoay phai
//         {
//             Motor_Base_Direct_Right;
//             Motor_Base_Speed = base.targetMotorSpeed;
//         }
//         else
//         {
//             Motor_Base_Direct_Left;
//             Motor_Base_Speed = base.targetMotorSpeed;
//         }
//     }
//     else // xoay trai
//     {
//         Motor_Base_Speed = base.minMotorSpeed;
//     }
// }

void moveBaseToBienTro(int targetBienTro, int targetSpeed)
{
}

void moveBaseToAngle(float angle, int speed)
{
}

// static void taskBase(void *p)
// {
//     initBase();
//     while (1)
//     {
//         vTaskDelay(5);
//         updateBase();
//         if (!base.isReady)
//             continue;

//         setMotorBase();
//     }
// }
