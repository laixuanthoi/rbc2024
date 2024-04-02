// stm32 send uart

int WIDTH = 560;
int HEIGHT = 450;
void USART_SendSTRING(void)
{
//    USART_SendData(USART3, 255);// bat dau gui du lieu
//    vTaskDelay(5);
   //------------------------------------------
   USART_SendData(USART3, GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_15));
   vTaskDelay(500);
}
void getXYFromXuanThoi(){
    if (GP_BTN[1] >= 0 && GP_BTN[1] < 255)
        Y_Thoi = map_int(GP_BTN[1],0,254,(int)-HEIGHT/2,(int)HEIGHT/2);
    else Y_Thoi = 0;
    if (GP_BTN[0] >= 0 && GP_BTN[0] < 255)
        X_Thoi = map_int(GP_BTN[0],0,254,(int)-WIDTH/2,(int)WIDTH/2);
    else X_Thoi = 0;
    vTaskDelay(5);

}