


void Bam_thanh_laser_phai(int speed, int AngleHead, int lazer_stable_phai, int num_change_stable)
{
    int fix;

    fix = abs(_lazerRight - lazer_stable_phai) * 15;

    if (fix > 600)
        fix = 600;

    if (_lazerRight - lazer_stable_phai > num_change_stable)
    {
        robotRunAngle(0 + fix, speed, AngleHead, 0.1);
    }
    else if (_lazerRight - lazer_stable_phai < num_change_stable)
    {
        robotRunAngle(0 - fix, speed, AngleHead, 0.1);
    }
    else
        robotRunAngle(0, speed, AngleHead, 0.1);
}
void Bam_thanh_laser_phai_lui(int speed, int AngleHead, int lazer_stable_phai, int num_change_stable)
{
    int fix;

    fix = abs(_lazerRight - lazer_stable_phai) * 15;

    if (fix > 600)
        fix = 600;

    if (_lazerRight - lazer_stable_phai > num_change_stable)
    {
        robotRunAngle(1800 - fix, speed, AngleHead, 0.1);
    }
    else if (_lazerRight - lazer_stable_phai < num_change_stable)
    {
        robotRunAngle(1800 + fix, speed, AngleHead, 0.1);
    }
    else
        robotRunAngle(1800, speed, AngleHead, 0.1);
}

void Bam_thanh_laser_trai(int speed, int AngleHead, int lazer_stable_trai, int num_change_stable)
{
    int fix;

    fix = abs(_lazerLeft - lazer_stable_trai) * 15;

    if (fix > 600)
        fix = 600;

    if (_lazerLeft - lazer_stable_trai > num_change_stable)
    {
        robotRunAngle(0 - fix, speed, AngleHead, 0.1);
    }
    else if (_lazerLeft - lazer_stable_trai < num_change_stable)
    {
        robotRunAngle(0 + fix, speed, AngleHead, 0.1);
    }
    else
        robotRunAngle(0, speed, AngleHead, 0.1);
}

void Bam_thanh_laser_trai_lui(int speed, int AngleHead, int lazer_stable_trai, int num_change_stable)
{
    int fix;

    fix = abs(_lazerLeft - lazer_stable_trai) * 15;

    if (fix > 600)
        fix = 600;

    if (_lazerLeft - lazer_stable_trai > num_change_stable)
    {
        robotRunAngle(-1800 + fix, speed, AngleHead, 0.1);
    }
    else if (_lazerLeft - lazer_stable_trai < num_change_stable)
    {
        robotRunAngle(-1800 - fix, speed, AngleHead, 0.1);
    }
    else
        robotRunAngle(1800, speed, AngleHead, 0.1);
}


// void runToSilo(int silo)
// {
//     int goc_temp = 0;
//     // xoay ve goc 0
//     while (abs(_robotIMUAngle) > 10)
//     {
//         if (_robotIMUAngle > 0)
//             robotRotate(0, -0.5, 0);
//         else
//             robotRotate(0, 0.5, 0);
//         vTaskDelay(1);
//     }
//     // robotRunAngle(0, 40, 0, 0.2);
//     for (i = 0; i < 50; i++)
//         while (_lazerFront > 20)
//         {
//             Bam_thanh_laser_phai(40, 0, listLazerSilo[silo], 3);
//             vTaskDelay(1);
//         }

    // for (i = 0; i < 50; i++)
    // {
    //     while (_lazerFront > 20)
    //     {
    //         if (abs(_lazerRight - listLazerSilo[silo]) > 3)
    //         {
    //             goc_temp = (int)((_lazerRight - listLazerSilo[silo]) / 20 * 4500);
    //             if (goc_temp > 450)
    //                 goc_temp = 450;
    //             if (goc_temp < -450)
    //                 goc_temp = -450;
    //             if (_lazerRight > listLazerSilo[silo])
    //                 robotRunAngle(goc_temp, 20, 0, 0.5);
    //             else
    //                 robotRunAngle(goc_temp, 20, 0, -0.5);
    //         }
    //         else
    //             robotRunAngle(0, 40, 0, 0.2);
    //         vTaskDelay(1);
    //     }
    // for (i = 0; i < 50; i++)
    //     while ((_lazerRight - listLazerSilo[silo]) - 3)
    //     {
    //         if (_lazerRight > listLazerSilo[silo])
    //             robotRunAngle(900, 20, 0, 0.2);
    //         else
    //             robotRunAngle(-900, 20, 0, -0.2);
    //     }

