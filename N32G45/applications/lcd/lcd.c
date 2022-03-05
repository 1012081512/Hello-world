#include "lcd.h"
#include "spi.h"
#include "lcdfont.h"
#include <stdint.h>
#include <rtthread.h>
#include <rtdevice.h>

uint8_t LCD_WR_DATA8( uint8_t dat )
{
    n32_spi_send_byte(dat);
}

uint8_t LCD_WR_DATA( uint16_t dat )
{
    n32_spi_send_byte(dat>>8);
    n32_spi_send_byte(dat);
}


/******************************************************************************
      ����˵����LCDд������
      ������ݣ�dat д�������
      ����ֵ��  ��
******************************************************************************/
void LCD_WR_REG(uint8_t dat)
{
    LCD_DC_Clr();//д����
    n32_spi_send_byte(dat);
    LCD_DC_Set();//д����
}


/******************************************************************************
      ����˵����������ʼ�ͽ�����ַ
      ������ݣ�x1,x2 �����е���ʼ�ͽ�����ַ
                y1,y2 �����е���ʼ�ͽ�����ַ
      ����ֵ��  ��
******************************************************************************/
void LCD_Address_Set(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2)
{
    if(USE_HORIZONTAL==0)
    {
        LCD_WR_REG(0x2a);//�е�ַ����
        LCD_WR_DATA(x1+2);
        LCD_WR_DATA(x2+2);
        LCD_WR_REG(0x2b);//�е�ַ����
        LCD_WR_DATA(y1+67);
        LCD_WR_DATA(y2+67);
        LCD_WR_REG(0x2c);//������д
    }
    else if(USE_HORIZONTAL==1)
    {
        LCD_WR_REG(0x2a);//�е�ַ����
        LCD_WR_DATA(x1+2);
        LCD_WR_DATA(x2+2);
        LCD_WR_REG(0x2b);//�е�ַ����
        LCD_WR_DATA(y1+1);
        LCD_WR_DATA(y2+1);
        LCD_WR_REG(0x2c);//������д
    }
    else if(USE_HORIZONTAL==2)
    {
        LCD_WR_REG(0x2a);//�е�ַ����
        LCD_WR_DATA(x1+1);
        LCD_WR_DATA(x2+1);
        LCD_WR_REG(0x2b);//�е�ַ����
        LCD_WR_DATA(y1+2);
        LCD_WR_DATA(y2+2);
        LCD_WR_REG(0x2c);//������д
    }
    else
    {
        LCD_WR_REG(0x2a);//�е�ַ����
        LCD_WR_DATA(x1+67);
        LCD_WR_DATA(x2+67);
        LCD_WR_REG(0x2b);//�е�ַ����
        LCD_WR_DATA(y1+2);
        LCD_WR_DATA(y2+2);
        LCD_WR_REG(0x2c);//������д
    }
}

