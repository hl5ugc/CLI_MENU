//
// =======================================================================
// [ PROJECT   ]
// -----------------------------------------------------------------------
// [ License   ] SAMJIN ELECTRONICS
// [ Author    ] Copyright 2021-08 By HAG-SEONG KANG
// [ E-MAIL    ] hl5ugc@nate.com (82)10- 3841-9706
// [ C  P  U   ]
// [ Compller  ] CodeWizardAVR V3.12 Professional
// [ Filename  ] Cli.C
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

#include "Cli.H"
#include "Uart.H"


// ---------------------------------------------------------------------------
// Define basic
// ---------------------------------------------------------------------------
//
#define CLI_KEY_BACK              0x08U
#define CLI_KEY_DEL               0x7FU
#define CLI_KEY_ENTER             0x0DU
#define CLI_KEY_ESC               0x1BU
#define CLI_KEY_LEFT              0x44U
#define CLI_KEY_RIGHT             0x43U
#define CLI_KEY_UP                0x41U
#define CLI_KEY_DOWN              0x42U
#define CLI_KEY_HOME              0x31U
#define CLI_KEY_END               0x34U
//
#define CLI_PROMPT_STR            "TMS # "
// ---------------------------------------------------------------------------
//  Define typedef & Struct
// ---------------------------------------------------------------------------
//
enum
{
  CLI_RX_IDLE,
  CLI_RX_SP1,
  CLI_RX_SP2,
  CLI_RX_SP3,
  CLI_RX_SP4,
};

typedef struct
{
  uint8_t   buf[CLI_LINE_BUF_MAX] ;
  uint8_t   buf_len ;
  uint8_t   cursor ;
  uint8_t   count ;

} cli_line_t;

typedef struct
{
  uint8_t       ch;
  uint16_t      baud;
  bool          is_open;
  bool          is_log;
  uint8_t       log_ch;
  uint16_t      log_baud;
  uint8_t       state;

  bool          hist_line_new;
  int8_t        hist_line_i;
  uint8_t       hist_line_last;
  uint8_t       hist_line_count;

  cli_line_t    line_buf[CLI_LINE_HIS_MAX];
  cli_line_t    line ;
} cli_t;

cli_t   cli_node ;
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
static bool cliUpdate(cli_t *p_cli, uint8_t rx_data);
static void cliLineClean(cli_t *p_cli);
static void cliLineAdd(cli_t *p_cli);
static void cliLineChange(cli_t *p_cli, int8_t key_up);
static void cliShowPrompt(cli_t *p_cli);
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
bool cliInit(void)
{
    cli_node.is_open = false ;
    cli_node.is_log  = false ;
    cli_node.state  = CLI_RX_IDLE ;
    //
    cli_node.hist_line_i     = 0 ;
    cli_node.hist_line_last  = 0 ;
    cli_node.hist_line_count = 0 ;
    cli_node.hist_line_new   = false  ;
    //
    cliLineClean(&cli_node);
}
/*
 *
 */
bool cliOpen(uint8_t ch, uint16_t u16Baud)
{
    cli_node.ch = ch ;
    cli_node.baud =  u16Baud ;
    //
    cli_node.is_open = uartOpen(ch,u16Baud);
    //
    return cli_node.is_open ;
}
/*
 *
 */
bool cliOpenLog(uint8_t ch, uint16_t u16Baud)
{
    uint8_t bRet ;
    //
    cli_node.log_ch = ch ;
    cli_node.log_baud =  u16Baud ;
    //
    bRet = uartOpen(ch,u16Baud) ;
    if(bRet == true)
    {
        cli_node.is_log = true ;
    }
    //
    return bRet ;
}
bool cliLogClose(void)
{
    cli_node.is_log = false;
    return true;
}
/*
 *
 */
void cliShowLog(cli_t *p_cli)
{
    uint8_t u8Loop ;
    uint8_t u8Len ;
    //
    if(cli_node.is_log == true)
    {
        uartMsgByte2ASC(p_cli->log_ch,"\nCount  : ", p_cli->line.count);
        uartMsgByte2ASC(p_cli->log_ch,"\ncursor: ", p_cli->line.cursor);
        u8Len = strlen(p_cli->line.buf);
        uartMsgByte2ASC(p_cli->log_ch,"\nBuf_len: ", u8Len);
        uartMsgStr(p_cli->log_ch,"\nBuf: ", p_cli->line.buf);
        //
        if( p_cli->line.cursor == 0x00)
        {
            uartMsgByte2ASC(p_cli->log_ch,"\nLine_i : ", p_cli->hist_line_i);
            uartMsgByte2ASC(p_cli->log_ch,"\nLine_lt  : ", p_cli->hist_line_last);
            uartMsgByte2ASC(p_cli->log_ch,"\nBuf_len: ", p_cli->hist_line_count);
            //
            for(u8Loop = 0 ; u8Loop < p_cli->hist_line_count; u8Loop++)
            {
                 uartMsgByte2ASC(p_cli->log_ch,"\nbuf ", u8Loop);
                 uartMsgStr(p_cli->log_ch, " : ", p_cli->line_buf[u8Loop].buf);
            }
            uartMsg(p_cli->log_ch,"\n\n");
        }
    }
}
/*
 *
 */