//     robotStop(0);
// }



// void startSanXanh()
// {
//     RESET_ENCODER_WH();
//     robotRunAngle(900, 70, 0, 0.2);
//     for (i = 0; i < 50; i++)
//         while (getEncoderTong() < 3800)
//         {
//             vTaskDelay(1);
//         }
//     robotRunAngle(900, 50, 0, 0.2);
//     for (i = 0; i < 50; i++)
//         while (getEncoderTong() < 4200)
//         {
//             vTaskDelay(1);
//         }
//     robotRunAngle(900, 40, 0, 0.2);
//     for (i = 0; i < 50; i++)
//         while (_lazerRight > 50)
//         {
//             vTaskDelay(1);
//         }
//     RESET_ENCODER_WH();
//     robotRunAngle(0, 70, 0, 0.2);
//     for (i = 0; i < 50; i++)
//         while (getEncoderTong() < 2500)
//         {
//             vTaskDelay(1);
//         }
//     robotRunAngle(0, 40, 0, 0.2);
//     for (i = 0; i < 50; i++)
//         while (_lazerRight < 45)
//         {
//             vTaskDelay(1);
//         }
//     RESET_ENCODER_WH();
//     for (i = 0; i < 50; i++)
//         while (getEncoderTong() < 300)
//         {
//             vTaskDelay(1);
//         }
//     robotRunAngle(900, 50, 0, 0.2);
//     for (i = 0; i < 50; i++)
//         while (getEncoderTong() < 2200)
//         {
//             vTaskDelay(1);
//         }
//     for (i = 0; i < 50; i++)
//         while (_lazerRight > 180)
//         {
//             if (_lazerRight > 113)
//                 robotRunAngle(850, 20, 0, 0.3);
//             else if (lazerTruocValue < 113)
//                 robotRunAngle(950, 20, 0, 0.3);
//             else
//                 robotRunAngle(900, 20, 0, 0.3);
//         }

//     robotStop(0);
// }

// void startSanDo()
// {
//     RESET_ENCODER_WH();
//     robotRunAngle(-900, 70, 0, 0.2);
//     for (i = 0; i < 50; i++)
//         while (getEncoderTong() < 3800)
//         {
//             vTaskDelay(1);
//         }
//     robotRunAngle(-900, 50, 0, 0.2);
//     for (i = 0; i < 50; i++)
//         while (getEncoderTong() < 4200)
//         {
//             vTaskDelay(1);
//         }
//     robotRunAngle(-900, 40, 0, 0.2);
//     for (i = 0; i < 50; i++)
//         while (lazerTraiValue > 50)
//         {
//             vTaskDelay(1);
//         }
//     RESET_ENCODER_WH();
//     robotRunAngle(0, 70, 0, 0.2);
//     for (i = 0; i < 50; i++)
//         while (getEncoderTong() < 2500)
//         {
//             vTaskDelay(1);
//         }
//     robotRunAngle(0, 40, 0, 0.2);
//     for (i = 0; i < 50; i++)
//         while (lazerTraiValue < 45)
//         {
//             vTaskDelay(1);
//         }
//     RESET_ENCODER_WH();
//     for (i = 0; i < 50; i++)
//         while (getEncoderTong() < 300)
//         {
//             vTaskDelay(1);
//         }
//     robotRunAngle(-900, 50, 0, 0.2);
//     for (i = 0; i < 50; i++)
//         while (getEncoderTong() < 2200)
//         {
//             vTaskDelay(1);
//         }
//     for (i = 0; i < 50; i++)
//         while (lazerTraiValue > 180)
//         {
//             if (lazerTruocValue > 113)
//                 robotRunAngle(-850, 20, 0, 0.3);
//             else if (lazerTruocValue < 113)
//                 robotRunAngle(-950, 20, 0, 0.3);
//             else
//                 robotRunAngle(-900, 20, 0, 0.3);
//         }

