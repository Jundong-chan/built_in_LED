
#define GPIOAALTFN1 *(volatile unsigned int *)(0xC0010000 + 0xA024)
#define GPIOBALTFN1 *(volatile unsigned int *)(0xC0010000 + 0xB024)
#define GPIOAOUTENB *(volatile unsigned int *)(0xC0010000 + 0xA004)
#define GPIOBOUTENB *(volatile unsigned int *)(0xC0010000 + 0xB004)
#define GPIOAPAD *(volatile unsigned int *)(0xC0010000 + 0xA018)
#define GPIOBPAD *(volatile unsigned int *)(0xC0010000 + 0xB018)
#define GPIOCALTFN0 *(volatile unsigned int *)(0xC0010000 + 0xC020)
#define GPIOCOUTENB *(volatile unsigned int *)(0xC0010000 + 0xC004)
#define GPIOCOUT *(volatile unsigned int *)(0xC0010000 + 0xC000)
#define GPIOEALTFN0 *(volatile unsigned int *)(0xC0010000 + 0xE020)
#define GPIOEOUTENB *(volatile unsigned int *)(0xC0010000 + 0xE004)
#define GPIOEOUT *(volatile unsigned int *)(0xC0010000 + 0xE000)
void delay(int val);
void delay(int val)
{
	while(val--);	
}

int _start()
{
    //设置按键k2,k3,k4,k6,为I/O功能
    //设置k2，GPIOA28的25，24为设置00
    GPIOAALTFN1 &=~(3<<24);
    //设置k3，GPIOB30的29，28为设置01
    GPIOBALTFN1 |=(1<<28);
    GPIOBALTFN1 &=~(1<<29);
    //设置k4，GPIOB31的31，30为设置01
    GPIOBALTFN1 |=(1<<30);
    GPIOBALTFN1 &=~(1<<31);
    //设置k6，GPIOB9的19，18为设置00
    GPIOAALTFN1 &=~(3<<18);
    
    //设置按键k2,k3,k4,k6,为INPUT功能
    GPIOAOUTENB &=~(1<<28);
    GPIOBOUTENB &=~(1<<30);
    GPIOBOUTENB &=~(1<<31);
    GPIOBOUTENB &=~(1<<9);

    //蜂鸣器 GPIOC14的29，28位设置为01 I/O功能
    GPIOCALTFN0 |=(1<<28);
    GPIOCALTFN0 &=~(1<<29);

    //GPIOC14设置成OUTPUT
    GPIOCOUTENB |=(1<<14);

    //设置D7灯为输出
    GPIOEALTFN0 &= ~(3<<26); 
    GPIOEOUTENB |= (1<<13);

    while(1)
    {
        //按下k2，蜂鸣器响
        if((GPIOAPAD & (1<<28))==0) //如果成立，则有输入
        {
            delay(0x200); //稍微延迟一下
            if((GPIOAPAD & (1<<28))==0) //再确认一次
            {
                while((GPIOAPAD & (1<<28))==0);  //等待按键松开
                //蜂鸣器响
                GPIOCOUT |=(1<<14);
            }

        }
        
        //按下k3，蜂鸣器不响
        if((GPIOBPAD & (1<<30))==0) //如果成立，则有输入
        {
            delay(0x200); //稍微延迟一下
            if((GPIOBPAD & (1<<30))==0) //再确认一次
            {
                while((GPIOBPAD & (1<<30))==0);  //等待按键松开
                //蜂鸣器不响
                GPIOCOUT &=~(1<<14);
            }

        }

        //按下k4，蜂鸣器响一下
        if((GPIOBPAD & (1<<31))==0) //如果成立，则有输入
        {
            delay(0x200); //稍微延迟一下
            if((GPIOBPAD & (1<<31))==0) //再确认一次
            {
                while((GPIOBPAD & (1<<31))==0);  //等待按键松开
                
                GPIOCOUT |=(1<<14);
                delay(0x20000000);
                GPIOCOUT &=~(1<<14);

            }

        }


         //按下k6，D7的灯亮一下
        if((GPIOBPAD & (1<<9))==0) //如果成立，则有输入
        {
            delay(0x200); //稍微延迟一下
            if((GPIOBPAD & (1<<9))==0) //再确认一次
            {
                while((GPIOBPAD & (1<<9))==0);  //等待按键松开
                //D7灯亮一下
                GPIOEOUT &=~(1<<13);
                delay(0x20000000);
                GPIOEOUT |=1<<13;
            }
        }

    }
}


