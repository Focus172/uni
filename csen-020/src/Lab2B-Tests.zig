extern fn Bits2OctalString(_: u8, _: [*c]u8) void;
extern fn Bits2UnsignedString(_: u8, _: [*c]u8) void;
extern fn Bits2HexString(_: u8, _: [*c]u8) void;
extern fn Bits2TwosCompString(_: u8, _: [*c]u8) void;
extern fn Bits2SignMagString(_: u8, _: [*c]u8) void;

extern fn FromatTwosCompCorrect(_: u8, _: [*c]u8) void;

const std = @import("std");
const mem = std.mem;

// fn makeTester(comptime f: fn (u8, [*c]u8) callconv(.C) void, comptime fmt: []const u8) (*const fn(u8) !void);

fn testFunc(comptime f: fn (u8, [*c]u8) callconv(.C) void, comptime fmt: []const u8, value: u8) !void {
    var buf: [8]u8 = .{0} ** 8;
    f(value, &buf);

    var exp: [8]u8 = .{0} ** 8;
    _ = try std.fmt.bufPrint(&exp, fmt, .{value});

    try std.testing.expectEqualSlices(u8, &exp, &buf);
}

fn testAll(comptime f: fn (u8, [*c]u8) callconv(.C) void, comptime fmt: []const u8) !void {
    var i: u8 = 0;
    while (true) : (i += 1) {
        try testFunc(f, fmt, i);

        if (i == std.math.maxInt(u8)) break;
    }
}

test "Octal" {
    try testAll(Bits2OctalString, "{o}");
}

test "Unsigned" {
    try testAll(Bits2UnsignedString, "{}");
}

test "Hex" {
    try testAll(Bits2HexString, "{X}");
}

test "TwosComp" {
    var bits: u8 = 0;
    while (true) : (bits += 1) {
        var buf: [8]u8 = .{0} ** 8;
        Bits2TwosCompString(bits, &buf);

        var exp: [8]u8 = .{0} ** 8;
        FromatTwosCompCorrect(bits, &exp);

        try std.testing.expectEqualSlices(u8, &exp, &buf);

        if (bits == std.math.maxInt(u8)) break;
    }
}

test "SignMag" {
    var bits: u8 = 0;
    while (true) : (bits += 1) {
        var buf: [8]u8 = .{0} ** 8;
        Bits2SignMagString(bits, &buf);

        const sign: u8 = if (bits & (1 << 7) != 0) '-' else '+';
        const magn: u8 = bits & ~@as(u8, (1 << 7));
        var exp: [8]u8 = .{0} ** 8;
        _ = try std.fmt.bufPrint(&exp, "{c}{}", .{ sign, magn });

        try std.testing.expectEqualSlices(u8, &exp, &buf);

        if (bits == std.math.maxInt(u8)) break;
    }
}

// void __attribute__((weak)) Bits2TwosCompString(uint8_t bits, char string[])
//     {
//     }