//     robotStop(0);
// }

// void runToBallsRed()
// {
//     RESET_ENCODER_WH();
//     robotRunAngle(1800, 50, 0, 0.3);
//     for (i = 0; i < 50; i++)
//         while (getEncoderTong() < 3400)
//         {
//             if (lazerTraiValue > 170)
//                 robotRunAngle(1850, 50, 0, 0.3);
//             else if (lazerTraiValue < 170)
//                 robotRunAngle(1750, 50, 0, 0.3);
//             else
//                 robotRunAngle(1800, 50, 0, 0.3);
//             vTaskDelay(1);
//         }
//     robotStop(0);
//     // gripperGetBallByXY(0,300);
// }

// void runToSiloesRed()
// {
//     RESET_ENCODER_WH();
//     robotRunAngle(0, 50, 0, 0.3);
//     for (i = 0; i < 50; i++)
//         while (getEncoderTong() < 1000)
//         {
//             if (lazerTraiValue > 170)
//                 robotRunAngle(-50, 50, 0, 0.3);
//             else if (lazerTraiValue < 170)
//                 robotRunAngle(50, 50, 0, 0.3);
//             else
//                 robotRunAngle(0, 50, 0, 0.3);
//             vTaskDelay(1);
//         }
//     for (i = 0; i < 50; i++)
//         while (lazerTruocValue > 113)
//         {
//             if (lazerTraiValue > 170)
//                 robotRunAngle(-50, 50, 0, 0.3);
//             else if (lazerTraiValue < 170)
//                 robotRunAngle(50, 50, 0, 0.3);
//             else
//                 robotRunAngle(0, 50, 0, 0.3);
//             vTaskDelay(1);
//         }
//     robotStop(0);
//     // gripperGetBallByXY(0,300);
// }

// // //===================================SHAGAI 2 DO======================================//
// // void Retry_SanDo_2(void)
// // {
// // 	xl_Nang_Dai_Ve, delay_ms(500);
// // 	xl_Nang_Ngan_Ra, delay_ms(1500);
// // 	xl_Don_Ra, delay_ms(500);

// // 	robotRunAngle(-900, 10, -900, 0);
// // 	while (lazeTruocValue > 80)
// // 		if (WannaExit())
// // 			while (1)
// // 				robotStop(0);

// // 	robotRunAngle(-900, 10, -890, 0);
// // 	delay_ms(300);
// // 	robotStop(0);

// // 	xl_Shagai_Kep, delay_ms(500);
// // 	xl_Truot_Len, delay_ms(1000);
// // 	xl_Don_Ve;
// // 	delay_ms(500);
// // 	xl_Nang_Ngan_Ve;

// // 	//---------------------------CHAY VAO VI TRI BAN 2---------------------------------//
// // 	RESET_ENCODER();

// // 	while (lazeTruocValue > 200)
// // 	{
// // 		if (WannaExit())
// // 			while (1)
// // 				robotStop(0);
// // 		robotRunAngle(-1920, 50, 0, 0);
// // 	}

// // 	RESET_ENCODER();
// // 	while (ENCODER() < 3000)
// // 	{
// // 		if (WannaExit())
// // 			while (1)
// // 				robotStop(0);
// // 		cap_thanh_lazer_truoc(-900, -900, 60, 40);
// // 	}

// // 	while (ENCODER() < 3200)
// // 	{
// // 		if (WannaExit())
// // 			while (1)
// // 				robotStop(0);
// // 		cap_thanh_lazer_truoc(-900, -900, 30, 40);
// // 	}

