// //*****************************8 bien toan cuc *************************************
// char bien_xi_lanh_nang, bien_xi_lanh_kep, Khoang_cach_1_vong = 16, bien_xl_nang_ha, bien_xl_mac_vong, bien_xl_chot, bien_xl_kep_vong, bien_xl_day, bien_xl_tru_giua, bien_xl_keo_loxo;
// char vi_tri = 0, Cbcc = 0, Cbnv = 0, Cbnn = 0, Resetnangvong = 0;

// // int  Nang_vong_max = 322, Nang_vong_min = 105, i;
// // int  Nang_goc_max = 540, Nang_goc_min = 300;
// int max_speed = 50;
// int speed_temp = 0;
// int en_tru = 60;
// int reset_Y = 1;
// int reset_X = 1;
// int reset_Mam = 1;
// int tagetEncoderY = 3000;
// int tagetEncoderX = -530;
// int tagetBTNangBong = 330; // 720;
// int tagetMamXoay = 650;

// int dangXoayY = 0;
// int dangRunY = 0;

// int midMamXoay = 900;

// int valueLazerTamV3 = 175;

// void robotGamePadControl(void)
// {

//     int tocdo = 50, td_x = 30;
//     float tocdoXoay = 0;
//     int rJoy_LR = (RJOY_LR >= 5 && RJOY_LR <= 250) ? 1 : 0;
//     int lJoy_LR = (LJOY_LR >= 5 && LJOY_LR <= 250) ? 1 : 0;

//     if (UP && DOWN && RIGHT && LEFT && rJoy_LR && lJoy_LR && O)
//     {                 // Khong dieu khien
//         robotStop(0); // truot banh

//         return;
//     }
//     /*_____________________________//___________________________*/

//     /********************** TOC DO ****************************/
//     /*_____________________________//___________________________*/
//     if (!L1)
//         tocdo = 35, tocdoXoay = 0.3;
//     else
//         tocdo = 10, tocdoXoay = 0.2;

//     //--------- chay cac huong -----------
//     if (!UP && DOWN && RIGHT && LEFT && L2)
//         robotRun(0, tocdo);
//     else if (UP && !DOWN && RIGHT && LEFT && L2)
//         robotRun(1800, tocdo);
//     else if (UP && DOWN && !RIGHT && LEFT && L2)
//         robotRun(900, tocdo);
//     else if (UP && DOWN && RIGHT && !LEFT && L2)
//         robotRun(-900, tocdo);

//     else if (!UP && DOWN && !RIGHT && LEFT && L2)
//         robotRun(450, tocdo);
//     else if (!UP && DOWN && RIGHT && !LEFT && L2)
//         robotRun(-450, tocdo);
//     else if (UP && !DOWN && !RIGHT && LEFT && L2)
//         robotRun(1350, tocdo);
//     else if (UP && !DOWN && RIGHT && !LEFT && L2)
//         robotRun(-1350, tocdo);

//     //-------------- Dang chay va Khong chay nua, chi xoay ----------------
//     if (UP && DOWN && RIGHT && LEFT && !rJoy_LR && lJoy_LR && robotIsRun())
//         robotStop(0);

//     //-------------- Xoay ----------------
//     if (rJoy_LR)
//         robotRotateStop();
//     else if ((RJOY_LR < 5) && L2)
//     {
//         if (robotIsRun())
//             robotRotateFree(-0.3, 0);
//         else
//             robotRotateFree(-tocdoXoay, 0);
//     }
//     else if ((RJOY_LR > 250) && L2)
//     {
//         if (robotIsRun())
//             robotRotateFree(0.3, 0);
//         else
//             robotRotateFree(tocdoXoay, 0);
//     }

//     else
//         robotRotateStop();
// }
// //////-------------------------------------------------------------
// void ADCValue_Control(void)
// {
//     // KHAI BAO LAZER
//     static unsigned int lazeTruocCouter = 0, lazeTruoc_SUM = 0;
//     static unsigned int lazeSauCouter = 0, lazeSau_SUM = 0;
//     static unsigned int lazePhaiCouter = 0, lazePhai_SUM = 0;
//     static unsigned int lazeTraiCouter = 0, lazeTrai_SUM = 0;

//     // KHAI BAO BIEN TRO
//     static unsigned int BientroNangBongCouter = 0, BientroNangBong_SUM = 0;
//     static unsigned int BientroMamXoayCouter = 0, BientroMamXoay_SUM = 0;
//     ////------------------------
//     if (lazeTruocCouter++ < 50)
//     {
//         lazeTruoc_SUM += cam_bien_laze_truoc;
//     }
//     else
//     {
//         lazeTruocValue = lazeTruoc_SUM / 50;
//         lazeTruocCouter = 0;
//         lazeTruoc_SUM = 0;
//     }