static void cliShowPrompt(cli_t *p_cli)
{
    uartMsg(p_cli->ch,"\n\r");
    uartMsg(p_cli->ch,CLI_PROMPT_STR);

}
/*
 *
 */
void cliShowPrompt1(void)
{
    uartFMsg(1,"\n\rTMS #");
}
/*
 *
 */
bool cliMain(void)
{
    if (cli_node.is_open != true)
    {
        return false;
    }
    if(uartAvailable(cli_node.ch) > 0)
    {

        cliUpdate(&cli_node, uartRead(cli_node.ch));
    }
    //
    return true;
}
/**
 * @brief   New Recive Data save to Buff
 *
 * @param   p_cli   : handle
 * @param   rx_data : new rx bytedata
 * @return  true    : save ok
 * @return  false
 */
bool cliUpdate(cli_t *p_cli, uint8_t rx_data)
{
    bool    bRet = false ;
    uint8_t tx_buf[8] ;
    uint8_t u8i = 0 ;
    uint8_t u8mov_Len = 0 ;
    cli_line_t *line ;
    //
    line = &p_cli->line ;
    //
    if(p_cli->state == CLI_RX_IDLE)
    {
        switch(rx_data)
        {
            case CLI_KEY_ENTER :

                        if(line->count > 0)  { cliLineAdd(p_cli) ; }
                        //
                        line->count  = 0 ;
                        line->cursor = 0 ;
                        line->buf[0] = 0 ;
                        //
                        cliShowPrompt(p_cli) ;
                        break ;

            case CLI_KEY_ESC :

                        p_cli->state = CLI_RX_SP1 ;
                        break ;

            case CLI_KEY_DEL :

                        if(line->cursor < line->count)
                        {
                            u8mov_Len =  line->count - line->cursor ;
                            for(u8i = 0 ; u8i <u8mov_Len ; u8i++)
                            {
                                line->buf[line->cursor + u8i - 1] = line->buf[line->cursor + u8i] ;
                            }
                            //
                            line->count-- ;
                            line->buf[line->count] = 0 ;
                            //
                            uartMsg(p_cli->ch,"\x1B[1P");
                        }
                        break ;

            case CLI_KEY_BACK :

                        if((line->count > 0) && (line->cursor > 0))
                        {
                            if(line->count == line->cursor)
                            {
                                line->count-- ;
                                line->buf[line->count] = 0 ;
                            }
                            //
                            if(line->cursor < line->count)
                            {
                                u8mov_Len =  line->count - line->cursor ;
                                for(u8i = 0 ; u8i <u8mov_Len ; u8i++)
                                {
                                    line->buf[line->cursor + u8i - 1] = line->buf[line->cursor + u8i] ;
                                }
                                //
                                line->count-- ;
                                line->buf[line->count] = 0 ;
                            }
                        }
                        //
                        if(line->cursor > 0)
                        {
                            line->cursor-- ;
                            uartMsg(p_cli->ch,"\b \b\x1B[1P");
                        }
                        break ;

            default :
                        if((line->count +1) < line->buf_len) // check max buff
                        {
                            if(line->cursor == line->count)  // last in check
                            {
                                uartMsgWrite(p_cli->ch,&rx_data,1);
                                //
                                line->buf[line->cursor] = rx_data ;
                                line->count++ ;
                                line->cursor++ ;
                                line->buf[line->cursor] = 0 ;
                            }
                            //
                            if(line->cursor < line->count) //
                            {
                                u8mov_Len =  line->count - line->cursor ;
                                //  DATA SHIFT FOR RX DATA INSERT
                                for(u8i = 0 ; u8i <u8mov_Len ; u8i++)
                                {
                                    line->buf[line->count - u8i] = line->buf[line->count - u8i - 1] ;
                                }
                                //
                                line->buf[line->cursor] = rx_data ;
                                line->cursor++ ;
                                line->count++ ;
                                line->buf[line->count] = 0 ;
                                //
                                uartMsg(p_cli->ch,"\x1B[4h");
                                uartMsgWrite(p_cli->ch,&rx_data,1);
                                uartMsg(p_cli->ch,"\x1B[4l");
                            }
                        }
                        break ;
        }
    }
    //
    switch(p_cli->state)
    {
        case CLI_RX_SP1 :
                            p_cli->state = CLI_RX_SP2 ;
                            break ;

        case CLI_RX_SP2 :

                            p_cli->state = CLI_RX_SP3 ;
                            break ;

        case CLI_RX_SP3 :
                            p_cli->state = CLI_RX_IDLE ;

                            if(rx_data == CLI_KEY_LEFT)
                            {
                                if (line->cursor > 0)
                                {
                                    line->cursor-- ;
                                    tx_buf[0] = 0x1B;
                                    tx_buf[1] = 0x5B;
                                    tx_buf[2] = rx_data;
                                    uartMsgWrite(p_cli->ch, &tx_buf[0], 3);
                                }
                            }
                            else if(rx_data == CLI_KEY_RIGHT)
                            {
                                if (line->cursor < line->buf_len) { line->cursor++ ; }
                                //
                                tx_buf[0] = 0x1B;
                                tx_buf[1] = 0x5B;
                                tx_buf[2] = rx_data;
                                uartMsgWrite(p_cli->ch, &tx_buf[0], 3) ;
                            }
                            else if(rx_data == CLI_KEY_UP)
                            {
                                cliLineChange(p_cli, true);
                                uartMsg(p_cli->ch, (char *)p_cli->line.buf);
                            }
                            else if(rx_data == CLI_KEY_DOWN)
                            {
                                cliLineChange(p_cli, false);
                                uartMsg(p_cli->ch, (char *)p_cli->line.buf);
                            }
                            else if(rx_data == CLI_KEY_HOME)
                            {
                                uartMsgByte2ASC(p_cli->ch,"\x1B[",line->cursor);
                                uartMsg(p_cli->ch,"D");
                                line->cursor = 0 ;
                                p_cli->state = CLI_RX_SP4 ;
                            }
                            else if(rx_data == CLI_KEY_END)
                            {
                                if(line->cursor < line->count)
                                {
                                    u8mov_Len =  line->count - line->cursor ;
                                    uartMsgByte2ASC(p_cli->ch,"\x1B[",u8mov_Len);
                                    uartMsg(p_cli->ch,"C");
                                }
                                else  if(line->cursor > line->count)
                                {
                                    u8mov_Len =  line->cursor - line->count ;
                                    uartMsgByte2ASC(p_cli->ch,"\x1B[",u8mov_Len);
                                    uartMsg(p_cli->ch,"D");
                                }
                                //
                                line->cursor = line->count ;
                                p_cli->state = CLI_RX_SP4 ;
                            }
                            break ;
        case CLI_RX_SP4 :

                            p_cli->state = CLI_RX_IDLE ;
                            break  ;
    }
    //
    cliShowLog(p_cli);
    //
    return bRet ;
}
/**
 * @brief   CLI LINE Data Clear
 *
 * @param   p_cli
 */
