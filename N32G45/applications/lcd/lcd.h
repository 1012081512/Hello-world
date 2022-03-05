#ifndef __LCD_H
#define __LCD_H

#include <n32g45x.h>


#define USE_HORIZONTAL 0  //设置横屏或者竖屏显示
                          //0:正向
                          //1:旋转180度
                                                    //2:旋转90度
                                                    //3:旋转270度
#if USE_HORIZONTAL<2
#define LCD_W 128
#define LCD_H 64
#else
#define LCD_W 64
#define LCD_H 128
#endif


//-----------------LCD端口定义----------------
#define LCD_PORT       GPIOA
#define LCD_PORT_CLK   RCC_APB2_PERIPH_GPIOA
#define LCD_SCLK_PIN   GPIO_PIN_5
#define LCD_SDA_PIN    GPIO_PIN_7
#define LCD_RES_PIN    GPIO_PIN_0
#define LCD_DC_PIN     GPIO_PIN_1
#define LCD_BLK_PIN    GPIO_PIN_2

//#define LCD_SCLK_Clr() GPIO_ResetBits(LCD_PORT,LCD_SCLK_PIN)//SCL=SCLK
//#define LCD_SCLK_Set() GPIO_SetBits(LCD_PORT,LCD_SCLK_PIN)
//
//#define LCD_MOSI_Clr() GPIO_ResetBits(LCD_PORT,LCD_SDA_PIN)//SDA=MOSI
//#define LCD_MOSI_Set() GPIO_SetBits(LCD_PORT,LCD_SDA_PIN)

#define LCD_RES_Clr()  GPIO_ResetBits(LCD_PORT,LCD_RES_PIN)//RES
#define LCD_RES_Set()  GPIO_SetBits(LCD_PORT,LCD_RES_PIN)

#define LCD_DC_Clr()   GPIO_ResetBits(LCD_PORT,LCD_DC_PIN)//DC
#define LCD_DC_Set()   GPIO_SetBits(LCD_PORT,LCD_DC_PIN)

#define LCD_BLK_Clr()  GPIO_ResetBits(LCD_PORT,LCD_BLK_PIN)//BLK
#define LCD_BLK_Set()  GPIO_SetBits(LCD_PORT,LCD_BLK_PIN)

//#define LCD_MOSI_Read() GPIO_ResetBits(LCD_PORT,LCD_SDA_PIN)//SDA=MOSI



//画笔颜色
#define WHITE            0xFFFF
#define BLACK            0x0000
#define BLUE             0x001F
#define BRED             0XF81F
#define GRED                   0XFFE0
#define GBLUE                  0X07FF
#define RED              0xF800
#define MAGENTA          0xF81F
#define GREEN            0x07E0
#define CYAN             0x7FFF
#define YELLOW           0xFFE0
#define BROWN                0XBC40 //棕色
#define BRRED                0XFC07 //棕红色
#define GRAY                 0X8430 //灰色
#define DARKBLUE         0X01CF //深蓝色
#define LIGHTBLUE        0X7D7C //浅蓝色
#define GRAYBLUE         0X5458 //灰蓝色
#define LIGHTGREEN       0X841F //浅绿色
#define LGRAY                0XC618 //浅灰色(PANNEL),窗体背景色
#define LGRAYBLUE        0XA651 //浅灰蓝色(中间层颜色)
#define LBBLUE           0X2B12 //浅棕蓝色(选择条目的反色)

uint8_t LCD_WR_DATA( uint16_t dat );
void LCD_WR_REG(uint8_t dat);
void LCD_Address_Set(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2);
void LCD_Init(void);


void LCD_Fill(uint16_t xsta,uint16_t ysta,uint16_t xend,uint16_t yend,uint16_t color);//指定区域填充颜色
void LCD_DrawPoint(uint16_t x,uint16_t y,uint16_t color);//在指定位置画一个点
void LCD_DrawLine(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint16_t color);//在指定位置画一条线
void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,uint16_t color);//在指定位置画一个矩形
void Draw_Circle(uint16_t x0,uint16_t y0,uint8_t r,uint16_t color);//在指定位置画一个圆

void LCD_ShowChinese(uint16_t x,uint16_t y,uint8_t *s,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode);//显示汉字串
void LCD_ShowChinese12x12(uint16_t x,uint16_t y,uint8_t *s,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode);//显示单个12x12汉字
void LCD_ShowChinese16x16(uint16_t x,uint16_t y,uint8_t *s,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode);//显示单个16x16汉字
void LCD_ShowChinese24x24(uint16_t x,uint16_t y,uint8_t *s,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode);//显示单个24x24汉字
void LCD_ShowChinese32x32(uint16_t x,uint16_t y,uint8_t *s,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode);//显示单个32x32汉字

void LCD_ShowChar(uint16_t x,uint16_t y,uint8_t num,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode);//显示一个字符
void LCD_ShowString(uint16_t x,uint16_t y,const uint8_t *p,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode);//显示字符串
u32 mypow(uint8_t m,uint8_t n);//求幂
void LCD_ShowIntNum(uint16_t x,uint16_t y,uint16_t num,uint8_t len,uint16_t fc,uint16_t bc,uint8_t sizey);//显示整数变量
void LCD_ShowFloatNum1(uint16_t x,uint16_t y,float num,uint8_t len,uint16_t fc,uint16_t bc,uint8_t sizey);//显示两位小数变量

void LCD_ShowPicture(uint16_t x,uint16_t y,uint16_t length,uint16_t width,const uint8_t pic[]);//显示图片

void LCD_thread_create( void );




#endif /*__LCD_H*/