void LCD_Init(void)
{
    uint8_t temp = 0;


    n32_spi_init();//��ʼ��GPIO

    LCD_RES_Clr();//��λ
    rt_thread_mdelay(100);
    LCD_RES_Set();
    rt_thread_mdelay(100);

    LCD_BLK_Set();//�򿪱���
    rt_thread_mdelay(100);

    LCD_WR_REG(0x11);//Sleep exit
    rt_thread_mdelay(100);

    //ST7735R Frame Rate
    LCD_WR_REG(0xB1);
    LCD_WR_DATA8(0x01);
    LCD_WR_DATA8(0x2C);
    LCD_WR_DATA8(0x2D);

    LCD_WR_REG(0xB2);
    LCD_WR_DATA8(0x01);
    LCD_WR_DATA8(0x2C);
    LCD_WR_DATA8(0x2D);

    LCD_WR_REG(0xB3);
    LCD_WR_DATA8(0x01);
    LCD_WR_DATA8(0x2C);
    LCD_WR_DATA8(0x2D);
    LCD_WR_DATA8(0x01);
    LCD_WR_DATA8(0x2C);
    LCD_WR_DATA8(0x2D);

    LCD_WR_REG(0xB4); //Column inversion
    LCD_WR_DATA8(0x07);

    //ST7735R Power Sequence
    LCD_WR_REG(0xC0);
    LCD_WR_DATA8(0xA2);
    LCD_WR_DATA8(0x02);
    LCD_WR_DATA8(0x84);
    LCD_WR_REG(0xC1);
    LCD_WR_DATA8(0xC5);

    LCD_WR_REG(0xC2);
    LCD_WR_DATA8(0x0A);
    LCD_WR_DATA8(0x00);

    LCD_WR_REG(0xC3);
    LCD_WR_DATA8(0x8A);
    LCD_WR_DATA8(0x2A);
    LCD_WR_REG(0xC4);
    LCD_WR_DATA8(0x8A);
    LCD_WR_DATA8(0xEE);

    LCD_WR_REG(0xC5); //VCOM
    LCD_WR_DATA8(0x0E);

    LCD_WR_REG(0x36);
    if(USE_HORIZONTAL==0)LCD_WR_DATA8(0xC8);
    else if(USE_HORIZONTAL==1)LCD_WR_DATA8(0x08);
    else if(USE_HORIZONTAL==2)LCD_WR_DATA8(0x78);
    else LCD_WR_DATA8(0xA8);

    //ST7735R Gamma Sequence
    LCD_WR_REG(0xe0);
    LCD_WR_DATA8(0x0f);
    LCD_WR_DATA8(0x1a);
    LCD_WR_DATA8(0x0f);
    LCD_WR_DATA8(0x18);
    LCD_WR_DATA8(0x2f);
    LCD_WR_DATA8(0x28);
    LCD_WR_DATA8(0x20);
    LCD_WR_DATA8(0x22);
    LCD_WR_DATA8(0x1f);
    LCD_WR_DATA8(0x1b);
    LCD_WR_DATA8(0x23);
    LCD_WR_DATA8(0x37);
    LCD_WR_DATA8(0x00);
    LCD_WR_DATA8(0x07);
    LCD_WR_DATA8(0x02);
    LCD_WR_DATA8(0x10);

    LCD_WR_REG(0xe1);
    LCD_WR_DATA8(0x0f);
    LCD_WR_DATA8(0x1b);
    LCD_WR_DATA8(0x0f);
    LCD_WR_DATA8(0x17);
    LCD_WR_DATA8(0x33);
    LCD_WR_DATA8(0x2c);
    LCD_WR_DATA8(0x29);
    LCD_WR_DATA8(0x2e);
    LCD_WR_DATA8(0x30);
    LCD_WR_DATA8(0x30);
    LCD_WR_DATA8(0x39);
    LCD_WR_DATA8(0x3f);
    LCD_WR_DATA8(0x00);
    LCD_WR_DATA8(0x07);
    LCD_WR_DATA8(0x03);
    LCD_WR_DATA8(0x10);

    LCD_WR_REG(0x2a);
    LCD_WR_DATA8(0x00);
    LCD_WR_DATA8(0x00);
    LCD_WR_DATA8(0x00);
    LCD_WR_DATA8(0x7f);

    LCD_WR_REG(0x2b);
    LCD_WR_DATA8(0x00);
    LCD_WR_DATA8(0x00);
    LCD_WR_DATA8(0x00);
    LCD_WR_DATA8(0x9f);

    LCD_WR_REG(0xF0); //Enable test command
    LCD_WR_DATA8(0x01);
    LCD_WR_REG(0xF6); //Disable ram power save mode
    LCD_WR_DATA8(0x00);

    LCD_WR_REG(0x3A); //65k mode
    LCD_WR_DATA8(0x05);

    LCD_WR_REG(0x29);//Display on
    LCD_Fill(0,0,128,64,WHITE);
}


static rt_thread_t lcd_thread;

