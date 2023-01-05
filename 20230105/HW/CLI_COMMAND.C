//
// =======================================================================
// [ PROJECT   ]
// -----------------------------------------------------------------------
// [ License   ] SAMJIN ELECTRONICS
// [ Author    ] Copyright 2021-08 By HAG-SEONG KANG
// [ E-MAIL    ] hl5ugc@nate.com (82)10- 3841-9706
// [ C  P  U   ]
// [ Compller  ] CodeWizardAVR V3.12 Professional
// [ Filename  ] Cli_COMMAND.C
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

#include "Cli_COMMAND.H"
#include "Uart.H"
#include "ConvertData.H"

// ---------------------------------------------------------------------------
// Define basic
// ---------------------------------------------------------------------------
//
//
#define CLI_CTRL_B              2
#define CLI_CTRL_C              3
#define CLI_CTRL_F              6
#define CLI_EOL                 '\0'
//
#define CLI_KEY_ENTER           '\r'
#define CLI_KEY_BS              '\b'
#define CLI_KEY_ESC             0x1BU
#define CLI_KEY_ESC2            '['
#define CLI_KEY_DELIMIT         '~'
#define CLI_KEY_DELETE          0x7FU
#define CLI_KEY_UP              'A'
#define CLI_KEY_DOWN            'B'
#define CLI_KEY_RIGHT           'C'
#define CLI_KEY_LEFT            'D'
#define CLI_KEY_HOME            '1'
#define CLI_KEY_END             '4'
//
#define CLI_CMD_BUF_SIZE         32
static char command_buf[CLI_CMD_BUF_SIZE];
// ---------------------------------------------------------------------------
//  Define typedef & Struct
// ---------------------------------------------------------------------------
//
typedef struct
{
  char   cmd_str[CLI_CMD_NAME_MAX];
  char   help_str[CLI_HLP_STR_MAX];
  void  (*cmd_func)(cli_args_t *);

} cli_cmd_t;
//
typedef struct
{
  uint8_t       ch;
  uint16_t      baud;
  bool          is_open;
  //
  uint8_t       argc;
  char          *argv[CLI_ARGS_MAX];
  //
  char          command_buf[CLI_CMD_BUF_SIZE];
  //
  uint8_t       cmd_count;
  cli_cmd_t     cmd_list[CLI_CMD_LIST_MAX];
  cli_args_t    cmd_args;
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


// ---------------------------------------------------------------------------
//  Define private function definitions.
// ---------------------------------------------------------------------------
//
static void cliToUpper(uint8_t *str);
static bool cliRunCmd(cli_t *p_cli);
static bool cliParseArgs(cli_t *p_cli);
//
//
static uint8_t  cliArgsGetData(uint8_t index);
static uint8_t  cliArgsGetHEXData(uint8_t index);
static uint16_t cliArgsGetHEX16Data(uint8_t index);
//
static uint8_t *cliArgsGetStr(uint8_t index);
static bool     cliArgsIsStr(uint8_t index, char *p_str);
static void     cb_cliShowList(cli_args_t *args);
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
    cli_node.ch = CLI_COMMAND_UART ;
    cli_node.baud  = 38400 ;
    cli_node.command_buf[0] =  CLI_EOL ;
    //;
    cli_node.cmd_args.getData   = cliArgsGetHEXData ; // cliArgsGetData ;
    cli_node.cmd_args.get16Data = cliArgsGetHEX16Data ;
    cli_node.cmd_args.getStr    = cliArgsGetStr ;
    cli_node.cmd_args.isStr     = cliArgsIsStr ;
    //
    // init function
    cliAdd("help"," ",cb_cliShowList);
    return true ;
}
void Cli_CMD_Open(void)
{
    cliInit() ;
    uartOpen(cli_node.ch,cli_node.baud) ;
}
/*
 *
 */
void cliShowPrompt(void)
{
    uartMsg(CLI_COMMAND_UART,"\n\r");
    uartMsg(CLI_COMMAND_UART,CLI_PROMPT_STR);

}

/**
 * @brief
 *
 * @param p_cli
 * @return true
 * @return false
 */
