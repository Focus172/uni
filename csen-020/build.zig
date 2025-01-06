const std = @import("std");
const builtin = @import("builtin");

// -------- Programs ---------------------------------------------------
const CC = "arm-none-eabi-gcc";
const AS = "arm-none-eabi-as";
const OBJCOPY = "arm-none-eabi-objcopy";
const GREP = "grep";
// const WHERE = "where";
// const RM = "rm";

// -------- Command line options ----------------------------------------
const AFLAGS: []const []const u8 = &.{
    "-mcpu=cortex-m4", "-mthumb", "-mfloat-abi=hard", "-mfpu=fpv4-sp-d16",
};
const CFLAGS: []const []const u8 = &.{
    "-mcpu=cortex-m4",             "-mthumb",         "-mfloat-abi=hard",     "-mfpu=fpv4-sp-d16",
    "-fsingle-precision-constant", "-std=c99",        "-O3",                  "-Wall",
    "-ffunction-sections",         "-fdata-sections", "-fno-strict-aliasing",
};
const LFLAGS: []const []const u8 = &.{
    "-mcpu=cortex-m4", "-mthumb",          "-mfloat-abi=hard", "-mfpu=fpv4-sp-d16",
    "-lm",             "-lc",              "-lnosys",          "-lc",
    "-u",              "_printf_float",    "-Wl,-gc-sections", "-T",
    LNK,               "-Wl,-Map," ++ MAP,
};

const LIB: []const u8 = "env/library.a";
const ELF: []const u8 = "env/output.elf";
const LNK: []const u8 = "env/linker.ld";
const INC: []const u8 = "env/inc";
const BIN: []const u8 = "output.bin";
const MAP: []const u8 = "zig-out/output.map";

const NULL: []const u8 = if (builtin.os.tag == .windows) "NUL" else "/dev/null";

const Project = struct {
    cfiles: []const []const u8,
    sfiles: []const []const u8,
    tests: ?[]const u8,
};

const PROJECTS: []const Project = &.{
    .{
        .cfiles = &.{"Lab1B-Main.c"},
        .sfiles = &.{"Lab1B-Implementation.s"},
        .tests = null,
    },
    .{
        .cfiles = &.{ "Lab2B-Main.c", "Lab2B-Implementation.c" },
        .sfiles = &.{},
        .tests = "Lab2B-Tests.zig",
    },
    .{
        .cfiles = &.{"Lab3B-Main.c"},
        .sfiles = &.{"Lab3B-Implementation.s"},
        .tests = "Lab3B-Tests.zig",
    },
    .{
        .cfiles = &.{"Lab4C-Main.c"},
        .sfiles = &.{"Lab4C-Implementation.s"},
        .tests = "Lab4C-Tests.zig",
    },
    .{
        .cfiles = &.{"Lab5C-Main.c"},
        .sfiles = &.{"Lab5C-Implementation.s"},
        .tests = "Lab5C-Tests.zig",
    },
    .{
        .cfiles = &.{"Lab6C-Main.c"},
        .sfiles = &.{"Lab6C-Implementation.s"},
        .tests = "Lab6C-Tests.zig",
    },
    .{
        .cfiles = &.{"Lab7C-Main.c"},
        .sfiles = &.{"Lab7C-Implementation.s"},
        .tests = "Lab7C-Tests.zig",
    },
    .{
        .cfiles = &.{"Lab8C-Main.c"},
        .sfiles = &.{"Lab8C-Resistors.s"},
        .tests = "Lab8C-Tests.zig",
    },
    .{
        .cfiles = &.{"Lab9C-Main.c"},
        .sfiles = &.{"Lab9C-SunAndMoon.s"},
        .tests = "Lab9C-Tests.zig",
    },
};

pub fn build(b: *std.Build) void {
    // target for tests, needs a libc for most things
    const target = b.standardTargetOptions(.{ .default_target = .{ .cpu_arch = .arm, .abi = .musleabi } });
    const optimize = b.standardOptimizeOption(.{});

    const src = b.path("src");

    var id: u8 = 1;
    inline for (PROJECTS) |project| {
        const cfiles = project.cfiles;
        const sfiles = project.sfiles;

        const link = b.addSystemCommand(&.{CC});

        // --------- Tests ---------------------------------------------------------
        const testsuite: ?*std.Build.Step.Compile = if (project.tests) |testfile| blk: {
            const tests = b.addTest(.{
                .root_source_file = src.path(b, testfile),
                .target = target,
                .optimize = optimize,
            });
            tests.linkLibC();

            const unittests = b.addRunArtifact(tests);

            const name = std.fmt.allocPrint(b.allocator, "test-{}", .{id}) catch unreachable;
            const desc = std.fmt.allocPrint(b.allocator, "Run the lab {} tests", .{id}) catch unreachable;

            const teststep = b.step(name, desc);
            teststep.dependOn(&unittests.step);

            break :blk tests;
        } else null;

        // ------------------------------------------------------------------------
        // Objects

        inline for (cfiles) |file| {
            const srcfile = src.path(b, file);
            const gcc = b.addSystemCommand(&.{CC});
            gcc.addArgs(CFLAGS);
            gcc.addArg("-I" ++ INC);
            gcc.addArg("-c");
            gcc.addArg("-o");
            const output = gcc.addOutputFileArg(file ++ ".o");
            gcc.addFileArg(srcfile);

            link.addFileArg(output);

            if (testsuite) |tests| {
                if (std.mem.count(u8, file, "Main") == 0) {
                    tests.addCSourceFile(.{ .file = srcfile });
                }
            }
        }

        inline for (sfiles) |file| {
            const srcfile = src.path(b, file);
            const gcc = b.addSystemCommand(&.{AS});
            gcc.addArgs(AFLAGS);
            gcc.addArg("-o");
            const output = gcc.addOutputFileArg(file ++ ".o");
            gcc.addFileArg(srcfile);

            link.addFileArg(output);

            if (testsuite) |tests| {
                tests.addAssemblyFile(srcfile);
            }
        }

        // ------------------------------------------------------------------------

        link.addArg("-o");
        const elf = link.addOutputFileArg(ELF);

        link.addFileArg(b.path(LIB));
        link.addArgs(LFLAGS);

        const copy = b.addSystemCommand(&.{ OBJCOPY, "-O", "binary" });
        copy.addFileArg(elf);
        const bin = copy.addOutputFileArg(BIN);
        // @$(GREP) -H -F ".main" $(MAP) -q || echo '**** There is no function main in output.bin! ****'

        const install = b.addInstallFile(bin, BIN);

        const nativename = std.fmt.allocPrint(b.allocator, "native-{}", .{id}) catch unreachable;
        const nativedesc = std.fmt.allocPrint(b.allocator, "Build lab {} for presentation", .{id}) catch unreachable;
        const native = b.step(nativename, nativedesc);

        native.dependOn(&install.step);

        id += 1;
    }

    // const check = b.step("check", "Check that it all worked");
    // const weakFunctions = b.addSystemCommand(&.{ "sh", "-c", GREP ++ " -H -F \"__attribute__((weak))\" src/*.c 2>" ++ NULL });
    // weakFunctions.expectExitCode(0);
    // check.dependOn(&weakFunctions.step);
    // check.dependOn(b.getInstallStep());

    // @$(GREP) -A 12 -G "[.]text[^\r\n]*obj/.*-s[.]o$$" $(MAP) 2>$(NULL) || echo '**** Assembly language replacements not found! ***'
}
