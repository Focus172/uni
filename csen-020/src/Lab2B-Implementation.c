#include <stdint.h>

static const char hex[] = "0123456789ABCDEF";

void
convertRadix(uint8_t radix, uint8_t bits, char buffer[]) 
{
    int i, in;
    uint8_t buf[256];

    // amount of characters written
    i = 0;

    // do while so if 0 is passed at least 1 character is written
    do {
        // continuous divsion
        buf[i] = bits % radix;
        bits /= radix;

        i += 1;
    } while (bits != 0);


    // reverse the buffer
    for (in = 0; in < i; in++) {
        uint8_t v = buf[i - in - 1];
        // convert from numbers the characters
        buffer[in] = hex[v];
    }

    // write the null byte
    buffer[i] = '\0';
}

void
Bits2OctalString(uint8_t bits, char string[])
{
    // radix 8
    convertRadix(8, bits, string);
}

void
Bits2UnsignedString(uint8_t bits, char string[]) {
    // radix 10
    convertRadix(10, bits, string);
}

void
Bits2HexString(uint8_t bits, char string[])
{
    // radix 16
    convertRadix(16, bits, string);
}


void
Bits2TwosCompString(uint8_t bits, char string[])
{
    uint8_t mag;
    uint8_t is_signed; // boolean
    char sign;

    // get the first bit to see if this is a signed number or unsigned
    is_signed = ( bits & (1 << 7) ) != 0;
    // get the leading character of either positive or negative
    sign = is_signed ? '-' : '+';
    string[0] = sign;


    // check if it is signed
    if (is_signed) {
        // if it is then, in short few digets mean a high magnitude and many
        // digets is low value.
        //
        // so what this does in order, get the last 7 bits of the value,
        // subract it from 2^7 or 2^(8-1) so that the low values become high
        // and low become high.
        mag = 128 - ( bits & ~(1 << 7) );
    } else {
        // if it is unsigned then it is read normaly
        mag = bits;
    }

    // convert the parsed number to base 10 starting writing from index 1
    // instead of 0
    convertRadix(10, mag, string + 1);
}

void
Bits2SignMagString(uint8_t bits, char string[])
{
    char sign;
    uint8_t d;

    // same as prevoius but shorthand, get sign character
    sign = (bits & (1 << 7)) != 0 ? '-' : '+' ;
    string[0] = sign;

    // get the bits minus the leader 1
    d = bits & ~(1 << 7) ;

    // convert the rest of the number to base 10 starting at index 1
    convertRadix(10, d, string + 1);
}

// ----------------------------------------------------------------------------
// For external test purposes only

#include <stdio.h>

void 
FromatTwosCompCorrect(uint8_t bits, char string[])
{
    sprintf(string, "%+d", (int8_t) bits) ;
}
