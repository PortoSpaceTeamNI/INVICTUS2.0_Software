#include "commands.h"
typedef enum 
{
    IDLE,
    PROG,
    MANUAL,
    READY,
    ARMED,
    LAUNCH,
    SOFT_ABORT,
    ABORT,
    FLIGHT,
    RECOVERY,
    rocket_state_size, //this needs to be the last state for size to work
} RocketState;

RocketState get_next_state(RocketState current_state, cmd_type cmd);