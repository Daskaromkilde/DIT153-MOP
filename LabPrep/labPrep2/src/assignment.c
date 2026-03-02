///////////////////////////////////////////////////////////////////////////////
// Lab Preparation 2
// ============================================================================
// In Lab 2 you will need to know how the ASCII display works, so in this lab 
// you will write a program that interacts with it, on the simulator. 
//
// YOU ARE ALSO EXPECTED TO HAVE DONE THE EXERCISE FOR LECTURE 05, so you know 
// how the keyboard input works. 
//
// IMPORTANT: Before you do this lab, go through Lecture06, Excercise 02, where
// you learn how to create short delays using systick. This exercise will not
// test that your delay functions work correctly, and if they don't work
// it might still work on the simulator but not on hardware. 
//
// In this assignment there are check_assignment_x() functions  already in place
// where we try to check that you have solved each assignment correctly. Once you 
// have passed an assignment, you can comment these out.
// 
// Please see the quickguide for a summary of the ASCII Display.
// 
// In the simulator IO Setup, connect 
// GPIO E(0-15)/SPI Display -> 18 LC/TFT Display   AND
// Serial Communications Interface 1 -> 06 Console
///////////////////////////////////////////////////////////////////////////////

#include <stdint.h>

void check_assignment_1(); 
void check_assignment_2_1(uint8_t command_or_data);
void check_assignment_2_2();
void check_assignment_4_1();
void check_assignment_4_2();
void check_assignment_4_3();
void check_assignment_4_4();
void check_assignment_4_5();
void check_assignment_5();

///////////////////////////////////////////////////////////////////////////////
// Register macros. 
///////////////////////////////////////////////////////////////////////////////

/* TODO: Put all your register macros here */
#define STK_BASE 0xE000F000
#define STK_CTLR     ((volatile uint32_t *)(STK_BASE + 0x00))
#define STK_SR       ((volatile uint32_t *)(STK_BASE + 0x04))
#define STK_CNTL     ((volatile uint32_t *)(STK_BASE + 0x08))
#define STK_CNTH     ((volatile uint32_t *)(STK_BASE + 0x0C))
#define STK_CMPL     ((volatile uint32_t *)(STK_BASE + 0x10))
#define STK_CMPH     ((volatile uint32_t *)(STK_BASE + 0x14))
#define GPIO_E_BASE  0x40011800
#define GPIO_E_CFGLR ((volatile uint32_t *)(GPIO_E_BASE + 0x00))
#define GPIO_E_CFGHR ((volatile uint32_t *)(GPIO_E_BASE + 0x04))
#define GPIO_E_INDR  ((volatile uint32_t *)(GPIO_E_BASE + 0x08))
#define GPIO_E_OUTDR ((volatile uint16_t *)(GPIO_E_BASE + 0x0C))
#define GPIO_E_BSHR  ((volatile uint32_t *)(GPIO_E_BASE + 0x10))
#define GPIO_E_BCR   ((volatile uint16_t *)(GPIO_E_BASE + 0x14))



///////////////////////////////////////////////////////////////////////////////
// Assignment 0: If you have done Lecture06 Exercise02, you already have
//               the code for this. Implement the delay functions below.
//               They are not tested in this assignment, so make sure they
//               work using the Lecture06 Exercise02.
///////////////////////////////////////////////////////////////////////////////
void delay_ns(uint64_t ns)
{
   for (int i = 0; i < 10000; i++){
    int j;
   }
}

void delay_us(uint32_t us)
{
    // Delay for us microseconds using delay_ns
    delay_ns((uint64_t)us * 1000);
}


void delay_ms(uint32_t ms)
{
    // Delay for ms milliseconds using delay_us
    delay_us(ms * 1000);
}


