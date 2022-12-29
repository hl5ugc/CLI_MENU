//
// =======================================================================
// [ PROJECT   ]
// -----------------------------------------------------------------------
// [ License   ] SAMJIN ELECTRONICS
// [ Author    ] Copyright 2021-08 By HAG-SEONG KANG
// [ E-MAIL    ] hl5ugc@nate.com (82)10- 3841-9706
// [ C  P  U   ]
// [ Compller  ] CodeWizardAVR V3.12 Professional
// [ Filename  ] UartBuff.C
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
//
#pragma used+

#include "UartBuff.H"


// ---------------------------------------------------------------------------
// Define basic
// ---------------------------------------------------------------------------
//



// ---------------------------------------------------------------------------
//  Define Macros .
// ---------------------------------------------------------------------------
//

// ---------------------------------------------------------------------------
//  Define Constants.
// ---------------------------------------------------------------------------
//

// ---------------------------------------------------------------------------
// Bit control PortA - PortG
// ---------------------------------------------------------------------------
//

// ---------------------------------------------------------------------------
//  Define Varibales.
// ---------------------------------------------------------------------------
//

// ---------------------------------------------------------------------------
//  Define Private function protoypye.
// ---------------------------------------------------------------------------
//

// ---------------------------------------------------------------------------
//  Define private function definitions.
// ---------------------------------------------------------------------------
//


// ---------------------------------------------------------------------------
// Declare your private variables here
// ---------------------------------------------------------------------------
//


// ---------------------------------------------------------------------------
//  Define Public function definitions.
// ---------------------------------------------------------------------------
//
void  qUartbufferInit(void)
{

}
/*
 *
*/
bool  qUartbufferCreate(qUartBuff_t *p_node, uint8_t *p_buf, uint8_t length)
{
  bool  bRet = true ;
  //
  p_node->wr_ptr = 0 ;
  p_node->rd_ptr = 0 ;
  p_node->len    = length ;
  p_node->count  = 0 ;
  p_node->time   = 0 ;
  p_node->event  = 0 ;
  //
  p_node->p_buf  = p_buf ;
  //
  return  bRet ;

}
/*
 *
*/
bool  qUartbufferWrite(qUartBuff_t *p_node, uint8_t *p_data, uint8_t length)
{
    bool bRet = true ;
    uint8_t u8i= 0 ;
    uint8_t u8Next_wr ;
    //
    for(u8i = 0 ; u8i < length; u8i++)
    {
        u8Next_wr = (p_node->wr_ptr + 1) % p_node->len ;
        if(u8Next_wr != p_node->rd_ptr)
        {
            if(p_node->p_buf != NULL)
            {
                p_node->p_buf[p_node->wr_ptr] = p_data[u8i] ;
                p_node->count++ ;
            }
            p_node->wr_ptr =  u8Next_wr ;
        }
        else
        {
            bRet = false ;
            break ;
        }
    }
    //
    return bRet ;
}
/*
 *
*/
bool  qUartbufferWriteByte(qUartBuff_t *p_node, uint8_t *p_data)
{
    bool bRet = true ;
    uint8_t u8Next_wr ;
    //
    u8Next_wr = (p_node->wr_ptr + 1) % p_node->len ;
    if(u8Next_wr != p_node->rd_ptr) // check 1 cycle OverFlow
    {
        if(p_node->p_buf != NULL)
        {
            p_node->p_buf[p_node->wr_ptr] = *p_data  ;
            p_node->count++ ;
            p_node->time = 3 ;
        }
        p_node->wr_ptr =  u8Next_wr ;
    }
    else
    {
        bRet = false ;
    }
    //
    return bRet ;
}
/*
 *
*/
bool  qUartbufferRead(qUartBuff_t *p_node, uint8_t *p_data, uint8_t length)
{
    bool bRet = true ;
    uint8_t u8i= 0 ;
    //
    for( u8i = 0 ; u8i <length ; u8i++)
    {
        if(p_node->p_buf != NULL)
        {
            p_data[u8i] = p_node->p_buf[p_node->rd_ptr] ;
            p_node->count-- ;
        }
        //
        if(p_node->rd_ptr != p_node->wr_ptr)
        {
            p_node->rd_ptr = (p_node->rd_ptr + 1) % p_node->len ;
        }
        else
        {
            bRet = false ;
            break ;
        }
    }
    //
    return bRet ;
}
/*
 *
*/
bool  qUartbufferReadByte(qUartBuff_t *p_node, uint8_t *p_data)
{
    bool bRet = true ;
    //
    if(p_node->p_buf != NULL)
    {
        *p_data = p_node->p_buf[p_node->rd_ptr] ;
        p_node->count-- ;
    }
    //
    if(p_node->rd_ptr != p_node->wr_ptr)
    {
        p_node->rd_ptr = (p_node->rd_ptr + 1) % p_node->len ;
    }
    else
    {
        bRet = false ;
    }
    //
    return bRet ;
}
/*
 *
*/
uint8_t qUartbufferAvailable(qUartBuff_t *p_node)
{
    uint8_t u8Ret = 0 ;
    //
    if(p_node->wr_ptr == p_node->rd_ptr)     { u8Ret = 0 ; }
    else if(p_node->wr_ptr > p_node->rd_ptr) { u8Ret = (p_node->wr_ptr - p_node->rd_ptr) ; }
    else {
        u8Ret = ( p_node->len - p_node->rd_ptr) + p_node->wr_ptr ;
    }
    //
    return u8Ret ;
}
bool qUartbufferEmpty(qUartBuff_t *p_node)
{
    bool u8Ret = false ;
    //
    if(p_node->wr_ptr == p_node->rd_ptr)     { u8Ret = true ; }

    //
    return u8Ret ;
}
bool qUartbufferNotEmpty(qUartBuff_t *p_node)
{
    bool u8Ret = false ;
    //
    if(p_node->wr_ptr != p_node->rd_ptr)     { u8Ret = true ; }

    //
    return u8Ret ;
}
/*
 *
*/
void  qUartbufferSetEvent(qUartBuff_t *p_node)
{
    //p_node->event  = 1 ;
    p_node->event++ ;
}

void  qUartbufferClsEvent(qUartBuff_t *p_node)
{
    p_node->event  = 0 ;
}
uint8_t  qUartbufferGetEvent(qUartBuff_t *p_node)
{
    return p_node->event   ;
}
bool qUartbufferEvent(qUartBuff_t *p_node)
{
    bool bReseult =  false ;

    if(p_node->event  == 1 )  { bReseult = true; }
    else  { bReseult = false ; }
    //
    return bReseult ;
}

bool qUartbufferNotEvent(qUartBuff_t *p_node)
{
    bool bReseult =  false ;
    if(p_node->event  == 0 )  { bReseult = true; }
    else  { bReseult = false ; }
    //
    return bReseult ;
}
void  qUartbufferMTime(qUartBuff_t *p_node)
{
    if(p_node->time > 0 ) {  p_node->time-- ; }
}
uint8_t  qUartbufferIsTime(qUartBuff_t *p_node)
{
    return  p_node->time ;
}

/*
 *
*/
void  qUartbufferFlush(qUartBuff_t *p_node)
{
    p_node->rd_ptr = 0 ;
    p_node->wr_ptr = 0 ;
    p_node->count  = 0 ;
}



#pragma used- /* uartbuffer */