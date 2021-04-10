#include "../../source/speed_control/speed_control.h"
#include "../unity/unity_fixture.h"
#include "../fakse_switch/fake_switches.h"
#include "../../source/swtich_driver/switches.h"

#include <stdio.h>
#include <string.h>
#include<stdlib.h>


/**
 * @brief Get the sequence data
 * * Gets 3 sequential moves to make move between 4 states to achieve one swtich state transition coverage
 * @param states  array that have the state of each button during each sequence
 * @param duration_tofunc  duration set by reference of the p pressed time if exists
 * @param test_num test case number
 */
static void get_sequence_test_data(SWITCH_STATE_t *states,int *duration_tofunc,int test_num)
{

    test_num=test_num-1;//to make the parameter easy to read from the outside
	FILE* f = fopen("switch_data.txt","r+");
    char positive[20];
    char negative[20];
    char p[20];
	char duration[20];
	if(f)
	{
        fscanf(f, "%*[^\n]\n");
        fscanf(f, "%*[^\n]\n");
        for(int i=0;i<test_num;i++)
        {
            for(int j=0;j<3;j++)
            {
             fscanf(f, "%*[^\n]\n");// to skip lines to the line i need
            }
        }
		for(int sequence=0;sequence<3;sequence++)
        {

            memset(positive,0,20);
            memset(negative,0,20);
            memset(p,0,20);
            memset(duration,0,20);
            fscanf(f, "%s\t%s\t%s\t%s\n",positive, negative, p,duration);


            if(strcmp(positive,"SW_PRE_PRESSED")==0)
            {
                states[0+(sequence*3)]=SW_PRE_PRESSED;
            }
            else if(strcmp(positive,"SW_PRESSED")==0)
            {
                states[0+(sequence*3)]=SW_PRESSED;
            }
            else if(strcmp(positive,"SW_PRE_RELEASED")==0){
                states[0+(sequence*3)]=SW_PRE_RELEASED;
            }
            else if (strcmp(positive,"SW_RELEASED")==0){
                states[0+(sequence*3)]=SW_RELEASED;
            }
            else{
                printf("\n*********************************************");
                printf("\n INVALID DATA!\n");
                printf("*********************************************\n");

                exit(EXIT_SUCCESS);
                #if 0
                for (int i=0;i<12;i++)
                {
                    states[i]=-1;
                }
                #endif // 0

                }



            if(strcmp(negative,"SW_PRE_PRESSED")==0)
            {
                states[1+(sequence*3)]=SW_PRE_PRESSED;
            }
            else if(strcmp(negative,"SW_PRESSED")==0)
            {
                states[1+(sequence*3)]=SW_PRESSED;
            }
            else if(strcmp(negative,"SW_PRE_RELEASED")==0)
            {
                states[1+(sequence*3)]=SW_PRE_RELEASED;
            }
            else if (strcmp(negative,"SW_RELEASED")==0){
                states[1+(sequence*3)]=SW_RELEASED;
            }
            else{
                printf("\n*********************************************");
                printf("\n INVALID DATA!\n");
                printf("*********************************************\n");
                exit(EXIT_SUCCESS);
            }


            if(strcmp(p,"SW_PRE_PRESSED")==0)
            {
                states[2+(sequence*3)]=SW_PRE_PRESSED;
            }
            else if(strcmp(p,"SW_PRESSED")==0)
            {
                states[2+(sequence*3)]=SW_PRESSED;
            }
            else if(strcmp(p,"SW_PRE_RELEASED")==0)
            {
                states[2+(sequence*3)]=SW_PRE_RELEASED;
            }
            else if (strcmp(p,"SW_RELEASED")==0){
                states[2+(sequence*3)]=SW_RELEASED;
            }
            else{
                printf("\n*********************************************");
                printf("\n INVALID DATA!\n");
                printf("*********************************************\n");
                exit(EXIT_SUCCESS);
                }

            duration_tofunc[(sequence)]=atoi(duration);



        }
        fscanf(f, "%*[^\n]\n");
    }
	fclose(f);
}
/**
 * @brief Helper function that implements the sequence provided by the swtiches text
 *
 * @param sequence_states  the states copied from the text file
 * @param duration the duration copied from the text file
 */
void sequence_implementer(SWITCH_STATE_t *sequence_states,int *duration)
{
    for(int i=0;i<3;i++)
    {
        SWITCH_setSwState(pos,sequence_states[0+(i*3)]);
        SWITCH_setSwState(neg,sequence_states[1+(i*3)]);
        SWITCH_setSwState(p,sequence_states[2+(i*3)]);
        set_duration(duration[i]);
        update();
    }
}
TEST_GROUP(init);