///////////////////////////////////////////////////////////////////////////////
// Assignment 1: Configure GPIO Port E so that all pins [0:15] are set as 
//               output, 2MHz, push-pull.
///////////////////////////////////////////////////////////////////////////////
void init_gpio_port_e()
{
    // Configure pins 0-7 in CFGLR
    for (int pin = 0; pin < 8; pin++) {
        int shift = 4 * pin;
        int mask = 0xF << shift;
        unsigned int cnfMode = 0b0010 << shift;  // 0010 = output, 2MHz, push-pull
        *GPIO_E_CFGLR = (*GPIO_E_CFGLR & ~mask) | cnfMode;
    }
    
    // Configure pins 8-15 in CFGHR
    for (int pin = 8; pin < 16; pin++) {
        int shift = 4 * (pin - 8);  // Shift within CFGHR register
        int mask = 0xF << shift;
        unsigned int cnfMode = 0b0010 << shift;  // 0010 = output, 2MHz, push-pull
        *GPIO_E_CFGHR = (*GPIO_E_CFGHR & ~mask) | cnfMode;
    }
    
}



///////////////////////////////////////////////////////////////////////////////
// Assignment 2: Implement the write cycle. This will be used to write both 
//               commands and data to the display. 
//    
//               Look at the "Writing a command or data to the display" 
//               timing diagram in the quickguide, to see how this works.
// 
// Input: command_or_data - the byte to write to the display. This can be 
//                          either a command or data, depending on the state 
//                          of the control lines.
///////////////////////////////////////////////////////////////////////////////
void ascii_write_controller(uint8_t command_or_data)
{
    // The control lines (RS and RW) are set before calling this function.
    // According to the quickguide, you need to wait 40ns after setting the
    // control lines before initiating a write to the display. 
    //
    // 40ns is the time it takes to execute 8 instructions, so that time 
    // will already have passed by the time the processor has entered this
    // function. 

    ///////////////////////////////////////////////////////////////////////////
    // Assignment 2.1: Set E = 1 to start the write cycle
    //                 Then write the command or data to GPIOE_OUTDR[8..15].
    //                 Hint: Make sure your data write does not overwrite 
    //                 the control bits in GPIOE_OUTDR[0..7]!
    ///////////////////////////////////////////////////////////////////////////
    // Your code here
    *GPIO_E_OUTDR |= (1 << 2);
    *GPIO_E_OUTDR |= (command_or_data << 8);
    check_assignment_2_1(command_or_data);
    

    ///////////////////////////////////////////////////////////////////////////
    // Assignment 2.2: Wait for at least  max(tsu2, tw) = 230ns, then set 
    //                 E = 0 to end the write cycle.
    ///////////////////////////////////////////////////////////////////////////
    // Your code here
    delay_ns(500);
    *GPIO_E_OUTDR &= ~100;
    check_assignment_2_2();

    // Finally, wait for th = 10ns before returning from the function. This 
    //is the time it takes for the display to process the command or data after 
    // the write cycle has ended.
    //
    // 10ns is the time it takes to execute 2 instructions, so that time will
    // already have passed by the this function returns. 
}

///////////////////////////////////////////////////////////////////////////////
// Assignment 3: Implement code for writing a command to the display.
///////////////////////////////////////////////////////////////////////////////
void ascii_write_command(uint8_t command)
{
    // TODO: Set RS = 0 and RW = 0 to indicate a command write, then call
    //       ascii_write_controller to write the command to the display.
    *GPIO_E_OUTDR &= ~(0x3);  // or ~3
    ascii_write_controller(command);
}