// // 	//---------------------------XOAY GOC BAN 2---------------------------------//
// // 	robotRun(-900, 10);
// // 	robotRotate(-1400, -1, 3);
// // 	while (_robotIMUAngle > -1400)
// // 		if (WannaExit())
// // 			while (1)
// // 				robotStop(0);
// // 	robotStop(0);

// // 	robotRun(0, 8);
// // 	xl_Doi_Ra;
// // 	delay_ms(1500);
// // 	robotStop(0);
// // 	xl_Shagai_Nha;
// // 	delay_ms(500);
// // 	xl_Truot_Xuong;
// // 	delay_ms(700);
// // 	xl_Shagai_Kep;
// // 	delay_ms(500);
// // 	xl_Shagai_Nha;
// // 	delay_ms(1500);

// // 	xl_Ban_Ra;
// // 	delay_ms(1000);
// // 	xl_Ban_Ve;
// // 	delay_ms(500);
// // 	xl_Doi_Ve;

// // 	//==============================LAY SHAGAI 3===================================//
// // 	RESET_ENCODER();

// // 	while (_robotIMUAngle < -900)
// // 	{
// // 		robotRun(1400, 25);
// // 		robotRotate(-900, 1, 0);
// // 	}

// // 	//---------------------------CAP THANH LUI LAY SHAGAI 3---------------------------------//
// // 	while (ENCODER() < 3500)
// // 	{
// // 		if (WannaExit())
// // 			while (1)
// // 				robotStop(0);
// // 		cap_thanh_lazer_truoc(900, -900, 70, 25);
// // 	}

// // 	while (ENCODER() < 4100)
// // 	{
// // 		if (WannaExit())
// // 			while (1)
// // 				robotStop(0);
// // 		cap_thanh_lazer_truoc(900, -900, 60, 25);
// // 	}

// // 	while (lazeTruocValue < 400)
// // 	{
// // 		if (WannaExit())
// // 			while (1)
// // 				robotStop(0);
// // 		robotRunAngle(0, 50, -900, 0);
// // 	}

// // 	//---------------------------CHAY LAY SHAGAI 3---------------------------------//
// // 	RESET_ENCODER();
// // 	xl_Nang_Ngan_Ra;

// // 	while (ENCODER() < 700)
// // 	{
// // 		if (WannaExit())
// // 			while (1)
// // 				robotStop(0);
// // 		xl_Nang_Ngan_Ra;
// // 		robotRunAngle(-250, 50, -900, 0);
// // 	}

// // 	robotRunAngle(-250, 35, -900, 0);
// // 	while (ENCODER() < 1500)
// // 		if (WannaExit())
// // 			while (1)
// // 				robotStop(0);

// // 	robotRunAngle(-250, 25, -910, 0);
// // 	while (ENCODER() < 2400)
// // 		if (WannaExit())
// // 			while (1)
// // 				robotStop(0);

// // 	robotRunAngle(-250, 15, -910, 0);
// // 	while (lazeTruocValue > 400)
// // 		if (WannaExit())
// // 			while (1)
// // 				robotStop(0);

// // 	robotRun(900, 8), delay_ms(1000);
// // 	robotRun(900, 5), delay_ms(500);
// // 	robotStop(0);

// // 	//---------------------------TOI VI TRI GAP SHAGAI 3---------------------------------//
// // 	xl_Don_Ra;
// // 	delay_ms(500);

// // 	robotRunAngle(-900, 10, 0, 0);
// // 	while (lazeTruocValue > 80)
// // 		if (WannaExit())
// // 			while (1)
// // 				robotStop(0);

// // 	robotRunAngle(-900, 10, 0, 0);
// // 	delay_ms(300);
// // 	robotStop(0);

// // 	xl_Shagai_Kep, delay_ms(500);
// // 	xl_Truot_Len, delay_ms(1000);
// // 	xl_Don_Ve;
// // 	delay_ms(500);

// // 	//---------------------------CHAY VAO VI TRI BAN 3---------------------------------//

