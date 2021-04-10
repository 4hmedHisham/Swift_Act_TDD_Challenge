#include "switches.h"


static SWITCH_STATE_t real_pos_switchState;
static SWITCH_STATE_t real_neg_switchState;
static SWITCH_STATE_t real_p_switchState;

SWITCH_STATE_t   (*SWITCH_getSwState)(SWITCH_TYPE);
void   (*SWITCH_setSwState)(SWITCH_TYPE,SWITCH_STATE_t);
void   (*SWITCH_init)(void);

void pos_SWITCH_init()
    {
        real_pos_switchState=SW_RELEASED;
    }
void neg_SWITCH_init()
    {
        real_neg_switchState=SW_RELEASED;
    }
void p_SWITCH_init()
    {
        real_p_switchState=SW_RELEASED;
    }
void  switchesInit()
    {
        SWITCH_getSwState=GET_REAL_SWITCH_STATE;
        SWITCH_setSwState=Set_REAL_SWITCH_STATE;
        pos_SWITCH_init();
        neg_SWITCH_init();
        p_SWITCH_init();
    }

SWITCH_STATE_t GET_REAL_SWITCH_STATE(SWITCH_TYPE SW_TYPE)
{
    switch(SW_TYPE)
    {
    case pos:
        return real_pos_switchState;
        break;
    case neg:
        return real_neg_switchState;
        break;
    case p:
        return real_p_switchState;
        break;
    default:
        printf("INVALID TYPE");
    }
}

void Set_REAL_SWITCH_STATE(SWITCH_TYPE type,SWITCH_STATE_t state)
{
    type=state;
}