///////////////////////////////////////////////////////////////////////////////
// Assignment 4: Implement a function that reads the status byte from the 
//               display, to see if it is busy or ready for the next command.
//
//               Look at the "Reading status or data from the display" timing 
//               diagram in the quickguide, to see how this works.
//
// Output: 1 if busy, 0 if ready for new command.
///////////////////////////////////////////////////////////////////////////////
uint8_t ascii_read_status()
{
    ///////////////////////////////////////////////////////////////////////////
    // Assignment 4.1: Temporarily configure GPIO Port E pins [8:15] as 
    //                 input, floating.
    ///////////////////////////////////////////////////////////////////////////
    // Your code here

    // Configure pins 8-15 in CFGHR
    for (int pin = 8; pin < 16; pin++) {
        int shift = 4 * (pin - 8);  // Shift within CFGHR register
        shift += 1;
        int mask = 0xF << shift;
        unsigned int cnfMode = 0b0010 << shift;  // 0100 = input, floating
        *GPIO_E_CFGHR = (*GPIO_E_CFGHR & ~mask) | cnfMode;
    }
    check_assignment_4_1(); 
    ///////////////////////////////////////////////////////////////////////////
    // Assignment 4.2: Set RS = 0 (command) and RW = 1 (read) to indicate 
    //                 a status read.
    ///////////////////////////////////////////////////////////////////////////
    // Your code here
    *GPIO_E_OUTDR = (*GPIO_E_OUTDR & ~(1 << 0)) | (1 << 1);
    check_assignment_4_2(); 
    ///////////////////////////////////////////////////////////////////////////
    // Assignment 4.3: Set E = 1 to start the read cycle,
    //                 wait for tD = 360ns
    //                 then read the status byte from GPIO Port E INDR register
    //                 pins [8:15]
    ///////////////////////////////////////////////////////////////////////////
    // Your code here
    *GPIO_E_OUTDR |= (1 << 2);
    delay_ns(500);
    uint8_t status_byte = (uint8_t)((*GPIO_E_INDR >> 8) & 0xFF);
    check_assignment_4_3(); 
    ///////////////////////////////////////////////////////////////////////////
    // Assignment 4.4: Set E = 0 to end the read cycle.
    ///////////////////////////////////////////////////////////////////////////
    // Your code here
    *GPIO_E_OUTDR &= ~100;
    check_assignment_4_4(); 

    ///////////////////////////////////////////////////////////////////////////
    // Assignment 4.5: Configure GPIO Port E pins [8:15] back to output,
    //                 2MHz, push-pull.
    ///////////////////////////////////////////////////////////////////////////
    // Your code here
    for (int pin = 8; pin < 16; pin++) {
        int shift = 4 * (pin - 8);
        int mask = 0xF << shift;
        unsigned int cnfMode = 0b0010 << shift;  // 0010 = output 2MHz push-pull
        *GPIO_E_CFGHR = (*GPIO_E_CFGHR & ~mask) | cnfMode;
    }
    check_assignment_4_5(); 

    ///////////////////////////////////////////////////////////////////////////
    // Assignment 4.6: Return the busy flag (bit 7 of the status byte)
    ///////////////////////////////////////////////////////////////////////////
    return (status_byte & 0x80) ? 1 : 0;  // Bit 7 = busy flag
}


///////////////////////////////////////////////////////////////////////////////
// Assignment 5: Implement code for writing a chareacter (data) to the display.
///////////////////////////////////////////////////////////////////////////////
void ascii_write_data(uint8_t data)
{
    // TODO: Set RS = 1 (data) and RW = 0 (write) to indicate a command write, 
    //       then call ascii_write_controller to write the character to the 
    //       display.
    *GPIO_E_OUTDR = (*GPIO_E_OUTDR & ~(1 << 1)) | (1 << 0);
    ascii_write_controller(data);

}


///////////////////////////////////////////////////////////////////////////////
// Assignment 6: Remove the training wheels!
// ============================================================================
// If you have passed all the previous assignments, and can see the password
// on the display when you run the program, then it is time to write your own
// main function that uses your functions to write to the display. 
// 
// Assignment 6.1: In the main.c file, rename "int main(void)" to 
// "int main_old(void)". 
// 
// Then uncomment the main function below and implement the missing code.
// You will need to consult the list of commands in the quickguide for this. 
///////////////////////////////////////////////////////////////////////////////

/*  
int main()
{
    // Initialize GPIO Port E (just call your function from Assignment 1

    // Read status until display is not busy.
    // Write a "Display Control" command that turns the display off

    // Read status until display is not busy.
    // Write a "Function Set" command that sets the function to 2 lines, 5x8 dots.

    // Read status until display is not busy.
    // Write a "Display Control" command that turns the dusplay on, cursor on, blink

    // Read status until display is not busy.
    // Write a "Entry Mode Set" command that says cursor should move right and 
    // display should not shift.

    // Read status until display is not busy.
    // Write a "Clear Display" command to clear the display.

    // Write the name of your group to the display

}
*/