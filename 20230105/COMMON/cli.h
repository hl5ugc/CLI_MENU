// =======================================================================
// [ PROJECT   ]
// -----------------------------------------------------------------------
// [ License   ] SAMJIN ELECTRONICS
// [ Author    ] Copyright 2021-08 By HAG-SEONG KANG
// [ E-MAIL    ] hl5ugc@nate.com (82)10- 3841-9706
// [ C  P  U   ]
// [ Compller  ] CodeWizardAVR V3.12 Professional
// [ Filename  ] CLI.H
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
#ifndef SRC_COMMON_HW_INCLUDE_CLI_H_
#define SRC_COMMON_HW_INCLUDE_CLI_H_


#include "HW_DEF.H"

#ifdef _USE_HW_CLI

#define CLI_CMD_LIST_MAX      HW_CLI_CMD_LIST_MAX
#define CLI_CMD_NAME_MAX      HW_CLI_CMD_NAME_MAX
#define CLI_HLP_STR_MAX       HW_CLI_HLP_NAME_MAX

#define CLI_LINE_HIS_MAX      HW_CLI_LINE_HIS_MAX
#define CLI_LINE_BUF_MAX      HW_CLI_LINE_BUF_MAX

//
#define _USE_CLI_BYTE           0
#define _USE_CLI_STR            1

typedef struct
{
  uint16_t   argc;
  char     **argv;

  int16_t  (*getData)(uint8_t index);
  int32_t  (*get32Data)(uint8_t index);
  char    *(*getStr)(uint8_t index);
  bool     (*isStr)(uint8_t index, char *p_str);

} cli_args_t;


bool cliInit(void);
bool cliOpen(uint8_t ch, uint16_t baud);
bool cliOpenLog(uint8_t ch, uint16_t baud);
bool cliMain(void);
void cliShowPrompt1(void) ;
//
//void cliPrintf(flash char *fmt, ...);
bool cliAdd(const char *cmd_str, const char *help_str,void (*p_func)(cli_args_t *)) ;
bool cliKeepLoop(void);

#endif




#endif /* SRC_COMMON_HW_INCLUDE_CLI_H_ */