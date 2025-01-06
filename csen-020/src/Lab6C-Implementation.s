            .syntax     unified
            .cpu        cortex-m4
            .text

// void CopyCell(uint32_t *dst, uint32_t *src) ;        // R0 = dst, R1 = src
            .global     CopyCell
            .thumb_func
            .align
CopyCell:   push {r4}
            ldr r2, =60         // R2 = row
            ldr r3, =60         // R3 = col
NextRow1:   ldr r4, [r1]        // -\---------------\
            str r4, [r0]        //  |               |
            add r0, r0, #4      //  | offset dst    |
            add r1, r1, #4      //  | offset src    |
            subs r3, r3, #1     //  |               |
            bne NextRow1        // -/               |
            ldr r3, =60         // reset col        |
            add r0, r0, #720    // next dst row     | =4 * 4 * 60
            add r1, r1, #720    // next src row     | =4 * 4 * 60
            subs r2, r2, #1     //                  |
            bne  NextRow1       // -----------------/
            pop {r4}
            bx   lr

// void FillCell(uint32_t *dst, uint32_t color) ;       // R0 = dst, R1 = color
            .global     FillCell
            .thumb_func
            .align 
FillCell:   ldr r2, =60        // rows = 60
            ldr r3, =60        // cols = 60
NextRow2:   str r1, [r0]       // -\---------------\
            add r0, r0, #4     //  | offset dst    |
            subs r3, r3, #1    //  |               |
            bne NextRow2       // -/               |
            ldr r3, =60        // reset col        |
            add r0, r0, #720   // next dst row     | 4 * 4 * 60
            subs r2, r2, #1    //                  |
            bne  NextRow2      // -----------------/
            bx   lr

            .end