//     //	if(lazeSauCouter++ < 50)
//     //	{
//     //		lazeSau_SUM += cam_bien_laze_sau;
//     //	}
//     //	else
//     //  {
//     //		lazeSauValue = lazeSau_SUM/50;
//     //		lazeSauCouter = 0;
//     //		lazeSau_SUM = 0;}
//     //

//     if (lazePhaiCouter++ < 20)
//     {
//         lazePhai_SUM += cam_bien_laze_phai;
//     }
//     else
//     {
//         lazePhaiValue = lazePhai_SUM / 20;
//         lazePhaiCouter = 0;
//         lazePhai_SUM = 0;
//     }

//     if (lazeTraiCouter++ < 50)
//     {
//         lazeTrai_SUM += cam_bien_laze_trai;
//     }
//     else
//     {
//         lazeTraiValue = lazeTrai_SUM / 50;
//         lazeTraiCouter = 0;
//         lazeTrai_SUM = 0;
//     }

//     if (BientroMamXoayCouter++ < 50)
//     {
//         BientroMamXoay_SUM += bien_tro_xoay_mam;
//     }
//     else
//     {
//         BienTroMamXoayValue = BientroMamXoay_SUM / 50;
//         BientroMamXoayCouter = 0;
//         BientroMamXoay_SUM = 0;
//     }
//     if (BientroNangBongCouter++ < 50)
//     {
//         BientroNangBong_SUM += bien_tro_nang_bong;
//     }
//     else
//     {
//         BienTroNangBongValue = BientroNangBong_SUM / 50;
//         BientroNangBongCouter = 0;
//         BientroNangBong_SUM = 0;
//     }
// }
// // void test_truc_XY (void)
// //{
// //	if(!TRIANGLE) 			Mor_TrucY = 50, Mor_TrucY_len;
// //	else if(!X)					Mor_TrucY = 50, Mor_TrucY_xuong;
// //	else if(!SQUARE)		Mor_Mam = 250, Mor_Mam_thuan;
// //	else if(!O)					Mor_Mam = 250, Mor_Mam_nghich;
// //
// //	else 								Mor_TrucY = 0,
// //											Mor_Mam=0;
// //
// // }
// void test_cylinder(void)
// {
//     //***********************************************************************************
//     if (!NUT_3 == 0)
//     {
//         bien_xi_lanh_nang = ~bien_xi_lanh_nang;
//         while (!NUT_3)
//             vTaskDelay(1);
//     }
//     if (bien_xi_lanh_nang == 0)
//         XI_LANH_NANG_BONG_ON;
//     else
//         XI_LANH_NANG_BONG_OFF;
// }

// // void giu_Mam_Xoay(){
// //	if(BienTroMamXoayValue < Min_BT_Xoay - 7 || BienTroMamXoayValue > Max_BT_Xoay + 7)  {Mor_Mam = 0; return;}
// //	if(abs(BienTroMamXoayValue - taget_BT_Xoay) > 3){
// //		if(BienTroMamXoayValue > taget_BT_Xoay) Mor_Mam_nghich ;
// //		else Mor_Mam_thuan;
// //
// //		speed_temp = abs(BienTroMamXoayValue - taget_BT_Xoay)*5;
// //		if(speed_temp > 250) speed_temp = 250;
// //		if(speed_temp < 30) speed_temp = 70;
// //	  Mor_Mam = speed_temp;
// //	}
// //	else Mor_Mam = 0;
// // }
// void Quay_mam(void)
// {
//     if ((!SQUARE) && (taget_BT_Xoay < Max_BT_Xoay))
//         taget_BT_Xoay++, vTaskDelay(200);
//     else if ((!O) && (taget_BT_Xoay > Min_BT_Xoay))
//         taget_BT_Xoay--, vTaskDelay(200);
// }

// //******************************* dieu khien truc Y **************************************************************
// // void Giu_Truc_Y(){
// //	if(BienTroTrucYValue < Min_BT_Truc_Y - 7 || BienTroTrucYValue > Max_BT_Truc_Y + 7)  {Mor_TrucY = 2; return;}
// //	if(abs(BienTroTrucYValue - taget_BT_Truc_Y) > 4){
// //		if(BienTroTrucYValue > taget_BT_Truc_Y) Mor_TrucY_xuong;
// //		else Mor_TrucY_len;
// //
// //		speed_temp = abs(BienTroTrucYValue - taget_BT_Truc_Y)*2;
// //
// //		if(speed_temp > 80) speed_temp = 80;
// //		if(speed_temp < 30) speed_temp = 20;
// //	  Mor_TrucY = speed_temp;
// //	}
// //	else Mor_TrucY = 2;
// //}

