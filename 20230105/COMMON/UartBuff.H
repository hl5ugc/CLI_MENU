// =======================================================================
// [ PROJECT   ]
// -----------------------------------------------------------------------
// [ License   ] SAMJIN ELECTRONICS
// [ Author    ] Copyright 2021-08 By HAG-SEONG KANG
// [ E-MAIL    ] hl5ugc@nate.com (82)10- 3841-9706
// [ C  P  U   ]
// [ Compller  ] CodeWizardAVR V3.12 Professional
// [ Filename  ] UartBuff.H
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
#ifndef _UartBuff_INCLUDED_
#define _UartBuff_INCLUDED_

#include "def.h"

typedef struct
{
  uint8_t wr_ptr ;
  uint8_t rd_ptr ;
  uint8_t len ;
  uint8_t count ;
  uint8_t time ;
  uint8_t event ;

  uint8_t *p_buf ;
} qUartBuff_t ;

// -----------------------------------------------------------------------------
// Function Prototypes Definitions
// -----------------------------------------------------------------------------
void    qUartbufferInit(void);
bool    qUartbufferCreate(qUartBuff_t *p_node, uint8_t *p_buf, uint8_t length);
bool    qUartbufferWrite(qUartBuff_t *p_node, uint8_t *p_data, uint8_t length);
bool    qUartbufferWriteByte(qUartBuff_t *p_node, uint8_t *p_data) ;
bool    qUartbufferRead(qUartBuff_t *p_node, uint8_t *p_data, uint8_t length);
bool    qUartbufferReadByte(qUartBuff_t *p_node, uint8_t *p_data) ;
uint8_t qUartbufferAvailable(qUartBuff_t *p_node);
bool    qUartbufferEmpty(qUartBuff_t *p_node) ;
bool    qUartbufferNotEmpty(qUartBuff_t *p_node) ;
void    qUartbufferFlush(qUartBuff_t *p_node);
//
void    qUartbufferSetEvent(qUartBuff_t *p_node) ;
void    qUartbufferClsEvent(qUartBuff_t *p_node);
bool    qUartbufferEvent(qUartBuff_t *p_node) ;
uint8_t qUartbufferGetEvent(qUartBuff_t *p_node) ;
bool    qUartbufferNotEvent(qUartBuff_t *p_node);
void    qUartbufferMTime(qUartBuff_t *p_node) ;
uint8_t qUartbufferIsTime(qUartBuff_t *p_node) ;

// -----------------------------------------------------------------------------
// Function Definition
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------


#endif /* HEADERS_BH_CPU_TEST_H_ End Of file !! Well Done !! */
// -----------------------------------------------------------------------------