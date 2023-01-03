//
// =======================================================================
// [ PROJECT   ]
// -----------------------------------------------------------------------
// [ License   ] SAMJIN ELECTRONICS
// [ Author    ] Copyright 2021-08 By HAG-SEONG KANG
// [ E-MAIL    ] hl5ugc@nate.com (82)10- 3841-9706
// [ C  P  U   ]
// [ Compller  ] CodeWizardAVR V3.12 Professional
// [ Filename  ]  UART.C
// [ Version   ] 1.0
// [ Created   ] 2021-08-10
// ----------------------------------------------------------------------------
// Revision History :
// ----------------------------------------------------------------------------
// Author         Date          Comments on this revision
// ----------------------------------------------------------------------------
// HAG-SEONG KANG 2021-12-09    First release of header file
//
//
// ============================================================================
//
//
//
#pragma used+
//
#include "Uart.H"
#include "UartBuff.H"
#include "ConvertData.H"

// ---------------------------------------------------------------------------
// Define basic
// ---------------------------------------------------------------------------
//

#define RXB8 1
#define TXB8 0
#define UPE 2
#define OVR 3
#define FE 4
#define UDRE 5
#define RXC 7

#define FRAMING_ERROR (1<<FE)
#define PARITY_ERROR (1<<UPE)
#define DATA_OVERRUN (1<<OVR)
#define DATA_REGISTER_EMPTY (1<<UDRE)
#define RX_COMPLETE (1<<RXC)

// ---------------------------------------------------------------------------
//  Define Macros .
// ---------------------------------------------------------------------------
//
typedef struct
{
    void (*callBackUartRx)(uint8_t u8Data) ;
} uart_cb_tbl_t ;

typedef void (*cbuart_t)(uint8_t);
static  uart_cb_tbl_t uart_cb_tbl[HW_UART_MAX_CH] ;

// ---------------------------------------------------------------------------
//  Define Constants.
// ---------------------------------------------------------------------------
//

// ---------------------------------------------------------------------------
// Bit control PortA - PortG
// ---------------------------------------------------------------------------
//

// ---------------------------------------------------------------------------
// Declare your private variables here
// ---------------------------------------------------------------------------
//
static uint8_t is_Open[UART_MAX_CH] ;
static qUartBuff_t qUartTxBuff[UART_MAX_CH] ;
static qUartBuff_t qUartRxBuff[UART_MAX_CH] ;


//
#ifdef      _USE_UART0_
static uint8_t tx_buf0[UART0_TX_MAX_BUFF] ;
static uint8_t rx_buf0[UART0_RX_MAX_BUFF] ;
#endif

#ifdef      _USE_UART1_
static uint8_t tx_buf1[UART1_TX_MAX_BUFF] ;
static uint8_t rx_buf1[UART1_RX_MAX_BUFF] ;
#endif

#ifdef      _USE_UART2_
static uint8_t tx_buf2[UART2_TX_MAX_BUFF] ;
static uint8_t rx_buf2[UART2_RX_MAX_BUFF] ;
#endif

#ifdef      _USE_UART3_
static uint8_t tx_buf3[UART3_TX_MAX_BUFF] ;
static uint8_t rx_buf3[UART3_RX_MAX_BUFF] ;
#endif
// ---------------------------------------------------------------------------
//  Define Private function protoypye.
// ---------------------------------------------------------------------------
/*
uint8_t   uartInit(void) ;
uint8_t   uartOpen(uint8_t ch, uint16_t baud) ;
uint8_t   uartAvailable(uint8_t ch);
uint8_t   uartRead(uint8_t ch);
void      uartWrite(uint8_t ch, uint8_t *p_data, uint32_t length);
*/
// ---------------------------------------------------------------------------
//  Define private function definitions.
// ---------------------------------------------------------------------------
//




// ---------------------------------------------------------------------------
//  Define Public function definitions.
// ---------------------------------------------------------------------------
//

/*
 * Pointer stored in EEPROM to a char string placed in RAM
 * char * eeprom eeprom_ptr_to_ram="This string is placed in RAM";
 * Pointer stored in EEPROM to a char string placed in FLASH
 * flash char * eeprom eeprom_ptr_to_flash="This string is placed in FLASH";
 * Pointer stored in EEPROM to a char string placed in EEPROM
 * eeprom char * eeprom eeprom_ptr_to_eeprom="This string is placed in EEPROM";
 *
 */
