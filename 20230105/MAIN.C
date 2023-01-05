/*******************************************************
This program was created by the
CodeWizardAVR V3.12 Advanced
Automatic Program Generator
© Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project :
Version :
Date    : 2022-12-23
Author  :
Company :
Comments:


Chip type               : ATmega2560
Program type            : Application
AVR Core Clock frequency: 16.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 2048
*******************************************************/

#include <mega2560.h>
// Standard Input/Output functions
#include <delay.h>
#include <stdio.h>
#include "UART.h"
#include "Cli_COMMAND.h"

uint8_t msg[50] ;
static uint8_t  u8Count  = 0 ;
unsigned int u16Count = 0 ;
static void cb_Cli_Write_Port(cli_args_t *args) ;
static void cb_Cli_Read_Port(cli_args_t *args) ;
//cb_Cli_Uart_Test
static void cb_Cli_Uart_Test(cli_args_t *args) ;
static void cb_Cli_Write_PortA(cli_args_t *args) ;
static void cb_Cli_Write_PortB(cli_args_t *args) ;
static void cb_Cli_Read_PortA(cli_args_t *args) ;
static void cb_Cli_Read_PortB(cli_args_t *args) ;
//
void main(void)
{
    // Declare your local variables here

    // Crystal Oscillator division factor: 1
    #pragma optsize-
    CLKPR=(1<<CLKPCE);
    CLKPR=(0<<CLKPCE) | (0<<CLKPS3) | (0<<CLKPS2) | (0<<CLKPS1) | (0<<CLKPS0);
    #ifdef _OPTIMIZE_SIZE_
    #pragma optsize+
    #endif

    // Input/Output Ports initialization
    // Port A initialization
    // Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In
    DDRA=(0<<DDA7) | (0<<DDA6) | (0<<DDA5) | (0<<DDA4) | (0<<DDA3) | (0<<DDA2) | (0<<DDA1) | (0<<DDA0);
    // State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T
    PORTA=(0<<PORTA7) | (0<<PORTA6) | (0<<PORTA5) | (0<<PORTA4) | (0<<PORTA3) | (0<<PORTA2) | (0<<PORTA1) | (0<<PORTA0);

    // Port B initialization
    // Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In
    DDRB=(0<<DDB7) | (0<<DDB6) | (0<<DDB5) | (0<<DDB4) | (0<<DDB3) | (0<<DDB2) | (0<<DDB1) | (0<<DDB0);
    // State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T
    PORTB=(0<<PORTB7) | (0<<PORTB6) | (0<<PORTB5) | (0<<PORTB4) | (0<<PORTB3) | (0<<PORTB2) | (0<<PORTB1) | (0<<PORTB0);

    // Port C initialization
    // Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In
    DDRC=(0<<DDC7) | (0<<DDC6) | (0<<DDC5) | (0<<DDC4) | (0<<DDC3) | (0<<DDC2) | (0<<DDC1) | (0<<DDC0);
    // State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T
    PORTC=(0<<PORTC7) | (0<<PORTC6) | (0<<PORTC5) | (0<<PORTC4) | (0<<PORTC3) | (0<<PORTC2) | (0<<PORTC1) | (0<<PORTC0);

    // Port D initialization
    // Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In
    DDRD=(0<<DDD7) | (0<<DDD6) | (0<<DDD5) | (0<<DDD4) | (0<<DDD3) | (0<<DDD2) | (0<<DDD1) | (0<<DDD0);
    // State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T
    PORTD=(0<<PORTD7) | (0<<PORTD6) | (0<<PORTD5) | (0<<PORTD4) | (0<<PORTD3) | (0<<PORTD2) | (0<<PORTD1) | (0<<PORTD0);

    // Port E initialization
    // Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In
    DDRE=(0<<DDE7) | (0<<DDE6) | (0<<DDE5) | (0<<DDE4) | (0<<DDE3) | (0<<DDE2) | (0<<DDE1) | (0<<DDE0);
    // State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T
    PORTE=(0<<PORTE7) | (0<<PORTE6) | (0<<PORTE5) | (0<<PORTE4) | (0<<PORTE3) | (0<<PORTE2) | (0<<PORTE1) | (0<<PORTE0);

    // Port F initialization
    // Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In
    DDRF=(0<<DDF7) | (0<<DDF6) | (0<<DDF5) | (0<<DDF4) | (0<<DDF3) | (0<<DDF2) | (0<<DDF1) | (0<<DDF0);
    // State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T
    PORTF=(0<<PORTF7) | (0<<PORTF6) | (0<<PORTF5) | (0<<PORTF4) | (0<<PORTF3) | (0<<PORTF2) | (0<<PORTF1) | (0<<PORTF0);

    // Port G initialization
    // Function: Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In
    DDRG=(0<<DDG5) | (0<<DDG4) | (0<<DDG3) | (0<<DDG2) | (0<<DDG1) | (0<<DDG0);
    // State: Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T
    PORTG=(0<<PORTG5) | (0<<PORTG4) | (0<<PORTG3) | (0<<PORTG2) | (0<<PORTG1) | (0<<PORTG0);

    // Port H initialization
    // Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In
    DDRH=(0<<DDH7) | (0<<DDH6) | (0<<DDH5) | (0<<DDH4) | (0<<DDH3) | (0<<DDH2) | (0<<DDH1) | (0<<DDH0);
    // State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T
    PORTH=(0<<PORTH7) | (0<<PORTH6) | (0<<PORTH5) | (0<<PORTH4) | (0<<PORTH3) | (0<<PORTH2) | (0<<PORTH1) | (0<<PORTH0);

    // Port J initialization
    // Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In
    DDRJ=(0<<DDJ7) | (0<<DDJ6) | (0<<DDJ5) | (0<<DDJ4) | (0<<DDJ3) | (0<<DDJ2) | (0<<DDJ1) | (0<<DDJ0);
    // State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T
    PORTJ=(0<<PORTJ7) | (0<<PORTJ6) | (0<<PORTJ5) | (0<<PORTJ4) | (0<<PORTJ3) | (0<<PORTJ2) | (0<<PORTJ1) | (0<<PORTJ0);

    // Port K initialization
    // Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In
    DDRK=(0<<DDK7) | (0<<DDK6) | (0<<DDK5) | (0<<DDK4) | (0<<DDK3) | (0<<DDK2) | (0<<DDK1) | (0<<DDK0);
    // State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T
    PORTK=(0<<PORTK7) | (0<<PORTK6) | (0<<PORTK5) | (0<<PORTK4) | (0<<PORTK3) | (0<<PORTK2) | (0<<PORTK1) | (0<<PORTK0);

    // Port L initialization
    // Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In
    DDRL=(0<<DDL7) | (0<<DDL6) | (0<<DDL5) | (0<<DDL4) | (0<<DDL3) | (0<<DDL2) | (0<<DDL1) | (0<<DDL0);
    // State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T
    PORTL=(0<<PORTL7) | (0<<PORTL6) | (0<<PORTL5) | (0<<PORTL4) | (0<<PORTL3) | (0<<PORTL2) | (0<<PORTL1) | (0<<PORTL0);

    // USART0 initialization
    // Communication Parameters: 8 Data, 1 Stop, No Parity
    // USART0 Receiver: On
    // USART0 Transmitter: On
    // USART0 Mode: Asynchronous
    // USART0 Baud Rate: 9600
    UCSR0A=(0<<RXC0) | (0<<TXC0) | (0<<UDRE0) | (0<<FE0) | (0<<DOR0) | (0<<UPE0) | (0<<U2X0) | (0<<MPCM0);
    UCSR0B=(1<<RXCIE0) | (1<<TXCIE0) | (0<<UDRIE0) | (1<<RXEN0) | (1<<TXEN0) | (0<<UCSZ02) | (0<<RXB80) | (0<<TXB80);
    UCSR0C=(0<<UMSEL01) | (0<<UMSEL00) | (0<<UPM01) | (0<<UPM00) | (0<<USBS0) | (1<<UCSZ01) | (1<<UCSZ00) | (0<<UCPOL0);
    UBRR0H=0x00;
    UBRR0L=0x67;

    // USART1 initialization
    // Communication Parameters: 8 Data, 1 Stop, No Parity
    // USART1 Receiver: On
    // USART1 Transmitter: On
    // USART1 Mode: Asynchronous
    // USART1 Baud Rate: 9600
    UCSR1A=(0<<RXC1) | (0<<TXC1) | (0<<UDRE1) | (0<<FE1) | (0<<DOR1) | (0<<UPE1) | (0<<U2X1) | (0<<MPCM1);
    UCSR1B=(1<<RXCIE1) | (1<<TXCIE1) | (0<<UDRIE1) | (1<<RXEN1) | (1<<TXEN1) | (0<<UCSZ12) | (0<<RXB81) | (0<<TXB81);
    UCSR1C=(0<<UMSEL11) | (0<<UMSEL10) | (0<<UPM11) | (0<<UPM10) | (0<<USBS1) | (1<<UCSZ11) | (1<<UCSZ10) | (0<<UCPOL1);
    UBRR1H=0x00;
    UBRR1L=0x67;

    // USART3 initialization
    // Communication Parameters: 8 Data, 1 Stop, No Parity
    // USART3 Receiver: On
    // USART3 Transmitter: On
    // USART3 Mode: Asynchronous
    // USART3 Baud Rate: 9600
    UCSR3A=(0<<RXC3) | (0<<TXC3) | (0<<UDRE3) | (0<<FE3) | (0<<DOR3) | (0<<UPE3) | (0<<U2X3) | (0<<MPCM3);
    UCSR3B=(0<<RXCIE3) | (0<<TXCIE3) | (0<<UDRIE3) | (1<<RXEN3) | (1<<TXEN3) | (0<<UCSZ32) | (0<<RXB83) | (0<<TXB83);
    UCSR3C=(0<<UMSEL31) | (0<<UMSEL30) | (0<<UPM31) | (0<<UPM30) | (0<<USBS3) | (1<<UCSZ31) | (1<<UCSZ30) | (0<<UCPOL3);
    UBRR3H=0x00;
    UBRR3L=0x67;

// Global enable interrupts
    #asm("sei")
    //
    uartInit();
    uartOpen(_DEF_UART1,38400);
    uartOpen(_DEF_UART2,38400);
    //
    Cli_CMD_Open();
    //
    //cliAdd("PORTA"," Write Port", cb_Cli_Write_PortA);
    //cliAdd("PORTB"," Write Port", cb_Cli_Write_PortB);
    //cliAdd("INA"," Read Port", cb_Cli_Read_PortA);
    //cliAdd("INB"," Read Port", cb_Cli_Read_PortB);
    cliAdd("READP"," Read Port", cb_Cli_Read_Port);
    cliAdd("WRITEP"," Write Port", cb_Cli_Write_Port);
    cliAdd("UART"," Test Uart", cb_Cli_Uart_Test);
    while(1)
    {
       wait_Command() ;
    }
    //
}
static void cb_Cli_Uart_Test(cli_args_t *args)
{
    uint8_t u8SendData = '1' ;
    //
    for(u8SendData = '!' ; u8SendData < '~'  ; u8SendData++)
    {
        uartMsg(CLI_LOG_UART,"\n Data = ");  delay_ms(10) ;
        uartMsg(CLI_LOG_UART, &u8SendData);  delay_ms(10) ;
    }
    //

}
//
static void cb_Cli_Write_Port(cli_args_t *args)
{
    uint8_t u8WData = 0 ;
    uint8_t *u8Port ;
    // Todo log Disable
    if(args->argc >= 2) {

        uartMsg(CLI_LOG_UART,"\n\rargs->argv[0]");
        delay_ms(10) ;
        uartMsg(CLI_LOG_UART,args->argv[0]) ;
        delay_ms(10) ;
        //
        uartMsg(CLI_LOG_UART,"\n\rargs->argv[1]");
        delay_ms(10) ;
        uartMsg(CLI_LOG_UART,args->argv[1]) ;
        delay_ms(10) ;
        //
    }
    //
    u8Port = args->argv[0] ;
    u8WData = args->getData(1) ;
    //
    if(strcmp(u8Port,"PORTA") == 0)         { PORTA =  u8WData ; }
    else if(strcmp(u8Port,"PORTB") == 0)    { PORTB =  u8WData ; }
    else if(strcmp(u8Port,"PORTC") == 0)    { PORTC =  u8WData ; }
    else if(strcmp(u8Port,"PORTD") == 0)    { PORTD =  u8WData ; }
    else if(strcmp(u8Port,"PORTE") == 0)    { PORTE =  u8WData ; }
    else if(strcmp(u8Port,"PORTF") == 0)    { PORTF =  u8WData ; }
    else if(strcmp(u8Port,"PORTG") == 0)    { PORTG =  u8WData ; }
    #ifdef _MEGA2560_INCLUDED_
    else if(strcmp(u8Port,"PORTH") == 0)    { PORTH =  u8WData ; }
    else if(strcmp(u8Port,"PORTJ") == 0)    { PORTJ =  u8WData ; }
    else if(strcmp(u8Port,"PORTK") == 0)    { PORTK =  u8WData ; }
    else if(strcmp(u8Port,"PORTL") == 0)    { PORTL =  u8WData ; }
    #endif
    uartMsg(CLI_COMMAND_UART,"\n\r") ;
    uartMsg(CLI_COMMAND_UART,args->argv[0]);  delay_ms(10) ;
    uartMsgByte2Hex(CLI_COMMAND_UART," = 0x",u8WData) ; delay_ms(10) ;
    uartMsg(CLI_COMMAND_UART,"\n\r") ;

}
static void cb_Cli_Read_Port(cli_args_t *args)
{
    uint8_t u8RData = 0 ;
    uint8_t u8Ch = 0 ;
    //
    while(1)
    {
        uartMsg(CLI_COMMAND_UART,"\n\r") ;       delay_ms(10) ;
        uartMsg(CLI_COMMAND_UART,"\n 1) Read Port A" );  delay_ms(10) ;
        uartMsg(CLI_COMMAND_UART,"\n 2) Read Port B" );  delay_ms(10) ;
        uartMsg(CLI_COMMAND_UART,"\n 3) Read Port C" );  delay_ms(10) ;
        uartMsg(CLI_COMMAND_UART,"\n 4) Read Port D" );  delay_ms(10) ;
        uartMsg(CLI_COMMAND_UART,"\n 5) Read Port E" );  delay_ms(10) ;
        uartMsg(CLI_COMMAND_UART,"\n 6) Read Port F" );  delay_ms(10) ;
        uartMsg(CLI_COMMAND_UART,"\n 7) Read Port G" );  delay_ms(10) ;
        uartMsg(CLI_COMMAND_UART,"\n 8) Read Port H" );  delay_ms(10) ;
        uartMsg(CLI_COMMAND_UART,"\n 9) Read Port J" );  delay_ms(10) ;
        uartMsg(CLI_COMMAND_UART,"\n A) Read Port K" );  delay_ms(10) ;
        uartMsg(CLI_COMMAND_UART,"\n B) Read Port L" );  delay_ms(10) ;
        uartMsg(CLI_COMMAND_UART,"\n Z) Exit " );  delay_ms(10) ;
        uartMsg(CLI_COMMAND_UART,"\n\r Select ? " );  delay_ms(10) ;
        //
        u8Ch = uartGetc(CLI_COMMAND_UART) ;
        if(u8Ch == '1')         { u8RData = PINA ; }
        else if(u8Ch == '2')    { u8RData = PINB ; }
        else if(u8Ch == '3')    { u8RData = PINC ; }
        else if(u8Ch == '4')    { u8RData = PIND ; }
        else if(u8Ch == '5')    { u8RData = PINE ; }
        else if(u8Ch == '6')    { u8RData = PINF ; }
        else if(u8Ch == '7')    { u8RData = PING ; }
        #ifdef _MEGA2560_INCLUDED_
        else if(u8Ch == '8')    { u8RData = PINH ; }
        else if(u8Ch == '9')    { u8RData = PINJ ; }
        else if((u8Ch == 'A') || (u8Ch == 'a'))    { u8RData = PINK ; }
        else if((u8Ch == 'B') || (u8Ch == 'b'))    { u8RData = PINL ; }
        #endif
        else if((u8Ch == 'Z') || (u8Ch == 'z'))   { break ; }
        //
        uartMsg(CLI_COMMAND_UART,"\n\r") ;
        uartMsgByte2Hex(CLI_COMMAND_UART,"Read Data = 0x",u8RData) ; delay_ms(10) ;
        uartMsg(CLI_COMMAND_UART,"\n\r") ;
        //
    }
}