bool cliRunCmd(cli_t *p_cli)
{
    bool bRet = false ;
    uint8_t u8I ;
    //
    if(cliParseArgs(p_cli) == true)
    {
        //uartMsg(_DEF_UART1,"\r\n");  // cliPrintf
        //uartMsgByte2ASC(_DEF_UART1,"Argc ", p_cli->argc );
        if( p_cli->argc >= 1 )
        {
            cliToUpper(p_cli->argv[0]);
            //
            if( p_cli->argc >= 1 ) {
                cliToUpper(p_cli->argv[1]);
            }
        }
        //
        for(u8I = 0 ; u8I <  p_cli->cmd_count  ; u8I++)
        {
            if(strcmp(p_cli->argv[0],p_cli->cmd_list[u8I].cmd_str) == 0)
            {
                p_cli->cmd_args.argc = p_cli->argc - 1 ;
                p_cli->cmd_args.argv = &p_cli->argv[1] ; // 2중 포인터
                p_cli->cmd_list[u8I].cmd_func(&p_cli->cmd_args);
            }
        }
    }
    //
    return bRet ;
}
/**
 * @brief
 *
 * @param p_cli
 * @return true
 * @return false
 */
bool cliParseArgs(cli_t *p_cli)
{
    bool bRet = false ;
    char *tok ;
    char *next_ptr ;
    uint8_t argc = 0 ;
    //
    flash char *delim = " "  ;
    char *cmdline ;
    char **argv ;
    //
    p_cli->argc = 0 ;
    cmdline =  (char *)p_cli->command_buf ;
    argv =  p_cli->argv ;
    argv[argc] = NULL ;
    //
    tok = strtok(cmdline,delim);
    if(tok == NULL)
    {
        return ;
    }
    while( tok != NULL)
    {
        argv[argc++] = tok ;
        tok = strtok(NULL," ");

    }
    p_cli->argc = argc ;
    //
    if(argc > 0)
    {
        bRet = true ;
    }
    return bRet ;

}
void wait_Command(void)
{
    // uint8_t *cp = command_buf ;
    uint8_t *cp = cli_node.command_buf ;
    uint8_t *end_cp ;
    uint8_t u8Ch ;
    uint8_t u8Len ;
    uint8_t u8i ;
    //
    *cp =  CLI_EOL ;
    //
    cliShowPrompt();
    //
    while(1)
    {
        u8Ch = uartGetc(CLI_COMMAND_UART) ;
        //
        switch(u8Ch)
        {
            case CLI_KEY_ENTER :
                    //
                    //uartMsg(CLI_COMMAND_UART,cli_node.command_buf);
                    //uartMsg(CLI_COMMAND_UART,"\n");
                    cliRunCmd(&cli_node);
                    //return  command_buf  ;
                    return ;
                    break ;

            case CLI_KEY_BS :
                    if(cp > command_buf)
                    {
                        uartMsg(CLI_COMMAND_UART,"\b\x1B[K");
                        //
                        if(*cp)
                        {
                            u8Len = strlen(--cp) ;
                            for(u8i = 0 ; u8i < u8Len ; u8i++)  { cp[u8i] = cp[u8i+1] ; }
                            uartMsg(CLI_COMMAND_UART,cp);
                            uartMsgByte2ASC(CLI_COMMAND_UART,"\x1B[", (u8Len-1));
                            uartMsg(CLI_COMMAND_UART,"D");
                        }
                        else {
                            *(--cp) =  CLI_EOL ;
                        }
                    }
                    break ;

            case CLI_KEY_DELETE :
                    if(*cp)
                    {
                        u8Len = strlen(cp) ;
                        for(u8i = 0 ; u8i < u8Len ; u8i++)  { cp[u8i] = cp[u8i+1] ; }
                        cp[u8i+1] = CLI_EOL ;
                        uartMsg(CLI_COMMAND_UART,"\x1B[K");
                        uartMsg(CLI_COMMAND_UART,cp);
                        uartMsgByte2ASC(CLI_COMMAND_UART,"\x1B[",(u8Len-1));
                        uartMsg(CLI_COMMAND_UART,"D");
                    }
                    break ;

            case CLI_CTRL_B :
                    u8i = 0 ;
                    //
                    if (cp > cli_node.command_buf)
                    {
                        --cp ;
                        u8i++ ;
                        //
                        while((cp > cli_node.command_buf) && (*cp == ' '))
                        {
                            --cp ;
                            u8i++ ;
                        }
                        while((cp > cli_node.command_buf) && (*cp != ' '))
                        {
                            --cp ;
                            u8i++ ;
                        }
                        //
                        ++cp ;
                        --u8i ;
                        //
                        // printf("\x1B[%uD", i)
                        uartMsgByte2ASC(CLI_COMMAND_UART,"\x1B[",u8i);
                        uartMsg(CLI_COMMAND_UART,"D");
                    }
                    break ;

            case CLI_CTRL_C :
                    cli_node.command_buf[0] = CLI_EOL ;
                    uartMsg(CLI_COMMAND_UART,"\n");
                    //return  &command_buf[0] ;
                    break ;
            case CLI_CTRL_F :
                    u8i = 0 ;
                    end_cp = cli_node.command_buf + strlen(cli_node.command_buf) ;
                    //
                    if(cp < end_cp)
                    {
                        while((cp < end_cp) && ( *cp != ' '))
                        {
                            ++cp ;
                            u8i++ ;
                        }
                        while((cp < end_cp) && ( *cp == ' '))
                        {
                            ++cp ;
                            u8i++ ;
                        }
                        if(u8i > 0) {
                            // printf("\x1B[%uC", i);
                            uartMsgByte2ASC(CLI_COMMAND_UART,"\x1B[",u8i);
                            uartMsg(CLI_COMMAND_UART,"C");
                        }
                    }
                    break ;

            case CLI_KEY_ESC :  // special key
                    if(uartGetc(CLI_COMMAND_UART) != CLI_KEY_ESC2) { break ; }
                    //
                    switch(uartGetc(CLI_COMMAND_UART))
                    {
                        case CLI_KEY_UP :       break ;
                        case CLI_KEY_DOWN :     break ;
                        case CLI_KEY_RIGHT :
                                if(cp < (cli_node.command_buf + strlen(cli_node.command_buf)))
                                {
                                    ++cp ;
                                    //puts("\x1B[C");
                                    uartMsg(CLI_COMMAND_UART,"\x1B[C");
                                }
                                break ;
                        case CLI_KEY_LEFT :
                                if(cp > cli_node.command_buf )
                                {
                                    --cp ;
                                    //puts("\x1B[D");
                                    uartMsg(CLI_COMMAND_UART,"\x1B[D");
                                }
                                break ;

                        case '1' :
                                u8Ch = uartGetc(CLI_COMMAND_UART) ;
                                //
                                if(u8Ch ==  CLI_KEY_DELIMIT)    // home key
                                {
                                    u8Len = cp - cli_node.command_buf ;
                                    if(u8Len > 0)
                                    {
                                        // printf("\x1B[%uD", len);
                                        uartMsgByte2ASC(CLI_COMMAND_UART,"\x1B[",u8Len);
                                        uartMsg(CLI_COMMAND_UART,"D");
                                        cp = cli_node.command_buf;
                                    }
                                    break ;
                                }
                                //
                                if( uartGetc(CLI_COMMAND_UART) !=  CLI_KEY_DELIMIT) { break ; }
                                //
                                switch(u8Ch)
                                {
                                    case '1' :  // KEY_F1 ;
                                                break ;
                                    case '2' :  // KEY_F2 ;
                                                break ;
                                    case '3' :  // KEY_F3 ;
                                                break ;
                                    case '4' :  // KEY_F4 ;
                                                break ;
                                    case '5' :  // KEY_F5 ;
                                                break ;
                                    case '7' :  // KEY_F6 ;
                                                break ;
                                    case '8' :  // KEY_F7 ;
                                                break ;
                                    case '9' :  // KEY_F8 ;
                                                break ;
                                }
                        case '2' :
                                u8Ch = uartGetc(CLI_COMMAND_UART) ;
                                //
                                if(u8Ch == CLI_KEY_DELIMIT) {  break; } // KEY_INS;
                                if(uartGetc(CLI_COMMAND_UART) != CLI_KEY_DELIMIT) { break ; }
                                //
                                switch (u8Ch)
                                {
                                    case '0':   // KEY_F9;
                                                break;

                                    case '1':   // KEY_F10;
                                                break;

                                    case '3':   // KEY_F11;
                                                break;

                                    case '4':   // KEY_F12;
                                                break;
                                }
                                break;
                        case '4':   // KEY_END;
                                if(uartGetc(CLI_COMMAND_UART) == CLI_KEY_DELIMIT)
                                {
                                    u8Len = strlen(cp);
                                    if (u8Len)
                                    {
                                        //printf("\x1B[%uC", len);
                                        //
                                        uartMsgByte2ASC(CLI_COMMAND_UART,"\x1B[",u8Len);
                                        uartMsg(CLI_COMMAND_UART,"C");
                                        cp += u8Len;
                                    }
                                }
                                break;

                        case '5':   // KEY_PGUP;
                                if(uartGetc(CLI_COMMAND_UART) == CLI_KEY_DELIMIT)
                                {
                                }
                                break;

                        case '6':   // KEY_PGDN;
                                if(uartGetc(CLI_COMMAND_UART) == CLI_KEY_DELIMIT)
                                {
                                }
                                break;
                    }
                    break ;

            default :
                    if(strlen(command_buf) < (CLI_CMD_BUF_SIZE - 1))
                    {
                        if(*cp)
                        {
                            u8Len = strlen(cp) ;
                            for(u8i = (u8Len+1) ;u8i ; u8i--)
                            {
                                cp[u8i] = cp[u8i-1] ;
                            }
                            //
                            *cp = u8Ch ;
                            /*
                            puts("\x1B[K");
                            puts(cp);
                            printf("\x1B[%uD", len);
                            */
                            uartMsg(CLI_COMMAND_UART,"\x1B[K");
                            uartMsg(CLI_COMMAND_UART,cp);
                            uartMsgByte2ASC(CLI_COMMAND_UART,"\x1B[",u8Len);
                            uartMsg(CLI_COMMAND_UART,"D");
                            //uartMsg(_DEF_UART1,"D");
                            //
                            ++cp ;
                        }
                        else {
                            *cp++ = u8Ch ;
                            *cp = CLI_EOL ;
                            //
                            uartMsgWrite(CLI_COMMAND_UART,&u8Ch,1);
                            //uartMsg(_DEF_UART1,cli_node.command_buf);
                            //uartMsg(_DEF_UART1,"\n");
                        }
                    }
                    break ;
        } // switch
    }  //  while
    //
    //return command_buf ;

}

