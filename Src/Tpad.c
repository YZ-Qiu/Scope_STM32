/* Includes ------------------------------------------------------------------*/
#include "Tpad.h"
#include "delay.h"

//
/* Private variables ---------------------------------------------------------*/
Matrix        matrix;
Coordinate    display;
Coordinate    ScreenSample[3];
Coordinate    DisplaySample[3] = { {30, 45}, {290, 45}, {160, 210} };

/* Private define ------------------------------------------------------------*/
#define THRESHOLD 2

void Tpad_Init(void) 
{ 
  GPIO_InitTypeDef GPIO_InitStruct;

  /* Configure GPIOs ---------------------------------------------------------*/
  //RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

  /* Configure SPI3 pins: SCK, MISO and MOSI ---------------------------------*/ 
  //see spi.c
/*  GPIO_InitStruct.Pin = Tpad_SCK_PIN | Tpad_MISO_PIN | Tpad_MOSI_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Speed =  GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_Init(Tpad_PORT, &GPIO_InitStruct);
*/
  /* TP_CS */
  GPIO_InitStruct.Pin = Tpad_CS_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(Tpad_PORT, &GPIO_InitStruct);

  /* TP_IRQ */
  GPIO_InitStruct.Pin =  Tpad_IRQ_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(Tpad_PORT, &GPIO_InitStruct);

  
  set_CS(); 

  /* Configure SPI -----------------------------------------------------------*/
	//see spi.c

} 

uint16_t Read_X(void)  
{  
  uint16_t curr_X;

  reset_CS(); 
  delay(1); 
  WR_CMD(CHX); 
  delay(1); 
  curr_X=RD_AD(); 
  set_CS(); 
  return curr_X;    
} 

uint16_t Read_Y(void)  
{  
  uint16_t curr_Y; 

  reset_CS(); 
  delay(1); 
  WR_CMD(CHY); 
  delay(1); 
  curr_Y=RD_AD(); 
  set_CS(); 
  return curr_Y;     
} 

void Tpad_GetAdXY(int *x,int *y)  
{ 
  uint16_t adx,ady; 
  adx=Read_X(); 
  delay(1); 
  ady=Read_Y(); 
  *x=adx; 
  *y=ady; 
} 
	
Coordinate *Read_Tpad(void)
{
  static Coordinate  screen;
  int m0,m1,m2,TP_X[1],TP_Y[1],temp[3];
  uint8_t count=0;
  int buffer[2][9]={{0},{0}};
  
  do
  {		   
    Tpad_GetAdXY(TP_X,TP_Y);  
	  buffer[0][count]=TP_X[0];  
	  buffer[1][count]=TP_Y[0];
	  count++;  
  }
  while(!read_IRQ()&& count<9);  /* TP_INT_IN  */
  if(count==9)   /* Average X Y  */ 
  {
	/* Average X  */
  temp[0]=(buffer[0][0]+buffer[0][1]+buffer[0][2])/3;
	temp[1]=(buffer[0][3]+buffer[0][4]+buffer[0][5])/3;
	temp[2]=(buffer[0][6]+buffer[0][7]+buffer[0][8])/3;

	m0=temp[0]-temp[1];
	m1=temp[1]-temp[2];
	m2=temp[2]-temp[0];

	m0=m0>0?m0:(-m0);
  m1=m1>0?m1:(-m1);
	m2=m2>0?m2:(-m2);

	if( m0>THRESHOLD  &&  m1>THRESHOLD  &&  m2>THRESHOLD ) return 0;

	if(m0<m1)
	{
	  if(m2<m0) 
	    screen.x=(temp[0]+temp[2])/2;
	  else 
	    screen.x=(temp[0]+temp[1])/2;	
	}
	else if(m2<m1) 
	  screen.x=(temp[0]+temp[2])/2;
	else 
	  screen.x=(temp[1]+temp[2])/2;

	/* Average Y  */
  temp[0]=(buffer[1][0]+buffer[1][1]+buffer[1][2])/3;
	temp[1]=(buffer[1][3]+buffer[1][4]+buffer[1][5])/3;
	temp[2]=(buffer[1][6]+buffer[1][7]+buffer[1][8])/3;
	m0=temp[0]-temp[1];
	m1=temp[1]-temp[2];
	m2=temp[2]-temp[0];
	m0=m0>0?m0:(-m0);
	m1=m1>0?m1:(-m1);
	m2=m2>0?m2:(-m2);
	if(m0>THRESHOLD&&m1>THRESHOLD&&m2>THRESHOLD) return 0;

	if(m0<m1)
	{
	  if(m2<m0) 
	    screen.y=(temp[0]+temp[2])/2;
	  else 
	    screen.y=(temp[0]+temp[1])/2;	
    }
	else if(m2<m1) 
	   screen.y=(temp[0]+temp[2])/2;
	else
	   screen.y=(temp[1]+temp[2])/2;

	return &screen;
  }  
  return 0; 
}
	 