void uartFMsg(uint8_t ch,flash uint8_t *pBuf)
{
    uint8_t u8Msg[32] ;
    uint8_t u8len = 0 ;
    //
    while(*pBuf != 0x00)
    {
        u8Msg[u8len] = *pBuf ;
        pBuf++ ;
        u8len++ ;
        //
    }
    //
    uartMsgWrite(ch,&u8Msg[0],u8len);
}
void uartMsg(uint8_t ch, uint8_t *pBuf)
{
    uartMsgWrite(ch,pBuf,strlen(pBuf));
}
void uartMsgByte2ASC(uint8_t ch, uint8_t *pBuf,uint8_t u8Byte)
{
    uint8_t u8Msg[2] ;
    //
    uartMsgWrite(ch,pBuf,strlen(pBuf));
    cvtByte2DASC(u8Byte,&u8Msg[0]) ;
    uartMsgWrite(ch,u8Msg,2);
    //
}
void uartByte2ASC(uint8_t ch, uint8_t u8Byte)
{
    uint8_t u8Msg[2] ;
    //
    cvtByte2DASC(u8Byte,&u8Msg[0]) ;
    uartMsgWrite(ch,u8Msg,2);
    //
}
void uartMsgByte3ASC(uint8_t ch, uint8_t *pBuf,uint8_t u8Byte)
{
    uint8_t u8Msg[3] ;
    //
    uartMsgWrite(ch,pBuf,strlen(pBuf));
    cvtByte3DASC(u8Byte,&u8Msg[0]) ;
    uartMsgWrite(ch,u8Msg,3);
    //
}
void uartByte3ASC(uint8_t ch,uint8_t u8Byte)
{
    uint8_t u8Msg[3] ;
    //
    cvtByte3DASC(u8Byte,&u8Msg[0]) ;
    uartMsgWrite(ch,u8Msg,3);
    //
}
void uartMsgWord3DASC(uint8_t ch, uint8_t *pBuf,uint16_t u16Data)
{
    uint8_t u8Msg[3] ;
    //
    uartMsgWrite(ch,pBuf,strlen(pBuf));
    cvtWord3DASC(u16Data,&u8Msg[0]) ;
    uartMsgWrite(ch,u8Msg,3);
}
void uartWord3DASC(uint8_t ch, uint16_t u16Data)
{
    uint8_t u8Msg[3] ;
    //
    cvtWord3DASC(u16Data,&u8Msg[0]) ;
    uartMsgWrite(ch,u8Msg,3);
}
void uartMsgWord4DASC(uint8_t ch, uint8_t *pBuf,uint16_t u16Data)
{
    uint8_t u8Msg[4] ;
    //
    uartMsgWrite(ch,pBuf,strlen(pBuf));
    cvtWord4DASC(u16Data,&u8Msg[0]) ;
    uartMsgWrite(ch,u8Msg,4);
}
void uartMsgWord5DASC(uint8_t ch, uint8_t *pBuf,uint16_t u16Data)
{
    uint8_t u8Msg[5] ;
    //
    uartMsgWrite(ch,pBuf,strlen(pBuf));
    cvtWord5DASC(u16Data,&u8Msg[0]) ;
    uartMsgWrite(ch,u8Msg,5);
}
void uartMsgByte2Hex(uint8_t ch, uint8_t *pBuf,uint8_t u8Data)
{
    uint8_t u8Msg[2] ;
    //
    uartMsgWrite(ch,pBuf,strlen(pBuf));
    cvtByte2HEX(u8Data,&u8Msg[0]) ;
    uartMsgWrite(ch,u8Msg,2);
}
void uartMsgWord4Hex(uint8_t ch, uint8_t *pBuf,uint16_t u16Data)
{
    uint8_t u8Msg[4] ;
    //
    uartMsgWrite(ch,pBuf,strlen(pBuf));
    cvtWord4HEX(u16Data,&u8Msg[0]) ;
    uartMsgWrite(ch,u8Msg,4);
}
void uartMsgByte7BASC(uint8_t ch, uint8_t *pBuf,uint8_t u8Data)
{
    uint8_t u8Msg[8] ;
    //
    uartMsgWrite(ch,pBuf,strlen(pBuf));
    cvtByte7BASC(u8Data,&u8Msg[0]) ;
    uartMsgWrite(ch,u8Msg,8);
}
void uartMsgStr(uint8_t ch, uint8_t *pBuf,uint8_t *u8Str)
{
    uartMsgWrite(ch,pBuf,strlen(pBuf));
    uartMsgWrite(ch,u8Str,strlen(u8Str));
}
//

