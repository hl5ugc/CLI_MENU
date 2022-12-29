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

#include "ConvertData.H"


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
static uint8_t HEX2BIN(uint8_t *pBuff);

// ---------------------------------------------------------------------------
// Declare your private variables here
// ---------------------------------------------------------------------------
//


// ---------------------------------------------------------------------------
//  Define Public function definitions.
// ---------------------------------------------------------------------------
//
/*
 * @brief
 *
 */
void cvtByte2DASC(uint8_t u8Data,uint8_t *pBuff)
{
    uint8_t u8Cal = 0 ;
    //
    if(u8Data > 99) { u8Data =  u8Data % 100 ;  }
    //
    u8Cal =  u8Data / 10 ;
    *pBuff = u8Cal + 0x30 ;
    pBuff++ ;
    //
    u8Cal =  u8Data % 10 ;
    *pBuff = u8Cal + 0x30 ;
}
/*
 * @brief
 *
 */
void cvtByte3DASC(uint8_t u8Data,uint8_t *pBuff)
{
    uint8_t u8Cal = 0 ;
    uint8_t u8Cal2 = 0 ;
    //
    u8Cal =  u8Data / 100 ;
    *pBuff = u8Cal + 0x30 ;
    pBuff++ ;
    //
    u8Cal =  u8Data % 100 ;
    u8Cal2 = u8Cal / 10 ;
    *pBuff = u8Cal2 + 0x30 ;
     pBuff++ ;
    //
    u8Cal2 =  u8Cal % 10 ;
    *pBuff = u8Cal2 + 0x30 ;
}
/*
 * @brief
 *
 */
void cvtWord3DASC(uint16_t u16Data,uint8_t *pBuff)
{
    uint8_t u8Cal = 0 ;
    uint8_t u8Cal2 = 0 ;
    //
    if(u16Data > 999) { u16Data =  u16Data % 1000 ;  }
    //
    u8Cal =  u16Data / 100 ;
    *pBuff = u8Cal + 0x30 ;
    pBuff++ ;
    //
    u8Cal =  u16Data % 100 ;
    u8Cal2 = u8Cal / 10 ;
    *pBuff = u8Cal2 + 0x30 ;
     pBuff++ ;
    //
    u8Cal2 =  u8Cal % 10 ;
    *pBuff = u8Cal2 + 0x30 ;
}
/*
 * @brief
 *
 */
void cvtWord4DASC(uint16_t u16Data,uint8_t *pBuff)
{
    uint8_t  u8Cal = 0 ;
    uint16_t u16Cal = 0 ;
    //
    if(u16Data > 999) { u16Data =  u16Data % 10000 ;  }
    //
    u8Cal =  u16Data / 1000 ;
    *pBuff = u8Cal + 0x30 ;
    pBuff++ ;
    //
    u16Cal =  u16Data % 1000 ;
    u8Cal = u16Cal / 100 ;
    *pBuff = u8Cal + 0x30 ;
     pBuff++ ;
    //
    u16Cal =  u16Cal % 100  ;
    u8Cal =  u16Cal / 10 ;
    *pBuff = u8Cal + 0x30 ;
     pBuff++ ;
    //
    u8Cal =  u16Cal % 10 ;
    *pBuff = u8Cal + 0x30 ;
}
/*
 * @brief
 *
 */
void cvtWord5DASC(uint16_t u16Data,uint8_t *pBuff)
{
    uint8_t  u8Cal = 0 ;
    uint16_t u16Cal = 0 ;
    //
    u8Cal  =  u16Data / 10000 ;
    *pBuff = u8Cal + 0x30 ;
    pBuff++ ;
    //
    u16Cal =  u16Data % 10000 ;
    u8Cal  = u16Cal / 1000 ;
    *pBuff = u8Cal + 0x30 ;
     pBuff++ ;
    //
    u16Cal =  u16Cal % 1000 ;
    u8Cal  =  u16Cal / 100 ;
    *pBuff = u8Cal + 0x30 ;
    pBuff++ ;
    //
    u16Cal =  u16Cal % 100 ;
    u8Cal  = u16Cal / 10 ;
    *pBuff = u8Cal + 0x30 ;
     pBuff++ ;
    //
    u8Cal =  u16Cal % 10 ;
    *pBuff = u8Cal + 0x30 ;
}
/*
 * @brief
 *
 */
void cvtByte2HEX(uint8_t u8Data,uint8_t *pBuff)
{
    uint8_t u8Cal = 0 ;
    //
    u8Cal =  (u8Data >> 4) & 0x0F ;
    if(u8Cal <= 9)  { *pBuff = u8Cal + 0x30U ; }
    else            { *pBuff = u8Cal + 0x37U ; }
    //
    pBuff++ ;
    u8Cal =  (u8Data  & 0x0F);
    if(u8Cal <= 9)  { *pBuff = u8Cal + 0x30U ; }
    else            { *pBuff = u8Cal + 0x37U ; }
}
/*
 * @brief
 *
 */
