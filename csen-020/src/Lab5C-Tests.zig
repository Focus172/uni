extern fn MxPlusB(x: i32, mtop: i32, mbtm: i32, b: i32) i32;

fn pointSlope(x: i32, mtop: i32, mbtm: i32, b: i32) i32 {
    const rounding = @divTrunc((((((mtop * x * mbtm) >> 31) * mbtm) << 1) + mbtm), 2);
    return @divTrunc((mtop * x + rounding), mbtm) + b;
}

const std = @import("std");

// fn div(x: i32, y: i32) i32 {
//     return std.math.divTrunc(i32, x, y) catch @panic("div error");
// }

test "MxPlusB" {
    var x: i32 = -100;
    const mtop: i32 = 1;
    const mbtm: i32 = 1;
    const b: i32 = 1;

    while (x < 100) : (x += 1) {
        try std.testing.expectEqual(pointSlope(x, mtop, mbtm, b), MxPlusB(x, mtop, mbtm, b));
    }
}
