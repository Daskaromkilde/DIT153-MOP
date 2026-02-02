.globl main # Make main function visible to startup code
main:
    ###########################################################################
    # Assignment 1: Calculate t0 = a + b
    # =================================================
    # Check that you have the correct value in t0 using "register list"
    # in the debugger
    ###########################################################################
    lh t1, a
    lb t2, b
    add t0, t1, t2

end: j end  # End with a forever loop

.align 1
a: .hword 10
b: .byte 20
###########################################################################
# Assignment 2: Declare a variable c that is a signed 4-byte integer and
#               initialize it to 1000
# =================================================
# (hint: don't forget about alignment!)
###########################################################################
