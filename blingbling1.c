//裸机程序，不是在Linux上运行，是在ARM上直接运行的，不能直接使用C库。
//使用芯片s5p6818

#define GPIOEALTFN0 *(volatile unsigned int *)(0xC0010000 + 0xE020)
#define GPIOCALTFN1 *(volatile unsigned int *)(0xC0010000 + 0xC024)
#define GPIOAALTFN1 *(volatile unsigned int *)(0xC0010000 + 0xA024)
#define GPIOBALTFN1 *(volatile unsigned int *)(0xC0010000 + 0xB024)
#define GPIOCALTFN0 *(volatile unsigned int *)(0xC0010000 + 0xC020)
#define GPIOEOUTENB *(volatile unsigned int *)(0xC0010000 + 0xE004)
#define GPIOCOUTENB *(volatile unsigned int *)(0xC0010000 + 0xC004)
#define GPIOAOUTENB *(volatile unsigned int *)(0xC0010000 + 0xA004)
#define GPIOBOUTENB *(volatile unsigned int *)(0xC0010000 + 0xB004)
#define GPIOEOUT *(volatile unsigned int *)(0xC0010000 + 0xE000)
#define GPIOCOUT *(volatile unsigned int *)(0xC0010000 + 0xC000)

void delay(int val);
void delay(int val)
{
	while(val--);	
}

int _start()
{
    //1.将GPIOE13,C17,C8,C7,C12设置成IO功能。
    //26,27位置00
    GPIOEALTFN0 &= ~(3<<26); 
    
    //GPIOC17的3，2位置01
    GPIOCALTFN1 |= 1<<2; 
    GPIOCALTFN1 &= ~(1<<3);

    //GPIOC8的17,16位置01
    GPIOCALTFN0 |= 1<<16;
    GPIOCALTFN0 &= ~(1<<17);

    //GPIOC7的15,14位置01
    GPIOCALTFN0 |= 1<<14; 
    GPIOCALTFN0 &= ~(1<<15); 

    //GPIOC12的25，24位置01
    GPIOCALTFN0 |= 1<<24; 
    GPIOCALTFN0 &= ~(1<<25);

    //2.将GPIOE13，C17,C8,C7,C12设置成输出。置1
    GPIOEOUTENB |= (1<<13);
    GPIOCOUTENB |= (1<<17);
    GPIOCOUTENB |= (1<<8);
    GPIOCOUTENB |= (1<<7);
    GPIOCOUTENB |= (1<<12);
    
    //蜂鸣器 GPIOC14的29，28位设置为01 I/O功能
    GPIOCALTFN0 |=(1<<28);
    GPIOCALTFN0 &=~(1<<29);

    //GPIOC14设置成OUTPUT
    GPIOCOUTENB |=(1<<14);
    
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


    //3.控制GPIOXOUT,令灯亮/灭
    while(1)
    {
        
        //D7灯亮
        GPIOEOUT &=~(1<<13);
        delay(0x2000000);//稍微延迟一下
        //D8灯亮
        GPIOCOUT &=~(1<<17);
        delay(0x2000000);//稍微延迟一下
        //D9灯亮，同时D7灯灭
        GPIOCOUT &=~(1<<8);
        GPIOEOUT |=(1<<13);
        delay(0x2000000);//稍微延迟一下
        //D10灯亮，同时D8灯灭
        GPIOCOUT &=~(1<<7);
        GPIOCOUT |=(1<<17);
        delay(0x2000000);//稍微延迟一下
        //D11灯亮，同时D9灯灭
        GPIOCOUT &=~(1<<12);
        GPIOCOUT |=(1<<8);
        delay(0x2000000);//稍微延迟一下

        //D10灯灭
        GPIOCOUT |=(1<<7);
        delay(0x2000000);//稍微延迟一下
        //D11灯灭
        GPIOCOUT |=(1<<12);
        delay(0x2000000);//稍微延迟一下

       
        //蜂鸣器输出高电平 响
        GPIOCOUT |=(1<<14);
        delay(0x2000000);//稍微延迟一下


    }


}

