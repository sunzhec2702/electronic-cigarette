#include "oled_ssd1306.h"
#include "delay.h"
#include "system_state.h"
#include "pwr_manager.h"

#ifdef SCREEN_SSD1306
#include "oledfont_ssd1306.h"
#include "oled_content_muxlock.h"
#define I2C_OWN_ADDRESS7    0x82  // don't care
#define I2C_CLK_HZ	400000
#define TIMEOUT_TIC         2 * SystemCoreClock / I2C_CLK_HZ


static u32 timeout_tic;
static u8 pos_x_offset = 0;

#define USE_I2C_LIB

//[0]0 1 2 3 ... 127
//[1]0 1 2 3 ... 127
//[2]0 1 2 3 ... 127
//[3]0 1 2 3 ... 127
//[4]0 1 2 3 ... 127
//[5]0 1 2 3 ... 127
//[6]0 1 2 3 ... 127
//[7]0 1 2 3 ... 127
/**********************************************
//IIC Start
**********************************************/
/**********************************************
//IIC Start
**********************************************/
#ifndef USE_I2C_LIB
void IIC_Start()
{

    OLED_SCLK_Set();
    OLED_SDIN_Set();
    OLED_SDIN_Clr();
    OLED_SCLK_Clr();
}

/**********************************************
//IIC Stop
**********************************************/


void IIC_Stop()
{
    OLED_SCLK_Set() ;
//	OLED_SCLK_Clr();
    OLED_SDIN_Clr();
    OLED_SDIN_Set();

}

void IIC_Wait_Ack()
{

    //GPIOB->CRH &= 0XFFF0FFFF;	//??PB12???????
    //GPIOB->CRH |= 0x00080000;
//	OLED_SDA = 1;
//	delay_us(1);
    //OLED_SCL = 1;
    //delay_us(50000);
    /*	while(1)
    	{
    		if(!OLED_SDA)				//???????OLED ????
    		{
    			//GPIOB->CRH &= 0XFFF0FFFF;	//??PB12?????????
    			//GPIOB->CRH |= 0x00030000;
    			return;
    		}
    	}
    */
    OLED_SCLK_Set() ;
    OLED_SCLK_Clr();
}
/**********************************************
// IIC Write byte
**********************************************/

void Write_IIC_Byte(unsigned char IIC_Byte)
{
    unsigned char i;
    unsigned char m,da;
    da=IIC_Byte;
    OLED_SCLK_Clr();
    for(i=0; i<8; i++)
    {
        m=da;
        //	OLED_SCLK_Clr();
        m=m&0x80;
        if(m==0x80)
        {
            OLED_SDIN_Set();
        }
        else OLED_SDIN_Clr();
        da=da<<1;
        OLED_SCLK_Set();
        OLED_SCLK_Clr();
    }


}


#else
void IIC_Start(void)
{
    /* Send a start condition to I2C bus */
    I2C_StartOnBus_Enable(BOARD_I2C,ENABLE);
    /* The software must wait until SBSEND bit is set */
#ifdef DBG_OLED_BLOCK
    while(!I2C_StateDetect(BOARD_I2C,I2C_PROGRAMMINGMODE_MASTER_SBSEND));
#else
    I2C_StateDetect_Timeout(BOARD_I2C,I2C_PROGRAMMINGMODE_MASTER_SBSEND);
#endif
}

void IIC_Stop(void)
{
    /* Send a stop condition to I2C bus */
    I2C_StopOnBus_Enable(BOARD_I2C,ENABLE);
#ifdef DBG_OLED_BLOCK
    while(BOARD_I2C->CTLR1&0x0200);
#else
    reset_timout_tic();
    while(BOARD_I2C->CTLR1&0x0200 && timeout_tic > 0) {
        timeout_tic--;
    }
    if (timeout_tic == 0) {
        reboot_system(SUCCESS);
    }
#endif

}

void IIC_Wait_Ack(void)
{
    return;
}

void Write_IIC_Byte(unsigned char IIC_Byte)
{
    I2C_SendData(BOARD_I2C,IIC_Byte);
#ifdef DBG_OLED_BLOCK
    while(!I2C_StateDetect(BOARD_I2C, I2C_PROGRAMMINGMODE_MASTER_BYTE_TRANSMITTED));
#else
    I2C_StateDetect_Timeout(BOARD_I2C,I2C_PROGRAMMINGMODE_MASTER_BYTE_TRANSMITTED);
#endif
}
#endif

