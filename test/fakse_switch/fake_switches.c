#include "fake_switches.h"

static SWITCH_STATE_t pos_switchState;
static SWITCH_STATE_t neg_switchState;
static SWITCH_STATE_t p_switchState;
static int press_duration;
SWITCH_STATE_t   (*SWITCH_getSwState)(SWITCH_TYPE);
void   (*SWITCH_setSwState)(SWITCH_TYPE,SWITCH_STATE_t);
void   (*SWITCH_init)(void);

int get_duration()
{
    return press_duration;
}
void set_duration(int duration)
{
    press_duration=duration;
}

void FAKE_SW_init(void)
{
    pos_switchState = SW_RELEASED;
    neg_switchState = SW_RELEASED;
    p_switchState = SW_RELEASED;

}



SWITCH_STATE_t FAKE_SW_getSwState(SWITCH_TYPE sw)
{
    switch(sw)
    {
    case pos:
        return pos_switchState;
        break;
    case neg:
        return neg_switchState;
        break;
    case p:
        return p_switchState;
        break;
    }
}

void FAKE_SW_setSwState(SWITCH_TYPE type,SWITCH_STATE_t state)
{
    switch(type)
    {
    case pos:
        pos_switchState=state;
        break;
    case neg:
        neg_switchState=state;
        break;
    case p:
        p_switchState=state;
        break;
    }
}