static void LCD_thread_entry( void* parameter )
{
    uint16_t temp = 0,blackground_color = 0;

    while(1)
    {
        if(temp < 17)
        {
            switch(temp)
            {
                case 0:blackground_color = WHITE;break;
                case 1:blackground_color = BLACK;break;
                case 2:blackground_color = BLUE;break;
                case 3:blackground_color = BRED;break;
                case 4:blackground_color = GRED;break;
                case 5:blackground_color = GBLUE;break;
                case 6:blackground_color = RED;break;
                case 7:blackground_color = MAGENTA;break;
                case 8:blackground_color = GREEN;break;
                case 9:blackground_color = CYAN;break;
                case 10:blackground_color = YELLOW;break;
                case 11:blackground_color = BROWN;break;
                case 12:blackground_color = BRRED;break;
                case 13:blackground_color = GRAY;break;
                case 14:blackground_color = DARKBLUE;break;
                case 15:blackground_color = LIGHTBLUE;break;
                case 16:blackground_color = GRAYBLUE;break;
                case 17:blackground_color = LIGHTGREEN;break;
            }
            temp++;
        }
        else
        {
            temp = 0;
        }

        LCD_Fill(0,0,128,64,blackground_color);
        rt_thread_mdelay(500);
    }
}

void LCD_thread_create( void )
{
    lcd_thread = rt_thread_create("lcd",
                                   LCD_thread_entry,
                                   NULL,
                                   512,
                                   15,
                                   20);

    if(lcd_thread != RT_NULL)
    {
        rt_thread_startup(lcd_thread);
        rt_kprintf("LCD thread startup.");
    }
}






/******************************************************************************
      ����˵������ָ�����������ɫ
      ������ݣ�xsta,ysta   ��ʼ����
                xend,yend   ��ֹ����
                                color       Ҫ������ɫ
      ����ֵ��  ��
******************************************************************************/
void LCD_Fill(uint16_t xsta,uint16_t ysta,uint16_t xend,uint16_t yend,uint16_t color)
{
    uint16_t i,j;
    LCD_Address_Set(xsta,ysta,xend-1,yend-1);//������ʾ��Χ
    for(i=ysta;i<yend;i++)
    {
        for(j=xsta;j<xend;j++)
        {
            LCD_WR_DATA(color);
        }
    }
}

/******************************************************************************
      ����˵������ָ��λ�û���
      ������ݣ�x,y ��������
                color �����ɫ
      ����ֵ��  ��
******************************************************************************/
void LCD_DrawPoint(uint16_t x,uint16_t y,uint16_t color)
{
    LCD_Address_Set(x,y,x,y);//���ù��λ��
    LCD_WR_DATA(color);
}


/******************************************************************************
      ����˵��������
      ������ݣ�x1,y1   ��ʼ����
                x2,y2   ��ֹ����
                color   �ߵ���ɫ
      ����ֵ��  ��
******************************************************************************/
void LCD_DrawLine(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint16_t color)
{
    uint16_t t;
    int xerr=0,yerr=0,delta_x,delta_y,distance;
    int incx,incy,uRow,uCol;
    delta_x=x2-x1; //������������
    delta_y=y2-y1;
    uRow=x1;//�����������
    uCol=y1;
    if(delta_x>0)incx=1; //���õ�������
    else if (delta_x==0)incx=0;//��ֱ��
    else {incx=-1;delta_x=-delta_x;}
    if(delta_y>0)incy=1;
    else if (delta_y==0)incy=0;//ˮƽ��
    else {incy=-1;delta_y=-delta_y;}
    if(delta_x>delta_y)distance=delta_x; //ѡȡ��������������
    else distance=delta_y;
    for(t=0;t<distance+1;t++)
    {
        LCD_DrawPoint(uRow,uCol,color);//����
        xerr+=delta_x;
        yerr+=delta_y;
        if(xerr>distance)
        {
            xerr-=distance;
            uRow+=incx;
        }
        if(yerr>distance)
        {
            yerr-=distance;
            uCol+=incy;
        }
    }
}


/******************************************************************************
      ����˵����������
      ������ݣ�x1,y1   ��ʼ����
                x2,y2   ��ֹ����
                color   ���ε���ɫ
      ����ֵ��  ��
******************************************************************************/
void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,uint16_t color)
{
    LCD_DrawLine(x1,y1,x2,y1,color);
    LCD_DrawLine(x1,y1,x1,y2,color);
    LCD_DrawLine(x1,y2,x2,y2,color);
    LCD_DrawLine(x2,y1,x2,y2,color);
}