// void Giu_Tay_Nang_Bong(void)
// {
//     if (fabs(BienTroNangBongValue - tagetBTNangBong) > 40)
//     {
//         if (BienTroNangBongValue > tagetBTNangBong)
//             Mor_Lat_Bong_Nghich;
//         else
//             Mor_Lat_Bong_Thuan;
//         Mor_Lat_Bong = 120;
//     }
//     else
//         Mor_Lat_Bong = 2;
// }

// void Giu_Truc_Y(void)
// {
//     if (reset_Y)
//     {
//         if (CBT_Y_TREN != 0)
//         {
//             Mor_Y_Len;
//             Mor_Y = 150;
//             dangXoayY = 1;
//         }
//         else
//         {
//             reset_Y = 0;
//             Mor_Y = 2;
//             dangXoayY = 0;
//             RESET_ENCODER_Y();
//         }
//     }
//     else
//     {
//         if (fabs(Encoder_Y - tagetEncoderY) > 20)
//         {
//             if (Encoder_Y > tagetEncoderY)
//                 Mor_Y_Len;
//             else
//                 Mor_Y_Xuong;
//             Mor_Y = 250;
//             dangXoayY = 1;
//         }
//         else
//             Mor_Y = 2;
//         dangXoayY = 0;
//     }
// }

// void Giu_Truc_X(void)
// {
//     if (reset_X)
//     {
//         if (CBT_X_VAO != 0)
//         {
//             if (dangXoayY == 0)
//             {
//                 Mor_X_Vao;
//                 Mor_X = 250;
//             }
//             else
//                 Mor_X = 2;
//         }
//         else
//         {
//             Mor_X = 2;
//             reset_X = 0;
//             RESET_ENCODER_X();
//         }
//     }
//     else
//     {
//         if (fabs(Encoder_X - tagetEncoderX) > 10)
//         {
//             if (Encoder_X > tagetEncoderX)
//             {
//                 Mor_X_Ra;
//             }
//             else
//                 Mor_X_Vao;

//             Mor_X = 250;
//         }
//         else
//             Mor_X = 2;
//     }
// }

// void Giu_Mam_Xoay(void)
// {
//     if (reset_Mam)
//     {
//         if (fabs(BienTroMamXoayValue - midMamXoay) > 10)
//         {
//             if (BienTroMamXoayValue > midMamXoay)
//                 Mor_Mam_Nghich;
//             else
//                 Mor_Mam_Thuan;
//             if (dangXoayY == 0)
//                 Mor_Mam = 20;
//             else
//                 Mor_Mam = 2;
//         }
//         else
//             Mor_Mam = 2;
//         reset_Mam = 0;
//     }
//     else
//     {
//         if (tagetMamXoay > 1020)
//             Mor_Mam = 2;
//         if (fabs(BienTroMamXoayValue - tagetMamXoay) > 10)
//         {
//             if (BienTroMamXoayValue > tagetMamXoay)
//                 Mor_Mam_Nghich;
//             else
//                 Mor_Mam_Thuan;
//             if (dangXoayY == 0)
//                 Mor_Mam = 40;
//             else
//                 Mor_Mam = 2;
//         }
//         else
//             Mor_Mam = 2;
//     }
// }

// void Nang_ha_Y(void)
// {
//     if ((LJOY_UD > 250) && (taget_BT_Truc_Y > Min_BT_Truc_Y))
//         taget_BT_Truc_Y--, vTaskDelay(200);
//     else if ((LJOY_UD < 5) && (taget_BT_Truc_Y < Max_BT_Truc_Y))
//         taget_BT_Truc_Y++, vTaskDelay(200);
// }

// //******************************* dieu khien truc X **************************************************************
// // void Giu_Truc_X(void){
// //	if(BienTroTrucXValue < Min_BT_Truc_X - 7 || BienTroTrucXValue > Max_BT_Truc_X +7)  {Mor_TrucX = 0; return;}
// //	if(abs(BienTroTrucXValue - taget_BT_Truc_X) > 3){
// //		if(BienTroTrucXValue > taget_BT_Truc_X) Mor_TrucX_vao;
// //		else Mor_TrucX_ra;
// //		speed_temp = (int)abs(BienTroTrucXValue - taget_BT_Truc_X)*10;
// //		if(speed_temp > 250) speed_temp = 250;
// //		if(speed_temp < 30) speed_temp = 30;
// //	  Mor_TrucX = speed_temp;
// //	}
// //	else Mor_TrucX = 0;
// //}

