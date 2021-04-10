#include"speed_control.h"
#include <stdio.h>
#include "../../test/fakse_switch/fake_switches.h"
#include <stdbool.h>
#include "../swtich_driver/switches.h"

static Speed_State current_speed;


Speed_State get_speed()
{
    return current_speed;
}
void set_speed(Speed_State speed)
{
    current_speed=speed;
}
void speed_init()
{
    current_speed=medium;
}

void update()
{

    static bool firstime=true;
    if(firstime)
    {
        firstime=false;
        FILE * fp;
        fp = fopen("motor_angles.txt","w");
        fprintf (fp, "MOTOR ANGLES \n");
        fclose (fp);
    }
    if(SWITCH_getSwState(p)==SW_PRESSED)
    {
        int duration=get_duration();
        if(duration>=30)
        {
          switch(get_speed())
            {
            case(medium):
                set_speed(minimum);
                break;
            case(maximum):
                set_speed(medium);
                break;
            }

        }

    }
    else if(SWITCH_getSwState(p)==SW_PRE_PRESSED)
    {

    }
    else if(SWITCH_getSwState(neg)==SW_PRE_PRESSED)
    {
        switch(get_speed())
        {
        case(medium):
            set_speed(minimum);
            break;
        case(maximum):
            set_speed(medium);
            break;
        }
    }
    else if(SWITCH_getSwState(pos)==SW_PRE_PRESSED)
    {
        switch(get_speed())
        {
        case(minimum):
            set_speed(medium);
            break;
        case(medium):
            set_speed(maximum);
            break;
        }

    }

    if(get_speed()==maximum)
        {
            FILE * fp;
            fp =fopen("motor_angles.txt", "a");
            fprintf (fp, "%d \n",140);
            fclose (fp);
        }
        else if(get_speed()==medium)
        {
            FILE * fp;
            fp =fopen("motor_angles.txt", "a");
            fprintf (fp, "%d \n",90);
            fclose (fp);
        }
        else if(get_speed()==minimum)
        {
            FILE * fp;
            fp = fopen("motor_angles.txt","a");
            fprintf (fp, "%d \n",10);
            fclose (fp);
        }
        else{
            printf("INVALID SPEED!");
        }


}