void cliLineClean(cli_t *p_cli)
{
    p_cli->line.count   = 0 ;
    p_cli->line.cursor  = 0 ;
    p_cli->line.buf_len = CLI_LINE_BUF_MAX - 1 ;
    p_cli->line.buf[0]  = 0 ;
}
/**
 * @brief   CLI 1 LINE Add
 *
 * @param   p_cli
 */
void cliLineAdd(cli_t *p_cli)
{
    p_cli->line_buf[p_cli->hist_line_last] = p_cli->line ;
    //
    if(p_cli->hist_line_count < CLI_LINE_HIS_MAX) { p_cli->hist_line_count++; }
    //
    p_cli->hist_line_i    = p_cli->hist_line_last ;
    p_cli->hist_line_last = (p_cli->hist_line_last + 1) % CLI_LINE_HIS_MAX ;
    p_cli->hist_line_new  = true ;
}
 /**
 * @brief
 *
 * @param p_cli
 * @param key_up
 */
void cliLineChange(cli_t *p_cli, int8_t key_up)
{
    uint8_t u8Change_i ;
    //
    if(p_cli->hist_line_count == 0) { return ; }
    //
    if(p_cli->line.cursor > 0)
    {
        uartMsgByte2ASC(p_cli->ch,"\x1B[",p_cli->line.cursor);
        uartMsg(p_cli->ch,"D");
    }
    if(p_cli->line.count > 0)
    {
        uartMsgByte2ASC(p_cli->ch,"\x1B[",p_cli->line.count);
        uartMsg(p_cli->ch,"P");
    }
    //
    if(key_up == true)
    {
        if(p_cli->hist_line_new  == true )
        {
            p_cli->hist_line_i = p_cli->hist_line_last ;
        }
        //
        p_cli->hist_line_i =  (p_cli->hist_line_i + p_cli->hist_line_count - 1) % p_cli->hist_line_count ;
        u8Change_i = p_cli->hist_line_i ;
    }
    else {

        p_cli->hist_line_i = (p_cli->hist_line_i + 1) % p_cli->hist_line_count ;
        u8Change_i = p_cli->hist_line_i ;
    }
    //
    p_cli->line = p_cli->line_buf[u8Change_i] ;
    p_cli->line.cursor = p_cli->line.count ;
    //
    p_cli->hist_line_new  = false ;
}

#pragma used- /* CLI */