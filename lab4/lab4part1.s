.global _start
_start:
    movia r7,TEST_NUM     
LOAD:
    bgt r2,r10,save
    mov r2,r0
    ldw r4,0(r7)       /* load digit*/
    beq r4,r0,END
    addi r7,r7,4       /* increment address: p++ */
    br ONES

ONES: 
    beq r4, r0, LOAD # loop until r9 contains no more 1s
    srli r11, r4, 0x01 # count the 1s by shifting the number
    and r4, r4, r11 # and ANDing it with the shifted
    # result
    addi r2, r2, 0x01 # increment the counter
    br ONES

save:
    mov r10,r2
    ret

END: br END # wait here
TEST_NUM:
.word 0x103fe00f
.word 0x103fefff
.word 0x11111111
.word 0x1111111f
.word 0