void Write_IIC_Addr7(unsigned char IIC_Addr_7bit)
{
    /* Send slave address to I2C bus */
    I2C_AddressingDevice_7bit(BOARD_I2C,IIC_Addr_7bit,I2C_DIRECTION_TRANSMITTER);
    /* The software must wait until ADDSEND bit is set*/
#ifdef DBG_OLED_BLOCK
    while(!I2C_StateDetect(BOARD_I2C,I2C_PROGRAMMINGMODE_MASTER_TRANSMITTER_ADDSEND));
#else
    I2C_StateDetect_Timeout(BOARD_I2C,I2C_PROGRAMMINGMODE_MASTER_TRANSMITTER_ADDSEND);
#endif

}



/**********************************************
// IIC Write Command
**********************************************/
void Write_IIC_Command(unsigned char IIC_Command)
{

#ifndef USE_I2C_LIB
    IIC_Start();
    Write_IIC_Byte(0x78);            //Slave address,SA0=0
    IIC_Wait_Ack();
    Write_IIC_Byte(0x00);			//write command
    IIC_Wait_Ack();
    Write_IIC_Byte(IIC_Command);
    IIC_Wait_Ack();
    IIC_Stop();

#else
    IIC_Start();
    Write_IIC_Addr7(0x78);
    Write_IIC_Byte(0x00);			//write command
    Write_IIC_Byte(IIC_Command);
    IIC_Stop();

#endif

}
/**********************************************
// IIC Write Data
**********************************************/
void Write_IIC_Data(unsigned char IIC_Data)
{
#ifndef USE_I2C_LIB
    IIC_Start();
    Write_IIC_Byte(0x78);			//D/C#=0; R/W#=0
    IIC_Wait_Ack();
    Write_IIC_Byte(0x40);			//write data
    IIC_Wait_Ack();
    Write_IIC_Byte(IIC_Data);
    IIC_Wait_Ack();
    IIC_Stop();
#else
    IIC_Start();
    Write_IIC_Addr7(0x78);
    Write_IIC_Byte(0x40);			//write command
    Write_IIC_Byte(IIC_Data);
    IIC_Stop();

#endif
}


void OLED_WR_Byte(unsigned dat,unsigned cmd)
{
    if(cmd)
    {
        Write_IIC_Data(dat);
    }
    else {
        Write_IIC_Command(dat);

    }
}

//坐标设置

void OLED_Set_Pos(unsigned char x, unsigned char y)
{   OLED_WR_Byte(0xb0+y,OLED_CMD);
    OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);
    OLED_WR_Byte((x&0x0f),OLED_CMD);
}
//开启OLED显示
void OLED_Display_On(void)
{
    OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC命令
    OLED_WR_Byte(0X14,OLED_CMD);  //DCDC ON
    OLED_WR_Byte(0XAF,OLED_CMD);  //DISPLAY ON
}
//关闭OLED显示
void OLED_Display_Off(void)
{
    OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC命令
    OLED_WR_Byte(0X10,OLED_CMD);  //DCDC OFF
    OLED_WR_Byte(0XAE,OLED_CMD);  //DISPLAY OFF
}

//清屏函数,清完屏,整个屏幕是黑色的!和没点亮一样!!!
void OLED_Clear(void)
{
    u8 i,n;
    for(i=0; i<8; i++)
    {
        OLED_WR_Byte (0xb0+i,OLED_CMD);    //设置页地址（0~7）
        OLED_WR_Byte (0x00,OLED_CMD);      //设置显示位置—列低地址
        OLED_WR_Byte (0x10,OLED_CMD);      //设置显示位置—列高地址
        OLED_Set_Pos(pos_x_offset, i);
        for(n=0+pos_x_offset; n<Max_Column+pos_x_offset; n++)
            OLED_WR_Byte(0,OLED_DATA);
    } //更新显示

}

void OLED_On(void)
{
    u8 i,n;
    for(i=0; i<8; i++)
    {
        OLED_WR_Byte (0xb0+i,OLED_CMD);    //设置页地址（0~7）
        OLED_WR_Byte (0x00,OLED_CMD);      //设置显示位置—列低地址
        OLED_WR_Byte (0x10,OLED_CMD);      //设置显示位置—列高地址
        for(n=0; n<Max_Column; n++)OLED_WR_Byte(1,OLED_DATA);
    } //更新显示
}