/**
 * @brief
 *
 * @param   cmd_str
 * @param   p_func
 * @return  true
 * @return  false
 */
bool cliAdd(const char *cmd_str, const char *help_str,void (*p_func)(cli_args_t *))
{
    bool ret = true;
    cli_t *p_cli = &cli_node;
    uint16_t index;

    if (p_cli->cmd_count >= CLI_CMD_LIST_MAX)
    {
        return false;
    }

    index = p_cli->cmd_count;
    //
    strcpy(p_cli->cmd_list[index].cmd_str, cmd_str);
    strcpy(p_cli->cmd_list[index].help_str, help_str);
    p_cli->cmd_list[index].cmd_func = p_func;
    //
    cliToUpper(p_cli->cmd_list[index].cmd_str);
    //
    p_cli->cmd_count++;
    //
    return ret;
}
/**
 * @brief   abcd to ABCD Convert
 *
 * @param str
 */
void cliToUpper(char *str)
{
    uint8_t u8I ;
    uint8_t u8Str_ch ;
    //
    for(u8I = 0 ; u8I < CLI_CMD_NAME_MAX ; u8I++)
    {
        u8Str_ch = str[u8I] ;
        if(u8Str_ch == 0x00) { break ; }
        //
        if((u8Str_ch >= 'a') && (u8Str_ch <= 'z'))
        {
            u8Str_ch = (u8Str_ch - 'a')  + 'A' ;
        }
        str[u8I] =  u8Str_ch ;
        //
        if(u8I == CLI_CMD_NAME_MAX) { str[u8I] = 0x00 ; }
    }
}
/**
 * @brief   arg data convert to uint16
 *
 * @param   index
 * @return  int16_t
 */
