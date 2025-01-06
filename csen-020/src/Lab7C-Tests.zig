extern fn GetNibble(nibbles: *anyopaque, index: u32) u32;
extern fn PutNibble(nibbles: *anyopaque, index: u32, value: u32) void;

const std = @import("std");

pub fn getnibble(nibbles: ?*anyopaque, which: u32) u32 {
    var byte: u8 = undefined;
    _ = &byte;
    byte = @as([*c]u8, @ptrCast(@alignCast(nibbles)))[which >> @intCast(1)];
    if ((which & @as(u32, @bitCast(@as(c_int, 1)))) == @as(u32, @bitCast(@as(c_int, 1)))) {
        byte >>= @intCast(@as(c_int, 4));
    }
    return @as(u32, @bitCast(@as(c_int, @bitCast(@as(c_uint, byte))) & @as(c_int, 15)));
}

pub fn putnibble(nibbles: ?*anyopaque, which: u32, value: u32) void {
    const ptr: [*]u8 = @alignCast(@ptrCast(nibbles));
    const pbyte: *u8 = &ptr[which >> 1];

    if ((which & @as(u32, @bitCast(@as(c_int, 1)))) == @as(u32, @bitCast(@as(c_int, 1)))) {
        pbyte.* &= @as(u8, 0b00001111);
        pbyte.* |= @as(u8, @truncate(value << 4));
    } else {
        pbyte.* &= @as(u8, @bitCast(@as(i8, @truncate(@as(c_int, 240)))));
        pbyte.* |= @as(u8, @bitCast(@as(u8, @truncate(value))));
    }
}

const ITEMS = 80;
const PACKED_AMOUNT = 2;
const UNPACKED_COUNT = ITEMS / PACKED_AMOUNT;

test {
    var nibbles1: [UNPACKED_COUNT]u8 = .{0} ** UNPACKED_COUNT;
    var nibbles2: [UNPACKED_COUNT]u8 = .{0} ** UNPACKED_COUNT;

    try std.testing.expectEqualSlices(u8, &nibbles1, &nibbles2);

    for (0..16) |v| {
        for (0..80) |r| {
            putnibble(&nibbles1, r, v);
            PutNibble(&nibbles2, r, v);
            try std.testing.expectEqualSlices(u8, &nibbles1, &nibbles2);
        }
    }
}
