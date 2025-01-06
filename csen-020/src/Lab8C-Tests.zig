extern fn Mul32X10(u32) u32;
extern fn Mul64X10(u64) u64;
extern fn Div32X10(u32) u32;

const std = @import("std");

fn testFunc(comptime T: type, comptime expected: fn (T) T, comptime acutal: fn (T) callconv(.C) T) !void {
    var n: T = 0;

    const MAX = (std.math.maxInt(T) / 11); // prevent overflow
    const INTR = (std.math.maxInt(T) / 10302); // around 1k values tested
    while (n < MAX) : (n +%= INTR) {
        std.testing.expectEqual(expected(n), acutal(n)) catch |err| {
            std.debug.print("value: {}\n", .{n});
            return err;
        };
    }
}
const funcs = struct {
    fn mul32x10(x: u32) u32 {
        return x * 10;
    }

    fn mul64x10(x: u64) u64 {
        return x * 10;
    }

    fn div32x10(x: u32) u32 {
        return @divTrunc(x, 10);
    }
};

test "mul32" {
    try testFunc(u32, funcs.mul32x10, Mul32X10);
}

test "mul64" {
    try testFunc(u64, funcs.mul64x10, Mul64X10);
}

test "div32" {
    try testFunc(u32, funcs.div32x10, Div32X10);
}

// test "div64" {
//     var n32: u32 = 0;
//     var n64: u32 = 0;
//
//     const MAX = 1000;
//     const INTR = 67;
//     while (n32 < MAX) : ({
//         n32 += INTR;
//         n64 += INTR;
//     }) {
//         try std.testing.expectEqual(@divTrunc(n32, 10), Div32X10(n32));
//     }
// }
