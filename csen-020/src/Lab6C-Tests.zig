extern fn CopyCell(dst: [*c]u32, src: [*c]u32) void;
extern fn FillCell(dst: [*c]u32, color: u32) void;

const CELL = 60;
const SIZE = 4;
const SIDE = CELL * SIZE;

fn zigCopyCell(argdst: [*]u32, argsrc: [*]const u32) void {
    var dst = argdst;
    var src = argsrc;

    var row: u32 = 0;
    while (row < CELL) : (row += 1) {
        var col: u32 = 0;
        while (col < CELL) : (col += 1) {
            dst[col] = src[col];
        }
        dst += SIDE;
        src += SIDE;
    }
}

fn zigFillCell(argdst: [*]u32, color: u32) void {
    var dst = argdst;

    var row: u32 = 0;
    var col: u32 = 0;

    while (row < CELL) : (row += 1) {
        col = 0;
        while (col < CELL) : (col += 1) {
            dst[col] = color;
        }
        dst += SIDE;
    }
}

const Screen = [SIDE * SIDE]u32;

const std = @import("std");

test "move tile" {
    const a = std.testing.allocator;
    const screen1 = try a.create(Screen);
    defer a.free(screen1);

    for (screen1, 0..) |*c, i| c.* = i;
    // var rand = std.rand.Sfc64.init(42);
    // rand.fill(std.mem.asBytes(screen1));

    const screen2 = try a.dupe(u32, screen1);
    defer a.free(screen2);

    CopyCell(screen1, screen1[60..]);
    zigCopyCell(screen2.ptr, screen2[60..].ptr);
    try std.testing.expectEqualSlices(u32, screen2, screen1);

    zigFillCell(screen2.ptr, 0);
    FillCell(screen1, 0);
    try std.testing.expectEqualSlices(u32, screen2, screen1);

    zigFillCell(screen2[3 * CELL ..].ptr, 0);
    FillCell(screen1[3 * CELL ..], 0);
    try std.testing.expectEqualSlices(u32, screen2, screen1);
}
