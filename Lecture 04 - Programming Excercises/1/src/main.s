############################################################
# Lecture 04 - Exercise 01
#
# For this exercice, you need to connect a bargraph to 
# GPIO port D, bits 8-15.
# 
# The assignments buld on each other, so do them in order.
############################################################

.section .text
.globl main
main: 
    ########################################################
    # Assignment 1: Configure GPIOD pins 8-15 as:
    #                - output 2Mhz
    #                - push-pull
    # (refer to the lecture notes and/or QuickGuide)
    # (also make sure you have done the quiz for this lecture)
    ########################################################
    # <Your code goes here>

    # 0x40011400 base address GPIOD
    # CNF push-pull is 00
    # output mode 2Mhz is 10
    # 0000 0000 0000 0000 0000 0010 0000 0000. this is setting 10bit CNF to 00 and 10bit MODE to 10.
    # hex: 0x00000200 so this is configuration value
    la t0, 0x40011404       # load address with offse 0x4 for higher bits
    li t1, 0x22222222
    sw t1, 0(t0)
    call assignment6
loop: j loop

assignment4: 
    ########################################################
    # Assignment 4: Blink one LED by calling the set_led
    # and clear_led functions and then loop.
    #
    # Step through it with the debugger to see it work
    # Press F5 to let it run at full speed.
    ########################################################
    # <Your code goes here>
    call set_led
    call assignment5
    call clear_led
    call assignment5
    j mod_loop

assignment5: 
    ########################################################
    # Assignment 5: Create a "delay" function that simply
    #               loops a certain number of times to make
    #               transitions visible to the human eye.
    #
    ########################################################
    li t0, 30000           # Load 30 into counter
    j delay_loop
    ret


delay_loop:
    addi t0, t0, -1     # Decrement counter
    bne t0, x0, delay_loop  # Branch if not zero
    ret

assignment6: 
    ########################################################
    # Assignment 6: Challenge!
    #               In each iteration of the loop, move to 
    #               the next led in the bargraph, going back 
    #               to the first led after the last one.    
    ########################################################
    # <Your code goes here>
    li s3, 0
    li s4, 8
    j mod_loop


mod_loop:
    rem a0, s3, s4
    addi s3, s3, 1
    j assignment4

set_led:
    ########################################################
    # Assignment 2: 
    # Write a function that turns on a specific led
    # It should not affect the other leds
    # You will do this by setting the correct bit in the 
    # GPIOD ODATA register
    #
    # Input: 
    # a0 - The led (0-7) to turn on
    ########################################################
    # <Your code goes here>
    # GPIOD_OUTDR is GPIOD ODATA REGISTER
    # base adress + offset = 0x40011400 + 0xC
    # GPIOD_OUTDR address  = 0x4001140C
    la t0, 0x4001140C # address to GPIOD_OUTDR
    lhu t3, 0(t0)      # fetch existing value
    li t2, 1           # single bit to later shift
    addi t5, a0, 8     # map LED index (0-7) to pins 8-15
    sll t4, t2, t5     # mask = 1 << (a0+8)
    or t1, t3, t4      # set the bit without affecting others
    sh t1, 0(t0)
    ret


clear_led:
    ########################################################
    # Assignment 3:
    # Write a function that turns off a specific led
    # It should not affect the other leds
    # You will do this by clearing the correct bit in the
    # GPIOD ODATA register
    #
    # Input:
    # a0 - The led (0-7) to turn off
    ########################################################
    # <Your code goes here>
    la t0, 0x4001140C
    lhu t3, 0(t0)
    li t2, 1
    addi t5, a0, 8     # map LED index to pins 8-15
    sll t4, t2, t5     # mask = 1 << (a0+8)
    not t4, t4         # invert mask
    and t3, t3, t4     # clear the bit
    sh t3, 0(t0)
    ret