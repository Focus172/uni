extern fn Return32Bits() u32;
extern fn Return64Bits() i64;
extern fn Add8Bits(x: u8, y: u8) u8;
extern fn FactSum32(x: u32, y: u32) u32;
extern fn XPlusGCD(x: u32, y: u32, z: u32) u32;

const std = @import("std");
const mem = std.mem;

pub export fn Factorial(arg_n: u32) u32 {
    var n = arg_n;
    var result: u32 = 1;
    // stack = (unsigned) &result ;
    while (n != 0) {
        result *= n;
        n = n - 1;
    }
    return result;
}

pub export fn gcd(x: u32, y: u32) u32 {
    return std.math.gcd(x, y);
}

test "return 32 bits test" {
    const init = stackPtr();

    var i: u32 = 12;
    i = Return32Bits();
    try std.testing.expectEqual(10, i);

    try std.testing.expectEqual(init, stackPtr());
    // try std.testing.expectEqualSlices(u8, &exp, &buf);
}

test "return 64 bits test" {
    const init = stackPtr();

    var i: i64 = 12;
    i = Return64Bits();
    try std.testing.expectEqual(-10, i);
    try std.testing.expect(12 != i);

    try std.testing.expectEqual(init, stackPtr());
}

test "add 8 bits" {
    const init = stackPtr();

    var i: u8 = undefined;
    var x: u8 = 0;
    while (x < 100) : (x += 1) {
        var y: u8 = 220;
        while (y < 250) : (y += 1) {
            i = Add8Bits(x, y);
            try std.testing.expectEqual(x +% y, i);
        }
    }

    try std.testing.expectEqual(init, stackPtr());
}

test "fact sum" {
    const init = stackPtr();

    var x: u32 = 0;
    while (x < 6) : (x += 1) {
        var y: u32 = 0;
        while (y < 8) : (y += 1) {
            const res = FactSum32(x, y);
            try std.testing.expectEqual(Factorial(x + y), res);
        }
    }

    try std.testing.expectEqual(init, stackPtr());
}

test "add gcd" {
    const init = stackPtr();

    var x: u32 = 1;
    while (x < 10) : (x += 1) {
        var y: u32 = 1;
        while (y < 15) : (y += 1) {
            var z: u32 = 1;
            while (z < 20) : (z += 1) {
                const res = XPlusGCD(x, y, z);
                const exp = x + gcd(y, z);
                try std.testing.expectEqual(exp, res);
            }
        }
    }

    try std.testing.expectEqual(init, stackPtr());
}

fn stackPtr() usize {
    var a: void = {};
    return @intFromPtr(&a);
}
