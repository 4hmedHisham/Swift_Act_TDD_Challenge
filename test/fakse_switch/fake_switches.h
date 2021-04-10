#ifndef fake_sw
#define fake_sw


#include"../../source/swtich_driver/switches.h"


SWITCH_STATE_t FAKE_SW_getSwState(SWITCH_TYPE);

/**
 * @brief Intialize fake switches
 * 
 */
void FAKE_SW_init(void);


/**
 * @brief Sets a certain switch state by adding it as a "type" variable and then addint the state as a second variable
 * 
 * @param type 
 * @param state 
 */
void FAKE_SW_setSwState(SWITCH_TYPE type,SWITCH_STATE_t state);
/**
 * @brief get a certain switch state , the certain switch type is provided by "sw" variable
 * 
 * @return SWITCH_STATE_t 
 */
SWITCH_STATE_t FAKE_SW_getSwState(SWITCH_TYPE sw);
/**
 * @brief Get the duration of p button
 * 
 * @return int 
 */
int get_duration();

/**
 * @brief Set the duration of p button
 * 
 */
void set_duration(int);
#endif // fake_sw
