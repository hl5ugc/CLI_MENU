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
#ifndef CLI_COMMON_DEF_H_
#define CLI_COMMON_DEF_H_


#include "HW_DEF.H"


#ifdef _USE_HW_CLI
#define CLI_LINE_HIS_MAX    HW_CLI_LINE_HIS_MAX
#define CLI_LINE_BUF_MAX    HW_CLI_LINE_BUF_MAX


bool cliInit(void);
bool cliOpen(uint8_t ch, uint16_t u16Baud);
bool cliOpenLog(uint8_t ch, uint16_t u16Baud);
bool cliMain(void);
void cliShowPrompt1(void);

#endif

#endif  /* SRC_HW_HW_DEF_H_ */