FunctionalState setCalibrationMatrix( Coordinate * displayPtr,
                          Coordinate * screenPtr,
                          Matrix * matrixPtr)
{

  FunctionalState retTHRESHOLD = ENABLE ;
  /* K��(X0��X2) (Y1��Y2)��(X1��X2) (Y0��Y2) */
  matrixPtr->Divider = ((screenPtr[0].x - screenPtr[2].x) * (screenPtr[1].y - screenPtr[2].y)) - 
                       ((screenPtr[1].x - screenPtr[2].x) * (screenPtr[0].y - screenPtr[2].y)) ;
  if( matrixPtr->Divider == 0 )
  {
    retTHRESHOLD = DISABLE;
  }
  else
  {
    /* A��((XD0��XD2) (Y1��Y2)��(XD1��XD2) (Y0��Y2))��K	*/
    matrixPtr->An = ((displayPtr[0].x - displayPtr[2].x) * (screenPtr[1].y - screenPtr[2].y)) - 
                    ((displayPtr[1].x - displayPtr[2].x) * (screenPtr[0].y - screenPtr[2].y)) ;
	/* B��((X0��X2) (XD1��XD2)��(XD0��XD2) (X1��X2))��K	*/
    matrixPtr->Bn = ((screenPtr[0].x - screenPtr[2].x) * (displayPtr[1].x - displayPtr[2].x)) - 
                    ((displayPtr[0].x - displayPtr[2].x) * (screenPtr[1].x - screenPtr[2].x)) ;
    /* C��(Y0(X2XD1��X1XD2)+Y1(X0XD2��X2XD0)+Y2(X1XD0��X0XD1))��K */
    matrixPtr->Cn = (screenPtr[2].x * displayPtr[1].x - screenPtr[1].x * displayPtr[2].x) * screenPtr[0].y +
                    (screenPtr[0].x * displayPtr[2].x - screenPtr[2].x * displayPtr[0].x) * screenPtr[1].y +
                    (screenPtr[1].x * displayPtr[0].x - screenPtr[0].x * displayPtr[1].x) * screenPtr[2].y ;
    /* D��((YD0��YD2) (Y1��Y2)��(YD1��YD2) (Y0��Y2))��K	*/
    matrixPtr->Dn = ((displayPtr[0].y - displayPtr[2].y) * (screenPtr[1].y - screenPtr[2].y)) - 
                    ((displayPtr[1].y - displayPtr[2].y) * (screenPtr[0].y - screenPtr[2].y)) ;
    /* E��((X0��X2) (YD1��YD2)��(YD0��YD2) (X1��X2))��K	*/
    matrixPtr->En = ((screenPtr[0].x - screenPtr[2].x) * (displayPtr[1].y - displayPtr[2].y)) - 
                    ((displayPtr[0].y - displayPtr[2].y) * (screenPtr[1].x - screenPtr[2].x)) ;
    /* F��(Y0(X2YD1��X1YD2)+Y1(X0YD2��X2YD0)+Y2(X1YD0��X0YD1))��K */
    matrixPtr->Fn = (screenPtr[2].x * displayPtr[1].y - screenPtr[1].x * displayPtr[2].y) * screenPtr[0].y +
                    (screenPtr[0].x * displayPtr[2].y - screenPtr[2].x * displayPtr[0].y) * screenPtr[1].y +
                    (screenPtr[1].x * displayPtr[0].y - screenPtr[0].x * displayPtr[1].y) * screenPtr[2].y ;
  }
  return( retTHRESHOLD ) ;
}

