############################################################
# Lecture 02 - Exercise 2
# ==========================================================
#
# This is the only file you should edit for the excercise. 
# The file main.c is a test harness to help you test your code.
#
# Before you start: 
# Start simserver and choose Server->IO Setup
# For "Serial Communication Interface 1", choose "06 Console"
# Then run the program with F5 (if it breaks on main, 
# continue with F5 again)
# You should see output on the simserver console telling you 
# which assignments are passed. 
#
############################################################
    .text
    .global question1
    .global question2
    .global question3
    .global question4
    .global question5

############################################################
# Assignment 1
#
# Input:
#   a0 = integer a
#
# Task:
#   Return:
#       a * 2
#
############################################################
question1:
    # TODO
    # ABI == ISA
    # a0 == x10
    # t0 == x5
    slli a0, a0, 1
    ret


############################################################
# Assignment 2
#
# Input:
#   a0 = integer a
#   a1 = integer b
#
# Task:
#   Return (put answer in a0):  
#       a * b
#
############################################################
question2:
    # TODO
    mul a0, a0, a1
    ret


############################################################
# Assignment 3
#
# Input:
#   a0 = integer a
#
# Task:
#   Return (put answer in a0):  
#       a*a + 10
#
############################################################
question3:
    # TODO
    mul a0, a0, a0
    addi a0, a0, 10
    ret


############################################################
# Assignment 4
#
# Input:
#   a0 = short x   (passed as a signed 32-bit integer)
#
# Task:
#   Return (put answer in a0):  
#       1   if x is negative
#       0   if x is positive or zero
#
# Notes:
#   * Do NOT use branches.
#   * Detect negativity by examining the sign bit.
#
############################################################
question4:
    # TODO
    slti a0, a0, 0
    ret


############################################################
# Assignment 5  (Challenge)
#
# Input:
#   a0 = integer a
#
# Task:
#   Return (put answer in a0):  
#       a * 7
#
# Rules:
#   * Do NOT use 'mul'
#   * Only shifts and adds/subs allowed
#
############################################################
question5:
    # compute a*7 using shifts and adds: 7*a = (a<<3) - a
    slli t0, a0, 3
    sub  a0, t0, a0
    ret