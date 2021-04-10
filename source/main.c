#include <stdio.h>
#include <stdlib.h>
#include"swtich_driver/switches.h"
/* Include Unity */
#include "../test/unity/unity_fixture.h"
#define MAKE_UNITY_VERBOSE	argc = 2; argv[1] = "-v"

 void RunAllTests(void)
{
    //RUN_TEST_GROUP(switches);
    RUN_TEST_GROUP(init);
    RUN_TEST_GROUP(update);
}


int main(int argc, char * argv[])
{
    MAKE_UNITY_VERBOSE;

    /* Call Unity Main */
    UnityMain(argc, argv, RunAllTests);


    switchesInit();
    speed_init();

    printf("Hello world!\n");
    return 0;
}
