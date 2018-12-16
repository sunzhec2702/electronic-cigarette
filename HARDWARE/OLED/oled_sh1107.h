#ifndef __OLED_SH1107_H
#define __OLED_SH1107_H
#include "sys.h"

#ifdef SCREEN_SH1107
#define OLED_MODE 0
#define SIZE 8
#define XLevelL		0x00
#define XLevelH		0x10
#define Max_Column	64
#define Max_Row		128
#define FLIP_X_POS_OFFSET 32
#define	Brightness	0xFF
#define X_WIDTH 	96
#define Y_WIDTH 	16
//-----------------OLED IIC端口定义----------------
#define SCL_GPIO GPIOB
#define SCL_PIN GPIO_PIN_6
#define SDL_GPIO GPIOB
#define SDL_PIN GPIO_PIN_7

#define OLED_RESET_RCC  RCC_AHBPERIPH_GPIOF
#define RST_GPIO GPIOF
#define RST_PIN GPIO_PIN_0

#define OLED_RCC RCC_AHBPERIPH_GPIOB
#define OLED_GPIO GPIOB
#define BOARD_I2C I2C1
#define I2C_SCL_GPIO_PIN GPIO_PIN_6
#define I2C_SDA_GPIO_PIN GPIO_PIN_7
#define I2C_SCL_GPIO_PINSOURCE GPIO_PINSOURCE6
#define I2C_SDA_GPIO_PINSOURCE GPIO_PINSOURCE7
#define I2C_RCC RCC_APB1PERIPH_I2C1


#define OLED_SCLK_Clr() GPIO_ResetBits(SCL_GPIO,SCL_PIN)//CLK
#define OLED_SCLK_Set() GPIO_SetBits(SCL_GPIO,SCL_PIN)

#define OLED_SDIN_Clr() GPIO_ResetBits(SDL_GPIO,SDL_PIN)//DIN
#define OLED_SDIN_Set() GPIO_SetBits(SDL_GPIO,SDL_PIN)

#define OLED_RST_Clr() GPIO_ResetBits(RST_GPIO,RST_PIN)//RES
#define OLED_RST_Set() GPIO_SetBits(RST_GPIO,RST_PIN)

#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据


//OLED控制用函数
void OLED_WR_Byte(unsigned dat,unsigned cmd);
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_Init(void);
void OLED_Clear(void);
void OLED_DrawPoint(u8 x,u8 y,u8 t);
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot);
void OLED_ShowString_Mode(u8 x, u8 y, char* str, u8 size, u8 mode);
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size);
void OLED_ShowChar_Mode(u8 x,u8 y,u8 chr,u8 Char_Size, u8 mode);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size, u8 mode);
void OLED_Set_Pos(unsigned char x, unsigned char y);
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1, const unsigned char BMP[]);
void OLED_ShowChar_Bold(u16 x,u8 y,u8 chr,u8 Char_Size);
void OLED_ShowChar_SMALL(u16 x,u8 y,u8 chr,u8 Char_Size);
void OLED_SHOW_SPACE(u16 x, u8 y, u8 size, u8 repeat);
void Delay_50ms(unsigned int Del_50ms);
void Delay_1ms(unsigned int Del_1ms);
void fill_picture(unsigned char fill_Data);
void IIC_Start(void);
void IIC_Stop(void);
void Write_IIC_Command(unsigned char IIC_Command);
void Write_IIC_Data(unsigned char IIC_Data);
void Write_IIC_Byte(unsigned char IIC_Byte);
void IIC_Wait_Ack(void);
void I2C_GPIO_init(void);
void Write_IIC_Addr7(unsigned char IIC_Addr_7bit);
void reset_timout_tic(void);
void I2C_StateDetect_Timeout(I2C_TypeDef* I2Cx, u32 state);
void I2C_GetBitState_Timeout(I2C_TypeDef* I2Cx, uint32_t I2C_FLAG);
#endif
#endif