uint8_t cliArgsGetData(uint8_t index)
{
    uint16_t u8Ret = 0 ;
    cli_t *p_cli = &cli_node ;
    //
    if(index >= p_cli->cmd_args.argc) { return 0 ; }
    //u16Ret = (int16_t)strtoul((const char * ) p_cli->cmd_args.argv[index], (char **)NULL, (int) 0);
    return  u8Ret ;
}

/**
 * @brief   Hex Ascii String To 8bit data Converion
 *
 * @param   index       string buffer index
 * @return  uint8_t     return hex ascii to bin
 */
static uint8_t  cliArgsGetHEXData(uint8_t index)
{
    uint8_t u8Ret = 0 ;
    cli_t *p_cli = &cli_node ;
    uint8_t *pHexStr = NULL ;
    uint8_t u8Len = 0 ;
    //
    if(index < p_cli->cmd_args.argc)
    {
        pHexStr = p_cli->cmd_args.argv[index] ;
        //
        u8Len = strlen(pHexStr) ;
        //
        cliToUpper(pHexStr) ;
        //

        if((u8Len == 2 ) || (u8Len == 1) )
        {
            cvt2HEXBin(pHexStr,&u8Ret) ;
        }
    }
    //
    return  u8Ret ;
}

/**
 * @brief   Hex Ascii String To 16bit data Converion
 *
 * @param   index       string buffer index
 * @return  uint16_t    return hex ascii to bin
 */
