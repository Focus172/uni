        .syntax     unified
        .cpu        cortex-m4
        .text

// void PutNibble(void *nibbles, uint32_t index, uint32_t nibble) ;
        .global     PutNibble
        .thumb_func
        .align
PutNibble:
        lsr r3, r1, #1
        add r0, r0, r3              // ptr = nibbles + (index >> 1)
        and r1, r1, #1              // index & 1
        cmp r1, #0                  // index & 1 == 0
        ldrb r1, [r0]
        ittee eq
        andeq r1, r1, #240          // 240 = 0b11110000
        orreq r1, r1, r2            // byte |= value
        andne r1, r1, #15           // 15 = 0b00001111
        orrne r1, r1, r2, LSL #4    // byte |= value << 4
        strb r1, [r0]
        bx   lr


// uint32_t GetNibble(void *nibbles, uint32_t index) ;
        .global     GetNibble
        .thumb_func
        .align
GetNibble:
        lsr r2, r1, #1
        add r0, r0, r2
        ldrb r0, [r0]               // byte = nibbles[index >> 1]
        and r1, r1, #1              // index & 1
        cmp r1, #0                  // index & 1 != 0
        it ne
        lsrne r0, r0, #4            //   byte >>= 4
        and r0, r0, #15             // 15 = 0b00001111
        bx   lr

        .end

