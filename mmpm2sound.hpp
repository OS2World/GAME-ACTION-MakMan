
/*
 * MMPM/2 Playlist defines
 */
#define DATA_OPERATION                                          0
#define BRANCH_OPERATION                                        1
#define LOOP_OPERATION                                          2
#define CALL_OPERATION                                          3
#define RETURN_OPERATION                                        4
#define EXIT_OPERATION                                          5
#define NOP_OPERATION                                           6
#define MESSAGE_OPERATION                                       7
#define CUEPOINT_OPERATION                                      8



typedef struct pls
{
   ULONG ulCommand;
   ULONG ulOperandOne;
   ULONG ulOperandTwo;
   ULONG ulOperandThree;
} PLAY_LIST_STRUCTURE_T;
