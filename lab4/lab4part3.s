.global _start
_start:
    movia r7,TEST_NUM 
    ldw r6,ONE(r0)    
LOAD:
    bgt r2,r10,saveONES
    bgt r3,r11,saveZEROS
    mov r2,r0
    mov r3,r0
    ldw r4,0(r7)       /* load digit*/
    ldw r5,0(r7)       /* load digit*/
    beq r4,r23,END
    addi r7,r7,4       /* increment address: p++ */
    br ONES

ONES: 
    beq r4, r0, ZEROS # loop until r9 contains no more 1s
    slli r9, r4, 0x01 # count the 1s by shifting the number
    and r4, r4, r9 # and ANDing it with the shifted
    # result
    addi r2, r2, 0x01 # increment the counter
    br ONES

ZEROS: 
    beq r5, r6, LOAD # loop until r9 contains no more 1s
    slli r9, r5, 0x01 # count the 1s by shifting the number
    or r5, r5, r9 # and ANDing it with the shifted
    ori r5,r5,1
    # result
    addi r3, r3, 0x01 # increment the counter
    br ZEROS

saveONES:
    mov r10,r2
    ret

saveZEROS:
    mov r11,r3
    ret


END: br END # wait here
TEST_NUM:
.word 0x1d7cde24
.word 0x103fefff
.word 0x103fe00f
.word 0

ONE: .word 0xffffffff
