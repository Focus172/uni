        .syntax         unified
        .cpu            cortex-m4
        .text

// int32_t Return32Bits(void);
        .global         Return32Bits
        .thumb_func
        .align
Return32Bits:
        ldr r0, =10             // just load 10
        bx  lr


// int64_t Return64Bits(void);
        .global         Return64Bits
        .thumb_func
        .align
Return64Bits:
        ldr r0, =-10            // set value to -10
        ldr r1, =-1             // set high register to all 1s
        bx lr


// uint8_t Add8Bits(uint8_t x, uint8_t y);
        .global         Add8Bits
        .thumb_func
        .align
Add8Bits:
        add r0, r0, r1          // add the numbers
        uxtb r0, r0             // set all but the first 8 bits to 0
        bx lr


// uint32_t FactSum32(uint32_t x, uint32_t y);
        .global         FactSum32
        .thumb_func
        .align
FactSum32:
        push {r4, lr}           // save the link register
        add r0, r0, r1          // add the values into r0
        bl Factorial            // call the functions
        pop {r4, lr}            // get the saved register. Can also be `pc`
                                // instead of `lr`
        bx lr


// uint32_t XPlusGCD(uint32_t x, uint32_t y, uint32_t z);
        .global         XPlusGCD
        .thumb_func
        .align
XPlusGCD:
        // Implementation
        push {r4, lr}
        mov r4, r0              // save the r0 register to r4
        mov r0, r2              // setup registers for functionall, this does
                                // swap the argument order but that doesnt
                                // matter for this function
        bl gcd
        add r0, r0, r4          // add the saved value and returned value
        pop {r4, pc}            // move pc to calling code, the cpu will auto
                                // end the stack frame

        .end

// vim: tabstop=8