TEST_SETUP(init)
{
    UT_PTR_SET(SWITCH_getSwState,FAKE_SW_getSwState);
    UT_PTR_SET(SWITCH_setSwState,FAKE_SW_setSwState);
    UT_PTR_SET(SWITCH_init,FAKE_SW_init);
    SWITCH_init();
    speed_init();

}

TEST_TEAR_DOWN(init)
{

}

TEST(init, speed_at_init)
{
    /*!
		  * @par Given : All switches Released
		  * @par When  : Init function called
		  * @par Then  : Speed should be medium
	*/
	Speed_State expected_speed=medium;
	// sitchesInit() called on setup
    LONGS_EQUAL(expected_speed,get_speed());

}
TEST_GROUP_RUNNER(init)
{
    RUN_TEST_CASE(init, speed_at_init);
}



TEST_GROUP(update);

TEST_SETUP(update)
{
    UT_PTR_SET(SWITCH_getSwState,FAKE_SW_getSwState);
    UT_PTR_SET(SWITCH_setSwState,FAKE_SW_setSwState);
    UT_PTR_SET(SWITCH_init,FAKE_SW_init);
    SWITCH_init();
    speed_init();

}

TEST_TEAR_DOWN(update)
{

}

TEST(update, Positive_Positive_Positive)
{
    /*!
          ** 1-Switch State Coverage ,Test 1/27
		  * @par Given : Speed is medium
		  * @par When  : Sequence Mid-(+)>MAX-(+)>MAX-(+)>MAX
		  * @par Then  : Speed is MAX
	*/
	Speed_State expected_speed=maximum;
	SWITCH_STATE_t sequence_states[12];
	int durations[3];
	get_sequence_test_data(&sequence_states,&durations,1);
    sequence_implementer(sequence_states,durations);
    LONGS_EQUAL(expected_speed,get_speed());
}

TEST(update, Positive_Positive_P30)
{
    /*!
          ** 1-Switch State Coverage ,Test 2/27
		  * @par Given : Speed is Medium
		  * @par When  : Sequence MAX-(+)>MAX-(+)>MAX-(P30)->Medium
		  * @par Then  : Speed is Medium
	*/
	Speed_State expected_speed=medium;
	SWITCH_STATE_t sequence_states[9];
	int durations[3];
	get_sequence_test_data(&sequence_states,&durations,2);
    sequence_implementer(sequence_states,durations);
    LONGS_EQUAL(expected_speed,get_speed());
}

TEST(update, Positive_Positive_Negative)
{
    /*!
          ** 1-Switch State Coverage ,Test 3/27
		  * @par Given : Speed is Medium
		  * @par When  : Sequence MAX-(+)>MAX-(+)>MAX-(-)>Medium
		  * @par Then  : Speed is Medium
	*/
	Speed_State expected_speed=medium;
	SWITCH_STATE_t sequence_states[9];
	int durations[3];
	get_sequence_test_data(&sequence_states,&durations,3);
    sequence_implementer(sequence_states,durations);
    LONGS_EQUAL(expected_speed,get_speed());
}

TEST(update, Positive_P30_Positive)
{
    /*!
          ** 1-Switch State Coverage ,Test 4/27
		  * @par Given : Speed is Medium
		  * @par When  : Sequence Medium-(+)>MAX-(P30)->Medium-(+)>MAX
		  * @par Then  : Speed is MAX
	*/
	Speed_State expected_speed=maximum;
	SWITCH_STATE_t sequence_states[9];
	int durations[3];
	get_sequence_test_data(&sequence_states,&durations,4);
    sequence_implementer(sequence_states,durations);
    LONGS_EQUAL(expected_speed,get_speed());
}

TEST(update, Positive_P30_P30)
{
    /*!
          ** 1-Switch State Coverage, Test 5/27
		  * @par Given : Speed is Medium
		  * @par When  : Sequence Medmium-(+)>MAX-(P30)->Medium-(P30)>MIN
		  * @par Then  : Speed is MIN
	*/
	Speed_State expected_speed=minimum;
	SWITCH_STATE_t sequence_states[9];
	int durations[3];
	get_sequence_test_data(&sequence_states,&durations,5);
    sequence_implementer(sequence_states,durations);
    LONGS_EQUAL(expected_speed,get_speed());
}

