// =======================================================================
// [ PROJECT   ]
// -----------------------------------------------------------------------
// [ License   ] SAMJIN ELECTRONICS
// [ Author    ] Copyright 2021-08 By HAG-SEONG KANG
// [ E-MAIL    ] hl5ugc@nate.com (82)10- 3841-9706
// [ C  P  U   ]
// [ Compller  ] CodeWizardAVR V3.12 Professional
// [ Filename  ] CLI_COMMAND.H
// [ Version   ] 1.0
// [ Created   ] 2023-01-0
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
#ifndef SRC_COMMON_HW_INCLUDE_CLI_COMMAND_H_
#define SRC_COMMON_HW_INCLUDE_CLI_COMMAND_H_


#include "HW_DEF.H"

#ifdef _USE_HW_CLI_COMMAND

#define CLI_CMD_LIST_MAX            HW_CLI_CMD_LIST_MAX
#define CLI_CMD_NAME_MAX            HW_CLI_CMD_NAME_MAX
#define CLI_HLP_STR_MAX             HW_CLI_HLP_NAME_MAX
//
#define CLI_PROMPT_STR              "Cli:> "
#define CLI_ARGS_MAX                32
#define CLI_PRINT_BUF_MAX           256

//
typedef struct
{
  uint8_t       argc;
  uint8_t          **argv;

  uint8_t       (*getData)(uint8_t index);
  uint16_t      (*get16Data)(uint8_t index);
  char         *(*getStr)(uint8_t index);
  bool  (*isStr)(uint8_t index, uint8_t *p_str);

} cli_args_t;

#endif

void Cli_CMD_Open(void);
void cliShowPrompt(void);
bool cliAdd(const char *cmd_str, const char *help_str,void (*p_func)(cli_args_t *)) ;
void wait_Command(void);


#endif /* SRC_COMMON_HW_INCLUDE_CLI_H_ */