void OLED_ShowString_Mode(u8 x, u8 y, char* str, u8 size, u8 mode)
{
    u8 wide_size = 0;
    if (size == 8) {
        wide_size = 6;
    } else if (size == 16) {
        wide_size = 8;
    }
    while(*str != '\0') {
        OLED_ShowChar_Mode(x,y,*str,size,mode);
        x+=wide_size;
        str++;
    }
}

//在指定位置显示一个字符,包括部分字符
//x:0~127
//y:0~63
//mode:0,反白显示;1,正常显示
//size:选择字体 16/12
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size)
{
    OLED_ShowChar_Mode(x, y, chr, Char_Size, 1);
}

void OLED_ShowChar_Mode(u8 x,u8 y,u8 chr,u8 Char_Size, u8 mode)
{
    unsigned char c=0,i=0;
    x += pos_x_offset;
    c=chr-' ';//得到偏移后的值
    if(Char_Size ==16)
    {
        OLED_Set_Pos(x,y);
        for(i=0; i<8; i++)
            if (mode == 1)
                OLED_WR_Byte(F8X16[c*16+i], OLED_DATA);
            else if (mode == 0)
                OLED_WR_Byte(~F8X16[c*16+i], OLED_DATA);
        OLED_Set_Pos(x,y+1);
        for(i=0; i<8; i++)
            if (mode == 1)
                OLED_WR_Byte(F8X16[c*16+i+8], OLED_DATA);
            else if (mode == 0)
                OLED_WR_Byte(~F8X16[c*16+i+8], OLED_DATA);
    }
    else {
        OLED_Set_Pos(x,y);
        for(i=0; i<6; i++)
            if (mode == 1)
                OLED_WR_Byte(F6x8[c][i],OLED_DATA);
            else if (mode == 0)
                OLED_WR_Byte(~F6x8[c][i],OLED_DATA);
    }
}

//m^n函数
u32 oled_pow(u8 m,u8 n)
{
    u32 result=1;
    while(n--)result*=m;
    return result;
}
//显示2个数字
//x,y :起点坐标
//len :数字的位数
//size:字体大小
//mode:模式	0,填充模式;1,叠加模式
//num:数值(0~4294967295);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size2, u8 mode)
{
    u8 t,temp, size1;
    u8 enshow=0;
    if (size2 == 8) {
        size1 = 6;
    } else if (size2 == 16) {
        size1 = 8;
    }
    for(t=0; t<len; t++)
    {
        temp=(num/oled_pow(10,len-t-1))%10;
        if(enshow==0&&t<(len-1))
        {
            if(temp==0)
            {
                OLED_ShowChar_Mode(x+(size1)*t,y,' ',size2, mode);
                continue;
            } else enshow=1;

        }
        OLED_ShowChar_Mode(x+(size1)*t,y,temp+'0',size2, mode);
    }
}

void OLED_ShowChar_Bold(u16 x,u8 y,u8 chr,u8 Char_Size)
{

    unsigned char c=0,i=0;
    x += pos_x_offset;
    c = chr-'0';//得到偏移后的值
    if(Char_Size == 16) {
        OLED_Set_Pos(x,y);
        for(i=0; i<8; i++)
            OLED_WR_Byte(BoldF8x16[c][i],OLED_DATA);
        OLED_Set_Pos(x,y+1);
        for(i=0; i<8; i++)
            OLED_WR_Byte(BoldF8x16[c][i+8],OLED_DATA);
    } else {
        OLED_Set_Pos(x,y);
        for(i=0; i<6; i++)
            OLED_WR_Byte(F6x8[c][i],OLED_DATA);

    }
}

/*
void OLED_ShowString_SMALL(u8 x, u8 y, char* str, u8 size)
{
    u8 wide_size = 0;
    if (size == 16) {
        wide_size = 7;
    } else if (size == 8) {
        wide_size = 6;
    }
    while(*str != '\0') {
        OLED_ShowChar_SMALL(x,y,*str,size);
        x+=wide_size;
        str++;
    }
}
*/

void OLED_ShowChar_SMALL(u16 x,u8 y,u8 chr,u8 Char_Size)
{
    unsigned char c=0,i=0;
    x += pos_x_offset;
    c = chr-'0';//得到偏移后的值
    if(Char_Size == 16) {
        OLED_Set_Pos(x,y);
        for(i=0; i<7; i++)
            OLED_WR_Byte(SMALLF7x16[c][i],OLED_DATA);
        OLED_Set_Pos(x,y+1);
        for(i=0; i<7; i++)
            OLED_WR_Byte(SMALLF7x16[c][i+7],OLED_DATA);
    } else {
        OLED_Set_Pos(x,y);
        for(i=0; i<6; i++)
            OLED_WR_Byte(F6x8[c][i],OLED_DATA);
    }
}