TEST(update, Positive_P30_Negative)
{
    /*!
          ** Test 1-Switch State Coverage, Test 6/27
		  * @par Given : Speed is Medium
		  * @par When  : Sequence Medium-(+)>HIGH-(P30)->Medium-(-)>MIN
		  * @par Then  : Speed is MIN
	*/
	Speed_State expected_speed=minimum;
	SWITCH_STATE_t sequence_states[9];
	int durations[3];
	get_sequence_test_data(&sequence_states,&durations,6);
    sequence_implementer(sequence_states,durations);
    LONGS_EQUAL(expected_speed,get_speed());
}

TEST(update, Positive_Negative_Negative)
{
    /*!
          ** Test 1-Switch State Coverage, Test 7/27
		  * @par Given : Speed is Medium
		  * @par When  : Sequence Medium-(+)>MAX-(-)>Medium-(-)>MIN
		  * @par Then  : Speed is MIN
	*/
	Speed_State expected_speed=minimum;
	SWITCH_STATE_t sequence_states[9];
	int durations[3];
	get_sequence_test_data(&sequence_states,&durations,7);
    sequence_implementer(sequence_states,durations);
    LONGS_EQUAL(expected_speed,get_speed());
}

TEST(update, Positive_Negative_P30)
{
    /*!
          ** 1-Switch State Coverage, Test 8/27
		  * @par Given : Speed is Medium
		  * @par When  : Sequence Medium-(+)>MAX-(-)>Medium-(P30)>MIN
		  * @par Then  : Speed is MIN
	*/
	Speed_State expected_speed=minimum;
	SWITCH_STATE_t sequence_states[9];
	int durations[3];
	get_sequence_test_data(&sequence_states,&durations,8);
    sequence_implementer(sequence_states,durations);
    LONGS_EQUAL(expected_speed,get_speed());
}

TEST(update, Positive_Negative_Positive)
{
    /*!
          ** 1-Switch State Coverage, Test 9/27
		  * @par Given : Speed is Medium
		  * @par When  : Sequence Medium-(+)>MAX-(-)>Medium-(+)>MAX
		  * @par Then  : Speed is MAX
	*/
	Speed_State expected_speed=maximum;
	SWITCH_STATE_t sequence_states[9];
	int durations[3];
	get_sequence_test_data(&sequence_states,&durations,9);
    sequence_implementer(sequence_states,durations);
    LONGS_EQUAL(expected_speed,get_speed());
}

TEST(update, P30_Postive_Positive)
{
    /*!
          ** 1-Switch State Coverage, Test 10/27
		  * @par Given : Speed is Medium
		  * @par When  : Sequence Medium-(P30)>MIN-(+)>Medium-(+)>MAX
		  * @par Then  : Speed is MAX
	*/
	Speed_State expected_speed=maximum;
	SWITCH_STATE_t sequence_states[9];
	int durations[3];
	get_sequence_test_data(&sequence_states,&durations,10);
    sequence_implementer(sequence_states,durations);
    LONGS_EQUAL(expected_speed,get_speed());
}

TEST(update, P30_Positive_P30)
{
    /*!
          ** 1-Switch State Coverage, Test 11/27
		  * @par Given : Speed is Medium
		  * @par When  : Sequence Medium-(P30)>MIN-(+)>Medium-(P30)>MIN
		  * @par Then  : Speed is MIN
	*/
	Speed_State expected_speed=minimum;
	SWITCH_STATE_t sequence_states[9];
	int durations[3];
	get_sequence_test_data(&sequence_states,&durations,11);
    sequence_implementer(sequence_states,durations);
    LONGS_EQUAL(expected_speed,get_speed());
}
TEST(update, P30_Positive_Negative)
{
    /*!
          ** 1-Switch State Coverage, Test 12/27
		  * @par Given : Speed is Medium
		  * @par When  : Sequence Medium-(P30)>MIN-(+)>Medium-(-)>MIN
		  * @par Then  : Speed is MIN
	*/
	Speed_State expected_speed=minimum;
	SWITCH_STATE_t sequence_states[9];
	int durations[3];
	get_sequence_test_data(&sequence_states,&durations,12);
    sequence_implementer(sequence_states,durations);
    LONGS_EQUAL(expected_speed,get_speed());
}

