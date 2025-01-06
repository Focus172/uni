// ----------------------------------------------------------
// unsigned HalfWordAccess(int16_t *src) ;
extern fn HalfWordAccess(src: *i16) c_uint;
// ----------------------------------------------------------
// ----------------------------------------------------------
// unsigned FullWordAccess(int32_t *src) ;
// ----------------------------------------------------------
// ----------------------------------------------------------
// unsigned NoAddressDependency(uint32_t *src) ;
// ----------------------------------------------------------
// ----------------------------------------------------------
// unsigned AddressDependency(uint32_t *src) ;
// ----------------------------------------------------------
// ----------------------------------------------------------
// unsigned NoDataDependency(float f1) ;
// ----------------------------------------------------------
// ----------------------------------------------------------
// unsigned DataDependency(float f1) ;
// ----------------------------------------------------------
// ----------------------------------------------------------
// void VDIVOverlap(float dividend, float divisor) ;
// ----------------------------------------------------------

const std = @import("std");

test "perf" {
    // try std.testing.expect(try getcycles(10000) < 40000);
}

// TODO: this doesnt work beacuse when running under qemu beacuse it links
// against linux syscalls which are not provided
//
// fn getcycles(iter: usize) !c_longlong {
//     var pe = std.os.linux.perf_event_attr{
//         .type = .HARDWARE,
//         .config = @intFromEnum(std.os.linux.PERF.COUNT.HW.CPU_CYCLES),
//         .flags = .{
//             .disabled = true,
//             .exclude_kernel = true,
//             // Don't count hypervisor events.
//             .exclude_hv = true,
//         },
//     };
//
//     const fd = try std.posix.perf_event_open(&pe, 0, -1, -1, 0);
//
//     _ = std.os.linux.ioctl(fd, std.os.linux.PERF.EVENT_IOC.RESET, 0);
//     _ = std.os.linux.ioctl(fd, std.os.linux.PERF.EVENT_IOC.ENABLE, 0);
//
//     var bits: i16 = undefined;
//     for (0..iter) |_| {
//         _ = HalfWordAccess(&bits);
//     }
//
//     _ = std.os.linux.ioctl(fd, std.os.linux.PERF.EVENT_IOC.DISABLE, 0);
//
//     var cycles: c_longlong = undefined;
//     _ = try std.posix.read(fd, std.mem.asBytes(&cycles));
//
//     std.debug.print("{}\n", .{cycles});
//
//     std.posix.close(fd);
//     return cycles;
// }
