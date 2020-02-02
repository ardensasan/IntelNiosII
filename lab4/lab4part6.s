/* Program that counts consecutive 1's */

            .text                               
            .global _start  

TEST_NUM:   
            .word   0x00FF00AA, 0xFFC00555
#            .word   0x103fe00f          # array access and definition
#            .word   0x3fabedef
#            .word   0x4ffacc3d
#            .word   0x5bbef12c
#            .word   0x11dabc3f
#            .word   0x288f9d91
#            .word   0x6ffc2312
#            .word   0x7ccddeff
#            .word   0x4fffffff
#            .word   0x933212ac   
            .word   0

ALTVAL:
            .word   0x55555555

_start:      
            mov     r10, r0
            movi    r5, 0xFFFFFFFF      
            movia   r3, TEST_NUM                           

            mov     r10, r0             # one's result
            mov     r11, r0             # zero's result
            mov     r12, r0             # alt's result
            mov     r13, r0             # mloop counter

MLOOP:       
            ldw     r1, 0(r3)
            beq     r1, r0, DISPLAY         # loop until r1 = 0
            mov     r4, r1              
            call    ONES

            bgt     r2, r10, SETO
            mov     r4, r1
            call    ZEROS

            bgt     r2, r11, SETZ
            mov     r4, r1
            call    ALTS
CT:
            addi    r3,r3, 3            # increment to nxt value of array 
            br      MLOOP               


SETO:       
            mov     r10, r2
            ret

SETZ:
            mov     r11, r2
            ret

SETA:
            mov     r12, r2
            ret



ONES:       
            mov     r2, r0              # r2 will hold the result
            mov     r14, r0
OLOOP:       
            srli    r14, r4, 0x01       # count the 1s by shifting the number
            and     r4, r4, r14         # and ANDing it with the shifted
                                        # result
            addi    r2, r2, 0x01      # increment the counter
            bne     r4, r0, OLOOP
            ret

ZEROS:
            mov     r4, r1
            mov     r2, r0
            mov     r14, r0
ZLOOP:      
            slli    r14, r4, 0x01
            or      r4, r4, r14
            ori     r4, r4, 0x01
            addi    r2, r2, 0x01
            bne     r4, r5, ZLOOP
            ret

ALTS:
            mov     r4, r1
            mov     r2, r0

            ldw     r15, ALTVAL(r0)
            xor     r4, r4, r15
            call    ONES
            bgt     r2, r12, SETA

            mov     r4, r1
            slli    r15, r15, 0x01
            xor     r4, r4, r15

            call    ONES
            bgt     r2, r12, SETA
            br      CT

END:        
            br      END                       

DIVIDE:
            mov r2, r4 # r2 will be the remainder

            movi r5, 10 # divisor

            movi r3, 0 # r3 will be the quotient
CONT: 
            blt r2, r5, DIV_END

            sub r2, r2, r5 # subtract the divisor, then ...

            addi r3, r3, 1 # increment the quotient
            br CONT

DIV_END: ret 

SEG7_CODE: 
            movia r15, BIT_CODES # starting address of bit codes

            add r15, r15, r4 # index into the bit codes

            ldb r2, (r15) # read the bit code needed for our
            # digit
             ret

DISPLAY: 
            movia r8, 0xFF200020

            mov r4, r10 # display r10 on HEX1??0

            call DIVIDE # ones digit will be in r2; tens
            # digit in r3
            mov r4, r2 # pass ones digit to SEG7_CODE

            call SEG7_CODE

            mov r14, r2 # save bit code

            mov r4, r3 # retrieve tens digit, pass to
            # SEG7_CODE

            call SEG7_CODE

            slli r2, r2, 8

            or r14, r14, r2 # bit code for tens j bit code for

            mov r4, r11 # display r10 on HEX1??0

            call DIVIDE # ones digit will be in r2; tens
            # digit in r3
            mov r4, r2 # pass ones digit to SEG7_CODE

            call SEG7_CODE

            slli r2, r2, 16

            or r14, r14, r2 # bit code for tens j bit code for

            mov r4, r3 # retrieve tens digit, pass to
            # SEG7_CODE

            call SEG7_CODE

            slli r2, r2, 24

            or r14, r14, r2 # bit code for tens j bit code for

            stwio r14, (r8) # display the results from r10 and r11

            movia r8, 0xFF200030

            mov r4, r12 # display r10 on HEX1??0

            call DIVIDE # ones digit will be in r2; tens
            # digit in r3
            mov r4, r2 # pass ones digit to SEG7_CODE

            call SEG7_CODE

            mov r14, r2 # save bit code

            mov r4, r3 # retrieve tens digit, pass to
            # SEG7_CODE

            call SEG7_CODE

            slli r2, r2, 8

            or r14, r14, r2 # bit code for tens j bit code for

            stw r14, (r8) # display the results from r10 and r11

            br END


BIT_CODES: .byte 0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110
.byte 0b01101101, 0b01111101, 0b00000111, 0b01111111, 0b01100111
.skip 2 # pad with 2 bytes to maintain word alignment                


.end