TEST(update, P30_P30_Negative)
{
    /*!
          ** 1-Switch State Coverage, Test 13/27
		  * @par Given : Speed is Medium
		  * @par When  : Sequence Medium-(P30)>MIN-(P30)>MIN-(-)>MIN
		  * @par Then  : Speed is MIN
	*/
	Speed_State expected_speed=minimum;
	SWITCH_STATE_t sequence_states[9];
	int durations[3];
	get_sequence_test_data(&sequence_states,&durations,13);
    sequence_implementer(sequence_states,durations);
    LONGS_EQUAL(expected_speed,get_speed());
}

TEST(update, P30_P30_P30)
{
    /*!
          ** 1-Switch State Coverage, Test 14/27
		  * @par Given : Speed is Medium
		  * @par When  : Sequence Medium-(P30)>MIN-(P30)>MIN-(P30)>MIN
		  * @par Then  : Speed is MIN
	*/
	Speed_State expected_speed=minimum;
	SWITCH_STATE_t sequence_states[9];
	int durations[3];
	get_sequence_test_data(&sequence_states,&durations,14);
    sequence_implementer(sequence_states,durations);
    LONGS_EQUAL(expected_speed,get_speed());
}

TEST(update, P30_P30_Positive)
{
    /*!
          ** 1-Switch State Coverage, Test 15/27
		  * @par Given : Speed is Medium
		  * @par When  : Sequence Medium-(P30)>MIN-(P30)>MIN-(+)>Medium
		  * @par Then  : Speed is Medium
	*/
	Speed_State expected_speed=medium;
	SWITCH_STATE_t sequence_states[9];
	int durations[3];
	get_sequence_test_data(&sequence_states,&durations,15);
    sequence_implementer(sequence_states,durations);
    LONGS_EQUAL(expected_speed,get_speed());
}

TEST(update, P30_Negative_Negative)
{
    /*!
          ** 1-Switch State Coverage, Test 16/27
		  * @par Given : Speed is Medium
		  * @par When  : Sequence Medium-(P30)>MIN-(-)>MIN-(-)>MIN
		  * @par Then  : Speed is MIN
	*/
	Speed_State expected_speed=minimum;
	SWITCH_STATE_t sequence_states[9];
	int durations[3];
	get_sequence_test_data(&sequence_states,&durations,16);
    sequence_implementer(sequence_states,durations);
    LONGS_EQUAL(expected_speed,get_speed());
}
TEST(update, P30_Negative_Positive)
{
    /*!
          ** 1-Switch State Coverage, Test 17/27
		  * @par Given : Speed is Medium
		  * @par When  : Sequence Medium-(P30)>MIN-(-)>MIN-(+)>Medium
		  * @par Then  : Speed is Medium
	*/
	Speed_State expected_speed=medium;
	SWITCH_STATE_t sequence_states[9];
	int durations[3];
	get_sequence_test_data(&sequence_states,&durations,17);
    sequence_implementer(sequence_states,durations);
    LONGS_EQUAL(expected_speed,get_speed());
}
TEST(update, P30_Negative_P30)
{
    /*!
          ** 1-Switch State Coverage, Test 18/27
		  * @par Given : Speed is Medium
		  * @par When  : Sequence Medium-(P30)>MIN-(-)>MIN-(P30)>MIN
		  * @par Then  : Speed is MIN
	*/
	Speed_State expected_speed=minimum;
	SWITCH_STATE_t sequence_states[9];
	int durations[3];
	get_sequence_test_data(&sequence_states,&durations,18);
    sequence_implementer(sequence_states,durations);
    LONGS_EQUAL(expected_speed,get_speed());
}

TEST(update, Negative_Negative_Negative)
{
    /*!
          ** 1-Switch State Coverage, Test 19/27
		  * @par Given : Speed is Medium
		  * @par When  : Sequence Medium-(-)>MIN-(-)>MIN-(-)>MIN
		  * @par Then  : Speed is MIN
	*/
	Speed_State expected_speed=minimum;
	SWITCH_STATE_t sequence_states[9];
	int durations[3];
	get_sequence_test_data(&sequence_states,&durations,19);
    sequence_implementer(sequence_states,durations);
    LONGS_EQUAL(expected_speed,get_speed());
}

TEST(update, Negative_Negative_P30)
{
    /*!
          ** 1-Switch State Coverage, Test 20/27
		  * @par Given : Speed is Medium
		  * @par When  : Sequence Medium-(-)>MIN-(-)>MIN-(P30)>MIN
		  * @par Then  : Speed is MIN
	*/
	Speed_State expected_speed=minimum;
	SWITCH_STATE_t sequence_states[9];
	int durations[3];
	get_sequence_test_data(&sequence_states,&durations,20);
    sequence_implementer(sequence_states,durations);
    LONGS_EQUAL(expected_speed,get_speed());
}