/******************************************************************************
      ����˵������Բ
      ������ݣ�x0,y0   Բ������
                r       �뾶
                color   Բ����ɫ
      ����ֵ��  ��
******************************************************************************/
void Draw_Circle(uint16_t x0,uint16_t y0,uint8_t r,uint16_t color)
{
    int a,b;
    a=0;b=r;
    while(a<=b)
    {
        LCD_DrawPoint(x0-b,y0-a,color);             //3
        LCD_DrawPoint(x0+b,y0-a,color);             //0
        LCD_DrawPoint(x0-a,y0+b,color);             //1
        LCD_DrawPoint(x0-a,y0-b,color);             //2
        LCD_DrawPoint(x0+b,y0+a,color);             //4
        LCD_DrawPoint(x0+a,y0-b,color);             //5
        LCD_DrawPoint(x0+a,y0+b,color);             //6
        LCD_DrawPoint(x0-b,y0+a,color);             //7
        a++;
        if((a*a+b*b)>(r*r))//�ж�Ҫ���ĵ��Ƿ��Զ
        {
            b--;
        }
    }
}

/******************************************************************************
      ����˵������ʾ���ִ�
      ������ݣ�x,y��ʾ����
                *s Ҫ��ʾ�ĺ��ִ�
                fc �ֵ���ɫ
                bc �ֵı���ɫ
                sizey �ֺ� ��ѡ 16 24 32
                mode:  0�ǵ���ģʽ  1����ģʽ
      ����ֵ��  ��
******************************************************************************/
void LCD_ShowChinese(uint16_t x,uint16_t y,uint8_t *s,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode)
{
    while(*s!=0)
    {
        if(sizey==12) LCD_ShowChinese12x12(x,y,s,fc,bc,sizey,mode);
        else if(sizey==16) LCD_ShowChinese16x16(x,y,s,fc,bc,sizey,mode);
        else if(sizey==24) LCD_ShowChinese24x24(x,y,s,fc,bc,sizey,mode);
        else if(sizey==32) LCD_ShowChinese32x32(x,y,s,fc,bc,sizey,mode);
        else return;
        s+=2;
        x+=sizey;
    }
}

/******************************************************************************
      ����˵������ʾ����12x12����
      ������ݣ�x,y��ʾ����
                *s Ҫ��ʾ�ĺ���
                fc �ֵ���ɫ
                bc �ֵı���ɫ
                sizey �ֺ�
                mode:  0�ǵ���ģʽ  1����ģʽ
      ����ֵ��  ��
******************************************************************************/
void LCD_ShowChinese12x12(uint16_t x,uint16_t y,uint8_t *s,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode)
{
    uint8_t i,j,m=0;
    uint16_t k;
    uint16_t HZnum;//������Ŀ
    uint16_t TypefaceNum;//һ���ַ���ռ�ֽڴ�С
    uint16_t x0=x;
    TypefaceNum=(sizey/8+((sizey%8)?1:0))*sizey;

    HZnum=sizeof(tfont12)/sizeof(typFNT_GB12);  //ͳ�ƺ�����Ŀ
    for(k=0;k<HZnum;k++)
    {
        if((tfont12[k].Index[0]==*(s))&&(tfont12[k].Index[1]==*(s+1)))
        {
            LCD_Address_Set(x,y,x+sizey-1,y+sizey-1);
            for(i=0;i<TypefaceNum;i++)
            {
                for(j=0;j<8;j++)
                {
                    if(!mode)//�ǵ��ӷ�ʽ
                    {
                        if(tfont12[k].Msk[i]&(0x01<<j))LCD_WR_DATA(fc);
                        else LCD_WR_DATA(bc);
                        m++;
                        if(m%sizey==0)
                        {
                            m=0;
                            break;
                        }
                    }
                    else//���ӷ�ʽ
                    {
                        if(tfont12[k].Msk[i]&(0x01<<j)) LCD_DrawPoint(x,y,fc);//��һ����
                        x++;
                        if((x-x0)==sizey)
                        {
                            x=x0;
                            y++;
                            break;
                        }
                    }
                }
            }
        }
        continue;  //���ҵ���Ӧ�����ֿ������˳�����ֹ��������ظ�ȡģ����Ӱ��
    }
}

