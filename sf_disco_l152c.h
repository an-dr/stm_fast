

#ifndef SF_DISCO_L152C_H_
#define SF_DISCO_L152C_H_
/*                   */
#ifdef __cplusplus
extern "C"
{
#endif
/*                   */
#include "main.h" // hal

#include <stdbool.h>

#define GPIO_PIN_BLUE GPIO_PIN_6
#define GPIO_PIN_GREEN GPIO_PIN_7

/**
 * @author     Andrey Gramakov
 * @date       21-Dec-2018
 * @brief      Inits GPIO to work with
 * @details    { detailed_item_description }
 */
void SF_Disco_InitLeds();


/**
 * @author     Andrey Gramakov
 * @date       21-Dec-2018
 * @brief      { function_description }
 * @details    -
 *
 * @param[in]  state  The state
 */
void Green(bool state);
void GreenToggle();
void Blue(bool state);
void BlueToggle();
/*                   */
#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* SF_DISCO_L152C_H_ */