void uartWord4DASC(uint8_t ch, uint16_t u16Data)
{
    uint8_t u8Msg[4] ;
    //
    cvtWord4DASC(u16Data,&u8Msg[0]) ;
    uartMsgWrite(ch,u8Msg,4);
}
void uartWord5DASC(uint8_t ch, uint16_t u16Data)
{
    uint8_t u8Msg[5] ;
    //
    cvtWord5DASC(u16Data,&u8Msg[0]) ;
    uartMsgWrite(ch,u8Msg,5);
}
void uartByte2Hex(uint8_t ch,uint8_t u8Data)
{
    uint8_t u8Msg[2] ;
    //
    cvtByte2HEX(u8Data,&u8Msg[0]) ;
    uartMsgWrite(ch,u8Msg,2);
}
void uartWord4Hex(uint8_t ch,uint16_t u16Data)
{
    uint8_t u8Msg[4] ;
    //
    cvtWord4HEX(u16Data,&u8Msg[0]) ;
    uartMsgWrite(ch,u8Msg,4);
}
void uartByte7BASC(uint8_t ch,uint8_t u8Data)
{
    uint8_t u8Msg[8] ;
    //
    cvtByte7BASC(u8Data,&u8Msg[0]) ;
    uartMsgWrite(ch,u8Msg,8);
}
//
//
//
uint8_t   uartInit(void)
{
    uint8_t i = 0 ;
    //
    for(i = 0 ; i < UART_MAX_CH ;  i++)
    {
        is_Open[i] = false ;
    }
    //
    return true ;
}
/*
 *
 */
bool uartOpen(uint8_t ch, uint16_t baud)
{
    bool bRet = false ;
    //
    uint16_t u16Baud = 0x0067 ;
    uint8_t  u8TxLenth = 0 ;
    uint8_t  u8RxLenth = 0 ;
    uint8_t  *pRxd_buff ;
    uint8_t  *pTxd_buff ;
    //
    switch(baud)
    {
        case 9600:
                    u16Baud = 0x0067 ;
                    break ;
        case 19200:
                    u16Baud = 0x0033 ;
                    break ;
        case 38400:
                    u16Baud = 0x0019;
                    break ;
        default :
                    u16Baud = 0x0067 ;
                    break ;
    }
    //
    switch(ch)
    {
        #ifdef _USE_UART0_
        case _DEF_UART1:
                            UCSR0A = 0x00 ;
                            UCSR0B = 0xD8 ;
                            UCSR0C = 0x06 ;
                            UBRR0H = (u16Baud >> 8) ;
                            UBRR0L =  u16Baud   ;
                            //
                            u8TxLenth =  UART0_TX_MAX_BUFF ;
                            u8RxLenth =  UART0_RX_MAX_BUFF ;
                            //
                            is_Open[ch] = true ;
                            bRet = true ;
                            pRxd_buff = &rx_buf0[0] ;
                            pTxd_buff = &tx_buf0[0] ;
                            break ;
        #endif
        //
        #ifdef _USE_UART1_
        case _DEF_UART2:
                            UCSR1A = 0x00 ;
                            UCSR1B = 0xD8 ;
                            UCSR1C = 0x06 ;
                            UBRR1H = (u16Baud >> 8) ;
                            UBRR1L =  u16Baud   ;
                            //
                            u8TxLenth =  UART1_TX_MAX_BUFF ;
                            u8RxLenth =  UART1_RX_MAX_BUFF ;
                            //
                            is_Open[ch] = true ;
                            bRet = true ;
                            pRxd_buff = &rx_buf1[0] ;
                            pTxd_buff = &tx_buf1[0] ;
                            break ;
        #endif
        //
        #ifdef _USE_UART2_
        case _DEF_UART3:
                            UCSR2A = 0x00 ;
                            UCSR2B = 0xD8 ;
                            UCSR2C = 0x06 ;
                            UBRR2H = (u16Baud >> 8) ;
                            UBRR2L =  u16Baud   ;
                            //
                            u8TxLenth =  UART2_TX_MAX_BUFF ;
                            u8RxLenth =  UART2_RX_MAX_BUFF ;
                            //
                            is_Open[ch] = true ;
                            bRet = true ;
                            pRxd_buff = &rx_buf2[0] ;
                            pTxd_buff = &tx_buf2[0] ;
                            break ;
        #endif
        //
        #ifdef _USE_UART3_
        case _DEF_UART4:
                            UCSR3A = 0x00 ;
                            UCSR3B = 0xD8 ;
                            UCSR3C = 0x06 ;
                            UBRR3H = (u16Baud >> 8) ;
                            UBRR3L =  u16Baud   ;
                            //
                            u8TxLenth =  UART3_TX_MAX_BUFF ;
                            u8RxLenth =  UART3_RX_MAX_BUFF ;
                            //
                            is_Open[ch] = true ;
                            bRet = true ;
                            pRxd_buff = &rx_buf3[0] ;
                            pTxd_buff = &tx_buf3[0] ;
                            break ;
        #endif
    }
    //
    if(is_Open[ch] == true)
    {
        qUartbufferCreate(&qUartTxBuff[ch],pTxd_buff,u8TxLenth);
        qUartbufferCreate(&qUartRxBuff[ch],pRxd_buff,u8RxLenth);
        //
        uart_cb_tbl[ch].callBackUartRx = NULL ;
    }
    //
    return  bRet ;
}