// // 	while (lazeTruocValue < 445)
// // 	{
// // 		if (WannaExit())
// // 			while (1)
// // 				robotStop(0);
// // 		robotRun(1800, 15);
// // 	}
// // 	robotStop(0);

// // 	RESET_ENCODER();

// // 	robotRunAngle(-2040, 50, 0, 0);
// // 	xl_Nang_Ngan_Ve;
// // 	delay_ms(800);
// // 	while (lazeTruocValue > 250)
// // 		if (WannaExit())
// // 			while (1)
// // 				robotStop(0);

// // 	RESET_ENCODER();
// // 	while (ENCODER() < 3000)
// // 	{
// // 		if (WannaExit())
// // 			while (1)
// // 				robotStop(0);
// // 		cap_thanh_lazer_truoc(-900, -900, 60, 40);
// // 	}

// // 	while (ENCODER() < 3200)
// // 	{
// // 		if (WannaExit())
// // 			while (1)
// // 				robotStop(0);
// // 		cap_thanh_lazer_truoc(-900, -900, 30, 40);
// // 	}

// // 	//---------------------------XOAY GOC BAN 3---------------------------------//
// // 	robotRun(-900, 10);
// // 	robotRotate(-1410, -1, 3);
// // 	while (_robotIMUAngle > -1400)
// // 		if (WannaExit())
// // 			while (1)
// // 				robotStop(0);

// // 	robotRun(0, 8);
// // 	xl_Doi_Ra;
// // 	delay_ms(1500);
// // 	robotStop(0);

// // 	xl_Shagai_Nha;
// // 	delay_ms(500);
// // 	xl_Truot_Xuong;
// // 	delay_ms(700);
// // 	xl_Shagai_Kep;
// // 	delay_ms(500);
// // 	xl_Shagai_Nha;
// // 	delay_ms(1500);

// // 	xl_Ban_Ra;
// // 	delay_ms(1000);
// // 	xl_Ban_Ve;
// // 	delay_ms(500);
// // 	xl_Doi_Ve;

// // 	robotStop(0);
// // }

// // //--------------------------------------------------------------------------------------//
// // //====================================SHAGAI 3 DO==========================================//
// // //--------------------------------------------------------------------------------------//

// // void Retry_SanDo_3(void)
// // {
// // 	xl_Nang_Dai_Ve, delay_ms(500);
// // 	xl_Nang_Ngan_Ra, delay_ms(1500);
// // 	xl_Don_Ra, delay_ms(500);

// // 	robotRunAngle(-900, 10, 0, 0);
// // 	while (lazeTruocValue > 80)
// // 		if (WannaExit())
// // 			while (1)
// // 				robotStop(0);

// // 	robotRunAngle(-900, 10, 0, 0);
// // 	delay_ms(300);
// // 	robotStop(0);

// // 	xl_Shagai_Kep, delay_ms(500);
// // 	xl_Truot_Len, delay_ms(1000);
// // 	xl_Don_Ve;
// // 	delay_ms(500);

// // 	//---------------------------CHAY VAO VI TRI BAN 3---------------------------------//

// // 	while (lazeTruocValue < 445)
// // 	{
// // 		if (WannaExit())
// // 			while (1)
// // 				robotStop(0);
// // 		robotRun(1800, 15);
// // 	}
// // 	robotStop(0);

// // 	RESET_ENCODER();

// // 	robotRunAngle(-2040, 50, 0, 0);
// // 	xl_Nang_Ngan_Ve;
// // 	delay_ms(800);
// // 	while (lazeTruocValue > 250)
// // 		if (WannaExit())
// // 			while (1)
// // 				robotStop(0);

// // 	RESET_ENCODER();
// // 	while (ENCODER() < 3000)
// // 	{
// // 		if (WannaExit())
// // 			while (1)
// // 				robotStop(0);
// // 		cap_thanh_lazer_truoc(-900, -900, 60, 40);
// // 	}

