#ifndef __BATTERY_BMP_H
#define __BATTERY_BMP_H

unsigned char BATTERY_CHARGING_ICON[][70] =
{
    {
        0x00,0x00,0xF8,0xF8,0xFF,0xFF,0xFF,0x03,0x03,0xFB,0xFB,0xFB,0xFB,0xFB,0xFB,0xFB,0xFB,0xFB,0xFB,0xFB,0xFB,0xFB,0xFB,0xFB,0xFB,0xFB,0xFB,0xFB,0xFB,0x03,0x03,0xFF,0xFF,0x00,0x00,0x00,
        0x00,0x1F,0x1F,0xFF,0xFF,0xFF,0xC0,0xC0,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xC0,0xC0,0xFF,0xFF,0x00,0x00,/*"C:\Users\Darren\Documents\STM32Project\charging icon\battery100_charging.bmp",0*/
    },
    {
        0x00,0x00,0xF8,0xF8,0xFF,0xFF,0xFF,0x03,0x03,0x03,0x03,0xFB,0xFB,0xFB,0xFB,0xFB,0xFB,0xFB,0xFB,0xFB,0xFB,0xFB,0xFB,0xFB,0xFB,0xFB,0xFB,0xFB,0xFB,0x03,0x03,0xFF,0xFF,0x00,0x00,0x00,
        0x00,0x1F,0x1F,0xFF,0xFF,0xFF,0xC0,0xC0,0xC0,0xC0,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xC0,0xC0,0xFF,0xFF,0x00,0x00,/*"C:\Users\Darren\Documents\STM32Project\charging icon\battery90_charging.BMP",0*/
    },
    {
        0x00,0x00,0xF8,0xF8,0xFF,0xFF,0xFF,0x03,0x03,0x03,0x03,0x03,0x03,0xFB,0xFB,0xFB,0xFB,0xFB,0xFB,0xFB,0xFB,0xFB,0xFB,0xFB,0xFB,0xFB,0xFB,0xFB,0xFB,0x03,0x03,0xFF,0xFF,0x00,0x00,0x00,
        0x00,0x1F,0x1F,0xFF,0xFF,0xFF,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xC0,0xC0,0xFF,0xFF,0x00,0x00,/*"C:\Users\Darren\Documents\STM32Project\charging icon\battery80_charging.BMP",0*/
    },
    {
        0x00,0x00,0xF8,0xF8,0xFF,0xFF,0xFF,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0xFB,0xFB,0xFB,0xFB,0xFB,0xFB,0xFB,0xFB,0xFB,0xFB,0xFB,0xFB,0xFB,0xFB,0x03,0x03,0xFF,0xFF,0x00,0x00,0x00,
        0x00,0x1F,0x1F,0xFF,0xFF,0xFF,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xC0,0xC0,0xFF,0xFF,0x00,0x00,/*"C:\Users\Darren\Documents\STM32Project\charging icon\battery70_charging.BMP",0*/
    },
    {
        0x00,0x00,0xF8,0xF8,0xFF,0xFF,0xFF,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0xFB,0xFB,0xFB,0xFB,0xFB,0xFB,0xFB,0xFB,0xFB,0xFB,0xFB,0xFB,0x03,0x03,0xFF,0xFF,0x00,0x00,0x00,
        0x00,0x1F,0x1F,0xFF,0xFF,0xFF,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xC0,0xC0,0xFF,0xFF,0x00,0x00,/*"C:\Users\Darren\Documents\STM32Project\charging icon\battery60_charging.BMP",0*/
    },
    {
        0x00,0x00,0xF8,0xF8,0xFF,0xFF,0xFF,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0xFB,0xFB,0xFB,0xFB,0xFB,0xFB,0xFB,0xFB,0xFB,0xFB,0x03,0x03,0xFF,0xFF,0x00,0x00,0x00,
        0x00,0x1F,0x1F,0xFF,0xFF,0xFF,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xC0,0xC0,0xFF,0xFF,0x00,0x00,/*"C:\Users\Darren\Documents\STM32Project\charging icon\battery50_charging.BMP",0*/
    },
    {
        0x00,0x00,0xF8,0xF8,0xFF,0xFF,0xFF,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0xFB,0xFB,0xFB,0xFB,0xFB,0xFB,0xFB,0xFB,0x03,0x03,0xFF,0xFF,0x00,0x00,0x00,
        0x00,0x1F,0x1F,0xFF,0xFF,0xFF,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xC0,0xC0,0xFF,0xFF,0x00,0x00,/*"C:\Users\Darren\Documents\STM32Project\charging icon\battery40_charging.BMP",0*/
    },
    {
        0x00,0x00,0xF8,0xF8,0xFF,0xFF,0xFF,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0xFB,0xFB,0xFB,0xFB,0xFB,0xFB,0x03,0x03,0xFF,0xFF,0x00,0x00,0x00,
        0x00,0x1F,0x1F,0xFF,0xFF,0xFF,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xC0,0xC0,0xFF,0xFF,0x00,0x00,/*"C:\Users\Darren\Documents\STM32Project\charging icon\battery30_charging.BMP",0*/
    },
    {
        0x00,0x00,0xF8,0xF8,0xFF,0xFF,0xFF,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0xFB,0xFB,0xFB,0xFB,0x03,0x03,0xFF,0xFF,0x00,0x00,0x00,
        0x00,0x1F,0x1F,0xFF,0xFF,0xFF,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xDF,0xDF,0xDF,0xDF,0xC0,0xC0,0xFF,0xFF,0x00,0x00,/*"C:\Users\Darren\Documents\STM32Project\charging icon\battery20_charging.BMP",0*/
    },
    {
        0x00,0x00,0xF8,0xF8,0xFF,0xFF,0xFF,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0xFB,0xFB,0x03,0x03,0xFF,0xFF,0x00,0x00,0x00,
        0x00,0x1F,0x1F,0xFF,0xFF,0xFF,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xDF,0xDF,0xC0,0xC0,0xFF,0xFF,0x00,0x00,/*"C:\Users\Darren\Documents\STM32Project\charging icon\battery10_charging.BMP",0*/
    },
    {

        0x00,0x00,0xF8,0xF8,0xFF,0xFF,0xFF,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0xFF,0xFF,0x00,0x00,0x00,
        0x00,0x1F,0x1F,0xFF,0xFF,0xFF,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xFF,0xFF,0x00,0x00,/*"C:\Users\Darren\Documents\STM32Project\charging icon\battery0_charging.BMP",0*/
    },
};

