        .syntax     unified
        .cpu        cortex-m4
        .text

// ----------------------------------------------------------
// unsigned HalfWordAccess(int16_t *src) ;
// ----------------------------------------------------------

        // instructions: 101
        // cycles:
        // - allign x00 : 101 cycles
        // - allign x01 : 201 cycles
        // - allign x10 : 101 cycles
        // - allign x11 : 201 cycles
        // cpi:
        // - allign x00 : 1 c/i
        // - allign x01 : 2 c/i
        // - allign x10 : 1 c/i
        // - allign x11 : 2 c/i
        .global     HalfWordAccess
        .thumb_func
        .align
HalfWordAccess:
        .rept 100
        LDRH R1,[R0]
        .endr
        BX LR

// ----------------------------------------------------------
// unsigned FullWordAccess(int32_t *src) ;
// ----------------------------------------------------------

        // instructions: 101
        // cycles:
        // - allign x00 : 101 cycles
        // - allign x01 : 301 cycles
        // - allign x10 : 201 cycles
        // - allign x11 : 301 cycles
        // cpi:
        // - allign x00 : 1 c/i
        // - allign x01 : 3 c/i
        // - allign x10 : 2 c/i
        // - allign x11 : 3 c/i
        .global     FullWordAccess
        .thumb_func
        .align
FullWordAccess:
        .rept 100
        ldr r1,[r0]
        .endr
        BX LR

// ----------------------------------------------------------
// unsigned NoAddressDependency(uint32_t *src) ;
// ----------------------------------------------------------

        // instructions: 201
        // cycles: 201
        // cpi: 1 c/i
        .global     NoAddressDependency
        .thumb_func
        .align
NoAddressDependency:
        .rept 100
        LDR R1,[R0]
        LDR R2,[R0]
        .endr
        BX LR

// ----------------------------------------------------------
// unsigned AddressDependency(uint32_t *src) ;
// ----------------------------------------------------------

        // instructions: 201
        // cycles: 400
        // cpi: 2 c/i
        .global     AddressDependency
        .thumb_func
        .align
AddressDependency:
        .rept 100
        LDR R1,[R0]
        LDR R0,[R1]
        .endr
        BX LR

// ----------------------------------------------------------
// unsigned NoDataDependency(float f1) ;
// ----------------------------------------------------------

        // instructions: 202
        // cycles: 201
        // cpi: 1 c/i
        .global     NoDataDependency
        .thumb_func
        .align
NoDataDependency:
        .rept 100
        VADD.F32 S1,S0,S0
        VADD.F32 S2,S0,S0
        .endr
        VMOV S1,S0
        BX LR

// ----------------------------------------------------------
// unsigned DataDependency(float f1) ;
// ----------------------------------------------------------

        // instructions: 202
        // cycles: 401
        // cpi: 2 c/i
        .global     DataDependency
        .thumb_func
        .align
DataDependency:
        .rept 100
        VADD.F32 S1,S0,S0
        VADD.F32 S0,S1,S1
        .endr
        VMOV S1,S0
        BX LR

// ----------------------------------------------------------
// void VDIVOverlap(float dividend, float divisor) ;
// ----------------------------------------------------------

        // instructions: 4
        // cycles: 16
        // cpi: 4 c/i
        .global     VDIVOverlap
        .thumb_func
        .align
VDIVOverlap:
        VDIV.F32 S2,S1,S0
        .rept 1
        NOP
        .endr
        VMOV S3,S2
        BX LR


        .end