// // 	while (ENCODER() < 3200)
// // 	{
// // 		if (WannaExit())
// // 			while (1)
// // 				robotStop(0);
// // 		cap_thanh_lazer_truoc(-900, -900, 30, 40);
// // 	}

// // 	//---------------------------XOAY GOC BAN 3---------------------------------//
// // 	robotRun(-900, 10);
// // 	robotRotate(-1410, -1, 3);
// // 	while (_robotIMUAngle > -1400)
// // 		if (WannaExit())
// // 			while (1)
// // 				robotStop(0);

// // 	robotRun(0, 8);
// // 	xl_Doi_Ra;
// // 	delay_ms(1500);
// // 	robotStop(0);

// // 	xl_Shagai_Nha;
// // 	delay_ms(500);
// // 	xl_Truot_Xuong;
// // 	delay_ms(700);
// // 	xl_Shagai_Kep;
// // 	delay_ms(500);
// // 	xl_Shagai_Nha;
// // 	delay_ms(1500);

// // 	xl_Ban_Ra;
// // 	delay_ms(1000);
// // 	xl_Ban_Ve;
// // 	delay_ms(500);
// // 	xl_Doi_Ve;

// // 	robotStop(0);
// // }

// // //-------------------------------------------------------------------------------------------//
// // //====================================SHAGAI  2 XANH==========================================//
// // //-------------------------------------------------------------------------------------------//

// // void Retry_SanXanh_2(void)
// // {
// // 	xl_Nang_Dai_Ve, delay_ms(500);
// // 	xl_Nang_Ngan_Ra, delay_ms(1500);
// // 	xl_Don_Ra, delay_ms(500);

// // 	robotRunAngle(900, 7, 0, 0);
// // 	while (lazeTruocValue > 80)
// // 		if (WannaExit())
// // 			while (1)
// // 				robotStop(0);

// // 	robotRunAngle(890, 7, 0, 0);
// // 	delay_ms(300);
// // 	robotStop(0);

// // 	xl_Shagai_Kep, delay_ms(700);
// // 	xl_Truot_Len, delay_ms(1500);
// // 	xl_Don_Ve;
// // 	delay_ms(500);

// // 	//---------------------------CHAY VAO VI TRI BAN 2---------------------------------//
// // 	RESET_ENCODER();

// // 	robotRunAngle(1850, 40, 0, 0);
// // 	xl_Nang_Ngan_Ve;
// // 	delay_ms(800);
// // 	while (lazeTruocValue > 200)
// // 		if (WannaExit())
// // 			while (1)
// // 				robotStop(0);

// // 	RESET_ENCODER();
// // 	while (ENCODER() < 3100)
// // 	{
// // 		if (WannaExit())
// // 			while (1)
// // 				robotStop(0);
// // 		cap_thanh_lazer_truoc(900, 900, 60, 40);
// // 	}

// // 	while (ENCODER() < 3600)
// // 	{
// // 		if (WannaExit())
// // 			while (1)
// // 				robotStop(0);
// // 		cap_thanh_lazer_truoc(900, 900, 20, 40);
// // 	}

// // 	//---------------------------XOAY GOC BAN 2---------------------------------//
// // 	robotRun(900, 15);
// // 	robotRotate(1410, 1, 4);
// // 	while (_robotIMUAngle < 1400)
// // 		if (WannaExit())
// // 			while (1)
// // 				robotStop(0);

// // 	robotRun(0, 8), delay_ms(500);
// // 	robotStop(0);

// // 	xl_Doi_Ra;
// // 	delay_ms(1200);
// // 	xl_Shagai_Nha;
// // 	delay_ms(500);
// // 	xl_Truot_Xuong;
// // 	delay_ms(700);
// // 	xl_Shagai_Kep;
// // 	delay_ms(500);
// // 	xl_Shagai_Nha;
// // 	delay_ms(1500);

// // 	xl_Ban_Ra;
// // 	delay_ms(1000);
// // 	xl_Ban_Ve;
// // 	delay_ms(500);
// // 	xl_Doi_Ve;