/*
 *   Rx Data Event Check  qUartbufferGetEvent
 */
uint8_t uartIsEvent(uint8_t ch)
{
    uint8_t u8Ret = 0  ;
    //
    u8Ret = qUartbufferGetEvent(&qUartRxBuff[ch]) ;
    //
    return u8Ret ;
}
void uartSetEvent(uint8_t ch)
{
    qUartbufferSetEvent(&qUartRxBuff[ch]);
}
void uartClsEvent(uint8_t ch)
{
    qUartbufferClsEvent(&qUartRxBuff[ch]);
}
void uartFlush(uint8_t ch)
{
    qUartbufferFlush(&qUartRxBuff[ch]);
}
/*
 *   Rx Data Time Check
 */
uint8_t uartIsTime(uint8_t ch)
{
    return qUartbufferIsTime(&qUartRxBuff[ch]);
}
void uartMTime(uint8_t ch)
{
    qUartbufferMTime(&qUartRxBuff[ch]);
}
/*
 *  Rx Data write Buffer
 */
uint8_t  uartGetc(uint8_t ch)
{
    while(uartAvailable(ch) == 0x00) ;
    return uartRead(ch);

}
/*
 *   Rx Data Available Check
 */
uint8_t uartAvailable(uint8_t ch)
{
    uint8_t u8Ret = 0 ;
    //
    u8Ret = qUartbufferAvailable(&qUartRxBuff[ch]);
    return u8Ret ;
}
/*
 *  Rx Data qbuff read byte
 */
uint8_t  uartRead(uint8_t ch)
{
    uint8_t u8Ret = 0 ;
    // TODO Check Receive
    qUartbufferReadByte(&qUartRxBuff[ch],&u8Ret);
    //
    return u8Ret ;
}

/*
 *  Rx Data write Buffer
 */
void  uartWrite(uint8_t ch,uint8_t *u8Data)
{
    qUartbufferWriteByte(&qUartRxBuff[ch], u8Data) ;
    //
}
/*
 *  Rx Data read MULT BYTE Check
 */
