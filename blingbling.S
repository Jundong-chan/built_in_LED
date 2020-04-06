#define GPIOEALTFN0 (0xC0010000 + 0xE020)
#define GPIOCALTFN1 (0xC0010000 + 0xC024)
#define GPIOCALTFN0 (0xC0010000 + 0xC020)
#define GPIOEOUTENB (0xC0010000 + 0xE004)
#define GPIOCOUTENB (0xC0010000 + 0xC004)
#define GPIOEOUT (0xC0010000 + 0xE000)
#define GPIOCOUT (0xC0010000 + 0xC000)
//寄存器R4～R12 用来存放局部变量
.global _start   //伪全局变量
_start:
    //将D7灯设置成I/O功能
    LDR R4,=GPIOEALTFN0    //把该寄存器的地址赋给R4
    LDR R5,[R4]            //把R4存的地址下的内容存到R5
    BIC R5,R5,#(1<<26)     //将R5的值26，27位取反并按位与
    STR R5,[R4]            //将R5的值写回地址

    //将D7灯设置成输出
    LDR R4,=GPIOEOUTENB    //把该寄存器的地址赋给R4
    LDR R5,[R4]            //把R4存的地址下的内容存到R5
    ORR R5,R5,#(1<<13)     //将R5的内容与立即数作逻辑或运算存到R5中
    STR R5,[R4]            //将R5的值写回地址

    //将D8灯设置成I/O功能
    LDR R6,=GPIOCALTFN1     
    LDR R7,[R6]
    ORR R7,R7,#(1<<2)      //将第2位置1
    BIC R7,R7,#(1<<3)      //将第3位置0
    STR R7,[R6]

    //将D8灯设置成输出
    LDR R6,=GPIOCOUTENB
    LDR R7,[R6]            
    ORR R7,R7,#(1<<17)     
    STR R7,[R6]        

    //将D9灯设置成I/O功能
    LDR R8,=GPIOCALTFN0   
    LDR R9,[R8]
    ORR R9,R9,#(1<<16)      //将第16位置1
    BIC R9,R9,#(1<<17)      //将第17位置0
    STR R9,[R8]

    //将D9灯设置成输出
    LDR R8,=GPIOCOUTENB
    LDR R9,[R8]            
    ORR R9,R9,#(1<<8)     
    STR R9,[R8] 

    //将D10灯设置成I/O功能
    LDR R4,=GPIOCALTFN0
    LDR R5,[R4]
    ORR R5,R5,#(1<<14)      //将第14位置1
    BIC R5,R5,#(1<<15)      //将第15位置0
    STR R5,[R4]
    
    //将D10灯设置成输出
    LDR R4,=GPIOCOUTENB
    LDR R5,[R4]            
    ORR R5,R5,#(1<<7)     
    STR R5,[R4] 

    //将D11灯设置成I/O功能
    LDR R6,=GPIOCALTFN0
    LDR R7,[R6]
    ORR R7,R7,#(1<<24)      //将第24位置1
    BIC R7,R7,#(1<<25)      //将第25位置0
    STR R7,[R6]

    //将D11灯设置成输出
    LDR R6,=GPIOCOUTENB
    LDR R7,[R6]            
    ORR R7,R7,#(1<<12)     
    STR R7,[R6]    

//while(1)
loop:
	//3.GPIOE13输出低电平，D7亮
	LDR R4,=GPIOEOUT
	LDR R5,[R4] 
	BIC R5,R5,#(1<<13)  
	STR R5,[R4]
    BL delay_2
    //D10灯灭
    LDR R4,=GPIOEOUT 
	LDR R5,[R4] 
	ORR R5,R5,#(1<<7)  
	STR R5,[R4]
	BL delay  //带链接跳转指令，先将下一条指令的地址放到LR寄存器，再跳转到delay执行
	
    //D8亮
    LDR R4,=GPIOEOUT
	LDR R5,[R4] 
	BIC R5,R5,#(1<<17)  
	STR R5,[R4]
    BL delay_2
    //D11灯灭
    LDR R4,=GPIOEOUT 
	LDR R5,[R4] 
	ORR R5,R5,#(1<<7)  
	STR R5,[R4]
    BL delay

    //D9灯亮，同时D7灯灭
    LDR R4,=GPIOEOUT
	LDR R5,[R4] 
	BIC R5,R5,#(1<<8)  
	STR R5,[R4]
    BL delay_2
    //D7灯灭
    LDR R4,=GPIOEOUT 
	LDR R5,[R4] 
	ORR R5,R5,#(1<<13)  
	STR R5,[R4]
    BL delay

    //D10灯亮，同时D8灯灭
    LDR R4,=GPIOEOUT
	LDR R5,[R4] 
	BIC R5,R5,#(1<<7)  
	STR R5,[R4]
    BL delay_2
    //D8灯灭
    LDR R4,=GPIOEOUT 
	LDR R5,[R4] 
	ORR R5,R5,#(1<<17)  
	STR R5,[R4]
    BL delay

    //D11灯亮，同时D9灯灭
    LDR R4,=GPIOEOUT
	LDR R5,[R4] 
	BIC R5,R5,#(1<<7)  
	STR R5,[R4]
    BL delay_2
    //D9灯灭
    LDR R4,=GPIOEOUT 
	LDR R5,[R4] 
	ORR R5,R5,#(1<<12)  
	STR R5,[R4]
	BL delay
	
	B loop    //跳转到指定地址执行程序，这里是跳转到loop

delay:
	mov r7, #0x5000000 //r7=0x5000000 --->LDR  R7, =0x5000000
temp:
	sub r7,r7,#1     //r7=r7-1
	cmp r7,#0        //compare 影响状态标志位
	bne temp        //B--branch，N--not，E--equal ---不相等才跳转
	mov pc,lr      //子程序返回，并跳转到主程序的下条指令

delay_2:
    mov r7, #0x3000000
    B temp