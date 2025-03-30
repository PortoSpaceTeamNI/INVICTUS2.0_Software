#include "state_machine.h"
#include "commands.h"

RocketState state_transitions[rocket_state_size][cmd_size] = {
    //                       STATUS      LOG         ABORT  EXEC        STOP   PROG        MANUAL      MAN_EXEC    READY       ARM         LAUNCH      RESUME      FIRE
    /* Idle            */ {  IDLE,       IDLE,       ABORT, IDLE,       IDLE,  PROG,       MANUAL,     IDLE,       READY,      IDLE,       IDLE,       IDLE,       IDLE,},
    /* Prog            */ {  PROG,       PROG,       IDLE,  PROG,       IDLE,  PROG,       MANUAL,     PROG,       PROG,       PROG,       PROG,       PROG,       PROG,},
    /* Manual          */ {  MANUAL,     MANUAL,     IDLE,  MANUAL,     IDLE,  MANUAL,     MANUAL,     MANUAL,     MANUAL,     MANUAL,     MANUAL,     MANUAL,     MANUAL,},
    /* Ready           */ {  READY,      READY,      IDLE,  READY,      IDLE,  READY,      READY,      READY,      READY,      ARMED,      READY,      READY,      READY,},
    /* Armed           */ {  ARMED,      ARMED,      IDLE,  ARMED,      READY, ARMED,      ARMED,      ARMED,      ARMED,      ARMED,      LAUNCH,     ARMED,      ARMED,},
    /* Launch          */ {  LAUNCH,     LAUNCH,     ABORT, LAUNCH,     IDLE,  LAUNCH,     LAUNCH,     LAUNCH,     LAUNCH,     LAUNCH,     LAUNCH,     LAUNCH,     LAUNCH,},
    /* Soft Abort      */ {  SOFT_ABORT, SOFT_ABORT, ABORT, SOFT_ABORT, IDLE,  SOFT_ABORT, SOFT_ABORT, SOFT_ABORT, SOFT_ABORT, SOFT_ABORT, SOFT_ABORT, SOFT_ABORT, SOFT_ABORT,},
    /* Abort           */ {  ABORT,      ABORT,      ABORT, ABORT,      IDLE,  ABORT,      ABORT,      ABORT,      IDLE,       ABORT,      ABORT,      ABORT,      ABORT,},
    /* Flight          */ {  FLIGHT,     FLIGHT,     ABORT, FLIGHT,     IDLE,  FLIGHT,     FLIGHT,     FLIGHT,     FLIGHT,     FLIGHT,     FLIGHT,     FLIGHT,     FLIGHT,},
    /* Recovery        */ {  RECOVERY,   RECOVERY,   IDLE,  RECOVERY,   IDLE,  RECOVERY,   RECOVERY,   RECOVERY,   RECOVERY,   RECOVERY,   RECOVERY,   RECOVERY,   RECOVERY,},
};

RocketState get_next_state(RocketState current_state, cmd_type cmd)
{
    return state_transitions[current_state][cmd];
}

