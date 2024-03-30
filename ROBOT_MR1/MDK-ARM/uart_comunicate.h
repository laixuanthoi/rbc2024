// stm32 send uart
// void USART_SendSTRING(void)
// {
//    USART_SendData(USART3, 255);// bat dau gui du lieu
//    vTaskDelay(5);
//    //------------------------------------------
//    USART_SendData(USART3, MauSan);
//    vTaskDelay(5);
//    USART_SendData(USART3, RobotMode);// 1- lay bong tai kho; 2- lay bong tu do; 5-quan sat ro bong
//    vTaskDelay(5);
//    USART_SendData(USART3, (uint16_t) Servo_Cam/100);
//    vTaskDelay(5);
// }