static uint16_t  cliArgsGetHEX16Data(uint8_t index)
{
    uint16_t u16Ret = 0 ;
    cli_t *p_cli = &cli_node ;
    char *pHexStr = NULL ;
    uint8_t u8Len = 0 ;
    //
    if(index < p_cli->cmd_args.argc)
    {
        pHexStr = p_cli->cmd_args.argv[index] ;
        //
        u8Len = strlen(pHexStr) ;
        //
        cliToUpper(pHexStr) ;
        //
        if((u8Len == 4 ) || (u8Len == 3))
        {
            cvt4HEXBin(pHexStr,&u16Ret) ;
        }
        else if((u8Len == 2 ) || (u8Len == 1) )
        {
            cvt2HEXBin(pHexStr,&u8Len) ;
            u16Ret = u8Len ;
        }
    }
    //
    return  u16Ret ;
}
//

char *cliArgsGetStr(uint8_t index)
{
    char *ret = NULL;
    cli_t *p_cli = &cli_node;
    //
    if (index >= p_cli->cmd_args.argc)
    {
        return 0;
    }
    //
    ret = p_cli->cmd_args.argv[index];
    //
    return ret;
}
//
//  args->isStr(0, "toggle") == true
//
bool cliArgsIsStr(uint8_t index, char *p_str)
{
    bool ret = false;
    cli_t *p_cli = &cli_node;
    //
    if (index >= p_cli->cmd_args.argc)
    {
        return 0;
    }
    //
    if(strcmp(p_str, p_cli->cmd_args.argv[index]) == 0)
    {
        ret = true;
    }
    //
    return ret;
}
bool cliKeepLoop(void)
{
    cli_t *p_cli = &cli_node;

    if (uartAvailable(p_cli->ch) == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void cb_cliShowList(cli_args_t *args)
{
    uint8_t i = 0 ;
    cli_t *p_cli = &cli_node;
    //
    uartMsg(p_cli->ch,"\r\n");
    uartMsg(p_cli->ch,"--------------- cmd list --------------\r\n");
    delay_ms(50);
    //
    for ( i=0; i<p_cli->cmd_count; i++)
    {
        uartMsg(p_cli->ch,p_cli->cmd_list[i].cmd_str);
        uartMsg(p_cli->ch," ");
        delay_ms(50);
        uartMsg(p_cli->ch,p_cli->cmd_list[i].help_str);
        uartMsg(p_cli->ch,"\r\n");
        delay_ms(50);
    }
    //
    uartMsg(p_cli->ch,"---------------------------------------\r\n");
}

#pragma used- /* CLI */