// void Ra_vao_X(void)
// {
//     if ((LJOY_LR > 250) && (taget_BT_Truc_X < Max_BT_Truc_X))
//         taget_BT_Truc_X++, vTaskDelay(200);
//     else if ((LJOY_LR < 5) && (taget_BT_Truc_X > Min_BT_Truc_X))
//         taget_BT_Truc_X--, vTaskDelay(200);
// }
// //******************************* san xanh **************************************************************
// // san xanh
// void bam_Thanh_Lazer_Truoc(int speed, int angle_fix, int AngleHead, int lazer_stable_truoc, int num_change_stable)
// {
//     if (lazeTruocValue - lazer_stable_truoc > num_change_stable)
//     {
//         robotRunAngle(900 + angle_fix, speed, AngleHead, 0.1);
//     }
//     else if (lazeTruocValue - lazer_stable_truoc < num_change_stable)
//     {
//         robotRunAngle(900 - angle_fix, speed, AngleHead, 0.1);
//     }
//     else
//         robotRunAngle(900, speed, AngleHead, 0.1);
// }

// void bam_Thanh_Lazer_Trai(int speed, int angle_fix, int AngleHead, int lazer_stable_truoc, int num_change_stable)
// {
//     if (lazeTraiValue - lazer_stable_truoc > num_change_stable)
//     {
//         robotRunAngle(0 + angle_fix, speed, AngleHead, 0.1);
//     }
//     else if (lazeTraiValue - lazer_stable_truoc < num_change_stable)
//     {
//         robotRunAngle(0 - angle_fix, speed, AngleHead, 0.1);
//     }
//     else
//         robotRunAngle(0, speed, AngleHead, 0.1);
// }

// // san do
// void bam_Thanh_Lazer_Truoc_SAN_DO(int speed, int angle_fix, int AngleHead, int lazer_stable_truoc, int num_change_stable)
// {
//     if (lazeTruocValue - lazer_stable_truoc > num_change_stable)
//     {
//         robotRunAngle(-900 - angle_fix, speed, AngleHead, 0.1);
//     }
//     else if (lazeTruocValue - lazer_stable_truoc < num_change_stable)
//     {
//         robotRunAngle(-900 + angle_fix, speed, AngleHead, 0.1);
//     }
//     else
//         robotRunAngle(-900, speed, AngleHead, 0.1);
// }

// void bam_Thanh_Lazer_Phai(int speed, int angle_fix, int AngleHead, int lazer_stable_truoc, int num_change_stable)
// {
//     if (lazePhaiValue - lazer_stable_truoc > num_change_stable)
//     {
//         robotRunAngle(0 - angle_fix, speed, AngleHead, 0.1);
//     }
//     else if (lazePhaiValue - lazer_stable_truoc < num_change_stable)
//     {
//         robotRunAngle(0 + angle_fix, speed, AngleHead, 0.1);
//     }
//     else
//         robotRunAngle(0, speed, AngleHead, 0.1);
// }

// void bam_Thanh_Lazer_Phai_lui(int speed, int angle_fix, int AngleHead, int lazer_stable_truoc, int num_change_stable)
// {
//     if (lazePhaiValue - lazer_stable_truoc > num_change_stable)
//     {
//         robotRunAngle(1800 + angle_fix, speed, AngleHead, 0.1);
//     }
//     else if (lazePhaiValue - lazer_stable_truoc < num_change_stable)
//     {
//         robotRunAngle(1800 - angle_fix, speed, AngleHead, 0.1);
//     }
//     else
//         robotRunAngle(1800, speed, AngleHead, 0.1);
// }

// void XUAT_PHAT_SAN_XANH(void)
// {
//     int speed1 = 40, speed = 10;
//     robotResetIMU();
//     RESET_ENCODER();

//     for (i = 0; i < 50; i++)
//         while (ENCODER_TONG() < 6000)
//             bam_Thanh_Lazer_Truoc(20, 50, 0, 365, 2);
//     vTaskDelay(1); // 80
//     for (i = 0; i < 50; i++)
//         while (lazeTraiValue > 30)
//             bam_Thanh_Lazer_Truoc(20, 50, 0, 20, 2);
//     vTaskDelay(1); // 20

//     RESET_ENCODER();
//     for (i = 0; i < 50; i++)
//         while (ENCODER_TONG() < 3000)
//             bam_Thanh_Lazer_Trai(40, 50, 0, 20, 2);
//     vTaskDelay(1); // 80