void OLED_SHOW_SPACE(u16 x, u8 y, u8 size, u8 repeat)
{
    u8 i;
    for (i = 0; i < repeat; i++) {
        switch (size) {
        case 8:
            OLED_DrawBMP(x + i, y, x + i + 1, y + size / 8, SPACEF1x8);
            break;
        case 16:
            OLED_DrawBMP(x + i, y, x + i + 1, y + size / 8, SPACEF1x16);
            break;
        }
    }
}

/***********功能描述：显示显示BMP图片Max_Column×64起始点坐标(x,y),x的范围0～127，y为页的范围0～7*****************/
/* What we input are (0,0,Max_Column,8,BMP1) */
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1, const unsigned char BMP[])
{
    unsigned int j=0;
    unsigned char x,y;
    x0 += pos_x_offset;
    x1 += pos_x_offset;
    for(y=y0; y<y1; y++)
    {
        OLED_Set_Pos(x0,y);
        for(x=x0; x<x1; x++)
        {
            OLED_WR_Byte(BMP[j++],OLED_DATA);
        }
    }
}

//初始化SSD1306
void OLED_Init(void)
{
    GPIO_InitPara  GPIO_InitStructure;
    RCC_AHBPeriphClock_Enable(OLED_RESET_RCC, ENABLE);
    GPIO_InitStructure.GPIO_Pin = RST_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_MODE_OUT;
    GPIO_InitStructure.GPIO_Speed = GPIO_SPEED_50MHZ;
    GPIO_InitStructure.GPIO_OType = GPIO_OTYPE_PP;
    GPIO_Init(RST_GPIO, &GPIO_InitStructure);

    GPIO_ResetBits(RST_GPIO, RST_PIN); // Pull CS low, Pull DC low; reset LCD
    delay_ms(10); //delay 100ms
    GPIO_SetBits(RST_GPIO, RST_PIN); // Toggle Reset High after 200ms
    delay_ms(10); //delay 100ms

// Reset OLED first then reset I2C bus
// If the OLED pannel has error(hold I2C SCLK, SDA low), we need reset the OLED first. Then reset the OLED pannel.
#ifndef USE_I2C_LIB
    RCC_AHBPeriphClock_Enable(OLED_RCC, ENABLE);
    GPIO_InitStructure.GPIO_Pin = SCL_PIN|SDL_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_MODE_OUT; 		 //????
    GPIO_InitStructure.GPIO_Speed = GPIO_SPEED_50MHZ;
    GPIO_InitStructure.GPIO_OType = GPIO_OTYPE_OD ;
    GPIO_Init(OLED_GPIO, &GPIO_InitStructure);	  //???GPIOD3,6
    GPIO_SetBits(OLED_GPIO, SCL_PIN|SDL_PIN);
#else
    I2C_GPIO_init();
#endif

    OLED_WR_Byte(0xAE,OLED_CMD);//--display off
    OLED_WR_Byte(0x00,OLED_CMD);//---set low column address
    OLED_WR_Byte(0x10,OLED_CMD);//---set high column address
    OLED_WR_Byte(0x40,OLED_CMD);//--set start line address
    OLED_WR_Byte(0xB0,OLED_CMD);//--set page address

    OLED_WR_Byte(0x81,OLED_CMD); // contract control
    OLED_WR_Byte(0xFF,OLED_CMD);//--96

    if (get_screen_flip_flag() == SYS_SCREEN_NORMAL) {
        OLED_WR_Byte(0xA1,OLED_CMD);//set segment remap
        pos_x_offset = 0;
    } else {
        OLED_WR_Byte(0xA0,OLED_CMD);//set segment remap
        pos_x_offset = FLIP_X_POS_OFFSET;
    }

    OLED_WR_Byte(0xA6,OLED_CMD);//--normal / reverse
    OLED_WR_Byte(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64)
    OLED_WR_Byte(0x0F,OLED_CMD);//-- 1/16 duty

    if (get_screen_flip_flag() == SYS_SCREEN_NORMAL)
        OLED_WR_Byte(0xC8,OLED_CMD);//Com scan direction
    else
        OLED_WR_Byte(0xC0,OLED_CMD);//Com scan direction

    OLED_WR_Byte(0xD3,OLED_CMD);//-set display offset
    OLED_WR_Byte(0x00,OLED_CMD);//
    OLED_WR_Byte(0xD5,OLED_CMD);//set osc division
    OLED_WR_Byte(0x80,OLED_CMD);//

    OLED_WR_Byte(0xD8,OLED_CMD);//set area color mode off
    OLED_WR_Byte(0x05,OLED_CMD);//

    OLED_WR_Byte(0xD9,OLED_CMD);//Set Pre-Charge Period
    OLED_WR_Byte(0xFF,OLED_CMD);//


    OLED_WR_Byte(0xDA,OLED_CMD);//set com pin configuartion
    OLED_WR_Byte(0x02,OLED_CMD);//


    OLED_WR_Byte(0xDB,OLED_CMD);//set Vcomh
    OLED_WR_Byte(0x40,OLED_CMD);//


    OLED_WR_Byte(0x8D,OLED_CMD);//set charge pump enable
    OLED_WR_Byte(0x14,OLED_CMD);//

    //OLED_WR_Byte(0xAF,OLED_CMD);//--turn on oled panel

}

