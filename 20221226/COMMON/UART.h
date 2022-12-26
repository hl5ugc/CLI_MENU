// =======================================================================
// [ PROJECT   ]
// -----------------------------------------------------------------------
// [ License   ] SAMJIN ELECTRONICS
// [ Author    ] Copyright 2021-08 By HAG-SEONG KANG
// [ E-MAIL    ] hl5ugc@nate.com (82)10- 3841-9706
// [ C  P  U   ]
// [ Compller  ] CodeWizardAVR V3.12 Professional
// [ Filename  ] Uart.H
// [ Version   ] 1.0
// [ Created   ] 2022-12-21
// ----------------------------------------------------------------------------
// [Updata  List] :
//
//
//
//
//
// =============================================================================
//
//
//
#ifndef _UART_INCLUDED_
#define _UART_INCLUDED_

#include "def.h"
#include "hw_def.h"

// -----------------------------------------------------------------------------
// Globals Defines
// -----------------------------------------------------------------------------
//
#ifdef      _USE_HW_UART

#define     UART_MAX_CH         HW_UART_MAX_CH
#define     _USE_UART0_         1
#define     _USE_UART1_         1
#define     _USE_UART2_         1
#define     _USE_UART3_         1
//
#ifdef      _USE_UART0_
#define     UART0_TX_MAX_BUFF   64
#define     UART0_RX_MAX_BUFF   64
#endif

#ifdef      _USE_UART1_
#define     UART1_TX_MAX_BUFF   64
#define     UART1_RX_MAX_BUFF   64
#endif

#ifdef      _USE_UART2_
#define     UART2_TX_MAX_BUFF   64
#define     UART2_RX_MAX_BUFF   64
#endif

#ifdef      _USE_UART3_
#define     UART3_TX_MAX_BUFF   64
#define     UART3_RX_MAX_BUFF   64
#endif
#endif
//
// -----------------------------------------------------------------------------
// Type Definitions
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// Constant Definitions
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
// Global Structures Define
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
// Global Variables Define
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
// Flag Macro Definitions
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
// Variable Definitions
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// Function Prototypes Definitions
// -----------------------------------------------------------------------------

uint8_t  uartInit(void) ;
uint8_t  uartOpen(uint8_t  ch, uint16_t  baud ) ;
uint8_t  uartAvailable(uint8_t ch);
uint8_t  uartRead(uint8_t ch);
uint8_t  uartReadMsg(uint8_t ch,uint8_t *pMsg);
void     uartWrite(uint8_t ch,uint8_t *u8Data);
void     uartMsgWrite(uint8_t ch, uint8_t *p_data, uint8_t length) ;
void     uartMsg(uint8_t ch, uint8_t *pBuf) ;
void     uartMsgByte2ASC(uint8_t ch, uint8_t *pBuf,uint8_t u8Byte) ;
void     uartMsgByte3ASC(uint8_t ch, uint8_t *pBuf,uint8_t u8Byte)  ;
void     uartMsgWord3DASC(uint8_t ch, uint8_t *pBuf,uint16_t u16Data) ;
void     uartMsgWord4DASC(uint8_t ch, uint8_t *pBuf,uint16_t u16Data) ;
void     uartMsgWord5DASC(uint8_t ch, uint8_t *pBuf,uint16_t u16Data) ;
void     uartMsgByte2Hex(uint8_t ch, uint8_t *pBuf,uint8_t u8Data) ;
void     uartMsgWord4Hex(uint8_t ch, uint8_t *pBuf,uint16_t u16Data) ;
void     uartMsgByte7BASC(uint8_t ch, uint8_t *pBuf,uint8_t u8Data)  ;
uint8_t  uartIsEvent(uint8_t ch) ;
void     uartSetEvent(uint8_t ch);
void     uartClsEvent(uint8_t ch) ;
uint8_t  uartIsTime(uint8_t ch) ;
void     uartMTime(uint8_t ch) ;
void     uartFlush(uint8_t ch) ;

// -----------------------------------------------------------------------------
// CallBAck Function Prototypes Definitions
// -----------------------------------------------------------------------------
void    canSetCallback(uint8_t ch, void (*callBackUartRx)(uint8_t));


#endif   /* HEADERS_BH_CPU_TEST_H_ End Of file !! Well Done !! */
// -----------------------------------------------------------------------------
