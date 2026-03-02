
#include <stdint.h>

#define SOLUTION 1
///////////////////////////////////////////////////////////////////////////////
// Assignment 1
// ===========================================================================
// Write a function that configures pin 11 of GPIO port D as input with 
// pull-down resistor enabled.
///////////////////////////////////////////////////////////////////////////////

// TODO: Macro definitions here
#define GPIO_D_BASE  0x40011400
#define GPIO_D_CFGLR ((unsigned int *)0x40011400)
#define GPIO_D_CFGHR ((unsigned int *)0x40011404)
#define GPIO_D_INDR  ((unsigned int *)0x40011408)
#define GPIO_D_OUTDR ((unsigned int *)0x4001140C)
#define GPIO_D_BSHR  ((unsigned int *)0x40011410)
#define GPIO_D_BCR   ((unsigned int *)0x40011414)


/* 
pin 11 as input with pull-down resistor enabled
CNF to 10  // Pull-up/Pull-down
Mode to 00 // Input Mode
binary: .... 1000 0000 0000 0000
pin:          11   10   9    8
hex: 0x8000
*/
void assignment_1(void)
{
    // Preserve other pins, only modify pin 11 bits [15:12]
    *GPIO_D_CFGHR = (*GPIO_D_CFGHR & ~0xF000) | 0x8000;
    
    // Set OUTDR bit 11 to 0 for pull-down
    *GPIO_D_OUTDR = 0b000000000000;
    //                109876543210
}

///////////////////////////////////////////////////////////////////////////////
// Assignment 2
// ===========================================================================
// Write a more general function that configures a pin of GPIO port D as
// input with pull up or down or floating.
// The function should be able to modify CFGLR and CFGHR if needed. 
///////////////////////////////////////////////////////////////////////////////