/******************************************************************************
      ����˵������ʾ����16x16����
      ������ݣ�x,y��ʾ����
                *s Ҫ��ʾ�ĺ���
                fc �ֵ���ɫ
                bc �ֵı���ɫ
                sizey �ֺ�
                mode:  0�ǵ���ģʽ  1����ģʽ
      ����ֵ��  ��
******************************************************************************/
void LCD_ShowChinese16x16(uint16_t x,uint16_t y,uint8_t *s,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode)
{
    uint8_t i,j,m=0;
    uint16_t k;
    uint16_t HZnum;//������Ŀ
    uint16_t TypefaceNum;//һ���ַ���ռ�ֽڴ�С
    uint16_t x0=x;
  TypefaceNum=(sizey/8+((sizey%8)?1:0))*sizey;
    HZnum=sizeof(tfont16)/sizeof(typFNT_GB16);  //ͳ�ƺ�����Ŀ
    for(k=0;k<HZnum;k++)
    {
        if ((tfont16[k].Index[0]==*(s))&&(tfont16[k].Index[1]==*(s+1)))
        {
            LCD_Address_Set(x,y,x+sizey-1,y+sizey-1);
            for(i=0;i<TypefaceNum;i++)
            {
                for(j=0;j<8;j++)
                {
                    if(!mode)//�ǵ��ӷ�ʽ
                    {
                        if(tfont16[k].Msk[i]&(0x01<<j))LCD_WR_DATA(fc);
                        else LCD_WR_DATA(bc);
                        m++;
                        if(m%sizey==0)
                        {
                            m=0;
                            break;
                        }
                    }
                    else//���ӷ�ʽ
                    {
                        if(tfont16[k].Msk[i]&(0x01<<j)) LCD_DrawPoint(x,y,fc);//��һ����
                        x++;
                        if((x-x0)==sizey)
                        {
                            x=x0;
                            y++;
                            break;
                        }
                    }
                }
            }
        }
        continue;  //���ҵ���Ӧ�����ֿ������˳�����ֹ��������ظ�ȡģ����Ӱ��
    }
}


/******************************************************************************
      ����˵������ʾ����24x24����
      ������ݣ�x,y��ʾ����
                *s Ҫ��ʾ�ĺ���
                fc �ֵ���ɫ
                bc �ֵı���ɫ
                sizey �ֺ�
                mode:  0�ǵ���ģʽ  1����ģʽ
      ����ֵ��  ��
******************************************************************************/
void LCD_ShowChinese24x24(uint16_t x,uint16_t y,uint8_t *s,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode)
{
    uint8_t i,j,m=0;
    uint16_t k;
    uint16_t HZnum;//������Ŀ
    uint16_t TypefaceNum;//һ���ַ���ռ�ֽڴ�С
    uint16_t x0=x;
    TypefaceNum=(sizey/8+((sizey%8)?1:0))*sizey;
    HZnum=sizeof(tfont24)/sizeof(typFNT_GB24);  //ͳ�ƺ�����Ŀ
    for(k=0;k<HZnum;k++)
    {
        if ((tfont24[k].Index[0]==*(s))&&(tfont24[k].Index[1]==*(s+1)))
        {
            LCD_Address_Set(x,y,x+sizey-1,y+sizey-1);
            for(i=0;i<TypefaceNum;i++)
            {
                for(j=0;j<8;j++)
                {
                    if(!mode)//�ǵ��ӷ�ʽ
                    {
                        if(tfont24[k].Msk[i]&(0x01<<j))LCD_WR_DATA(fc);
                        else LCD_WR_DATA(bc);
                        m++;
                        if(m%sizey==0)
                        {
                            m=0;
                            break;
                        }
                    }
                    else//���ӷ�ʽ
                    {
                        if(tfont24[k].Msk[i]&(0x01<<j)) LCD_DrawPoint(x,y,fc);//��һ����
                        x++;
                        if((x-x0)==sizey)
                        {
                            x=x0;
                            y++;
                            break;
                        }
                    }
                }
            }
        }
        continue;  //���ҵ���Ӧ�����ֿ������˳�����ֹ��������ظ�ȡģ����Ӱ��
    }
}

