/*
    This code was written to support the book, "ARM Assembly for Embedded Applications",
    by Daniel W. Lewis. Permission is granted to freely share this software provided
    that this notice is not removed. This software is intended to be used with a run-time
    library adapted by the author from the STM Cube Library for the 32F429IDISCOVERY 
    board and available for download from http://www.engr.scu.edu/~dlewis/book3.
*/

        .syntax     unified
        .cpu        cortex-m4
        .text

// uint32_t Mul32X10(uint32_t multiplicand) ;
        .global     Mul32X10
        .thumb_func
        .align
Mul32X10:
        lsl         r1, r0, #3          // r1 = 8r0
        add         r0, r1, r0, LSL #1  // r0 = r1 + 2r0
        bx          lr

// uint32_t Mul64X10(uint32_t multiplicand) ;
        .global     Mul64X10
        .thumb_func
        .align
Mul64X10:           // R1.R0 = multiplicand
        lsl         r2, r1, 3           // upr bits 8x
        add         r1, r2, r1, lsl #1  // upr bits 8+2x
        lsl         r2, r0, 3           // low bits 8x
        adds        r2, r2, r0, lsl #1  // low bits 8+2x + carry
        adc         r1, r1, r0, lsr #29 // upr += ovrflw of 8xlow + carry
        add         r1, r1, r0, lsr #31 // upr += ovrflw of 2xlow
        mov         r0, r2
        bx          lr

// uint32_t Div32X10(uint32_t dividend) ;
        .global     Div32X10
        .thumb_func
        .align
Div32X10:
        ldr         r1, =3435973837       // =2^35 / 10
        umull       r2, r1, r1,r0         // r2=low, r1=upr
        lsrs.n      r0, r1, 3             // >>(32) + >>(3) = >>(35)
        bx          lr

        .end