//     for (i = 0; i < 50; i++)
//         while (lazeTraiValue < 35)
//             bam_Thanh_Lazer_Trai(20, 50, 0, 20, 2);
//     vTaskDelay(1); // 20

//     RESET_ENCODER();
//     robotRunAngle(0, 40, 0, 0.1); // 40
//     for (i = 0; i < 50; i++)
//         while (ENCODER_TONG() < 270)
//             vTaskDelay(1);

//     RESET_ENCODER();
//     robotRunAngle(900, 40, 0, 0.1); // 60
//     for (i = 0; i < 50; i++)
//         while (ENCODER_TONG() < 4000)
//             vTaskDelay(1);
//     RESET_ENCODER();
//     robotRunAngle(-1800, 40, 0, 0.1); // 60
//     for (i = 0; i < 50; i++)
//         while (ENCODER_TONG() < 3500)
//             vTaskDelay(1);
//     RESET_ENCODER();

//     robotStop(0);

//     while (1)
//         ;
// }
// void XUAT_PHAT_SAN_DO(void)
// {

//     RESET_ENCODER();
//     robotRunAngle(-900, 70, 0, 0.1);
//     while (ENCODER_TONG() < 4200)
//     {
//         wantExit();
//         vTaskDelay(1);
//     }
//     robotRunAngle(-900, 50, 0, 0.1);

//     while (lazeTraiValue > 75)
//     {
//         wantExit();
//         vTaskDelay(1);
//     }

//     RESET_ENCODER();
//     robotRunAngle(0, 50, 0, 0.1);

//     while (ENCODER_TONG() < 3500)
//     {
//         wantExit();
//         vTaskDelay(1);
//     }
//     while (lazeTraiValue < 80)
//     {
//         wantExit();
//         vTaskDelay(1);
//     }
//     RESET_ENCODER();

//     robotRunAngle(0, 50, 0, 0.1);
//     while (ENCODER_TONG() < 280)
//     {
//         wantExit();
//         vTaskDelay(1);
//     }

//     robotRunAngle(-900, 50, 0, 0.1);
//     while (ENCODER_TONG() < 2500)
//     {
//         wantExit();
//         vTaskDelay(1);
//     }

//     while (lazeTraiValue > 185)
//     {
//         wantExit();
//         vTaskDelay(1);
//     }
//     RESET_ENCODER();
//     robotRunAngle(-1800, 50, 0, 0.1);
//     while (ENCODER_TONG() < 3600)
//     {
//         if (fabs(lazeTraiValue - valueLazerTamV3) > 2)
//         {
//             if (lazeTraiValue > valueLazerTamV3)
//                 robotRunAngle(-1770, 50, 0, 0.2);
//             else
//                 robotRunAngle(-1870, 50, 0, 0.2);
//         }
//         else
//             robotRunAngle(-1800, 50, 0, 0.2);
//     }

//     robotStop(0);

//     while (1)
//         ;

//     //	while(ENCODER_TONG()  < 3000)	 				{taget_BT_Xoay = 710;bam_Thanh_Lazer_Phai_lui(10,200,0,170,3); vTaskDelay(1);};
//     //
//     //	robotStop(0);
//     //	while(1);
// }

// void layBong(void)
// {
//     tagetBTNangBong = 330;
//     Mor_Hut = 1100;
//     tagetEncoderY = 5850;
//     while (fabs(Encoder_Y - tagetEncoderY) > 20)
//         vTaskDelay(100);
//     vTaskDelay(1000);
//     tagetEncoderY = 5;
//     vTaskDelay(1000);
//     tagetBTNangBong = 800;
//     while (fabs(Encoder_Y - tagetEncoderY) > 20)
//         vTaskDelay(100);
//     XI_LANH_NANG_BONG_ON;
//     vTaskDelay(1000);
//     Mor_Hut = 850;
//     tagetMamXoay = 5;
//     while (fabs(BienTroMamXoayValue - tagetMamXoay) > 10)
//         vTaskDelay(100);
// }

// void thaBong(void)
// {
//     Mor_Hut = 950;
//     tagetBTNangBong = 530;
//     while (fabs(BienTroNangBongValue - tagetBTNangBong) > 40)
//         vTaskDelay(100);
//     Mor_Hut = 400;
//     XI_LANH_NANG_BONG_OFF;
//     vTaskDelay(2500);
//     RESET_ENCODER();
//     robotRun(1800, 15);
//     while (ENCODER_TONG() < 300)
//     {
//         wantExit();
//         vTaskDelay(1);
//     }
//     robotStop(0);
// }