FunctionalState getDisplayPoint(Coordinate * displayPtr,
                     Coordinate * screenPtr,
                     Matrix * matrixPtr )
{
  FunctionalState retTHRESHOLD =ENABLE ;

  if( matrixPtr->Divider != 0 )
  {
    /* XD = AX+BY+C */        
    displayPtr->x = ( (matrixPtr->An * screenPtr->x) + 
                      (matrixPtr->Bn * screenPtr->y) + 
                       matrixPtr->Cn 
                    ) / matrixPtr->Divider ;
	/* YD = DX+EY+F */        
    displayPtr->y = ( (matrixPtr->Dn * screenPtr->x) + 
                      (matrixPtr->En * screenPtr->y) + 
                       matrixPtr->Fn 
                    ) / matrixPtr->Divider ;
  }
  else
  {
    retTHRESHOLD = DISABLE;
  }
  return(retTHRESHOLD);
} 

void Tpad_Calibrate(void)
{
  unsigned char i;
  Coordinate * Ptr;

  for(i=0;i<3;i++)
  {
   LCD_Clear(Black);
   LCD_Text(44,10,"Touch crosshair to calibrate",Red);
   delay(250);
   LCD_DrawCross(DisplaySample[i].x,DisplaySample[i].y, Red, RGB565CONVERT(184,158,131));
   do
   {
     Ptr = Read_Tpad();
   }
   while( Ptr == (void*)0 );
   ScreenSample[i].x= Ptr->x; ScreenSample[i].y= Ptr->y;
  }
  setCalibrationMatrix( &DisplaySample[0],&ScreenSample[0],&matrix );
  LCD_Clear(Black);
} 

static void set_CS(void)
{
  HAL_GPIO_WritePin(Tpad_PORT, Tpad_CS_PIN,GPIO_PIN_SET);
}

static void reset_CS(void)
{
  HAL_GPIO_WritePin(Tpad_PORT, Tpad_CS_PIN,GPIO_PIN_RESET);

}

static uint16_t read_IRQ(void)
{
  return ((uint16_t)Tpad_PORT->IDR);
}

uint16_t Tpad_Press(void)
{
  return read_IRQ();
}

static void WR_CMD (uint16_t cmd)  
{ 
  /* Wait for SPI3 Tx buffer empty */ 
  while (SPI_I2S_GetFlagStatus(SPI3, SPI_FLAG_TXE) == RESET); 
  /* Send SPI3 data */ 
  SPI_I2S_SendData(SPI3,cmd); 
  /* Wait for SPI3 data reception */ 
  while (SPI_I2S_GetFlagStatus(SPI3, SPI_FLAG_RXNE) == RESET); 
  /* Read SPI3 received data */ 
  SPI_I2S_ReceiveData(SPI3); 
} 

static uint16_t RD_AD(void)  
{ 
  SPI_HandleTypeDef hspi3;
  uint16_t buf, temp; 
  /* Wait for SPI3 Tx buffer empty */ 
  while (HAL_SPI_GetState(&hspi3) ==  HAL_SPI_STATE_RESET); 
  /* Send SPI3 data */ 
  SPI_I2S_SendData(SPI3,0x0000); 
  /* Wait for SPI3 data reception */ 
  while (HAL_SPI_GetState(&hspi3) ==  HAL_SPI_STATE_RESET); 
  /* Read SPI3 received data */ 
  temp=SPI_I2S_ReceiveData(SPI3); 
  buf=temp<<8; 
  Delay(1); 
  while (HAL_SPI_GetState(&hspi3) ==  HAL_SPI_STATE_RESET); 
  /* Send SPI3 data */ 
  SPI_I2S_SendData(SPI3,0x0000); 
  /* Wait for SPI3 data reception */ 
  while (HAL_SPI_GetState(&hspi3) ==  HAL_SPI_STATE_RESET); 
  /* Read SPI3 received data */ 
  temp=SPI_I2S_ReceiveData(SPI3); 
  buf |= temp; 
  buf>>=3; 
  buf&=0xfff; 
  return buf;  
}