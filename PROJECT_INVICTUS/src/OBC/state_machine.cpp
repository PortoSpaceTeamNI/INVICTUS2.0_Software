#include "state_machine.h"

rocket_state_t state = IDLE;

rocket_state_t comm_transition[rocket_state_size][cmd_size] = {
    //                       STATUS LOG ABORT EXEC  STOP   FUELING  MANUAL MAN_EXEC READY  ARM  LAUNCH  RESUME  FIRE
    /* Idle            */ {    -1,  -1, ABORT, -1,   -1,   FUELING, MANUAL,   -1,   READY,  -1,  -1,     -1,     -1,},
    /* Fueling         */ {    -1,  -1, IDLE,  -1,  IDLE,     -1,   MANUAL,   -1,    -1,    -1,  -1,     -1,     -1,},
    /* Manual          */ {    -1,  -1, IDLE,  -1,  IDLE,     -1,     -1,     -1,    -1,    -1,  -1,     -1,     -1,},
    /* Safety_Pressure */ {    -1,  -1, ABORT, -1,  FUELING,  -1,     -1,     -1,    -1,    -1,  -1,     -1,     -1,},
    /* Purge_Pressure  */ {    -1,  -1, ABORT, -1,  FUELING,  -1,     -1,     -1,    -1,    -1,  -1,     -1,     -1,},
    /* Purge_Liquid    */ {    -1,  -1, ABORT, -1,  FUELING,  -1,     -1,     -1,    -1,    -1,  -1,     -1,     -1,},
    /* Safety_Active   */ {    -1,  -1, ABORT, -1,  FUELING,  -1,     -1,     -1,    -1,    -1,  -1,     -1,     -1,},
    /* Ready           */ {    -1,  -1, IDLE,  -1,  IDLE,     -1,     -1,     -1,    -1,   ARMED,-1,     -1,     -1,},
    /* Armed           */ {    -1,  -1, IDLE,  -1,  READY,    -1,     -1,     -1,    -1,    -1, LAUNCH,  -1,     -1,},
    /* Launch          */ {    -1,  -1, ABORT, -1,  IDLE,     -1,     -1,     -1,    -1,    -1,  -1,     -1,     -1,},
    /* Abort           */ {    -1,  -1,  -1,   -1,  IDLE,     -1,     -1,     -1,    IDLE,  -1,  -1,     -1,     -1,},
    /* Flight          */ {    -1,  -1, ABORT, -1,  IDLE,     -1,     -1,     -1,    -1,    -1,  -1,     -1,     -1,},
    /* Recovery        */ {    -1,  -1, IDLE,  -1,  IDLE,     -1,     -1,     -1,    -1,    -1,  -1,     -1,     -1,}
};