uint8_t  uartReadMsg(uint8_t ch,uint8_t *pMsg)
{
    uint8_t u8Ret = 0 ;
    //
    u8Ret= qUartbufferAvailable(&qUartRxBuff[ch]);
    qUartbufferRead(&qUartRxBuff[ch],pMsg,u8Ret);
    //
    return u8Ret ;
}
//
void uartMsgWrite(uint8_t ch, uint8_t *p_data, uint8_t length)
{
    uint8_t u8Data = 0 ;
    //
    switch(ch)
    {
        #ifdef _USE_UART0_
        case _DEF_UART1:
                            if(qUartbufferEmpty(&qUartTxBuff[_DEF_UART1]))
                            {
                                if(length >  1)
                                {
                                    qUartbufferFlush(&qUartTxBuff[_DEF_UART1]);
                                    u8Data =  *p_data++ ;
                                    qUartbufferWrite(&qUartTxBuff[_DEF_UART1],p_data,(length-1)) ;
                                    UDR0 = u8Data ;
                                }
                                else { UDR0 = *p_data ; }
                            }
                            else {
                                qUartbufferWrite(&qUartTxBuff[_DEF_UART1],p_data, length) ;
                            }
                            break ;
        #endif
        //
        #ifdef _USE_UART1_
        case _DEF_UART2:
                            if(qUartbufferEmpty(&qUartTxBuff[_DEF_UART2])) {
                                if(length >  1)
                                {
                                    qUartbufferFlush(&qUartTxBuff[_DEF_UART2]);
                                    u8Data =  *p_data++ ;
                                    qUartbufferWrite(&qUartTxBuff[_DEF_UART2],p_data,(length-1)) ;
                                    UDR1 = u8Data ;
                                }
                                else { UDR1 = *p_data ; }
                            }
                            else {
                                qUartbufferWrite(&qUartTxBuff[_DEF_UART2],p_data, length) ;
                            }
                            break ;
        #endif
        //
        #ifdef _USE_UART2_
        case _DEF_UART3:
                            if(qUartbufferEmpty(&qUartTxBuff[_DEF_UART3])) {
                                if(length >  1)
                                {
                                    qUartbufferFlush(&qUartTxBuff[_DEF_UART3]);
                                    u8Data =  *p_data++ ;
                                    qUartbufferWrite(&qUartTxBuff[_DEF_UART3],p_data,(length-1)) ;
                                    UDR2 = u8Data ;
                                }
                                else { UDR2 = *p_data ; }
                            }
                            else {
                                qUartbufferWrite(&qUartTxBuff[_DEF_UART3],p_data, length) ;
                            }
                            break ;
        #endif
        //
        #ifdef _USE_UART3_
        case _DEF_UART4:
                            if(qUartbufferEmpty(&qUartTxBuff[_DEF_UART4])) {
                                if(length >  1)
                                {
                                    qUartbufferFlush(&qUartTxBuff[_DEF_UART4]);
                                    u8Data =  *p_data++ ;
                                    qUartbufferWrite(&qUartTxBuff[_DEF_UART4],p_data,(length-1)) ;
                                    UDR3 = u8Data ;
                                }
                                else { UDR3 = *p_data ; }
                            }
                            else {
                                qUartbufferWrite(&qUartTxBuff[_DEF_UART4],p_data, length) ;
                            }
                            break ;
        #endif
    }

}

/*
uartPrintf(p_cli->log_ch, "Cursor  : %d\n", p_cli->line.cursor);
uartPrintf(p_cli->log_ch, "buf     : %s\n", p_cli->line.buf);
uartPrintf(p_cli->log_ch, "buf %d   : %s\n", i, p_cli->line_buf[i].buf);
*/
uint8_t uartPrintf(uint8_t ch, uint8_t *pBuf , uint8_t u8Len)
{
  uint8_t u8Ret = 0 ;
  //
  uartMsgWrite(ch, (uint8_t *)pBuf, u8Len);

  return u8Ret ;
}
void my_printf(flash char *fmt, ...)
{
    va_list     ap;
    char        buf[128];
    int         rc;
    //
    va_start(ap, fmt);
    rc = vsprintf(buf, fmt, ap);
    va_end(ap);
    //
    uartMsgWrite(1, &buf[0],strlen(&buf[0]));
    //

}
// Todo Interrupt Vector Routine ....
// Data Send & Recieve
/*
int my_printf(const char *fmt, ...)
{
    va_list     ap;
    char        buf[128];
    int         rc;

    va_start(ap, fmt);
    rc = vsprintf(buf, fmt, ap);
    va_end(ap);

    uart_puts(buf);

    return rc;
}

void loop(void)
{
    static int loop_count = 0;

    my_printf("Running %u times\n", loop_count++);
    _delay_ms(200);
}
*/

