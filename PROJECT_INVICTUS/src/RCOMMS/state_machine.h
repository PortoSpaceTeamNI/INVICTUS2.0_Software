typedef rocket_state_t;
enum 
{
    IDLE,
    MANUAL,
    PREPRESSURIZING,
    FILLING_N,
    FILLING_N2O,
    POSTPRESSURIZING,
    READY,
    ARMED,
    LAUNCH,
    SOFT_ABORT,
    ABORT,
    FLIGHT,
    RECOVERY,
    rocket_state_size, //this needs to be the last state for size to work
} rocket_state;