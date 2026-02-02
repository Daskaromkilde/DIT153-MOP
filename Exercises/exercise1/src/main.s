.section .text
.globl main
main:
    # Put your program here!
    li t0, 10      # t0=10
    li t1, 20      # t1=20
    add t0, t1, t0 # t0 = t1 + t0
    li t1, 0x20001000
    sb t0, 0(t1)

    
    j main


