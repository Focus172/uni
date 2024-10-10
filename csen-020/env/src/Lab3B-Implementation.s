        .syntax         unified
        .cpu            cortex-m4
        .text

// int32_t Return32Bits(void) ;
        .global         Return32Bits
        .thumb_func
        .align
Return32Bits:
        // Implementation
        ldr r0, =10
        bx  lr


// int64_t Return64Bits(void) ;
        .global         Return64Bits
        .thumb_func
        .align
Return64Bits:
        // Implementation
        ldr r0,  =10
        mvn r0, r0
        add r0, r0, #1
        ldr r1,  =0
        mvn r1, r1
        bx lr 


// uint8_t Add8Bits(uint8_t x, uint8_t y) ;
        .global         Add8Bits
        .thumb_func
        .align
Add8Bits:
        // Implementation
        add r0, r0, r1
        and r0, 0xFF // mask out only 8 bits
        bx lr


// uint32_t FactSum32(uint32_t x, uint32_t y) ;
        .global         FactSum32
        .thumb_func
        .align
FactSum32:
        // Implementation
        push {r4, lr}
        add r0, r0, r1
        bl Factorial
        pop {r4, lr}
        bx lr


// uint32_t XPlusGCD(uint32_t x, uint32_t y, uint32_t z) ;
        .global         XPlusGCD
        .thumb_func
        .align
XPlusGCD:
        // Implementation
        push {r4, lr}
        push {r0, r4} // must stack allign

        mov r0, r1
        mov r1, r2
        bl gcd
        mov r1, r0
        pop {r0, r4} // must stack allign

        add r0, r0, r1
        pop {r4, lr}
        bx lr

        .end

// vim: tabstop=8