void cvtWord4HEX(uint16_t u16Data,uint8_t *pBuff)
{
    uint8_t u8Cal = 0 ;
    //
    u8Cal =  (u16Data >> 12) & 0x0F ;
    if(u8Cal <= 9)  { *pBuff = u8Cal + 0x30U ; }
    else            { *pBuff = u8Cal + 0x37U ; }
    //
    pBuff++ ;
    u8Cal =  (u16Data >> 8) & 0x0F ;
    if(u8Cal <= 9)  { *pBuff = u8Cal + 0x30U ; }
    else            { *pBuff = u8Cal + 0x37U ; }
    //
    pBuff++ ;
    u8Cal =  (u16Data >> 4) & 0x0F ;
    if(u8Cal <= 9)  { *pBuff = u8Cal + 0x30U ; }
    else            { *pBuff = u8Cal + 0x37U ; }
    //
    pBuff++ ;
    u8Cal =  (u16Data  & 0x0F);
    if(u8Cal <= 9)  { *pBuff = u8Cal + 0x30U ; }
    else            { *pBuff = u8Cal + 0x37U ; }
}
/*
 * @brief
 *
 */
void  cvtByte7BASC(uint8_t u8Data,uint8_t *pBuff)
{
    *pBuff = (((u8Data >> 7) & 0x01) + '0') ;  pBuff++ ;
    *pBuff = (((u8Data >> 6) & 0x01) + '0') ;  pBuff++ ;
    *pBuff = (((u8Data >> 5) & 0x01) + '0') ;  pBuff++ ;
    *pBuff = (((u8Data >> 4) & 0x01) + '0') ;  pBuff++ ;
    *pBuff = (((u8Data >> 3) & 0x01) + '0') ;  pBuff++ ;
    *pBuff = (((u8Data >> 2) & 0x01) + '0') ;  pBuff++ ;
    *pBuff = (((u8Data >> 1) & 0x01) + '0') ;  pBuff++ ;
    *pBuff = ((u8Data        & 0x01) + '0') ;
}

/**
 * @brief
 *
 * @param pBuff
 * @return uint8_t
 */
static uint8_t HEX2BIN(uint8_t *pBuff)
{
    uint8_t u8Cal = 0 ;
    uint8_t u8Caltemp = 0 ;

    u8Cal = *pBuff ;
    if(u8Cal < 0x3AU) { u8Cal = u8Cal - 0x30U; }
    else              { u8Cal = u8Cal - 0x37U; }
    u8Caltemp = ((u8Cal << 4 )  & 0xF0U ) ;
    pBuff++ ;
    //
    u8Cal = *pBuff ;
    if(u8Cal < 0x3AU) { u8Cal = u8Cal - 0x30U; }
    else              { u8Cal = u8Cal - 0x37U; }
    u8Caltemp = u8Caltemp +  u8Cal   ;
    //
    return u8Caltemp ;
}
/*
 * @brief
 *
 */
//
void cvt2HEXBin(uint8_t *pBuff , uint8_t *pData)
{
    uint8_t u8Cal = 0 ;
    uint8_t u8Len = 0 ;
    uint8_t u8Caltemp = 0 ;
    //
    u8Len = strlen(pBuff) ;

    if(u8Len == 2) {
        u8Cal = *pBuff ;
        if(u8Cal < 0x3AU) { u8Cal = u8Cal - 0x30U; }
        else              { u8Cal = u8Cal - 0x37U; }
        u8Caltemp = ((u8Cal << 4 )  & 0xF0U ) ;
        pBuff++ ;
        //
        u8Cal = *pBuff ;
        if(u8Cal < 0x3AU) { u8Cal = u8Cal - 0x30U; }
        else              { u8Cal = u8Cal - 0x37U; }
        u8Caltemp = u8Caltemp +  u8Cal   ;
    //
    }
    else if(u8Len == 1)
    {
        u8Cal = *pBuff ;
        if(u8Cal < 0x3AU) { u8Cal = u8Cal - 0x30U; }
        else              { u8Cal = u8Cal - 0x37U; }
        //
        u8Caltemp =  u8Cal  & 0x0F ;
    }
    else { u8Caltemp = 0 ; }
    //
    *pData =  u8Caltemp ;
}
/*
 * @brief
 *
 */