TEST(update, Negative_Negative_Positive)
{
    /*!
          ** 1-Switch State Coverage, Test 21/27
		  * @par Given : Speed is Medium
		  * @par When  : Sequence Medium-(-)>MIN-(-)>MIN-(+)>Medium
		  * @par Then  : Speed is Medium
	*/
	Speed_State expected_speed=medium;
	SWITCH_STATE_t sequence_states[9];
	int durations[3];
	get_sequence_test_data(&sequence_states,&durations,21);
    sequence_implementer(sequence_states,durations);
    LONGS_EQUAL(expected_speed,get_speed());
}

TEST(update, Negative_P30_Positive)
{
    /*!
          ** 1-Switch State Coverage, Test 22/27
		  * @par Given : Speed is Medium
		  * @par When  : Sequence Medium-(-)>MIN-(P30)>MIN-(+)>Medium
		  * @par Then  : Speed is Medium
	*/
	Speed_State expected_speed=medium;
	SWITCH_STATE_t sequence_states[9];
	int durations[3];
	get_sequence_test_data(&sequence_states,&durations,22);
    sequence_implementer(sequence_states,durations);
    LONGS_EQUAL(expected_speed,get_speed());
}

TEST(update, Negative_P30_Negative)
{
    /*!
          ** 1-Switch State Coverage, Test 23/27
		  * @par Given : Speed is Medium
		  * @par When  : Sequence Medium-(-)>MIN-(P30)>MIN-(-)>MIN
		  * @par Then  : Speed is MIN
	*/
	Speed_State expected_speed=minimum;
	SWITCH_STATE_t sequence_states[9];
	int durations[3];
	get_sequence_test_data(&sequence_states,&durations,23);
    sequence_implementer(sequence_states,durations);
    LONGS_EQUAL(expected_speed,get_speed());
}

TEST(update, Negative_P30_P30)
{
    /*!
          ** 1-Switch State Coverage, Test 24/27
		  * @par Given : Speed is Medium
		  * @par When  : Sequence Medium-(-)>MIN-(P30)>MIN-(P30)>MIN
		  * @par Then  : Speed is MIN
	*/
	Speed_State expected_speed=minimum;
	SWITCH_STATE_t sequence_states[9];
	int durations[3];
	get_sequence_test_data(&sequence_states,&durations,24);
    sequence_implementer(sequence_states,durations);
    LONGS_EQUAL(expected_speed,get_speed());
}

TEST(update, Negative_Positive_P30)
{
    /*!
          ** 1-Switch State Coverage, Test 25/27
		  * @par Given : Speed is Medium
		  * @par When  : Sequence Medium-(-)>MIN-(+)>Medium-(P30)>MIN
		  * @par Then  : Speed is MIN
	*/
	Speed_State expected_speed=minimum;
	SWITCH_STATE_t sequence_states[9];
	int durations[3];
	get_sequence_test_data(&sequence_states,&durations,25);
    sequence_implementer(sequence_states,durations);
    LONGS_EQUAL(expected_speed,get_speed());
}

TEST(update, Negative_Positive_Positive)
{
    /*!
          ** 1-Switch State Coverage, Test 26/27
		  * @par Given : Speed is Medium
		  * @par When  : Sequence Medium-(-)>MIN-(+)>Medium-(+)>MAX
		  * @par Then  : Speed is MAX
	*/
	Speed_State expected_speed=maximum;
	SWITCH_STATE_t sequence_states[9];
	int durations[3];
	get_sequence_test_data(&sequence_states,&durations,26);
    sequence_implementer(sequence_states,durations);
    LONGS_EQUAL(expected_speed,get_speed());
}

