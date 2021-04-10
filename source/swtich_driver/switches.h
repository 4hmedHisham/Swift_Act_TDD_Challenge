#ifndef SWITCH_H_INCLUDED
#define SWITCH_H_INCLUDED

typedef enum {SW_PRESSED, SW_RELEASED,SW_PRE_RELEASED,SW_PRE_PRESSED} SWITCH_STATE_t;
typedef enum {pos,neg,p} SWITCH_TYPE;

/**
 * @brief Initlaize Positive Switch State
 *
 */
void        pos_SWITCH_init(void);

/**
 * @brief Initlaize Negative Switch State
 *
 */
void        neg_SWITCH_init(void);

/**
 * @brief Initlaize P Switch State
 *
 */
void        p_SWITCH_init(void);

/**
 * @brief Set the switch state object
 *
 * @param SW_TYPE
 * @param state
 */
void        Set_REAL_SWITCH_STATE(SWITCH_TYPE SW_TYPE,SWITCH_STATE_t state);

/**
 * @brief Get the real switch state object
 *
 * @return SWITCH_STATE_t
 */
SWITCH_STATE_t        GET_REAL_SWITCH_STATE(SWITCH_TYPE);

extern      SWITCH_STATE_t   (*SWITCH_getSwState)(SWITCH_TYPE);
extern      void   (*SWITCH_setSwState)(SWITCH_TYPE,SWITCH_STATE_t);
extern      void   (*SWITCH_init)(void);



#endif
