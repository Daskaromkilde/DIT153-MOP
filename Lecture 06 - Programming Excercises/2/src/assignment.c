#include <stdint.h>
#include <stdio.h>

///////////////////////////////////////////////////////////////////////////////
// Lecture 06 - Exercise 02
// ============================================================================
// In this exercise, you will learn to use the SysTick timer to implement a 
// delay function. 
//
// Like previous exercises, your code will be tested from an external main.c
// file. Since your code will run on a simulator, meassuring the ACTUAL time
// is not possible (real-time for the simulator depends on the host computer).
//
// Instead, the test code will use another timer (TIMER6) to measure how many
// clock-cycles your delay function takes, and calculate the real time it would
// have taken on hardware. This is not super exact, so don't worry if your 
// results are a bit off.
//
///////////////////////////////////////////////////////////////////////////////

// Ignore this, it is just a declaration of a function you can use to test your
// code later. 
void check_assignment_3();

///////////////////////////////////////////////////////////////////////////////
// Assignment 1: 
// Open the quickguide and create definitions for the SysTick registers.
// Remember that STK_CNT and STK_CMP are 64-bit registers so you will either
// need to define them as uint64_t pointers, or as two uint32_t pointers.
///////////////////////////////////////////////////////////////////////////////

#define STK_BASE 0xE000F000
#define STK_CTLR ((volatile uint64_t *)0xE000F000)
#define STK_SR   ((volatile uint64_t *)0xE000F004)
#define STK_CNT  ((volatile uint64_t *)0xE000F008)
#define STK_CMP  ((volatile uint64_t *)0xE000F010)

///////////////////////////////////////////////////////////////////////////////
// Assignment 2: 
// The system runs at 144Mhz. Implement a function that calulates the number 
// of ticks needed for the requested delay in nanoseconds.
///////////////////////////////////////////////////////////////////////////////
// c = t [sec] * 144000000 [clocks/sec]
uint64_t ns_to_ticks(uint64_t ns)
{
	// Convert nanoseconds to seconds, then apply formula: (ns / 1000000000) * 144000000
	return (ns * 144000000) / 1000000000; 
}


///////////////////////////////////////////////////////////////////////////////
// Assignment 3: 
// Implement a function that uses the SysTick timer to create a delay
// of the requested length in nanoseconds.
///////////////////////////////////////////////////////////////////////////////
void delay(uint64_t ns)
{
	// Initialize systick so that it counts DOWN from STK_CMP.
	// STK_CMP should be set to the number of ticks corresponding to the requested delay.

	// You can uncomment this call to get some hints about your configuration.
	// But try to solve it yourself first!
	

	uint64_t ticks = ns_to_ticks(ns);

	*STK_CMP = ticks;
 	*STK_CTLR |= 0b100101;
	//check_assignment_3();

	while(*STK_SR == 0);


	*STK_CTLR &= ~1;
	*STK_SR = 0x00000000;

	//check_assignment_3();

	// Now start the timer and then read the status register until the count flag is set. 

	// Finally, disable the timer again, and clear the status register.
}

///////////////////////////////////////////////////////////////////////////////
// Assignment 4:
// Write a delay_us(), and a delay_ms() function that uses your delay(ns) function.
///////////////////////////////////////////////////////////////////////////////
void delay_us(uint32_t us)
{
	delay((uint64_t)us * 1000);
}

void delay_ms(uint32_t ms)
{
	delay((uint64_t)ms * 1000000);
}