// ---------------------------------------------------------------------------
// USART Receiver interrupt service routine
// ---------------------------------------------------------------------------
//
//
#ifdef _USE_UART0_
interrupt [USART0_RXC] void usart0_rx_isr(void)
{
	uint8_t u8Status = 0 ;
    uint8_t u8Data = 0 ;
	u8Status = UCSR1A;
	u8Data = UDR0;
    //
    // ToDo CallBAck Function .....

    //
    //qUartbufferWriteByte(&qUartRxBuff[0], &u8Data) ;
    if(uart_cb_tbl[0].callBackUartRx != NULL)
    {
        (*uart_cb_tbl[0].callBackUartRx)(u8Data);
    }
    else
    {
        qUartbufferWriteByte(&qUartRxBuff[0], &u8Data) ;
    }
    // -----------------------------------------------------------
    /*
    if(data == PC_STX)
    {
        rx_wr_index = 0x00 ;
        rx_buffer_overflow = 0 ;
    }
    else if(data == PC_ETX)
    {
        rx_buffer_overflow = 1 ;
    }

    //-------------------------------------------------------------
    if ((status & (FRAMING_ERROR | PARITY_ERROR | DATA_OVERRUN))==0)
    {
           rx_buffer[rx_wr_index] = data ;
           if (++rx_wr_index == RX_BUFFER_SIZE) rx_wr_index=0;
    };
    */
}
// --------------------------------------------------------------
// TX0
interrupt [USART0_TXC] void usart0_tx_isr(void)
{
    uint8_t u8Data = 0 ;
    //
    if(qUartbufferReadByte(&qUartTxBuff[0],&u8Data) == true)
    {
        UDR0 = u8Data ;
    }
}
#endif
// --------------------------------------------------------------
// RX1
//
#ifdef _USE_UART1_
interrupt [USART1_RXC] void usart1_rx_isr(void)
{
	uint8_t u8Status = 0 ;
    uint8_t u8Data = 0 ;
	u8Status = UCSR1A;
	u8Data = UDR1;
    //
    // ToDo CallBAck Function .....
    //qUartbufferWriteByte(&qUartRxBuff[1], &u8Data) ;

    if(uart_cb_tbl[1].callBackUartRx != NULL)
    {
        (*uart_cb_tbl[1].callBackUartRx)(u8Data);
    }
    else
    {
        qUartbufferWriteByte(&qUartRxBuff[1], &u8Data) ;
        //UDR0 = u8Data ;
    }
    //
}
// --------------------------------------------------------------
// TX1
interrupt [USART1_TXC] void usart1_tx_isr(void)
{
    uint8_t u8Data = 0 ;
    //
    if(qUartbufferReadByte(&qUartTxBuff[1],&u8Data) == true)
    {
        UDR1 = u8Data ;
    }
}
#endif
// --------------------------------------------------------------
// RX2
//
#ifdef _USE_UART2_
interrupt [USART2_RXC] void usart2_rx_isr(void)
{
	uint8_t u8Status = 0 ;
    uint8_t u8Data = 0 ;
	u8Status = UCSR1A;
	u8Data = UDR2;
    //
    //qUartbufferWriteByte(&qUartRxBuff[2], &u8Data) ;
    if(uart_cb_tbl[2].callBackUartRx != NULL)
    {
        (*uart_cb_tbl[2].callBackUartRx)(u8Data);
    }
    else
    {
        qUartbufferWriteByte(&qUartRxBuff[2], &u8Data) ;
    }
}
// --------------------------------------------------------------
// TX2
interrupt [USART2_TXC] void usart2_tx_isr(void)
{
    uint8_t u8Data = 0 ;
    //
    if(qUartbufferReadByte(&qUartTxBuff[2],&u8Data) == true)
    {
        UDR2 = u8Data ;

    }
}
#endif
// ---------------------------------------------------------------------------
// RX3
//
#ifdef _USE_UART3_
interrupt [USART3_RXC] void usart3_rx_isr(void)
{
	uint8_t u8Status = 0 ;
    uint8_t u8Data = 0 ;
	u8Status = UCSR1A;
	u8Data = UDR3;
    //
    //qUartbufferWriteByte(&qUartRxBuff[3], &u8Data) ;
    if(uart_cb_tbl[3].callBackUartRx != NULL)
    {
        (*uart_cb_tbl[3].callBackUartRx)(u8Data);
    }
    else
    {
        qUartbufferWriteByte(&qUartRxBuff[3], &u8Data) ;
    }

}
// --------------------------------------------------------------
// TX3
interrupt [USART3_TXC] void usart3_tx_isr(void)
{
    uint8_t u8Data = 0 ;
    //
    if(qUartbufferReadByte(&qUartTxBuff[3],&u8Data) == true)
    {
        UDR3 = u8Data ;

    }
}
/*
 *
 *
 */
void canSetCallback(uint8_t ch, void (*callBackUartRx)(uint8_t))
{
    uart_cb_tbl[ch].callBackUartRx = callBackUartRx  ;
}
#endif

#pragma used-


