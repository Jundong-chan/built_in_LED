#define GPIOEALTFN0 *(volatile unsigned int *)(0xC0010000 + 0xE020)
#define GPIOCALTFN1 *(volatile unsigned int *)(0xC0010000 + 0xC024)
#define GPIOAALTFN1 *(volatile unsigned int *)(0xC0010000 + 0xA024)
#define GPIOCALTFN0 *(volatile unsigned int *)(0xC0010000 + 0xC020)

#define GPIOEOUTENB *(volatile unsigned int *)(0xC0010000 + 0xE004)
#define GPIOCOUTENB *(volatile unsigned int *)(0xC0010000 + 0xC004)
#define GPIOAOUTENB *(volatile unsigned int *)(0xC0010000 + 0xA004)
#define GPIOEOUT *(volatile unsigned int *)(0xC0010000 + 0xE000)
#define GPIOCOUT *(volatile unsigned int *)(0xC0010000 + 0xC000)
#define GPIOAPAD *(volatile unsigned int *)(0xC0010000 + 0xA018)

void delay(int val);
int _start()
{
    //1.GPIOE13,C17,C8,C7,C12  设置成IO
    //GPIOE13 的26,27  置00
    GPIOEALTFN0 &= ~(3 << 26);

    //GPIOC17的 3，2  置01
    GPIOCALTFN1 |= 1 << 2;
    GPIOCALTFN1 &= ~(1 << 3);

    //GPIOC8的 17,16 置01
    GPIOCALTFN0 |= 1 << 16;
    GPIOCALTFN0 &= ~(1 << 17);

    //GPIOC7的 15,14  置01
    GPIOCALTFN0 |= 1 << 14;
    GPIOCALTFN0 &= ~(1 << 15);

    //GPIOC12的 25，24  置01
    GPIOCALTFN0 |= 1 << 24;
    GPIOCALTFN0 &= ~(1 << 25);

    //2. GPIOE13,C17,C8,C7,C12  设置成output
    GPIOEOUTENB |= (1 << 13);
    GPIOCOUTENB |= (1 << 17);
    GPIOCOUTENB |= (1 << 8);
    GPIOCOUTENB |= (1 << 7);

    //设置buzzer GPIOC14  29，28  01  I/O功能
    GPIOCALTFN0 |= (1 << 28);
    GPIOCALTFN0 &= ~(1 << 29);

    //GPIOC14 OUTPUT功能
    GPIOCOUTENB |= (1 << 14);

    //设置k2, I/O功能
    //k2，GPIOA28 25，24为 00
    GPIOAALTFN1 &= ~(3 << 24);

    //k2, INPUT
    GPIOAOUTENB &= ~(1 << 28);

    //3.GPIOXOUT
    while (1)
    {
        //push k2，start

        if ((GPIOAPAD & (1 << 28)) == 0) 
        {
           while (1)
           {
            //D7 on
            GPIOEOUT &= ~(1 << 13);
            //buzzer on
            GPIOCOUT ^= (1 << 14);
            delay(0x2000000); 
            //buzzer off
            GPIOCOUT ^= (1 << 14);

            //D8 on,D7 off
            GPIOCOUT &= ~(1 << 17);
            GPIOEOUT |= (1 << 13);
            delay(0x2000000);
            //buzzer on
            GPIOCOUT ^= (1 << 14);

            //D9 on，D8 off
            GPIOCOUT &= ~(1 << 8);
            GPIOCOUT |= (1 << 17);
            delay(0x2000000);
            //buzzer off
            GPIOCOUT ^= (1 << 14);

            //D10 on
            GPIOCOUT &= ~(1 << 7);
            //D9 off
            GPIOCOUT |= (1 << 8);
            delay(0x2000000);
            //D10 off
            GPIOCOUT |= (1 << 7);
            //buzzer on
            GPIOCOUT ^= (1 << 14);
            delay(0x2000000); 
           }
           
        }
    }
}
void delay(int val)
{
    while (val--);
}
