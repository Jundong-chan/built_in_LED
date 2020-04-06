#define GPIOCALTFN0 *(volatile unsigned int *)(0xC0010000 + 0xC020)
#define GPIOCOUTENB *(volatile unsigned int *)(0xC0010000 + 0xC004)
#define GPIOCOUT *(volatile unsigned int *)(0xC0010000 + 0xC000)

int _start()
{
    //蜂鸣器 GPIOC14的29，28位设置为01 I/O功能
    GPIOCALTFN0 |=(1<<28);
    GPIOCALTFN0 &=~(1<<29);

    //GPIOC14设置成OUTPUT
    GPIOCOUTENB |=(1<<14);

    while(1)
    {
        //蜂鸣器输出高电平 响，反之则不响
        GPIOCOUT |=(1<<14);
    }

}