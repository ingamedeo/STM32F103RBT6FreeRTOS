#ifndef SSD1306_H_
#define SSD1306_H_

#include "myFont.h"

#define I2C_SPEED                   50000                     /*!< I2C Speed */
#define I2C1_SSD1306_SLAVE_ADDRESS8 0x78                      // 8 bit slave address (write)
#define I2C_TIMEOUT                 100000

typedef struct{
    uint8_t hours;
    uint8_t minutes;
    uint8_t seconds;
}system_time_t;

typedef enum{
    clock_state,
    pattern_state,
} my_states_t;

typedef struct{
    my_states_t current_state;
    system_time_t current_system_time;
}system_status_t; 

system_time_t my_system_time;
system_status_t my_system_status;


// Globals
int8_t global_display_buffer[(128*64)/8];

//void ButtonsInit(void);
//uint32_t ButtonRead(GPIO_TypeDef* Button_Port, uint16_t Button);
#endif /* SSD1306_H_ */