// // 	//=================================LAY SHAGAI 3==================================//
// // 	RESET_ENCODER();
// // 	xl_Doi_Ve;

// // 	while (_robotIMUAngle > 900)
// // 	{
// // 		robotRun(-1400, 20);
// // 		robotRotate(900, -1, 0);
// // 	}

// // 	while (ENCODER() < 3500)
// // 	{
// // 		if (WannaExit())
// // 			while (1)
// // 				robotStop(0);
// // 		cap_thanh_lazer_truoc(-900, 900, 60, 35);
// // 	}

// // 	while (ENCODER() < 4000)
// // 	{
// // 		if (WannaExit())
// // 			while (1)
// // 				robotStop(0);
// // 		cap_thanh_lazer_truoc(-900, 900, 40, 35);
// // 	}

// // 	robotRunAngle(0, 40, 900, 0);
// // 	while (lazeTruocValue < 300)
// // 		if (WannaExit())
// // 			while (1)
// // 				robotStop(0);

// // 	//---------------------------CHAY LAY SHAGAI 3---------------------------------//
// // 	RESET_ENCODER();

// // 	while (ENCODER() < 700)
// // 	{
// // 		if (WannaExit())
// // 			while (1)
// // 				robotStop(0);
// // 		xl_Nang_Ngan_Ra;
// // 		robotRunAngle(200, 50, -900, 0);
// // 	}

// // 	robotRunAngle(200, 35, -900, 0);
// // 	while (ENCODER() < 1500)
// // 		if (WannaExit())
// // 			while (1)
// // 				robotStop(0);

// // 	robotRunAngle(200, 20, -900, 0);
// // 	while (ENCODER() < 2450)
// // 		if (WannaExit())
// // 			while (1)
// // 				robotStop(0);

// // 	robotRunAngle(200, 12, -900, 0);
// // 	while (lazeTruocValue > 500)
// // 		if (WannaExit())
// // 			while (1)
// // 				robotStop(0);

// // 	robotRunAngle(0, 7, -900, 0);
// // 	delay_ms(1000);

// // 	robotStop(0);

// // 	//---------------------------TOI VI TRI GAP SHAGAI 3---------------------------------//
// // 	xl_Don_Ra;
// // 	delay_ms(300);

// // 	robotRunAngle(900, 7, 0, 0);
// // 	while (lazeTruocValue > 80)
// // 		if (WannaExit())
// // 			while (1)
// // 				robotStop(0);

// // 	robotRunAngle(890, 7, 0, 0);
// // 	delay_ms(300);
// // 	robotStop(0);

// // 	xl_Shagai_Kep, delay_ms(700);
// // 	xl_Truot_Len, delay_ms(1500);
// // 	xl_Don_Ve;
// // 	delay_ms(500);

// // 	//---------------------------CHAY VAO VI TRI BAN 3---------------------------------//
// // 	while (lazeTruocValue < 445)
// // 	{
// // 		if (WannaExit())
// // 			while (1)
// // 				robotStop(0);
// // 		robotRun(1800, 15);
// // 	}

// // 	robotStop(0);
// // 	RESET_ENCODER();

// // 	robotRunAngle(2010, 40, 0, 0);
// // 	xl_Nang_Ngan_Ve;
// // 	delay_ms(800);
// // 	while (lazeTruocValue > 200)
// // 		if (WannaExit())
// // 			while (1)
// // 				robotStop(0);

// // 	RESET_ENCODER();
// // 	while (ENCODER() < 3100)
// // 	{
// // 		if (WannaExit())
// // 			while (1)
// // 				robotStop(0);
// // 		cap_thanh_lazer_truoc(900, 900, 60, 40);
// // 	}

// // 	while (ENCODER() < 3750)
// // 	{
// // 		if (WannaExit())
// // 			while (1)
// // 				robotStop(0);
// // 		cap_thanh_lazer_truoc(900, 900, 20, 40);
// // 	}

