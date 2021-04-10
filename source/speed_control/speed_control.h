#ifndef this
#define this

typedef enum {minimum,medium,maximum} Speed_State;
/**
 * @brief Initalize Speed With Medium
 * 
 */
void speed_init(void);

/**
 * @brief Get the speed object
 * 
 * @return Speed_State 
 */
Speed_State get_speed(void);

/**
 * @brief Set the speed object
 * 
 * @param speed 
 */
void set_speed(Speed_State speed);

/**
 * @brief Update/Tick function that progresses time and check the values to set in the speed/motor angle
 * 
 */
void update(void);

#endif