void gpio_d_set_pin_input( 
    int pin,    // The pin to configure (0-15)
    int mode    // 0 = PULLDOWN, 1 = PULLUP, 2 = FLOATING 
    )
{
    unsigned int cnfMode;
    if (mode == 2) {
        cnfMode = 0b0100;  // Floating: CNF=01
    } else {
        cnfMode = 0b1000;  // Pull-up/Pull-down: CNF=10
    }

    int shift = 4 * (pin % 8);  // Position within register (0-7 maps to 0-28)
    int mask = 0xF << shift;
    cnfMode = cnfMode << shift;

    if (pin >= 0 && pin < 8) {
        // Pins 0-7: use CFGLR
        *GPIO_D_CFGLR = (*GPIO_D_CFGLR & ~mask) | cnfMode;
        
        // Set OUTDR for pull-up/pull-down selection
        if (mode == 0) {
            *GPIO_D_OUTDR &= ~(1 << pin);  // Pull-down
        } else if (mode == 1) {
            *GPIO_D_OUTDR |= (1 << pin);   // Pull-up
        }
    } else if (pin >= 8 && pin <= 15) {
        // Pins 8-15: use CFGHR
        *GPIO_D_CFGHR = (*GPIO_D_CFGHR & ~mask) | cnfMode;
        
        // Set OUTDR for pull-up/pull-down selection
        if (mode == 0) {
            *GPIO_D_OUTDR &= ~(1 << pin);  // Pull-down
        } else if (mode == 1) {
            *GPIO_D_OUTDR |= (1 << pin);   // Pull-up
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
// Assignment 3
// ===========================================================================
// Write a function that configures a pin of GPIO port D as
// output with either push-pull or open-drain mode.
// The pin should be configured as output at 2 MHz.
///////////////////////////////////////////////////////////////////////////////
void gpio_d_set_pin_output( 
    int pin,    // The pin to configure
    int mode    // 0 = PUSHPULL, 1 = OPENDRAIN
    )
{
    unsigned int cnfMode;
    if (mode == 0) {
        cnfMode = 0b0010;  // Floating: CNF=10
    } else {
        cnfMode = 0b0110;  // Push-pull: CNF=00
    }

    int shift = 4 * (pin % 8);  // Position within register (0-7 maps to 0-28)
    int mask = 0xF << shift;
    cnfMode = cnfMode << shift;

    if (pin >= 0 && pin < 8) {
        // Pins 0-7: use CFGLR
        *GPIO_D_CFGLR = (*GPIO_D_CFGLR & ~mask) | cnfMode;

    } else if (pin >= 8 && pin <= 15) {
        // Pins 8-15: use CFGHR
        *GPIO_D_CFGHR = (*GPIO_D_CFGHR & ~mask) | cnfMode;
    }
}

///////////////////////////////////////////////////////////////////////////////
// Assignment 4
// ===========================================================================
// Write a function that sets one pin of GPIO port D high.
// The function should use bit set/reset register (BSHR)
// 
// EDIT: At the time you downloaded this code, there is a bug in the simulator
//       that means the BSHR register does not work properly. 
//       Use the OUTDR instead, but make sure you do not overwrite
//       any other pin.
///////////////////////////////////////////////////////////////////////////////
void gpio_d_set_pin_high(int pin)
{
    *GPIO_D_OUTDR |= (1 << pin);
}

///////////////////////////////////////////////////////////////////////////////
// Assignment 5
// ===========================================================================
// Write a function that sets one pin of GPIO port D low.
// The function should use the bit set/reset registers (BSHR or BCR)
//
// EDIT: At the time you downloaded this code, there is a bug in the simulator
//       that means the BSHR register does not work properly. 
//       Use the OUTDR instead, but make sure you do not overwrite
//       any other pin.
///////////////////////////////////////////////////////////////////////////////
void gpio_d_set_pin_low(int pin)
{
    *GPIO_D_OUTDR &= ~(1 << pin);
}  

///////////////////////////////////////////////////////////////////////////////
// Assignment 6
// ===========================================================================
// Assume that the keyboard is connected to GPIO port D pins 0-7
// Write a function that returns the number of the button on the keyboard: 
//
// /-------------------\
// |  0 |  1 |  2 |  3 |
// |----|----|----|----|    
// |  4 |  5 |  6 |  7 |
// |----|----|----|----|
// |  8 |  9 | 10 | 11 |
// |----|----|----|----|
// | 12 | 13 | 14 | 15 |
// \-------------------/
// 
// Follow the instructions in comments
// You can use the functions you have written above
///////////////////////////////////////////////////////////////////////////////
int get_keyboard_button(void)
{
    // Configure the row-selection pins (pins 4-7) as output, open drain, at 2 MHz
    /*
    void gpio_d_set_pin_output( 
    int pin,    // The pin to configure
    int mode    // 0 = PUSHPULL, 1 = OPENDRAIN
    );
    */
   for (int i = 4; i < 8; i++) {
    gpio_d_set_pin_output(i, 1);
   }


    // Configure the row-read pins (pins 0-3) as input with pull-up resistors
    for (int i = 0; i < 4; i++) {
        gpio_d_set_pin_input(i, 1);
    }

    // Deactivate all rows by setting pins the row selection pins  4-7 high
    // (remember that they are active low, so 0 selects a row)
    for (int i = 4; i < 8; i++) {
        gpio_d_set_pin_high(i);
    }

    for(int row = 0; row < 4; row++) {
        // Activate the current row by setting the corresponding pin low
        gpio_d_set_pin_low(row + 4);

        // Read the row (buttons 0-3, 4-7, 8-11, or 12-15) as the lower 4 bits of INDR
        uint32_t row_data = *GPIO_D_INDR & 0xF;

        // Check if any button in this row is pressed (low)
        for (int col = 0; col < 4; col++) {
            if ((row_data & (1 << col)) == 0) {
                // Button is pressed (bit is 0)
                int button = row * 4 + col;
                return button;
            }
        }

        // Deactivate the current row by setting the corresponding pin high
        gpio_d_set_pin_high(row + 4);
    }
    return -1; // No button pressed  
}