static void cb_Cli_Write_PortA(cli_args_t *args)
{
    uint8_t u8WiteData = 0 ;
    // Todo log Disable
    if(args->argc >= 1) {
        uartMsg(CLI_LOG_UART,"\n\rargs->argv[0]");
        delay_ms(10) ;
        uartMsg(CLI_LOG_UART," => 0x") ;
        delay_ms(10) ;
        uartMsg(CLI_LOG_UART,args->argv[0]) ;
        delay_ms(10) ;
        //
    }
    //
    u8WiteData = args->getData(0) ;
    PORTA = u8WiteData ;
    uartMsgByte2Hex(CLI_COMMAND_UART,"\n PORTA =0x",u8WiteData) ;
    uartMsg(CLI_COMMAND_UART,"\n\r") ;
}
static void cb_Cli_Write_PortB(cli_args_t *args)
{
    uint8_t u8WiteData = 0 ;
    // Todo log Disable
    if(args->argc >= 1) {
        uartMsg(CLI_LOG_UART,"\n\rargs->argv[0]");
        delay_ms(10) ;
        uartMsg(CLI_LOG_UART," => 0x") ;
        delay_ms(10) ;
        uartMsg(CLI_LOG_UART,args->argv[0]) ;
        delay_ms(10) ;
        //
    }
    //
    u8WiteData = args->getData(0) ;
    PORTB = u8WiteData ;
    uartMsgByte2Hex(CLI_COMMAND_UART,"\n PORTB =0x",u8WiteData) ;
    uartMsg(CLI_COMMAND_UART,"\n\r") ;
}
static void cb_Cli_Read_PortA(cli_args_t *args)
{
    uint8_t u8ReadData = 0 ;
    // Todo log Disable
    if(args->argc >= 1) {
        uartMsg(CLI_LOG_UART,"\n\rargs->argv[0]");
        delay_ms(10) ;
        uartMsg(CLI_LOG_UART," => 0x") ;
        delay_ms(10) ;
        uartMsg(CLI_LOG_UART,args->argv[0]) ;
        delay_ms(10) ;
        //
    }
    //
    u8ReadData =  PINA ;
    uartMsgByte2Hex(CLI_COMMAND_UART,"\n PINA =0x",u8ReadData) ;
    uartMsg(CLI_COMMAND_UART,"\n\r") ;
}
static void cb_Cli_Read_PortB(cli_args_t *args)
{
    uint8_t u8ReadData = 0 ;
    // Todo log Disable
    if(args->argc >= 1) {
        uartMsg(CLI_LOG_UART,"\n\rargs->argv[0]");
        delay_ms(10) ;
        uartMsg(CLI_LOG_UART," => 0x") ;
        delay_ms(10) ;
        uartMsg(CLI_LOG_UART,args->argv[0]) ;
        delay_ms(10) ;
        //
    }
    //
    u8ReadData =  PINB ;
    uartMsgByte2Hex(CLI_COMMAND_UART,"\n PINB =0x",u8ReadData) ;
    uartMsg(CLI_COMMAND_UART,"\n\r") ;
}
static void cb_Cli_MM(cli_args_t *args)
{

}
static void cb_Cli_MD(cli_args_t *args)
{

}