void  cvt4HEXBin(uint8_t *pBuff , uint16_t *pData)
{
    uint8_t  u8Cal = 0 ;
    uint8_t  u8Len = 0 ;
    uint16_t u16Caltemp = 0 ;
    //
    u8Len = strlen(pBuff) ;
    if(u8Len == 4)
    {
        u8Cal = *pBuff ;
        if(u8Cal < 0x3AU) { u8Cal = u8Cal - 0x30U; }
        else              { u8Cal = u8Cal - 0x37U; }
        u16Caltemp = (((uint16_t)u8Cal << 12)  & 0xF000U ) ;
        pBuff++ ;
        //
        u8Cal = *pBuff ;
        if(u8Cal < 0x3AU) { u8Cal = u8Cal - 0x30U; }
        else              { u8Cal = u8Cal - 0x37U; }
        u16Caltemp = u16Caltemp + (((uint16_t)u8Cal << 8)  & 0x0F00U ) ;
        pBuff++ ;
        //
        u8Cal = *pBuff ;
        if(u8Cal < 0x3AU) { u8Cal = u8Cal - 0x30U; }
        else              { u8Cal = u8Cal - 0x37U; }
        u16Caltemp = u16Caltemp + (((uint16_t)u8Cal << 4)  & 0x00F0U ) ;
        pBuff++ ;
        //
        u8Cal = *pBuff ;
        if(u8Cal < 0x3AU) { u8Cal = u8Cal - 0x30U; }
        else              { u8Cal = u8Cal - 0x37U; }
        u16Caltemp = u16Caltemp +  (uint16_t)u8Cal   ;
        //
    }
    else if(u8Len == 3)
    {
        //
        u8Cal = *pBuff ;
        if(u8Cal < 0x3AU) { u8Cal = u8Cal - 0x30U; }
        else              { u8Cal = u8Cal - 0x37U; }
        u16Caltemp = (((uint16_t)u8Cal << 8)  & 0x0F00U ) ;
        pBuff++ ;
        //
        u8Cal = *pBuff ;
        if(u8Cal < 0x3AU) { u8Cal = u8Cal - 0x30U; }
        else              { u8Cal = u8Cal - 0x37U; }
        u16Caltemp = u16Caltemp + (((uint16_t)u8Cal << 4)  & 0x00F0U ) ;
        pBuff++ ;
        //
        u8Cal = *pBuff ;
        if(u8Cal < 0x3AU) { u8Cal = u8Cal - 0x30U; }
        else              { u8Cal = u8Cal - 0x37U; }
        u16Caltemp = u16Caltemp +  (uint16_t)u8Cal   ;
        //
    }
    else if(u8Len == 2)
    {
        u8Cal = *pBuff ;
        if(u8Cal < 0x3AU) { u8Cal = u8Cal - 0x30U; }
        else              { u8Cal = u8Cal - 0x37U; }
        u16Caltemp = (((uint16_t)u8Cal << 4)  & 0x00F0U ) ;
        pBuff++ ;
        //
        u8Cal = *pBuff ;
        if(u8Cal < 0x3AU) { u8Cal = u8Cal - 0x30U; }
        else              { u8Cal = u8Cal - 0x37U; }
        u16Caltemp = u16Caltemp +  (uint16_t)u8Cal   ;
        //
    }
    else if(u8Len == 1)
    {
        u8Cal = *pBuff ;
        if(u8Cal < 0x3AU) { u8Cal = u8Cal - 0x30U; }
        else              { u8Cal = u8Cal - 0x37U; }
        u16Caltemp = (uint16_t)u8Cal   ;
        //
    }
    else { u16Caltemp = 0 ; }
    *pData =  u16Caltemp ;
}
/*
 * @brief
 *
 */
void  cvt6HEXBin(uint8_t *pBuff , uint32_t *pData)
{
    uint8_t  u8Cal = 0 ;
    uint8_t  u8Len = 0 ;
    cvt_u32_t u32Caltemp  ;
    //
    u32Caltemp.u32Val =  0 ;
    //
    u8Len = strlen(pBuff) ;
    //
    if(u8Len == 8)
    {
        u32Caltemp.u8Val.u8Data4 = HEX2BIN(&pBuff[0]);
        u32Caltemp.u8Val.u8Data3 = HEX2BIN(&pBuff[2]);
        u32Caltemp.u8Val.u8Data2 = HEX2BIN(&pBuff[4]);
        u32Caltemp.u8Val.u8Data1 = HEX2BIN(&pBuff[6]);
    }
    else if(u8Len == 6)
    {
        u32Caltemp.u8Val.u8Data4 = 0 ;
        u32Caltemp.u8Val.u8Data3 = HEX2BIN(&pBuff[0]);
        u32Caltemp.u8Val.u8Data2 = HEX2BIN(&pBuff[2]);
        u32Caltemp.u8Val.u8Data1 = HEX2BIN(&pBuff[4]);
    }
    else if(u8Len == 4)
    {
        u32Caltemp.u8Val.u8Data4 = 0 ;
        u32Caltemp.u8Val.u8Data3 = 0 ;
        u32Caltemp.u8Val.u8Data2 = HEX2BIN(&pBuff[0]);
        u32Caltemp.u8Val.u8Data1 = HEX2BIN(&pBuff[2]);
    }
    else if(u8Len == 2)
    {
        u32Caltemp.u8Val.u8Data4 = 0 ;
        u32Caltemp.u8Val.u8Data3 = 0 ;
        u32Caltemp.u8Val.u8Data2 = 0 ;
        u32Caltemp.u8Val.u8Data1 = HEX2BIN(&pBuff[0]);
    }
    else { u32Caltemp.u32Val = 0 ; }
    //
    *pData =  u32Caltemp.u32Val ;
}
/*
 * @brief
 *
 */