unsigned char PowerOnLogoF96x16[] =
{
    0x00,0x00,0x08,0xF8,0x08,0x08,0xF0,0x00,0x00,0x80,0x80,0x00,0x00,0x80,0x00,0x80,0x00,0x80,0x00,0x00,0x80,0x80,0x00,0x00,0x80,0x80,0x00,0x80,0x80,0x00,0x00,0x80,0x80,0x00,0x00,0x00,
    0x80,0x88,0xF8,0x00,0x00,0x00,0x00,0x08,0xF8,0x88,0x88,0x70,0x00,0x80,0x80,0x00,0x00,0x80,0x80,0x00,0x00,0x00,0x08,0xF8,0x88,0x88,0x70,0x00,0x00,0x80,0x80,0x00,0x00,0x80,0x80,0x80,
    0x80,0x00,0x80,0x80,0x80,0x80,0x18,0x08,0xF8,0x08,0x18,0x00,0x80,0x80,0x00,0x00,0x08,0xF8,0x00,0x80,0x80,0x80,0x00,0x00,0x00,0x00,0x20,0x3F,0x21,0x01,0x00,0x00,0x1F,0x20,0x20,0x1F,
    0x00,0x03,0x3C,0x03,0x3E,0x03,0x00,0x1F,0x22,0x22,0x23,0x00,0x20,0x3F,0x21,0x00,0x01,0x00,0x1F,0x22,0x22,0x23,0x00,0x1F,0x20,0x20,0x3F,0x20,0x00,0x00,0x00,0x20,0x3F,0x20,0x20,0x1F,
    0x00,0x80,0x87,0x78,0x0C,0x03,0x00,0x00,0x00,0x00,0x20,0x3F,0x20,0x20,0x1F,0x00,0x1F,0x20,0x20,0x1F,0x00,0x30,0x2C,0x23,0x30,0x00,0x30,0x2C,0x23,0x30,0x00,0x20,0x3F,0x20,0x00,0x1F,
    0x22,0x22,0x23,0x00,0x20,0x3F,0x24,0x06,0x39,0x20,0x00,0x00,/*"C:\Users\Darren\Documents\STM32Project\bootLOGO.BMP",0*/
};

unsigned char PowerOffLogoF72x16[] =
{
    0x08,0xF8,0x08,0x08,0x08,0x08,0xF0,0x00,0x00,0x00,0x80,0x80,0x80,0x80,0x00,0x00,0x80,0x80,0x00,0x80,0x80,0x00,0x80,0x80,0x00,0x00,0x80,0x80,0x80,0x80,0x00,0x00,0x80,0x80,0x80,0x00,
    0x80,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xE0,0x10,0x08,0x08,0x08,0x10,0xE0,0x00,0x08,0xF8,0x88,0x88,0xE8,0x08,0x10,0x00,0x08,0xF8,0x88,0x88,0xE8,0x08,0x10,0x00,
    0x20,0x3F,0x21,0x01,0x01,0x01,0x00,0x00,0x00,0x1F,0x20,0x20,0x20,0x20,0x1F,0x00,0x01,0x0E,0x30,0x0C,0x07,0x38,0x06,0x01,0x00,0x1F,0x24,0x24,0x24,0x24,0x17,0x00,0x20,0x20,0x3F,0x21,
    0x20,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0x10,0x20,0x20,0x20,0x10,0x0F,0x00,0x20,0x3F,0x20,0x00,0x03,0x00,0x00,0x00,0x20,0x3F,0x20,0x00,0x03,0x00,0x00,0x00,/*"E:\GDProject\D??��???t?D\Power_OFF.BMP",0*/
};

#endif
