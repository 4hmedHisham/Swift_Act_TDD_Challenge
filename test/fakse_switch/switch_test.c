#include "../../source/swtich_driver/switches.h"
#include "../unity/unity_fixture.h"

TEST_GROUP(switches);

TEST_SETUP(switches)
{
    switchesInit();
}


TEST_TEAR_DOWN(switches)
{

}


TEST(switches, pos_switch_init)
{
    /*!
		  * @par Given : pos Switch State is unknown
		  * @par When  : Init is called
		  * @par Then  : Switch state is SW_RELEASED
	*/
	// sitchesInit() called on setup

    SWITCH_STATE_t expected_switch_state;
    SWITCH_TYPE current_switch;
    get_switch_test_data(&expected_switch_state,&current_switch,0);

    LONGS_EQUAL(expected_switch_state,GET_SWITCH_STATE(current_switch));

}
TEST(switches, neg_switch_init)
{
        /*!
		  * @par Given : neg Switch State is unknown
		  * @par When  : Init is called
		  * @par Then  : Switch state is SW_RELEASED
	*/
	// sitchesInit() called on setup

    SWITCH_STATE_t expected_switch_state;
    SWITCH_TYPE current_switch;
    get_switch_test_data(&expected_switch_state,&current_switch,1);
    LONGS_EQUAL(expected_switch_state,GET_SWITCH_STATE(current_switch));
}
TEST(switches, p_switch_init)
{
        /*!
		  * @par Given : p Switch State is unknown
		  * @par When  : Init is called
		  * @par Then  : Switch state is SW_RELEASED
	*/
	// sitchesInit() called on setup

    SWITCH_STATE_t expected_switch_state;
    SWITCH_TYPE current_switch;
    get_switch_test_data(&expected_switch_state,&current_switch,2);
    LONGS_EQUAL(expected_switch_state,GET_SWITCH_STATE(current_switch));
}

TEST(switches, pos_switch__SET_ON)
{
        /*!
		  * @par Given : pos Switch State is unknown
		  * @par When  : pos swtich is PREPRESSED
		  * @par Then  : pos Switch state is SW_PREPRESSED
	*/
	// sitchesInit() called on setup

    SWITCH_STATE_t expected_switch_state;
    SWITCH_TYPE current_switch;
    get_switch_test_data(&expected_switch_state,&current_switch,3);
    // ACT
    SET_SWITCH_STATE(current_switch,expected_switch_state);

    //observe

    LONGS_EQUAL(expected_switch_state,GET_SWITCH_STATE(current_switch));
}
TEST(switches, neg_switch_SET_ON)
{
      /*!
		  * @par Given : neg Switch State is unknown
		  * @par When  : neg swtich is PREPRESSED
		  * @par Then  : Switch state is SW_PREPRESSED
	*/

    SWITCH_STATE_t expected_switch_state;
    SWITCH_TYPE current_switch;
    get_switch_test_data(&expected_switch_state,&current_switch,4);
    // ACT
    SET_SWITCH_STATE(current_switch,expected_switch_state);

    //observe

    LONGS_EQUAL(expected_switch_state,GET_SWITCH_STATE(current_switch));
}
TEST(switches, p_switch_SET_ON)
{
      /*!
		  * @par Given : p Switch State is unknown
		  * @par When  : p swtich is PREPRESSED
		  * @par Then  : Switch state is SW_PREPRESSED
	*/
	// sitchesInit() called on setup

    SWITCH_STATE_t expected_switch_state;
    SWITCH_TYPE current_switch;
    get_switch_test_data(&expected_switch_state,&current_switch,5);

    // ACT
    SET_SWITCH_STATE(current_switch,expected_switch_state);

    //observe

    LONGS_EQUAL(expected_switch_state,GET_SWITCH_STATE(current_switch));
}
TEST(switches, pos_switch_SET_OFF)
{
      /*!
		  * @par Given : pos Switch State is unknown
		  * @par When  : pos swtich is RESLEASED
		  * @par Then  : Switch state is SW_RESLEASED
	*/
	// sitchesInit() called on setup

    SWITCH_STATE_t expected_switch_state;
    SWITCH_TYPE current_switch;
    get_switch_test_data(&expected_switch_state,&current_switch,6);

    // ACT
    SET_SWITCH_STATE(current_switch,expected_switch_state);

    //observe

    LONGS_EQUAL(expected_switch_state,GET_SWITCH_STATE(current_switch));
}
TEST(switches, neg_switch_SET_OFF)
{
      /*!
		  * @par Given : neg Switch State is unknown
		  * @par When  : neg swtich is RESLEASED
		  * @par Then  : Switch state is SW_RESLEASED
	*/
	// sitchesInit() called on setup

    SWITCH_STATE_t expected_switch_state;
    SWITCH_TYPE current_switch;
    get_switch_test_data(&expected_switch_state,&current_switch,7);

    // ACT
    SET_SWITCH_STATE(current_switch,expected_switch_state);

    //observe

    LONGS_EQUAL(expected_switch_state,GET_SWITCH_STATE(current_switch));
}
TEST(switches, p_switch_SET_OFF)
{
      /*!
		  * @par Given : p Switch State is unknown
		  * @par When  : p swtich is RESLEASED
		  * @par Then  : Switch state is SW_RELEASED
	*/
	// sitchesInit() called on setup

    SWITCH_STATE_t expected_switch_state;
    SWITCH_TYPE current_switch;
    get_switch_test_data(&expected_switch_state,&current_switch,8);

    // ACT
    SET_SWITCH_STATE(current_switch,expected_switch_state);

    //observe

    LONGS_EQUAL(expected_switch_state,GET_SWITCH_STATE(current_switch));
}

TEST_GROUP_RUNNER(switches)
{
    RUN_TEST_CASE(switches, pos_switch_init);
    RUN_TEST_CASE(switches, neg_switch_init);
    RUN_TEST_CASE(switches, p_switch_init);
    RUN_TEST_CASE(switches, pos_switch__SET_ON);
    RUN_TEST_CASE(switches, neg_switch_SET_ON);
    RUN_TEST_CASE(switches, p_switch_SET_ON);
    RUN_TEST_CASE(switches, pos_switch_SET_OFF);
    RUN_TEST_CASE(switches, neg_switch_SET_OFF);
    RUN_TEST_CASE(switches, p_switch_SET_OFF);
}
#if 0

TEST_SETUP(switches)
{


}
TEST_TEAR_DOWN(switches)
{

}
TEST(switches, switchesAreReleasedAfterInit)
{
    SWITCH_STATE_t expectedstate=SW_RELEASED
    /*!
		  * @par Given : Switch State is unknown
		  * @par When  : Init is called
		  * @par Then  : Switch state is SW_RELEASED
	*/

    /* Note that init is called in TEST_SETUP() */
  LONGS_EQUAL(SW_RELEASED,SW_RELEASED );
}

#endif
