.section .rodata
fmt_str:
.string "Hello from Assembly Code!\n"

.section .text
.globl main
.type main, @function
main:
    # Prologue: create small stack frame and save return address
    addi    sp, sp, -16        # make room on stack (keep 16-byte alignment)
    sw      ra, 12(sp)         # save return address at offset 12

    # Prepare arguments for printf
    la      a0, fmt_str        # a0 = pointer to format string
    call    printf             # call libc printf

    # Epilogue: restore return address and deallocate stack
    lw      ra, 12(sp)
    addi    sp, sp, 16
    ret