/******************************************************************************
      ����˵������ʾ����32x32����
      ������ݣ�x,y��ʾ����
                *s Ҫ��ʾ�ĺ���
                fc �ֵ���ɫ
                bc �ֵı���ɫ
                sizey �ֺ�
                mode:  0�ǵ���ģʽ  1����ģʽ
      ����ֵ��  ��
******************************************************************************/
void LCD_ShowChinese32x32(uint16_t x,uint16_t y,uint8_t *s,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode)
{
    uint8_t i,j,m=0;
    uint16_t k;
    uint16_t HZnum;//������Ŀ
    uint16_t TypefaceNum;//һ���ַ���ռ�ֽڴ�С
    uint16_t x0=x;
    TypefaceNum=(sizey/8+((sizey%8)?1:0))*sizey;
    HZnum=sizeof(tfont32)/sizeof(typFNT_GB32);  //ͳ�ƺ�����Ŀ
    for(k=0;k<HZnum;k++)
    {
        if ((tfont32[k].Index[0]==*(s))&&(tfont32[k].Index[1]==*(s+1)))
        {
            LCD_Address_Set(x,y,x+sizey-1,y+sizey-1);
            for(i=0;i<TypefaceNum;i++)
            {
                for(j=0;j<8;j++)
                {
                    if(!mode)//�ǵ��ӷ�ʽ
                    {
                        if(tfont32[k].Msk[i]&(0x01<<j))LCD_WR_DATA(fc);
                        else LCD_WR_DATA(bc);
                        m++;
                        if(m%sizey==0)
                        {
                            m=0;
                            break;
                        }
                    }
                    else//���ӷ�ʽ
                    {
                        if(tfont32[k].Msk[i]&(0x01<<j)) LCD_DrawPoint(x,y,fc);//��һ����
                        x++;
                        if((x-x0)==sizey)
                        {
                            x=x0;
                            y++;
                            break;
                        }
                    }
                }
            }
        }
        continue;  //���ҵ���Ӧ�����ֿ������˳�����ֹ��������ظ�ȡģ����Ӱ��
    }
}


/******************************************************************************
      ����˵������ʾ�����ַ�
      ������ݣ�x,y��ʾ����
                num Ҫ��ʾ���ַ�
                fc �ֵ���ɫ
                bc �ֵı���ɫ
                sizey �ֺ�
                mode:  0�ǵ���ģʽ  1����ģʽ
      ����ֵ��  ��
******************************************************************************/
void LCD_ShowChar(uint16_t x,uint16_t y,uint8_t num,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode)
{
    uint8_t temp,sizex,t,m=0;
    uint16_t i,TypefaceNum;//һ���ַ���ռ�ֽڴ�С
    uint16_t x0=x;
    sizex=sizey/2;
    TypefaceNum=(sizex/8+((sizex%8)?1:0))*sizey;
    num=num-' ';    //�õ�ƫ�ƺ��ֵ
    LCD_Address_Set(x,y,x+sizex-1,y+sizey-1);  //���ù��λ��
    for(i=0;i<TypefaceNum;i++)
    {
        if(sizey==12)temp=ascii_1206[num][i];              //����6x12����
        else if(sizey==16)temp=ascii_1608[num][i];       //����8x16����
        else if(sizey==24)temp=ascii_2412[num][i];       //����12x24����
        else if(sizey==32)temp=ascii_3216[num][i];       //����16x32����
        else return;
        for(t=0;t<8;t++)
        {
            if(!mode)//�ǵ���ģʽ
            {
                if(temp&(0x01<<t))LCD_WR_DATA(fc);
                else LCD_WR_DATA(bc);
                m++;
                if(m%sizex==0)
                {
                    m=0;
                    break;
                }
            }
            else//����ģʽ
            {
                if(temp&(0x01<<t))LCD_DrawPoint(x,y,fc);//��һ����
                x++;
                if((x-x0)==sizex)
                {
                    x=x0;
                    y++;
                    break;
                }
            }
        }
    }
}