TEST(update, Negative_Positive_Negative)
{
    /*!
          ** 1-Switch State Coverage, Test 27/27
		  * @par Given : Speed is Medium
		  * @par When  : Sequence Medium-(-)>MIN-(+)>Medium-(-)>MIN
		  * @par Then  : Speed is MIN
	*/
	Speed_State expected_speed=minimum;
	SWITCH_STATE_t sequence_states[9];
	int durations[3];
	get_sequence_test_data(&sequence_states,&durations,27);
    sequence_implementer(sequence_states,durations);

    LONGS_EQUAL(expected_speed,get_speed());
}
TEST(update, P29_test)
{
    /*!
          ** Boundary  Value analysis at 29 , P should be >=30 to activate
		  * @par Given : Speed is Medium
		  * @par When  : Sequence Medium-(P29)>Medium
		  * @par Then  : Speed is Medium
	*/
	Speed_State expected_speed=medium;
	SWITCH_STATE_t sequence_states[9];
	int durations[3];
	get_sequence_test_data(&sequence_states,&durations,28);
    sequence_implementer(sequence_states,durations);
    LONGS_EQUAL(expected_speed,get_speed());
}
TEST(update, P31_test)
{
    /*!
          ** Boundary  Value analysis at 31 , P should be >=30 to activate
		  * @par Given : Speed is Medium
		  * @par When  : Sequence Medium-(P31)>MIN
		  * @par Then  : Speed is MIN
	*/
	Speed_State expected_speed=minimum;
	SWITCH_STATE_t sequence_states[9];
	int durations[3];
	get_sequence_test_data(&sequence_states,&durations,29);
    sequence_implementer(sequence_states,durations);
    LONGS_EQUAL(expected_speed,get_speed());
}

TEST(update, Priority_Testing_All_pressed)
{
    /*!
          ** Priority Testing
		  * @par Given : Speed is Medium
		  * @par When  : Pressing all the buttons one time and then releasing them all
		  * @par Then  : Speed is MIN due to P30 activating the update value
	*/
	Speed_State expected_speed=minimum;
	SWITCH_STATE_t sequence_states[9];
	int durations[3];
	get_sequence_test_data(&sequence_states,&durations,30);
    sequence_implementer(sequence_states,durations);
    LONGS_EQUAL(expected_speed,get_speed());
}

TEST(update, Priority_Testing_Postive_Negative_Pressed)
{
    /*!
          ** Priority Testing
		  * @par Given : Speed is Medium
		  * @par When  : Pressing Positive and Negative buttons one time and then releasing them all
		  * @par Then  : Speed is MIN due to negavive activating the update value
	*/
	Speed_State expected_speed=minimum;
	SWITCH_STATE_t sequence_states[9];
	int durations[3];
	get_sequence_test_data(&sequence_states,&durations,31);
    sequence_implementer(sequence_states,durations);
    LONGS_EQUAL(expected_speed,get_speed());
}


TEST_GROUP_RUNNER(update)
{
     RUN_TEST_CASE(update, Positive_Positive_Positive);
     RUN_TEST_CASE(update, Positive_Positive_P30);
     RUN_TEST_CASE(update, Positive_Positive_Negative);
     RUN_TEST_CASE(update, Positive_P30_Positive);
     RUN_TEST_CASE(update, Positive_P30_P30);
     RUN_TEST_CASE(update, Positive_P30_Negative);
     RUN_TEST_CASE(update, Positive_Negative_Negative);
     RUN_TEST_CASE(update, Positive_Negative_P30);
     RUN_TEST_CASE(update, Positive_Negative_Positive);
     RUN_TEST_CASE(update, P30_Postive_Positive);
     RUN_TEST_CASE(update, P30_Positive_P30);
     RUN_TEST_CASE(update, P30_Positive_Negative);
     RUN_TEST_CASE(update, P30_P30_Negative);
     RUN_TEST_CASE(update, P30_P30_P30);
     RUN_TEST_CASE(update, P30_P30_Positive);
     RUN_TEST_CASE(update, P30_Negative_Negative);
     RUN_TEST_CASE(update, P30_Negative_Positive);
     RUN_TEST_CASE(update, P30_Negative_P30);
     RUN_TEST_CASE(update, Negative_Negative_P30);
     RUN_TEST_CASE(update, Negative_Negative_Positive);
     RUN_TEST_CASE(update, Negative_Negative_Negative);
     RUN_TEST_CASE(update, Negative_P30_Positive);
     RUN_TEST_CASE(update, Negative_P30_Negative);
     RUN_TEST_CASE(update, Negative_P30_P30);
     RUN_TEST_CASE(update, Negative_Positive_P30);
     RUN_TEST_CASE(update, Negative_Positive_Positive);
     RUN_TEST_CASE(update, Negative_Positive_Negative);
     RUN_TEST_CASE(update, P31_test);
     RUN_TEST_CASE(update, P29_test);
     RUN_TEST_CASE(update, Priority_Testing_All_pressed);
     RUN_TEST_CASE(update, Priority_Testing_Postive_Negative_Pressed);




/*










*/



}