void I2C_GPIO_init(void)
{
    GPIO_InitPara GPIO_InitStructure;
    I2C_InitPara I2C_InitStructure;

    /* Enable GPIOB clock */
    RCC_AHBPeriphClock_Enable(RCC_AHBPERIPH_GPIOB,ENABLE);
    /* Enable BOARD_I2C APB1 clock */
    RCC_APB1PeriphClock_Enable(I2C_RCC,ENABLE);


    /* BOARD_I2C GPIO ports*/
    GPIO_InitStructure.GPIO_Pin =  I2C_SCL_GPIO_PIN | I2C_SDA_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_MODE_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_SPEED_50MHZ;
    GPIO_InitStructure.GPIO_OType = GPIO_OTYPE_OD;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PUPD_NOPULL;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_PinAFConfig(GPIOB,I2C_SCL_GPIO_PINSOURCE,GPIO_AF_1);
    GPIO_PinAFConfig(GPIOB,I2C_SDA_GPIO_PINSOURCE,GPIO_AF_1);

    // In order to not encounter the I2C BUSY jam, Manually Reset the I2C after GPIO set, before I2C configure.
    I2C_SoftwareReset_Enable(BOARD_I2C, ENABLE);
    I2C_SoftwareReset_Enable(BOARD_I2C, DISABLE);

    I2C_InitStructure.I2C_Protocol = I2C_PROTOCOL_I2C;
    I2C_InitStructure.I2C_DutyCycle = I2C_DUTYCYCLE_2;
    I2C_InitStructure.I2C_BitRate = I2C_CLK_HZ;
    I2C_InitStructure.I2C_AddressingMode = I2C_ADDRESSING_MODE_7BIT;
    I2C_InitStructure.I2C_DeviceAddress = I2C_OWN_ADDRESS7;
    I2C_Init(BOARD_I2C, &I2C_InitStructure);

    I2C_Enable(BOARD_I2C,ENABLE);


    /* Enable I2C2 */

    I2C_Acknowledge_Enable(BOARD_I2C,DISABLE);
    /* The software must wait until I2C Bus is idle */
#ifdef DBG_OLED_BLOCK
    while(I2C_GetBitState(BOARD_I2C,I2C_FLAG_I2CBSY));
#else
    I2C_GetBitState_Timeout(BOARD_I2C,I2C_FLAG_I2CBSY);
#endif

}

void reset_timout_tic()
{
    timeout_tic = TIMEOUT_TIC;
}

void I2C_StateDetect_Timeout(I2C_TypeDef* I2Cx, u32 state)
{
    reset_timout_tic();
    while(!I2C_StateDetect(I2Cx, state) && timeout_tic > 0)
    {
        timeout_tic --;
    }
    if (timeout_tic == 0) {
        reboot_system(SUCCESS);
    }
}

void I2C_GetBitState_Timeout(I2C_TypeDef* I2Cx, uint32_t I2C_FLAG)
{
    reset_timout_tic();
    while(I2C_GetBitState(I2Cx, I2C_FLAG) && timeout_tic > 0)
    {
        timeout_tic --;
    }
    if (timeout_tic == 0) {
        reboot_system(SUCCESS);
    }
}


#endif