// // 	//---------------------------XOAY GOC BAN 3---------------------------------//
// // 	robotRun(900, 15);
// // 	robotRotate(1410, 1, 4);
// // 	while (_robotIMUAngle < 1400)
// // 		if (WannaExit())
// // 			while (1)
// // 				robotStop(0);

// // 	robotRun(0, 8), delay_ms(1000);
// // 	robotStop(0);

// // 	xl_Doi_Ra;
// // 	delay_ms(1200);
// // 	xl_Shagai_Nha;
// // 	delay_ms(500);
// // 	xl_Truot_Xuong;
// // 	delay_ms(700);
// // 	xl_Shagai_Kep;
// // 	delay_ms(500);
// // 	xl_Shagai_Nha;
// // 	delay_ms(1500);

// // 	xl_Ban_Ra;
// // 	delay_ms(1000);
// // 	xl_Ban_Ve;
// // 	delay_ms(500);
// // 	xl_Doi_Ve;

// // 	robotStop(0);
// // }

// // //-------------------------------------------------------------------------------------------//
// // //====================================SHAGAI 3 XANH==========================================//
// // //-------------------------------------------------------------------------------------------//

// // void Retry_SanXanh_3(void)
// // {
// // 	xl_Nang_Dai_Ve, delay_ms(500);
// // 	xl_Nang_Ngan_Ra, delay_ms(1500);
// // 	xl_Don_Ra, delay_ms(500);

// // 	robotRunAngle(900, 7, 0, 0);
// // 	while (lazeTruocValue > 80)
// // 		if (WannaExit())
// // 			while (1)
// // 				robotStop(0);

// // 	robotRunAngle(890, 7, 0, 0);
// // 	delay_ms(300);
// // 	robotStop(0);

// // 	xl_Shagai_Kep, delay_ms(700);
// // 	xl_Truot_Len, delay_ms(1500);
// // 	xl_Don_Ve;
// // 	delay_ms(500);

// // 	//---------------------------CHAY VAO VI TRI BAN 3---------------------------------//
// // 	while (lazeTruocValue < 445)
// // 	{
// // 		if (WannaExit())
// // 			while (1)
// // 				robotStop(0);
// // 		robotRun(1800, 15);
// // 	}

// // 	robotStop(0);
// // 	RESET_ENCODER();

// // 	robotRunAngle(2010, 40, 0, 0);
// // 	xl_Nang_Ngan_Ve;
// // 	delay_ms(800);
// // 	while (lazeTruocValue > 200)
// // 		if (WannaExit())
// // 			while (1)
// // 				robotStop(0);

// // 	RESET_ENCODER();
// // 	while (ENCODER() < 3100)
// // 	{
// // 		if (WannaExit())
// // 			while (1)
// // 				robotStop(0);
// // 		cap_thanh_lazer_truoc(900, 900, 60, 40);
// // 	}

// // 	while (ENCODER() < 3750)
// // 	{
// // 		if (WannaExit())
// // 			while (1)
// // 				robotStop(0);
// // 		cap_thanh_lazer_truoc(900, 900, 20, 40);
// // 	}

// // 	//---------------------------XOAY GOC BAN 3---------------------------------//
// // 	robotRun(900, 15);
// // 	robotRotate(1410, 1, 4);
// // 	while (_robotIMUAngle < 1400)
// // 		if (WannaExit())
// // 			while (1)
// // 				robotStop(0);

// // 	robotRun(0, 8), delay_ms(1000);
// // 	robotStop(0);

// // 	xl_Doi_Ra;
// // 	delay_ms(1200);
// // 	xl_Shagai_Nha;
// // 	delay_ms(500);
// // 	xl_Truot_Xuong;
// // 	delay_ms(700);
// // 	xl_Shagai_Kep;
// // 	delay_ms(500);
// // 	xl_Shagai_Nha;
// // 	delay_ms(1500);

// // 	xl_Ban_Ra;
// // 	delay_ms(1000);
// // 	xl_Ban_Ve;
// // 	delay_ms(500);
// // 	xl_Doi_Ve;

// // 	robotStop(0);
// // }