/******************************************************************************
      ����˵������ʾ�ַ���
      ������ݣ�x,y��ʾ����
                *p Ҫ��ʾ���ַ���
                fc �ֵ���ɫ
                bc �ֵı���ɫ
                sizey �ֺ�
                mode:  0�ǵ���ģʽ  1����ģʽ
      ����ֵ��  ��
******************************************************************************/
void LCD_ShowString(uint16_t x,uint16_t y,const uint8_t *p,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode)
{
    while(*p!='\0')
    {
        LCD_ShowChar(x,y,*p,fc,bc,sizey,mode);
        x+=sizey/2;
        p++;
    }
}


/******************************************************************************
      ����˵������ʾ����
      ������ݣ�m������nָ��
      ����ֵ��  ��
******************************************************************************/
u32 mypow(uint8_t m,uint8_t n)
{
    u32 result=1;
    while(n--)result*=m;
    return result;
}


/******************************************************************************
      ����˵������ʾ��������
      ������ݣ�x,y��ʾ����
                num Ҫ��ʾ��������
                len Ҫ��ʾ��λ��
                fc �ֵ���ɫ
                bc �ֵı���ɫ
                sizey �ֺ�
      ����ֵ��  ��
******************************************************************************/
void LCD_ShowIntNum(uint16_t x,uint16_t y,uint16_t num,uint8_t len,uint16_t fc,uint16_t bc,uint8_t sizey)
{
    uint8_t t,temp;
    uint8_t enshow=0;
    uint8_t sizex=sizey/2;
    for(t=0;t<len;t++)
    {
        temp=(num/mypow(10,len-t-1))%10;
        if(enshow==0&&t<(len-1))
        {
            if(temp==0)
            {
                LCD_ShowChar(x+t*sizex,y,' ',fc,bc,sizey,0);
                continue;
            }else enshow=1;

        }
        LCD_ShowChar(x+t*sizex,y,temp+48,fc,bc,sizey,0);
    }
}


/******************************************************************************
      ����˵������ʾ��λС������
      ������ݣ�x,y��ʾ����
                num Ҫ��ʾС������
                len Ҫ��ʾ��λ��
                fc �ֵ���ɫ
                bc �ֵı���ɫ
                sizey �ֺ�
      ����ֵ��  ��
******************************************************************************/
void LCD_ShowFloatNum1(uint16_t x,uint16_t y,float num,uint8_t len,uint16_t fc,uint16_t bc,uint8_t sizey)
{
    uint8_t t,temp,sizex;
    uint16_t num1;
    sizex=sizey/2;
    num1=num*100;
    for(t=0;t<len;t++)
    {
        temp=(num1/mypow(10,len-t-1))%10;
        if(t==(len-2))
        {
            LCD_ShowChar(x+(len-2)*sizex,y,'.',fc,bc,sizey,0);
            t++;
            len+=1;
        }
        LCD_ShowChar(x+t*sizex,y,temp+48,fc,bc,sizey,0);
    }
}


/******************************************************************************
      ����˵������ʾͼƬ
      ������ݣ�x,y�������
                length ͼƬ����
                width  ͼƬ���
                pic[]  ͼƬ����
      ����ֵ��  ��
******************************************************************************/
void LCD_ShowPicture(uint16_t x,uint16_t y,uint16_t length,uint16_t width,const uint8_t pic[])
{
    uint16_t i,j;
    u32 k=0;
    LCD_Address_Set(x,y,x+length-1,y+width-1);
    for(i=0;i<length;i++)
    {
        for(j=0;j<width;j++)
        {
            LCD_WR_DATA8(pic[k*2]);
            LCD_WR_DATA8(pic[k*2+1]);
            k++;
        }
    }
}


