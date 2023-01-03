// =======================================================================
// [ PROJECT   ]
// -----------------------------------------------------------------------
// [ License   ] SAMJIN ELECTRONICS
// [ Author    ] Copyright 2021-08 By HAG-SEONG KANG
// [ E-MAIL    ] hl5ugc@nate.com (82)10- 3841-9706
// [ C  P  U   ]
// [ Compller  ] CodeWizardAVR V3.12 Professional
// [ Filename  ] HW_DEF.H
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
#ifndef SRC_HW_HW_DEF_H_
#define SRC_HW_HW_DEF_H_

#include "def.h"

#define _USE_HW_UART
#define     HW_UART_MAX_CH          4

#define _USE_HW_CLI_COMMAND
#define     CLI_COMMAND_UART        _DEF_UART2
#define     HW_CLI_CMD_NAME_MAX     8
#define     HW_CLI_HLP_NAME_MAX     16
#define     HW_CLI_CMD_LIST_MAX     8

#endif /* SRC_HW_HW_DEF_H_ */